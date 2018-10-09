unsigned long prevMillisLDR;
unsigned long prevMillisTemp;
int intervalLDR = 7000;
int intervalTemp = 5000;

void timerSetup(){
  prevMillisLDR = millis();
  prevMillisTemp = millis();
}

void timerLoop(){
  unsigned long currentMillisLDR = millis();
  unsigned long currentMillisTemp = millis();

  if (currentMillisLDR - prevMillisLDR >= intervalLDR) {
    prevMillisLDR = currentMillisLDR;
    
    Serial.println(getLDRValue());
  }
  
  if (currentMillisTemp - prevMillisTemp >= intervalTemp) {
    prevMillisTemp = currentMillisTemp;
    
    Serial.println(getLDRValue());
  }
}



