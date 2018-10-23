extern "C"
{
#include "circularbuffer.h"
#include "reader.h"
#include "tokenizer.h"
}


cbuffer *bufferTemp;
cbuffer *bufferLux;


IPAddress ip(192, 168, 1, 100);

EthernetServer server(80);

EthernetClient httpClient;

const int toksize = 20; // max token size


// make httpClient methods available as ordinary functions

int clientAvailable() { return httpClient.available(); }

char clientRead() { return httpClient.read(); }

char clientPeek() { return httpClient.peek(); }

void setup()
{
  Serial.begin(9600);
    webServerSetup();

  timerSetup();
  hardwareSetup();
  testSetup();
  //initParser(available, read, peek);
  
  timerSetup();
  hardwareSetup();
  testSetup();

   Ethernet.begin(mac, ip);

  server.begin();

  Serial.print("server is at ");

  Serial.println(Ethernet.localIP());
  initParser(clientAvailable, clientRead, clientPeek);
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
