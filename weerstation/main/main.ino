extern "C"
{
#include "circularbuffer.h"
#include "reader.h"
#include "tokenizer.h"
}


cbuffer *bufferTemp;
cbuffer *bufferLux;

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

IPAddress ip(192, 168, 1, 100);

EthernetServer server(80);

EthernetClient httpClient;

const int toksize = 20; // max token size


// make httpClient methods available as ordinary functions

int available() { return httpClient.available(); }

char read() { return httpClient.read(); }

char peek() { return httpClient.peek(); }

void setup()
{
  Serial.begin(9600);
<<<<<<< HEAD
  
  timerSetup();
  hardwareSetup();
  testSetup();

   Ethernet.begin(mac, ip);

  server.begin();

  Serial.print("server is at ");

  Serial.println(Ethernet.localIP());
  initParser(available, read, peek);
  
}

void loop() {
//  Serial.println(readTempValueRAW());
//  Serial.println(readTempValue());
=======
  Serial.println("test");
  webServerSetup();
   Serial.println("test1");
  timerSetup();
  hardwareSetup();
  testSetup();
>>>>>>> ba25a98be441541c26b9a16e67bfd9fa037d2a02
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
