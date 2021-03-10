#ifndef __SEGMENT_CLOCK_NTP_H__
#define __SEGMENT_CLOCK_NTP_H__

#include <PeriodicAction.h>
#include <RTClib.h>

class NTP : public PeriodicAction {
public:
  explicit NTP(unsigned long interval, RTC_DS3231* rtc);

protected:
  void run() override;

private:
  RTC_DS3231* rtc;
};

#endif // __SEGMENT_CLOCK_NTP_H__