#include <Arduino.h>
#include <unity.h>
#include <TestBlinker.h>

void setup() {
  delay(2000);
  UNITY_BEGIN();
  test_blinker_setup();
}

void loop() {
  if (test_blinker_run()) {
    UNITY_END();
  }
}
