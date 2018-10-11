void setup() {
  Serial.begin(9600);
  timerSetup();
  hardwareSetup();
  testSetup();
  
}

void loop() {
//  Serial.println(readTempValueRAW());
//  Serial.println(readTempValue());
  timerLoop();
  buttonLoop();
  testLoop();
  tempLedLoop();

  if(buttonDown()){
    setTestWeerstation(true);
  }

}

void hardwareSetup() {
  ldrSetup();
  ledControlSetup();
  buttonSetup();
}




