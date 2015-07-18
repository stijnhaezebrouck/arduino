//LoveOMeter

const int SENSOR = A0;
const float BASE_TEMP = 21.5;
const float LED1 = 2;
const float LED2 = 3;
const float LED3 = 4;

void setup() {
  Serial.begin(1200);
  initLED(LED1);
  initLED(LED2);
  initLED(LED3);
}

void initLED(int pinnr) {
    pinMode(pinnr, OUTPUT);
    digitalWrite(pinnr, LOW);
}

void off(int pinnr) {
  digitalWrite(pinnr, LOW);
}

void ledON(int pinnr) {
    digitalWrite(pinnr, HIGH);
}

void loop() {
  int sensorValue = analogRead(SENSOR);
  float voltage = sensorValue / 1024.0 * 5.0;
  Serial.print("sensor value: ");
  Serial.print(sensorValue);
  Serial.print(" voltage: ");
  Serial.println(voltage);
  delay(100);
  
}
