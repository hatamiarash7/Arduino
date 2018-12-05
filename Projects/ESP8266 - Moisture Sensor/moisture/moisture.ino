int sense_Pin = 0;
int value = 0;

int getMLevel(){
  value = analogRead(sense_Pin);
  value = value / 10;
  Serial.print("Moisture Level : ");
  Serial.println(value);
  return value;
}
