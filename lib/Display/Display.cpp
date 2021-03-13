#include "Display.h"
#include <Arduino.h>

Display::Display(unsigned long interval)
:PeriodicAction(interval), separatorState(true) {}

void Display::updateTime(short hours, short minutes) {
  separatorState = !separatorState;
  Serial.printf("[Display] %02d%s%02d\n", hours, separatorState ? ":" : " ", minutes);
}

bool Display::run() {
  return true;
}
