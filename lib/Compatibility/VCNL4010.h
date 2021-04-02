#ifndef __SEGMENT_CLOCK_COMPATIBILITY_VCNL4010_H__
#define __SEGMENT_CLOCK_COMPATIBILITY_VCNL4010_H__

#ifdef ESP8266

#include <Adafruit_VCNL4010.h>
#define VCNL4010 Adafruit_VCNL4010

#else

#include "gmock/gmock.h"
typedef enum {
  VCNL4010_1_95 = 0,    // 1.95     measurements/sec (Default)
  VCNL4010_3_90625 = 1, // 3.90625  measurements/sec
  VCNL4010_7_8125 = 2,  // 7.8125   measurements/sec
  VCNL4010_16_625 = 3,  // 16.625   measurements/sec
  VCNL4010_31_25 = 4,   // 31.25    measurements/sec
  VCNL4010_62_5 = 5,    // 62.5     measurements/sec
  VCNL4010_125 = 6,     // 125      measurements/sec
  VCNL4010_250 = 7,     // 250      measurements/sec
} vcnl4010_freq;

class VCNL4010Interface {
public:
  virtual ~VCNL4010Interface() {}
  virtual bool begin() = 0;
  virtual void setLEDcurrent(uint8_t c) = 0;
  virtual uint16_t readAmbient(void) = 0;
  virtual uint16_t readProximity() = 0;
  virtual void setFrequency(vcnl4010_freq f) = 0;
};
class VCNL4010 : public VCNL4010Interface {
public:
  MOCK_METHOD(bool, begin, (), (override));
  MOCK_METHOD(void, setLEDcurrent, (uint8_t c), (override));
  MOCK_METHOD(uint16_t, readAmbient, (), (override));
  MOCK_METHOD(uint16_t, readProximity, (), (override));
  MOCK_METHOD(void, setFrequency, (vcnl4010_freq f), (override));
};

#endif

#endif // __SEGMENT_CLOCK_COMPATIBILITY_VCNL4010_H__
