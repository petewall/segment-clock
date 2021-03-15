#include "Display.h"
#include <Arduino.h>

Display::Display(unsigned long interval)
:PeriodicAction(interval),
separatorState(true),
currentMode(MODE_OFF),
defaultMode(MODE_OFF) {}

void Display::setCurrentTime(DateTime newTime) {
  currentTime = newTime;
  separatorState = !separatorState;
  run();
}

bool Display::run() {
  currentMode = defaultMode;
  return true;
}

void Display::displayTime() {
  Serial.printf("[Display] %02d%s%02d\n", currentTime.hour(), separatorState ? ":" : " ", currentTime.minute());
}

void Display::displayDay() {
  Serial.printf("[Display] %02d%s%02d\n", currentTime.hour(), separatorState ? ":" : " ", currentTime.minute());
}
