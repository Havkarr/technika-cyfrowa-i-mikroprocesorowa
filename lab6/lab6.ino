void setup() {
  Serial.begin(19200);
}

void loop() {
  delay(200);
  Serial.println(analogRead(14));
  

}
