#ifndef __SEGMENT_CLOCK_CLOCK_H__
#define __SEGMENT_CLOCK_CLOCK_H__

#include <Display.h>
#include <DS3231.h>

class Clock {
public:
  explicit Clock(Display* display, DS3231* rtc);
  void check();

  time_t getTime();
  void setTime(time_t unixTime);

  float getTemperature();

private:
  Display* display;
  DS3231* rtc;
};

#endif // __SEGMENT_CLOCK_CLOCK_H__
