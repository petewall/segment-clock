#ifndef __SEGMENT_CLOCK_COMPATIBILITY_DS3231_H__
#define __SEGMENT_CLOCK_COMPATIBILITY_DS3231_H__

#ifdef ESP8266

#include <RTClib.h>
#define DS3231 RTC_DS3231

#else
#include "gmock/gmock.h"

enum Ds3231SqwPinMode {
  DS3231_OFF = 0x1C,            /**< Off */
  DS3231_SquareWave1Hz = 0x00,  /**<  1Hz square wave */
  DS3231_SquareWave1kHz = 0x08, /**<  1kHz square wave */
  DS3231_SquareWave4kHz = 0x10, /**<  4kHz square wave */
  DS3231_SquareWave8kHz = 0x18  /**<  8kHz square wave */
};

class DateTime {
public:
  DateTime(uint32_t now) : now(now) {}
  uint32_t unixtime(void) { return this->now; }
  uint32_t now;
  bool operator==(const DateTime& other) const { return this->now == other.now; }
};

class DS3231Interface {
public:
  virtual ~DS3231Interface() {}
  virtual void adjust(const DateTime &dt) = 0;
  virtual bool begin() = 0;
  virtual void disable32K() = 0;
  virtual float getTemperature() = 0;
  virtual bool lostPower() = 0;
  virtual DateTime now() = 0;
  virtual void writeSqwPinMode(Ds3231SqwPinMode mode) = 0;
};

class DS3231 : public DS3231Interface {
public:
  MOCK_METHOD(void, adjust, (const DateTime &dt), (override));
  MOCK_METHOD(bool, begin, (), (override));
  MOCK_METHOD(void, disable32K, (), (override));
  MOCK_METHOD(float, getTemperature, (), (override));
  MOCK_METHOD(bool, lostPower, (), (override));
  MOCK_METHOD(DateTime, now, (), (override));
  MOCK_METHOD(void, writeSqwPinMode, (Ds3231SqwPinMode mode), (override));
};

#endif

#endif // __SEGMENT_CLOCK_COMPATIBILITY_DS3231_H__
