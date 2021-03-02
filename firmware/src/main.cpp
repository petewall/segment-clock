#include <Arduino.h>
#include <Blinker.h>

#define INTERVAL 500
Blinker *blinker;

void setup() {
  blinker = new Blinker(INTERVAL);
}

void loop() {
  blinker->check(millis());
}
