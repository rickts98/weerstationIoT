extern "C"
{
#include "circularbuffer.h"
}

cbuffer *bufferTemp;
cbuffer *bufferLux;

void setup()
{
  Serial.begin(9600);
  timerSetup();
  hardwareSetup();
  testSetup();
  
}

void loop() {
//  Serial.println(readTempValueRAW());
//  Serial.println(readTempValue());
  bufferTemp = cbInit(10, OVERWRITE_IF_FULL);
  bufferLux = cbInit(10, OVERWRITE_IF_FULL);
  Serial.println("Seriale poort werkt");
}

void loop()
{
  timerLoop();
  buttonLoop();
  testLoop();
  tempLedLoop();

  if (buttonDown())
  {
    setTestWeerstation(true);
  }
}

void hardwareSetup()
{
  ldrSetup();
  ledControlSetup();
  buttonSetup();
}

cbuffer *getBufferTemp()
{
  return bufferTemp;
}



cbuffer *getBufferLux()
{
  return bufferLux;
}
