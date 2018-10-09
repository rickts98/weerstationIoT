void setup() {
  Serial.begin(9600);
  timerSetup();
  hardwareSetup();
}

void loop() {
  timerLoop();
  buttonLoop();

  if (buttonDown()) {
    testComponents();
  }
}

void hardwareSetup() {
  ldrSetup();
  ledControlSetup();
  buttonSetup();
}

void testComponents() {
  for (int i = 0; i < getNrLeds(); i++) {
    ledControlAan(i);
    delay(500);
    ledControlUit(i);
  }
  Serial.print("Lichtsterkte: ");
  Serial.println(getLDRValue());
  Serial.print("Temperaturr: ");
  Serial.println(readTempValue());


}

