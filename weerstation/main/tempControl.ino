//functionaliteiten die te maken hebben met de temperatuur 
#include <OneWire.h> //libray OneWire ophalen

const int tempPIN = 3;
OneWire ds18b20(tempPIN);
byte ds18b20Addr[8];


//setup van de sensor 
void initTemp() {
  while ( !ds18b20.search(ds18b20Addr) || OneWire::crc8(ds18b20Addr, 7) != ds18b20Addr[7]) {
    Serial.println("Address not found, retrying in 1 second...");
    ds18b20.reset_search();
    delay(1000); // deze delay mag blijven staan sensor heeft tijd nodig om op te starten 
  }
}

//ophalen van raw waarde
void initGetTemperature() {
  ds18b20.reset();
  ds18b20.select(ds18b20Addr);
  ds18b20.write(0x44);
}


//omzetten waarde naar temp
float actualGetTemperature() {


  byte ds18data[12];
  float celsius;
  ds18b20.reset();
  ds18b20.select(ds18b20Addr);
  ds18b20.write(0xBE);
  for (int i = 0; i < 9; i++) {
    ds18data[i] = ds18b20.read();
  }

  int16_t raw = (ds18data[1] << 8) | ds18data[0];
  byte cfg = (ds18data[4] & 0x60);
  if (cfg == 0x00) {
    raw = raw & ~7;
  }
  else if (cfg == 0x20) {
    raw = raw & ~3;
  }
  else if (cfg == 0x40) {
    raw = raw & ~1;
  }
  celsius = (float)raw / 16.0; return celsius;
}

//printen van de temp
int printTemperature() {
  initGetTemperature();
  return actualGetTemperature();
}
