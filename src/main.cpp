#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <OTA.h>

OTA* ota;

void setupWifi() {
  WiFi.mode(WIFI_STA);
  Serial.println("[WiFi] Connecting to wireless network \"" WIFI_SSID "\"...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("[WiFi] Failed to connect. Restarting...");
    delay(1000);
    ESP.restart();
  }
  Serial.println("[WiFi] WiFi connected");
  Serial.print("[WiFi] IP address: ");
  Serial.println(WiFi.localIP());
}

#define TEN_MINUTES 10 * 60 * 1000

// cppcheck-suppress unusedFunction
void setup() {
  Serial.begin(115200);
  setupWifi();
  ota = new OTA(TEN_MINUTES);
}

// cppcheck-suppress unusedFunction
void loop() {
  ota->check(millis());
}
