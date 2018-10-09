void setup() {
Serial.begin(9600);
  hardwareSetup();
}

void loop() {
  Serial.println(readTempValueRAW());
  sendTempString();
}

void hardwareSetup(){
  ldrSetup();
  }
