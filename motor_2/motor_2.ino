#include <WiFiClient.h>
#include <ESP8266WebServer.h>

int motorPin5 = 5;

const char* ssid = "NorfolkDwyer";
const char* password = "fertilefields";

WiFiClient client;
ESP8266WebServer server(80);

const char *webpage_on =
#include "crane_webpage_on.h"

const char *webpage_off =
#include "crane_webpage_off.h"

void setup(){
  Serial.begin(115200);
  Serial.println();

  WiFi.begin(ssid, password);
  delay(10000);

  if (WiFi.status() != WL_CONNECTED){
    Serial.print("DKD not connected- ERROR");
  }
  if (WiFi.status() == WL_CONNECTED){
    Serial.print("DKD is connected!!");
  }

  Serial.println(WiFi.localIP());

  pinMode(motorPin5, OUTPUT);

  server.on("/on", HTTP_GET, [](){
    Serial.println();
    Serial.print("Got Request ON!");
    analogWrite(motorPin5, 300);
    delay(2000);
    digitalWrite(motorPin5, 0);
    server.send(200);

  });
  server.on("/off", HTTP_GET, [](){
    Serial.println();
    Serial.print("Got Request OFF!");
    analogWrite(motorPin5, 0);
    server.send(200);
  });

  server.begin();
  }

void loop() {
  server.handleClient();
  }
