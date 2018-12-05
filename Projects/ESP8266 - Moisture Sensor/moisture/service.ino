#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "AteriadServer";
const char* password = "ateriad1234";

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", String(getMLevel()));
}

void setup(void){
  Serial.begin(9600);
  Serial.println("");
  WiFi.mode(WIFI_AP);          
  WiFi.softAP(ssid, password);  

  IPAddress IP = WiFi.softAPIP(); 
  Serial.print("Server IP : ");
  Serial.println(IP);
 
  server.on("/", handleRoot);     

  server.begin();                 
  Serial.println("Server Started");
}

void loop(void){
  server.handleClient();          
}
