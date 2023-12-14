#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
#include "index.h"
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);

#define ONE_WIRE_BUS 0
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float data, now;
uint64_t PM;
uint8_t looping;
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.hostname("Temp Meter");
  WiFi.begin("Free Internet");
  pinMode(2, OUTPUT);
  bool leds;
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    leds = !leds;
    digitalWrite(2, leds);
  }
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    request->send_P(200, "text/html", Temp);
  });
  server.on("/data", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    request->send(200, "text/plain", String(now).c_str());
  });
  server.begin();
  sensors.begin();
}

void loop() {
  looping++;
  sensors.requestTemperatures();
  data += sensors.getTempCByIndex(00);
  if (millis() - PM >= 1000)
  {
    PM = millis();
    now = data / looping;
    Serial.println(looping);
    Serial.println(data);
    Serial.println(now);
    looping = 0;
    data = 0;
  }
}
