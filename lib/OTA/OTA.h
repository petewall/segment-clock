#ifndef __SEGMENT_CLOCK_OTA_H__
#define __SEGMENT_CLOCK_OTA_H__

#include <PeriodicAction.h>

class OTA : public PeriodicAction {
public:
  explicit OTA(unsigned long interval);

protected:
  void run() override;
};

#endif // __SEGMENT_CLOCK_OTA_H__