#include <Ethernet.h>

extern "C"
{
#include "parser.h"
#include "reader.h"
}

byte mac[] = {
    0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

IPAddress ip(192, 168, 1, 100);
EthernetServer server(80);

EthernetClient httpClient;
const int toksize = 20;

int clientAvailable() { return httpClient.available(); }
char clientRead() { return httpClient.read(); }
char clientPeek() { return httpClient.peek(); }

void webServerSetup()
{

  Ethernet.begin(mac, ip);
  server.begin();

  // start the server
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());

  initParser(clientAvailable, clientRead, clientPeek);
}

void webServer()
{

  // listen for incoming clients
  EthernetClient client = server.available();
  if (client)
  {
    Serial.println("new client");

    while (client.connected())
    {
      if (client.available())
      {
        char output[toksize];
        enum response tok;

        tok = parse(output, toksize);

        if(tok == TEMP_200){
          client.print("GET /temp HTTP/1.1");
          client.println("Content-Type: application/json");
          client.println();
          client.print("{");
          client.print("\"timestamp\": 1475783909566791977,");
          client.print("\"data\": {");
          client.print("\"Temperatuur\": ");
          client.print(printTemperature());
          client.print("}");
          client.print("}");
          client.print("/n");

          resetParser();
        }else if(tok == LUX_200) {
          client.print("GET /lux HTTP/1.1");
          client.println("Content-Type: application/json");
          client.println();
          client.print("{");
          client.print("\"timestamp\": 1475783909566791977,");
          client.print("\"data\": {");
          client.print("\"Lux\": ");
          client.print(getLDRValue());
          client.print("}");
          client.print("}");
          client.print("/n");
          
          resetParser();
        }else{
          client.println("bad request");
        }
      
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
  /*
  client.print("HTTP/1.1");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.print("temperatuur ");
          client.print(printTemperature());
          
          client.print("</br>");
          client.print("Lichtintensiteit: ");
          client.print(getLDRValue());
          client.println("</html>");
 */
}
