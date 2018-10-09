void setup() {
Serial.begin(9600);
  timerSetup();
  hardwareSetup();
}

void loop() {
  buttonLoop();

  if(buttonDown()){
    testComponents()
  }
}

void testComponents(){
  for(int i=0; i<getNrLeds(); i++){
    ledControlAan(i);
  }
}

void hardwareSetup(){
  ldrSetup();
  buttonSetup();
  ledControlSetup();
  }
