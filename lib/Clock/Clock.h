#ifndef __SEGMENT_CLOCK_CLOCK_H__
#define __SEGMENT_CLOCK_CLOCK_H__

#include <Display.h>
#include <WString.h>

class Clock {
public:
  explicit Clock(Display* display);
  void check();

  DateTime getTime();
  void setTime(unsigned long unixTime);

  float getTemperature();

private:
  Display* display;
};

#endif // __SEGMENT_CLOCK_CLOCK_H__
