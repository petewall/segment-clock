#include "Clock.h"
#include "Compatibility.h"
#include "DS3231.h"

#define CLOCK_TICK_INTERRUPT_PIN D3

volatile bool tick;

ICACHE_RAM_ATTR void clockTick() {
  tick = true;
}

Clock::Clock(Display* display, DS3231* rtc)
: display(display), rtc(rtc) {
  while (!rtc->begin()) {
    printf("[Clock] Failed to find RTC.\n");
  }
  rtc->disable32K();
  rtc->writeSqwPinMode(DS3231_SquareWave1Hz);
  pinMode(CLOCK_TICK_INTERRUPT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(CLOCK_TICK_INTERRUPT_PIN), clockTick, FALLING);
}

void Clock::check() {
  if (tick) {
    if (rtc->lostPower()) {
      printf("[Clock] Time not set\n");
    } else {
      this->display->setCurrentTime(this->getTime());
    }
    tick = false;
  }
}

time_t Clock::getTime() {
  return time_t (rtc->now().unixtime());
}

void Clock::setTime(time_t unixTime) {
  printf("[Clock] Setting time to %ld\n", unixTime);
  rtc->adjust(DateTime(unixTime));
}

float Clock::getTemperature() {
  return rtc->getTemperature();
}
