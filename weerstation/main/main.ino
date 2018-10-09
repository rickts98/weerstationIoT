void setup() {
<<<<<<< HEAD
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
sendTempString();
=======
  ldrSetup();
  Serial.begin(9600);
}

void loop() {
  Serial.println(getLDRValue());
>>>>>>> ddf972e833cf203b481a5701d7825da0744a2f51

Serial.println(readTempValueRAW());
}
