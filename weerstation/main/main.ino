extern "C"
{
#include "circularbuffer.h"
}

cbuffer *bufferTemp;
cbuffer *bufferLux;

void setup()
{
  Serial.begin(9600);
  Serial.println("test");
  webServerSetup();
   Serial.println("test1");
  timerSetup();
  hardwareSetup();
  testSetup();
  bufferTemp = cbInit(10, OVERWRITE_IF_FULL);
  bufferLux = cbInit(10, OVERWRITE_IF_FULL);
}

void loop() {
 
webServer();
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
  initTemp();
  initGetTemperature();
}

cbuffer *getBufferTemp()
{
  return bufferTemp;
}



cbuffer *getBufferLux()
{
  return bufferLux;
}
