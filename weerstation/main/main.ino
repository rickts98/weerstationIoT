void setup() {
  ldrSetup();
  Serial.begin(9600);
}

void loop() {
  Serial.println(getLDRValue());

}
