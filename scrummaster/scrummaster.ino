const int SOUND_PIN = 8;
const int SOUND_LENGTH = 400;
const int TONE1 = 1000;
const int TONE2 = 500;

const int GREEN_LED = 9;
const int YELLOW_LED = 12;
const int RED_LED = 7;
const int SWITCH = 2;
const unsigned long SEC = 1000;

const unsigned long GREEN_DURATION=65*SEC;
const unsigned long YELLOW_DURATION=10*SEC;
const int NB_ALARM_SOUNDS=2;

unsigned long yellowTime = 0;
unsigned long redTime = 0;
boolean alarmPlayed = false;

void setup() {
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(SWITCH, INPUT);
  runTest();
  resetTimeAndAlarm();
}

void runTest() {
    allLedsOn();
    delay(300);
    playReady();
}

void allLedsOn() {
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(RED_LED, HIGH);
}

void green() {
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, LOW);
}

void yellow() {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(RED_LED, LOW);
}

void red() {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, HIGH);
}

void loop() {
  if (buttonPressed()) {
    allLedsOn();
    resetTimeAndAlarm();
  } else {
    unsigned long now = millis();
    updateLeds(now);
    if (isAlarm(now)) {
      playAlarmOnce(NB_ALARM_SOUNDS);
    }
  }  
}

void updateLeds(unsigned long time) {
    if (time < yellowTime) {
        green();
    } else if ((time >= yellowTime) && (time < redTime)) {
        yellow();
    } else {
        red();
    }
}

boolean isAlarm(unsigned long time) {
    return time >= redTime;
}

void resetTimeAndAlarm() {
    unsigned long currentTime = millis();
    yellowTime = currentTime + GREEN_DURATION;
    redTime = currentTime + GREEN_DURATION + YELLOW_DURATION;
    alarmPlayed = false;
}

boolean buttonPressed() {
    return digitalRead(SWITCH) == HIGH;
}

void playAlarmOnce(int times) {
  if (alarmPlayed) {
    return;
  }
  alarmPlayed = true;
  for (int i = 0; i < times; i++) {
    tone(SOUND_PIN, TONE1, SOUND_LENGTH);
    delay(SOUND_LENGTH);
    tone(SOUND_PIN, TONE2, SOUND_LENGTH);
    delay(SOUND_LENGTH);
  }
}

void playReady() {
    tone(SOUND_PIN, 600, 100);
    delay(100);
    tone(SOUND_PIN, 1000, 100);
}
