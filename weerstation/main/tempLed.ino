
const int GEEL = 0;
const int GROEN = 1;
const int ROOD = 2;


void tempLedLoop(){

int minTemp = 12;
int maxTemp = 30;



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

