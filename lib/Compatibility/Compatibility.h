#ifndef __SEGMENT_CLOCK_COMPATIBILITY_H__
#define __SEGMENT_CLOCK_COMPATIBILITY_H__

#ifdef ESP8266

#include <Arduino.h>
#define printf Serial.printf

#else

#include <stdint.h>
#include <stdio.h>

#define D3 0
#define FALLING 0
#define ICACHE_RAM_ATTR
#define INPUT_PULLUP 0

uint8_t digitalPinToInterrupt(uint8_t pin);
void pinMode(uint8_t pin, uint8_t mode);

typedef void interruptRoutine (void);

void attachInterrupt(uint8_t pin, interruptRoutine intRoutine, int mode);

#endif

#endif // __SEGMENT_CLOCK_COMPATIBILITY_H__
