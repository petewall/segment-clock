#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <NTP.h>
#include <OTA.h>
#include <RTClib.h>
#include <pins.h>

NTP* ntp;
OTA* ota;
RTC_DS3231 rtc;

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

ICACHE_RAM_ATTR void clockTick() {
  Serial.println("tick");
}

void setupRTC() {
  if (!rtc.begin()) {
    Serial.println("[RTC] Failed to find RTC. Restarting...");
    delay(1000);
    ESP.restart();
  }
  rtc.disable32K();
  rtc.writeSqwPinMode(DS3231_SquareWave1Hz);
  pinMode(CLOCK_TICK_INTERRUPT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(CLOCK_TICK_INTERRUPT_PIN), clockTick, FALLING);
}

#define TEN_MINUTES 10 * 60 * 1000
#define ONE_DAY 24 * 60 * 60 * 1000

// cppcheck-suppress unusedFunction
void setup() {
  Serial.begin(115200);
  setupRTC();
  setupWifi();
  ntp = new NTP(ONE_DAY, &rtc);
  ota = new OTA(TEN_MINUTES);
}

// cppcheck-suppress unusedFunction
void loop() {
  ntp->check(millis());
  // ota->check(millis());
}
