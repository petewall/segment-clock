#include "Compatibility.h"

uint8_t digitalPinToInterrupt(uint8_t pin) {
  return pin;
}

void pinMode(uint8_t pin, uint8_t mode) {

}

uint8_t mock_interrupt_pin;
int mock_interrupt_mode;
void attachInterrupt(uint8_t pin, interruptRoutine intRoutine, int mode) {
  mock_interrupt_pin = pin;
  mock_interrupt_mode = mode;
}
