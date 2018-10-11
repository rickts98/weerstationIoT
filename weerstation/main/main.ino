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
  bufferTemp = cbInit(10, OVERWRITE_IF_FULL);
  bufferLux = cbInit(10, OVERWRITE_IF_FULL);
}

void loop()
{
  timerLoop();
  buttonLoop();
  testLoop();

  if (buttonDown())
  {
    setTestWeerstation(true);
  }

  //bAdd(getBufferLux(), getLDRValue());
  // Serial.println(cbRead(bufferLux));
  // for(int i=0; i<10; i++){
  //   Serial.print(i);
  //   Serial.print(":  ");
  //   Serial.println(bufferLux->data[i]);
  // }
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
