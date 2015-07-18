int sensorValue;
int sensorLow = 1023;
int sensorHigh = 0;

const int LED_PIN = 13;
const int SOUND_PIN = 8;

void setup() {
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);
    
    while (millis() < 5000) {
        sensorValue = analogRead(A0);
        if (sensorValue > sensorHigh) {
            sensorHigh = sensorValue;
        }
        if (sensorValue < sensorLow) {
          sensorLow = sensorValue;
        }
    }
    
    digitalWrite(LED_PIN, LOW);
}

void loop() {
    sensorValue = analogRead(A0);
    int pitch = map (sensorValue, sensorLow, sensorHigh, 50, 4000);
    tone(SOUND_PIN, pitch, 20);
    delay(10);
}
