#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define LED 2

const char *NetworkSSID = "Arash 1";
const char *NetworkPassword = "Mna32#%12Thp";

WiFiUDP Udp;
unsigned int localUdpPort = 4210;
char incomingPacket[255];
char replyPacket[] = "Hi there! Got the message :-)";

void setup() {
    pinMode(LED, OUTPUT);

    Serial.begin(115200);
    Serial.println();

    Serial.printf("Connecting to %s ", NetworkSSID);
    WiFi.begin(NetworkSSID, NetworkPassword);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println(" connected");

    Udp.begin(localUdpPort);
    Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);
    digitalWrite(LED, HIGH);
}


void loop() {
    int packetSize = Udp.parsePacket();
    if (packetSize) {
        digitalWrite(LED, LOW);
        Serial.printf("Received from %s, port %d ", Udp.remoteIP().toString().c_str(), Udp.remotePort());
        int len = Udp.read(incomingPacket, 255);
        if (len > 0) {
            incomingPacket[len] = 0;
        }
        Serial.printf(" - Contents: %s\n", incomingPacket);
        delay(50);
        digitalWrite(LED, HIGH);
    }
}