#include "WebInterface.h"
#include <RTClib.h>
#include <LittleFS.h>

WebInterface::WebInterface(Clock* clock)
: clock(clock), server(new ESP8266WebServer(80))
{
  this->server->on("/data", HTTP_GET, [this]() {
    DateTime now = this->clock->getTime();
    String body = "{";
    body += "\"time\":{";
    body +=   "\"year\":" + String(now.year()) + ",";
    body +=   "\"month\":" + String(now.month()) + ",";
    body +=   "\"day\":" + String(now.day()) + ",";
    body +=   "\"hours\":" + String(now.hour()) + ",";
    body +=   "\"minutes\":" + String(now.minute()) + ",";
    body +=   "\"seconds\":" + String(now.second());
    body += "},";
    body += "\"temperature\":" + String(this->clock->getTemperature());
    body += "}";
    this->server->send(200, "application/json", body);
  });

  if (LittleFS.begin()) {
    Serial.println("[WebInt] Filesystem mounted successfully");
  } else {
    Serial.println("[WebInt] Filesystem mount failed");
  }

  this->server->serveStatic("/", LittleFS, "/");
  this->server->begin();
}

void WebInterface::check() {
  this->server->handleClient();
}
