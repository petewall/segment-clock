#ifndef __SEGMENT_CLOCK_DISPLAY_H__
#define __SEGMENT_CLOCK_DISPLAY_H__

#include <PeriodicAction.h>
#include <RTClib.h>

enum modes {
  MODE_OFF,
  MODE_TIME,
  MODE_DAY,
  // MODE_INTERNAL_TEMPERATURE,
  // EXTERNAL_TEMPERATURE
};

class Display : public PeriodicAction {
public:
  explicit Display(unsigned long interval);
  void setCurrentTime(DateTime newTime);

  void changeMode();
  virtual bool run() override;

private:
  bool separatorState;
  modes currentMode;
  modes defaultMode;

  DateTime currentTime;

  void displayTime();
  void displayDay();
};

#endif // __SEGMENT_CLOCK_DISPLAY_H__
