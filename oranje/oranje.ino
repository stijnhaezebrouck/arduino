const int R_LED=11;
const int G_LED=9;
const int B_LED=10;

const int R_SENSOR=A0;
const int G_SENSOR=A1;
const int B_SENSOR=A2;

int R_value = 0;
int G_value = 0;
int B_value = 0;

int R_sensor_value = 0;
int G_sensor_value = 0;
int B_sensor_value = 0;

void setup() {
  Serial.begin(9600);

  pinMode(R_LED,OUTPUT);
  pinMode(G_LED,OUTPUT);
  pinMode(B_LED,OUTPUT);
}

void loop() {
  R_sensor_value = analogRead(R_SENSOR)/6;
  delay(5);
  G_sensor_value = analogRead(G_SENSOR)/4;
  delay(5);
  B_sensor_value = analogRead(B_SENSOR)/6;
  delay(5);
  
  Serial.print("Raw Sensor values (RGB): ");
  Serial.print(R_sensor_value);
  Serial.print(" ");
  Serial.print(G_sensor_value);
  Serial.print(" ");
  Serial.println(B_sensor_value);
  
  analogWrite(R_LED, R_sensor_value);
  analogWrite(G_LED, G_sensor_value);
  analogWrite(B_LED, B_sensor_value);
}

