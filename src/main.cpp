#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Clock.h>
#include <Display.h>
#include <NTP.h>
#include <OTA.h>
#include <ProxSensor.h>
#include <WebInterface.h>

Clock* rtClock;
Display* display;
NTP* ntp;
OTA* ota;
ProxSensor* proxSensor;
WebInterface* webInterface;
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

#define FIVE_SECONDS 5 * 1000
#define TEN_MINUTES 10 * 60 * 1000
#define ONE_DAY 24 * 60 * 60 * 1000

// cppcheck-suppress unusedFunction
void setup() {
  Serial.begin(115200);
  setupWifi();

  display = new Display(FIVE_SECONDS);
  rtClock = new Clock(display, new DS3231());
  ntp = new NTP(ONE_DAY, rtClock);
  ota = new OTA(TEN_MINUTES);
  proxSensor = new ProxSensor(20, display, new VCNL4010());

  webInterface = new WebInterface(rtClock);
}

// cppcheck-suppress unusedFunction
void loop() {
  unsigned long now = millis();

  checkWifi();
  display->check(now);
  ntp->check(now);
  ota->check(now);
  proxSensor->check(now);
  rtClock->check();
  webInterface->check();
}
