extern "C" {
#include "circularbuffer.h"
}

cbuffer *bufferTemp;
cbuffer *bufferLux;

int weerstationID = 2;

void setup() {

  Serial.begin(9600);
  timerSetup();
  hardwareSetup();
  testSetup();
  webServerSetup();
  // maken van de buffer voor temp en lux deze is 10 groot en overschrijft als
  // het vol is
  bufferTemp = cbInit(10, OVERWRITE_IF_FULL);
  bufferLux = cbInit(10, OVERWRITE_IF_FULL);
}

void loop() {

  webServer();
  timerLoop();
  buttonLoop();
  testWeerstationLoop();

  // controle of er op testknop gedrukt is
  if (buttonDown()) {

    // zorg dat de test gebeurt
    setTestWeerstation(true);
    for (int i = 0; i < getNrLeds(); i++) {
      ledControlOff(i);
      setLedStatus(i, false);
    }
  }

  if (getTestWeerstation() == 0) {
    tempLedLoop();
  }
}

// Het voorbereiden van alle hardware onderdelen
void hardwareSetup() {
  ldrSetup();
  ledControlSetup();
  buttonSetup();
  // initGetTemperature();
  // initTemp();
}

// getter van de temp buffer
cbuffer *getBufferTemp() { return bufferTemp; }

// getter van de lux buffer
cbuffer *getBufferLux() { return bufferLux; }
