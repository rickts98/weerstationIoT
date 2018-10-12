#include <Ethernet.h>

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 177);
EthernetServer server(80);

void webServerSetup(){
  
  Ethernet.begin(mac, ip);
  server.begin();
  


  // start the server
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}
  

void webServer(){

 // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    bool currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header


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
   


          
           
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
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

