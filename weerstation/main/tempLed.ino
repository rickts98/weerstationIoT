
const int GEEL = 0;
const int GROEN = 1;
const int ROOD = 2;

int minTemp = 12;
int maxTemp = 30;

void tempLedLoop(){

  if (printTemperature() < minTemp) {
    ledControlOn(GEEL);
    ledControlOff(GROEN);
    ledControlOff(ROOD);
  }
  else if (printTemperature() > minTemp && printTemperature() < maxTemp) {
    ledControlOn(GROEN);
    ledControlOff(GEEL);
    ledControlOff(ROOD);
    
  }else if (printTemperature() > maxTemp) {
    ledControlOn(ROOD);
    ledControlOff(GROEN);
    ledControlOff(GEEL);
  }
}

int getMinTemp(){
  return minTemp;
}

int getMaxTemp(){
  return maxTemp;
}

void setMinTemp(int temp){
  minTemp = temp;
}

void setMaxTemp(int temp){
  maxTemp = temp;
}

