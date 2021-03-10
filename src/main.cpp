#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Clock.h>
#include <NTP.h>
#include <OTA.h>
#include <Report.h>

Clock* rtClock;
NTP* ntp;
OTA* ota;
Report* report;
bool wifiState = false;

void setupWifi() {
  WiFi.mode(WIFI_STA);
  Serial.println("[WiFi] Connecting to wireless network \"" WIFI_SSID "\"...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

void checkWifi() {
  if (!wifiState && WiFi.status() == WL_CONNECTED) {
    Serial.println("[WiFi] WiFi connected");
    Serial.print("[WiFi] IP address: ");
    Serial.println(WiFi.localIP());
    wifiState = true;
  }
}

#define TEN_MINUTES 10 * 60 * 1000
#define ONE_DAY 24 * 60 * 60 * 1000

// cppcheck-suppress unusedFunction
void setup() {
  Serial.begin(115200);
  setupWifi();

  rtClock = new Clock();
  ntp = new NTP(ONE_DAY, rtClock);
  ota = new OTA(TEN_MINUTES);

  std::vector<Reportable*> reportables;
  reportables.push_back(rtClock);
  report = new Report(reportables);
}

// cppcheck-suppress unusedFunction
void loop() {
  unsigned long now = millis();

  checkWifi();
  ntp->check(now);
  rtClock->check();
  ota->check(now);
  report->update();
}
