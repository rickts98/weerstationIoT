void setup() {
  Serial.begin(9600);
  timerSetup();
  hardwareSetup();
  testSetup();
}

void loop() {
  timerLoop();
  buttonLoop();
  testLoop();

  if(buttonDown()){
    setTestWeerstation(true);
  }

}

void hardwareSetup() {
  ldrSetup();
  ledControlSetup();
  buttonSetup();
}


