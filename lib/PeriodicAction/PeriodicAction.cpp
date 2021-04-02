#include "PeriodicAction.h"

PeriodicAction::PeriodicAction(unsigned long interval)
: interval(interval), next(0), reset(false)
{}

void PeriodicAction::check(unsigned long millis) {
  if (this->reset) {
    this->next = millis + this->interval;
  } else if (millis > this->next) {
    if (this->run()) {
      this->next = millis + this->interval;
    }
  }
}

void PeriodicAction::resetTimer() {
  this->reset = true;
}
