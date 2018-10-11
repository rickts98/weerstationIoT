
const int GEEL = 0;
const int GROEN = 1;
const int ROOD = 2;


void tempLedLoop(){

int minTemp = 12;
int maxTemp = 25;



  if (readTempValue() < minTemp) {
    ledControlOn(GEEL);
    ledControlOff(GROEN);
    ledControlOff(ROOD);
  }
  else if (readTempValue() > minTemp && readTempValue() < maxTemp) {
    ledControlOn(GROEN);
    ledControlOff(GEEL);
    ledControlOff(ROOD);
    
  }else if (readTempValue() > maxTemp) {
    ledControlOn(ROOD);
    ledControlOff(GROEN);
    ledControlOff(GEEL);
  }
}

