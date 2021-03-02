#ifndef __WALLHOUSE_REPORTABLE_H__
#define __WALLHOUSE_REPORTABLE_H__

#include <WString.h>

class Reportable {
public:
  virtual String report() = 0;
};

#endif // __WALLHOUSE_REPORTABLE_H__
