#ifndef __SEGMENT_CLOCK_CLOCK_H__
#define __SEGMENT_CLOCK_CLOCK_H__

#include <WString.h>

class Clock {
public:
  explicit Clock();
  void check();

  String getTime();
  void setTime(unsigned long unixTime);

  float getTemperature();
};

#endif // __SEGMENT_CLOCK_CLOCK_H__
