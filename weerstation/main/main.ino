void setup() {
Serial.begin(9600);
  timerSetup();
}

void loop() {
  timerLoop();
}


  hardwareSetup();
}

void loop() {
  Serial.println(readTempValueRAW());
  sendTempString();
}

void hardwareSetup(){
  ldrSetup();
  }
>>>>>>> 4b753b97c28774378e74986d360ef1bb0b50fbe5
