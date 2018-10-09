void setup() {
Serial.begin(9600);
  timerSetup();
  hardwareSetup();
}

void loop() {
  timerLoop();
  sendTempString();
}

void hardwareSetup(){
  ldrSetup();
  }
