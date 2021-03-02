#include "OTA.h"
#include <Arduino.h>
#include <WiFiClient.h>
#include <ESP8266httpUpdate.h>

OTA::OTA(unsigned long interval, String otaHost, String currentFirmware, String currentFirmwareVersion)
:
  otaURL(otaHost + "/api/update?firmware=" + currentFirmware + "&version=" + currentFirmwareVersion),
  PeriodicAction(interval) {}

void OTA::run() {
  WiFiClient client;

  ESPhttpUpdate.setLedPin(LED_BUILTIN, LOW);
  Serial.println("[OTA] Sending request to " + this->otaURL);
  t_httpUpdate_return result = ESPhttpUpdate.update(client, this->otaURL);
  switch(result) {
    case HTTP_UPDATE_FAILED:
      Serial.println("[OTA] Update failed");
      break;
    case HTTP_UPDATE_NO_UPDATES:
      Serial.println("[OTA] No updates");
      break;
    case HTTP_UPDATE_OK:
      Serial.println("[OTA] Updated!"); // may not be called since we reboot the ESP
      break;
  }
}