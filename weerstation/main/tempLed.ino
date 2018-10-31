// variablen
const int GEEL = 0;
const int GROEN = 1;
const int ROOD = 2;

// Minimale en maximale temp
int minTemp = 12;
int maxTemp = 30;

void tempLedLoop() {

  // bij een temperatuur onder de minTemp gaat geel aan en de rest uit
  if (printTemperature() < minTemp) {
    ledControlOn(GEEL);
    ledControlOff(GROEN);
    ledControlOff(ROOD);
  }
  // bij een temperatuur tussen de minTemp en maxTemp gaat groen aan en de rest
  // uit
  else if (printTemperature() > minTemp && printTemperature() < maxTemp) {
    ledControlOn(GROEN);
    ledControlOff(GEEL);
    ledControlOff(ROOD);

  }
  // bij een temperatuur boven de maxTemp gaat rood aan en de rest uit
  else if (printTemperature() > maxTemp) {
    ledControlOn(ROOD);
    ledControlOff(GROEN);
    ledControlOff(GEEL);
  }
}

// returned de waarde van minTemp
int getMinTemp() { return minTemp; }

// returned de waarde van maxTemp
int getMaxTemp() { return maxTemp; }

// zet de waarde van minTemp
void setMinTemp(int temp) { minTemp = temp; }

// zet de waarde van maxTemp
void setMaxTemp(int temp) { maxTemp = temp; }
