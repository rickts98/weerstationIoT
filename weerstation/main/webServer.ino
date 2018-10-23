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
  httpClient = server.available();
  if (httpClient)
  {
    Serial.println("new client");

    while (httpClient.connected())
    {
        char output[toksize];

        enum response tok;

        tok = parse(output, toksize);

        Serial.println(output);

        if(tok == TEMP_200){
          httpClient.println("GET /temp HTTP/1.1");
          httpClient.println("Content-Type: application/json");
          httpClient.println();
          httpClient.print("{");
          httpClient.print("\"timestamp\": 1475783909566791977,");
          httpClient.print("\"data\": {");
          httpClient.print("\"Temperatuur\": ");
          httpClient.print(printTemperature());
          httpClient.print("}");
          httpClient.println("}");

          resetParser();
          break;
        }else if(tok == LUX_200) {
          httpClient.println("GET /lux HTTP/1.1");
          httpClient.println("Content-Type: application/json");
          httpClient.println();
          httpClient.print("{");
          httpClient.print("\"timestamp\": 1475783909566791977,");
          httpClient.print("\"data\": {");
          httpClient.print("\"Lichtintensiteit\": ");
          httpClient.print(getLDRValue());
          httpClient.print("}");
          httpClient.println("}");
          
          resetParser();
          break;
        }else if(tok == BAD_REQUEST_400){
          httpClient.println("BAD_REQUEST_400");
          resetParser();
          break;
        }else if(tok == NOT_IMPLEMENTED_501){
          httpClient.println("NOT_IMPLEMENTED_501");
          resetParser();
          break;
        }
      
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    httpClient.stop();
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

void printJSON(){}
