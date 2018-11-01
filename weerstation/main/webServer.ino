#include <Ethernet.h>

extern "C" {
#include "parser.h"
#include "reader.h"
}

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

IPAddress ip(192, 168, 1, 100 + weerstationID);
EthernetServer server(80);

EthernetClient httpClient;

const int toksize = 20;

int clientAvailable() { return httpClient.available(); }
char clientRead() { return httpClient.read(); }
char clientPeek() { return httpClient.peek(); }

void webServerSetup() {

  Ethernet.begin(mac, ip);

  // start the server
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());

  initParser(clientAvailable, clientRead, clientPeek);
}

void webServer() {

  // listen for incoming clients
  httpClient = server.available();
  if (httpClient) {
    Serial.println("new client");

    while (httpClient.connected()) {
      char output[toksize];

      enum response tok;

      tok = parse(output, toksize);

      if (tok == TEMP_200) {
        printJSON("/temp");
        resetParser();
        break;
      } else if (tok == LUX_200) {
        printJSON("/lux");
        resetParser();
        break;
      } else if (tok == DATA_200) {
        printHTML();
        resetParser();
        break;
      } else if (tok == CONFIG_200) {
        printJSON("/conf");
        resetParser();
        break;
      } else if (tok == BAD_REQUEST_400) {
        httpClient.println("BAD_REQUEST_400");
        resetParser();
        break;
      } else if (tok == NOT_IMPLEMENTED_501) {
        httpClient.println("NOT_IMPLEMENTED_501");
        resetParser();
        break;
      } else if (tok == METHOD_NOT_ALLOWED_405) {
        httpClient.println("METHOD_NOT_ALLOWED_405");
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    httpClient.stop();
    Serial.println("client disconnected");
  }
}

void printJSON(String request) {
  httpClient.println("HTTP/1.1 200 OK");
  httpClient.println("Content-Type: application/json");
  httpClient.println("Connection: close");
  httpClient.println();
  httpClient.print("{");
  httpClient.print("\"Weerstation\": \"ID");
  httpClient.print(weerstationID);
  httpClient.print("\"");
  httpClient.print(", ");
  if (request == "/lux") {
    httpClient.print("\"Lichtintensiteit\": ");
    httpClient.print(getLDRValue());
  } else if (request == "/temp") {
    httpClient.print("\"Temperatuur\": ");
    httpClient.print(printTemperature());
  } else if (request == "/conf") {
    httpClient.print("\"maximale grenswaarde\": ");
    httpClient.print(getMaxTemp());
    httpClient.print(",");
    httpClient.print("\"minimale grenswaarde\": ");
    httpClient.print(getMinTemp());
    httpClient.print(",");
    httpClient.print("\"Temperatuur\": ");
    httpClient.print(printTemperature());
    httpClient.print(",");
    httpClient.print("\"Lichtintensiteit\": ");
    httpClient.print(getLDRValue());
  }
  httpClient.println("}");
}

void printHTML() {
  httpClient.print("HTTP/1.1");
  httpClient.println("Content-Type: text/html");
  httpClient.println("Connection: close"); // the connection will be closed
                                           // after completion of the response
  httpClient.println();
  httpClient.println("<!DOCTYPE HTML>");
  httpClient.println("<html>");
  httpClient.println("<head>");
  httpClient.println("<meta charset=\"UTF-8\">");
  httpClient.println("<title>");
  httpClient.println("Weerstation");
  httpClient.println("</title>");
  httpClient.println("<body>");
  httpClient.print("Temperatuur: ");
  httpClient.print(printTemperature());
  httpClient.print(" graden Celcius ");
  httpClient.print("(min: ");
  httpClient.print(getMinTemp());
  httpClient.print(", max: ");
  httpClient.print(getMaxTemp());
  httpClient.print(")");
  httpClient.print("</br>");
  httpClient.print("Lichtintensiteit: ");
  httpClient.print(getLDRValue());
  httpClient.println(" lux");
  httpClient.println("</body>");
  httpClient.println("</html>");
}
