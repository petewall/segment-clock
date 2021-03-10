#ifndef __SEGMENT_CLOCK_NTP_H__
#define __SEGMENT_CLOCK_NTP_H__

#include <PeriodicAction.h>
#include <Clock.h>

class NTP : public PeriodicAction {
public:
  explicit NTP(unsigned long interval, Clock* clock);

protected:
  bool run() override;

private:
  Clock* clock;
};

#endif // __SEGMENT_CLOCK_NTP_H__