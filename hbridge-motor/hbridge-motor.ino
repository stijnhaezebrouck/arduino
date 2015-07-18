const int CONTROL1 = 2;
const int CONTROL2 = 3;
const int ENABLE = 9;
const int DIRECTION_SW = 4;
const int ON_OFF_SW = 5;
const int POT_PIN= A0;

int onOff = 0;
int prev_onOff = 0;
int directionSwitchState = 0;
int prev_directionSwitchState = 0;

int motorEnabled = 0;
int motorSpeed = 0;
int motorDirection = 0;


void setup() {
  pinMode(DIRECTION_SW, INPUT);
  pinMode(ON_OFF_SW, INPUT);
  pinMode(CONTROL1, OUTPUT);
  pinMode(CONTROL2, OUTPUT);
  pinMode(ENABLE, OUTPUT);
  digitalWrite(ENABLE, LOW);

}

void loop() {
  onOff = digitalRead(ON_OFF_SW);
  delay(1);
  directionSwitchState = digitalRead(DIRECTION_SW);
  motorSpeed = analogRead(POT_PIN) / 4;
  if ((onOff != prev_onOff) && (onOff == HIGH)) {
    motorEnabled = ! motorEnabled;
  }
  if ((directionSwitchState != prev_directionSwitchState)
       && (directionSwitchState == HIGH)) {
         motorDirection = ! motorDirection;
  }
  
  if (motorDirection == 1) {
      digitalWrite(CONTROL1, HIGH);
      digitalWrite(CONTROL2, LOW);
  } else {
      digitalWrite(CONTROL1, LOW);
      digitalWrite(CONTROL2, HIGH);
  }
  if (motorEnabled = 1) {
      analogWrite(ENABLE, motorSpeed);
  } else {
      analogWrite(ENABLE, 0);
  }
  
  prev_directionSwitchState = directionSwitchState;
  prev_onOff = onOff;

}
