#include <LiquidCrystal.h>

//TEAM
String team[] = {"Nicolas", "Stéphane", "Rabha", "Baptiste", "Davy", "Géraldine", "Jean-François", "Stijn"};
const int TEAM_SIZE = 8;

const unsigned int RANDOM_ITER = 2500;

//non-LCD pins
const int BUTTON = 2;
const int SOUND_PIN = 13;
const int SOUND_LENGTH = 100;
const int TONE1 = 3000;
const int TONE2 = 2500;
const int NB_ALARM_SOUNDS=8;


//LCD pins
const int LCD_RS = 7;
const int LCD_ENABLE = 8;
const int LCD_D4 = 9;
const int LCD_D5 = 10;
const int LCD_D6 = 11;
const int LCD_D7 = 12;
LiquidCrystal lcd(LCD_RS, LCD_ENABLE, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

//custom characters
const byte EACUTE = 1;
const byte CCEDILLE = 2;

byte EACUTE_CHAR[8] = {
  B00010,
  B00100,
  B01110,
  B10001,
  B11111,
  B10000,
  B01110,
  B00000
};
byte CEDI_CHAR[8] = {
  B00000,
  B00000,
  B01110,
  B10000,
  B10000,
  B01110,
  B00100,
  B01100
};


// states
const int S_INITIAL = 0;
const int S_READY = 1;
const int S_GREEN = 2;
const int S_YELLOW = 3;
const int S_RED = 4;

//time management
const unsigned long SEC = 1000;
const unsigned long GREEN_DURATION=1*SEC;
const unsigned long YELLOW_DURATION=2*SEC;
unsigned long yellowTime = 0;
unsigned long redTime = 0;
unsigned long countdown_sec=0;


int nextTeamMemberIndex = 0;

boolean previousButtonState = false;
boolean buttonEventGenerated = false;
int currentState = S_INITIAL;

void setup() {
  //BUTTON setup
  pinMode(BUTTON, INPUT);

  //LCD setup
  lcd.createChar(EACUTE, EACUTE_CHAR);
  lcd.createChar(CCEDILLE, CEDI_CHAR);
  lcd.begin(16, 2);
  lcd.print("Press button to");
  lcd.setCursor(0, 1);
  lcd.print("shuffle");
}

void loop() {
  generateButtonEvent();
  if (buttonEvent()) {
    switch(currentState) {
      case S_INITIAL:
        shuffle();
        setReady();
        break;
      default:
        nextTeamMember();      
        break; 
    }
  }
  
  unsigned long now = millis();

  if ((currentState == S_GREEN) && (now >= yellowTime)) {
    setYellow();
  }
  if ((currentState == S_YELLOW) && (now >= redTime)) {
    setAlarm();
  }
  
  if ((currentState == S_GREEN) || (currentState == S_YELLOW) || (currentState==S_RED)) {
    showRemainingSeconds(now);
  }
}

void setGreen() {
  currentState = S_GREEN;
}

void setYellow() {
  currentState = S_YELLOW;
  lcd.setCursor(4,1);
  lcd.write("end now");
  playWarning();
}

void setAlarm() {
  currentState = S_RED;
  lcd.setCursor(4,1);
  lcd.write("NEXT !!!");
  playAlarm();
  
}

void showRemainingSeconds(unsigned long time) {
  
  unsigned long currentRemaining = getRemainingSeconds(time);
  if (currentRemaining != countdown_sec) {
    countdown_sec = currentRemaining;
    
    lcd.setCursor(14,0);
    if (countdown_sec < 10) {
      lcd.print(" ");
    }
    lcd.print(countdown_sec);
  }

}

unsigned long getRemainingSeconds(unsigned long time) {
  if (time >= redTime) {
    return 0;
  }
  return (redTime - time) / 1000;
  
}

void startCountDown() {
  unsigned long now = millis();
  yellowTime = now + GREEN_DURATION;
  redTime = yellowTime + YELLOW_DURATION;
  setGreen();  
}

void nextTeamMember() {
  if (nextTeamMemberIndex == TEAM_SIZE) {
    nextTeamMemberIndex = 0;
    setReady();
  } else {
    showMember(team[nextTeamMemberIndex++]);
    startCountDown();
  }
}

void showMember(String member) {
    lcd.clear();
     
    int i = 0;
    while (i<member.length()) {
      String stringChar = String(member.charAt(i));
      //in case of UTF-8 is the first byte negative. Assume max utf8 length 2 bytes for char
      if (member.charAt(i) < 0) {
        stringChar.concat(member.charAt(i+1));
        i++;
      } 
      i++;
      printStringChar(stringChar);
    }
    lcd.setCursor(0,1);
}

void printStringChar(String charToPrint) {
  if (charToPrint.equals(String("é"))) {
    lcd.write(EACUTE);
  } else if (charToPrint.equals(String("ç"))) {
    lcd.write(CCEDILLE);
  } else {
    lcd.print(charToPrint);
  }
}

void shuffle() {
  lcd.clear();
  lcd.print("Shuffling...");
  randomSeed(millis());
  randomize(team);
}

void setReady() {
   lcd.clear();
   lcd.print("Ready to start");
   lcd.setCursor(0,1);
   lcd.print(TEAM_SIZE);
   lcd.print(" team members");
   currentState = S_READY;
   playReady();
}

void randomize(String array[]) {
  int a = 0;
  int b = 0;
  for (unsigned int i = 0; i < RANDOM_ITER; i++) {
    a = random(0, TEAM_SIZE);
    b = random(0, TEAM_SIZE);
    swap(array, a, b);
  }
}

void swap(String array[], int i, int j) {
  String swap = array[i];
  array[i] = array[j];
  array[j] = swap;
}

void generateButtonEvent() {
  boolean buttonPress = (digitalRead(BUTTON) == HIGH);
  if ((! buttonPress) && previousButtonState) {
    buttonEventGenerated = true;
  }
  previousButtonState = buttonPress;
}

boolean buttonEvent() {
  if (buttonEventGenerated) {
    buttonEventGenerated = false;
    return true;
  } else {
    return false;
  }
}

void playReady() {
    tone(SOUND_PIN, 600, 100);
    delay(100);
    tone(SOUND_PIN, 1000, 100);
}

void playWarning() {
   tone(SOUND_PIN, 5000, 25);
   delay(50);
   tone(SOUND_PIN, 5000, 25);
   delay(50);
}

void playAlarm() {
  for (int i = 0; i < NB_ALARM_SOUNDS; i++) {
    tone(SOUND_PIN, TONE1, SOUND_LENGTH);
    delay(SOUND_LENGTH);
    tone(SOUND_PIN, TONE2, SOUND_LENGTH);
    delay(SOUND_LENGTH);
  }
}

