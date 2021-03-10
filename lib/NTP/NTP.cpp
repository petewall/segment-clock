#include "NTP.h"
#include <Arduino.h>
#include <WiFiUdp.h>
#include <NTPClient.h>


NTP::NTP(unsigned long interval, RTC_DS3231* rtc)
: PeriodicAction(interval), rtc(rtc) {}

void NTP::run() {
  Serial.println("[NTP] Getting time...");
  WiFiUDP client;
  NTPClient ntpClient(client, "pool.ntp.org");

  ntpClient.update();
  rtc->adjust(DateTime(ntpClient.getEpochTime()));
  Serial.print("[NTP] Time is ");

  char date[10] = "hh:mm:ss";
  rtc->now().toString(date);

  Serial.println(date);
}