#include <LiquidCrystal.h>
const int RS = 7;
const int ENABLE = 8;
const int D4 = 9;
const int D5 = 10;
const int D6 = 11;
const int D7 = 12;
LiquidCrystal lcd(RS, ENABLE, D4, D5, D6, D7);
char *namen[] = {"nul", "een", "twee", "drie", "vier", "Géraldine" };
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

void setup() {
  lcd.createChar(EACUTE, EACUTE_CHAR);
  lcd.createChar(CCEDILLE, CEDI_CHAR);
  lcd.begin(16, 2);
  
  
  
  lcd.print("array size=");
  lcd.print(arraySize(namen));
}

void loop() {
  
  
  
  // put your main code here, to run repeatedly:

}

int arraySize(char **charArray) {
    return sizeof(charArray) / 2;
}
