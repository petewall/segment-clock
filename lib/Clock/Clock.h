#ifndef __SEGMENT_CLOCK_CLOCK_H__
#define __SEGMENT_CLOCK_CLOCK_H__

#include <Reportable.h>

class Clock : public Reportable {
public:
  explicit Clock();
  void check();
  void setTime(unsigned long unixTime);
  String report() override;
};

#endif // __SEGMENT_CLOCK_CLOCK_H__
