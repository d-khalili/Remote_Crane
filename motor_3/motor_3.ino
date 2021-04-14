#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

int Pin5 = 5;
int Pin0 = 0;
int Pin4 = 4;
int Pin2 = 2;

const char* ssid = "NorfolkDwyer";
const char* password = "fertilefields";

WiFiClient client;
ESP8266WebServer server(80);

const char *webpage_on =
#include "crane_webpage_on.h"
;

const char *webpage_off =
#include "crane_webpage_off.h"
;

void setup(){
  Serial.begin(115200);
  Serial.println();
  Serial.print("New Connection started: ");
  Serial.println();
  
  WiFi.begin(ssid, password);
  delay(10000);

  if (WiFi.status() != WL_CONNECTED){
    Serial.print("Connection Failed!");
  }
  if (WiFi.status() == WL_CONNECTED){
    Serial.print("Successfully connected to IP: ");
  }

  Serial.println(WiFi.localIP());

  pinMode(Pin5, OUTPUT);
  pinMode(Pin0, OUTPUT);
  pinMode(Pin4, OUTPUT);
  pinMode(Pin2, OUTPUT);
  
  server.on("/", HTTP_GET, [](){
    Serial.println();
    Serial.print("Got Request OFF!");
    analogWrite(Pin5, 0);
    analogWrite(Pin0, 0);
    analogWrite(Pin4, 0);
    analogWrite(Pin2, 0);
    server.send(200, "text/html", webpage_off);
  });

  server.on("/forward", HTTP_GET, [](){
    Serial.println();
    Serial.print("Got Request ON!");
    analogWrite(Pin5, 300);
    analogWrite(Pin0, 0);
    analogWrite(Pin4, 0);
    analogWrite(Pin2, 0);
    server.send(200, "text/html", webpage_on);
  });

    server.on("/backward", HTTP_GET, [](){
    Serial.println();
    Serial.print("Got Request ON!");
    analogWrite(Pin5, 300);
    analogWrite(Pin0, 300);
    analogWrite(Pin4, 0);
    analogWrite(Pin2, 0);
    server.send(200, "text/html", webpage_on);
  });

  server.begin();
  };

void loop() {
  server.handleClient();
  };
