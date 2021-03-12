#include "Clock.h"
#include <RTClib.h>

#define CLOCK_TICK_INTERRUPT_PIN D3

RTC_DS3231 rtc;
volatile bool tick;

ICACHE_RAM_ATTR void clockTick() {
  tick = true;
}

Clock::Clock() {
  if (!rtc.begin()) {
    Serial.println("[Clock] Failed to find RTC. Restarting...");
    delay(1000);
    ESP.restart();
  }
  rtc.disable32K();
  rtc.writeSqwPinMode(DS3231_SquareWave1Hz);
  pinMode(CLOCK_TICK_INTERRUPT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(CLOCK_TICK_INTERRUPT_PIN), clockTick, FALLING);
}

void Clock::check() {
  if (tick) {
    if (rtc.lostPower()) {
      Serial.println("[Clock] Time not set");
    } else {
      Serial.print("[Clock] ");
      Serial.println(this->getTime());
    }
    tick = false;
  }
}

String Clock::getTime() {
  return rtc.now().timestamp();
}

void Clock::setTime(unsigned long unixTime) {
  Serial.print("[Clock] Setting time to ");
  Serial.println(unixTime);
  rtc.adjust(DateTime(unixTime));
}

float Clock::getTemperature() {
  return rtc.getTemperature();
}
