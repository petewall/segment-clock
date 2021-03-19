#include "Display.h"
#include <Arduino.h>

Display::Display(unsigned long interval)
:PeriodicAction(interval),
separatorState(true),
currentMode(MODE_OFF),
defaultMode(MODE_OFF) {}

void Display::setCurrentTime(DateTime newTime) {
  this->currentTime = newTime;
  this->separatorState = !this->separatorState;
  this->display();
}

void Display::changeMode() {
  Serial.printf("[Display] Chaging from mode %d", this->currentMode);
  this->currentMode = (this->currentMode + 1) % NUMBER_OF_MODES;
  Serial.printf(" to mode %d\n", this->currentMode);
  this->resetTimer();
  this->display();
}

bool Display::run() {
  if (this->currentMode != this->defaultMode) {
    Serial.printf("[Display] Back to mode %d\n", this->defaultMode);
    this->currentMode = this->defaultMode;
  }
  return true;
}

void Display::display() {
  switch (this->currentMode) {
  case MODE_TIME:
    this->displayTime();
    break;
  case MODE_DAY:
    this->displayDay();
    break;
  };
}

void Display::displayTime() {
  Serial.printf("[Display] %02d%s%02d\n", this->currentTime.hour(), this->separatorState ? ":" : " ", this->currentTime.minute());
}

char days_of_week[7][3] = {"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"};
void Display::displayDay() {
  Serial.printf("[Display] %s%02d\n", days_of_week[this->currentTime.dayOfTheWeek()], this->currentTime.day());
}
