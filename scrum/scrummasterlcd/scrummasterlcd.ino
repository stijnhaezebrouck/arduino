#include <LiquidCrystal.h>
const int RS = 7;
const int ENABLE = 8;
const int D4 = 9;
const int D5 = 10;
const int D6 = 11;
const int D7 = 12;
LiquidCrystal lcd(RS, ENABLE, D4, D5, D6, D7);
char *TEAM[] = {"nul", "een", "twee", "drie", "vier", "Géraldine", "vijf", "zes" };
const int TEAM_SIZE = sizeof(TEAM) / 2;
const byte EACUTE = 1;
const byte CCEDILLE = 2;
const byte HARTJE=3;
const byte HUISJE=4;
const byte VLOKJE=5;
int permutatie[] = {1, 2, 3, 4, 5, 6, 7, 8};
const byte RANDOM_ITER=100;


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
byte HARTJE_CHAR[8] {
    B00000,
    B00000,
    B01010,
    B11111,
    B11111,
    B01110,
    B00100,
    B00000
};
byte HUISJE_CHAR[8] {
  B00000,
  B00100,
  B01110,
  B10101,
  B11111,
  B11111,
  B11011,
  B11011
};
byte VLOKJE_CHAR[8] {
  B00100,
  B01010,
  B00100,
  B00100,
    B00100,
  B00100,
  B00100,
  B00100
};

void setup() {
  
  randomSeed(analogRead(0));
  
  //LCD setup
  lcd.createChar(EACUTE, EACUTE_CHAR);
  lcd.createChar(CCEDILLE, CEDI_CHAR);
  lcd.createChar(HARTJE, HARTJE_CHAR);
  lcd.createChar(HUISJE, HUISJE_CHAR);
  lcd.createChar(VLOKJE, VLOKJE_CHAR);
  lcd.begin(16, 2);
  
  randomize(permutatie);
  
  
  
  lcd.print("Hanne ");
  lcd.write(HARTJE);
  lcd.print(" ");
  lcd.write(HUISJE);
  lcd.print(" ");
  lcd.write(VLOKJE);
  lcd.print(" *");
  lcd.setCursor(0,1);
  for (int i = 0; i < TEAM_SIZE; i++) {
      lcd.print(permutatie[i]);
      lcd.print(" ");
  }
  
}

void loop() {
  
  
  
  // put your main code here, to run repeatedly:

}

void randomize(int permutatie[]) {
  int a = 0;
  int b = 0;
  for (int i = 0; i < RANDOM_ITER; i++) {
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

int arraySize(char **charArray) {
    return sizeof(charArray) / 2;
}
