//Naam: Rens Aerts
//Datum: 09-10-2018
//zorgen dat op de juiste tijdstippen de waardes worden geprint

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

    if(cbAvailable(getBufferLux())){
      cbAdd(getBufferLux(), getLDRValue());
    }
  }
  
  if (currentMillisTemp - prevMillisTemp >= intervalTemp) {
    prevMillisTemp = currentMillisTemp;

//hier word de data uiteindelijk verzonden
    if(cbAvailable(getBufferTemp())){
      cbAdd(getBufferTemp(), readTempValue());
    }
  }
}



