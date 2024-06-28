#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "**********";     
const char* password = "**********";

String html;

ESP8266WebServer server(80);

const int ledPin = 5; // GPIO 2

void handleRoot() {
  html = "<!DOCTYPE html><html><head><title>Controle de LED</title><style> .btn {font-size: 128px; border: solid red 5px; margin: 10px;}</style></head><body>";
  html += "<a href=\"/led/on\"><button class='btn'>ON</button></a><br>";
  html += "<a href=\"/led/off\"><button class='btn'>OFF</button></a>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleLEDOn() {
    for(int i = 0; i <= 255; i+=5){
      analogWrite(ledPin, i);
      delay(10);
    }
    server.send(200, "text/html", html);

}


void handleLEDOff() {
  for(int i = 255; i >= 0; i-=5){
    analogWrite(ledPin, i);
    delay(10);
  }
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  WiFi.begin(ssid, password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/led/on", handleLEDOn);
  server.on("/led/off", handleLEDOff);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
