int sense_Pin = 0; // A0
int value = 0;

void setup() {
  Serial.begin(9600);
  delay(2000);
}

void loop() {
  Serial.print("MOISTURE LEVEL : ");
  value = analogRead(sense_Pin);
  value = value / 10;
  Serial.println(value);
  delay(1000);
}
