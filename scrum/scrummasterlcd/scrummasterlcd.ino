#include <LiquidCrystal.h>
String team[] = {"Nicolas", "Stéphane", "Rabha", "Baptiste", "Davy", "Géraldine", "Jean-François", "Stijn"};
const int TEAM_SIZE = 8;

const int BUTTON = 2;
const int RS = 7;
const int ENABLE = 8;
const int D4 = 9;
const int D5 = 10;
const int D6 = 11;
const int D7 = 12;
LiquidCrystal lcd(RS, ENABLE, D4, D5, D6, D7);
const byte EACUTE = 1;
const byte CCEDILLE = 2;
int permutatie[TEAM_SIZE];
const unsigned int RANDOM_ITER = 2500;
int currentMember = 0;

boolean previousButtonState = false;
boolean buttonEventGenerated = false;
boolean isReady = false;



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

void setup() {

  //randomSeed(analogRead(0));

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
  if (! isReady && buttonEvent()) {
    initPermutation();
    showReady();
  }
  if (! isReady) return;
  
  if (buttonEvent()) {
     if (currentMember < TEAM_SIZE) {
       showMember(team[permutatie[currentMember]]);
       currentMember++;
     } else {
       showReady();
       currentMember = 0;
     }
     
  }
}

void showMember(String member) {
    lcd.clear();
     
    int i = 0;
    while (i<member.length()) {
      String s = String(member.charAt(i));
      if (member.charAt(i) < 0) {
        s.concat(member.charAt(i+1));
        i++;
      } 
      i++;
      printStringChar(s);
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


void initPermutation() {
  lcd.clear();
  lcd.print("Shuffling...");
  randomSeed(millis());
  for (int i = 0; i < TEAM_SIZE; i++) {
    permutatie[i]=i;
  }
  randomize(permutatie);
  isReady = true;
}

void showReady() {
   lcd.clear();
   lcd.print("Ready to start");
   lcd.setCursor(0,1);
   lcd.print(TEAM_SIZE);
   lcd.print(" team members");
}

void randomize(int permutatie[]) {
  int a = 0;
  int b = 0;
  for (unsigned int i = 0; i < RANDOM_ITER; i++) {
    a = random(0, TEAM_SIZE);
    b = random(0, TEAM_SIZE);
    swap(permutatie, a, b);
  }
}

void swap(int array[], int i, int j) {
  int swap = array[i];
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
