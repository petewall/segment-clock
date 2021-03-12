#include "WebInterface.h"
#include <LittleFS.h>

WebInterface::WebInterface(Clock* clock)
: clock(clock), server(new ESP8266WebServer(80))
{
  this->server->on("/device/clock", HTTP_GET, [this]() {
    String body = "{";
    body += "\"time\": \"" + this->clock->getTime() + "\",";
    body += "\"temperature\": " + String(this->clock->getTemperature());
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

void WebInterface::process() {
  this->server->handleClient();
}
