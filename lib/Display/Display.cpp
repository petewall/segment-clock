#include "Display.h"
#include "Compatibility.h"

Display::Display(unsigned long interval)
:PeriodicAction(interval),
separatorState(true),
currentMode(MODE_OFF),
defaultMode(MODE_OFF) {}

void Display::setCurrentTime(time_t newTime) {
  this->currentTime = newTime;
  this->separatorState = !this->separatorState;
  this->display();
}

void Display::changeMode() {
  printf("[Display] Chaging from mode %d\n", this->currentMode);
  this->currentMode = (this->currentMode + 1) % NUMBER_OF_MODES;
  printf(" to mode %d\n", this->currentMode);
  this->resetTimer();
  this->display();
}

display_mode_t Display::getMode() {
  return this->currentMode;
}

bool Display::run() {
  if (this->currentMode != this->defaultMode) {
    printf("[Display] Back to mode %d\n", this->defaultMode);
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
  tm* now = localtime(&this->currentTime);
  printf("[Display] %02d%s%02d\n", now->tm_hour, this->separatorState ? ":" : " ", now->tm_min);
}

char days_of_week[7][3] = {"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"};
void Display::displayDay() {
  tm* now = localtime(&this->currentTime);
  printf("[Display] %s%02d\n", days_of_week[now->tm_wday], now->tm_mday);
}
