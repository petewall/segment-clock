#ifndef __SEGMENT_CLOCK_CLOCK_H__
#define __SEGMENT_CLOCK_CLOCK_H__

class Clock {
public:
  explicit Clock();
  void check();
  void setTime(unsigned long unixTime);
};

#endif // __SEGMENT_CLOCK_CLOCK_H__
