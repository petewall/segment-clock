#ifndef __SEGMENT_CLOCK_REPORTABLE_H__
#define __SEGMENT_CLOCK_REPORTABLE_H__

#include <WString.h>

class Reportable {
public:
  virtual String report() = 0;
};

#endif // __SEGMENT_CLOCK_REPORTABLE_H__
