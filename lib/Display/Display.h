#ifndef __SEGMENT_CLOCK_DISPLAY_H__
#define __SEGMENT_CLOCK_DISPLAY_H__

#include <PeriodicAction.h>

enum modes {
  OFF,
  TIME,
  INTERNAL_TEMPERATURE,
  // EXTERNAL_TEMPERATURE
};

class Display : public PeriodicAction {
public:
  explicit Display(unsigned long interval);
  void updateTime(short minutes, short seconds);

  // void changeMode();
  virtual bool run() override;

private:
  bool separatorState;
  // modes defaultMode;
  // modes currentMode;
};

#endif // __SEGMENT_CLOCK_DISPLAY_H__
