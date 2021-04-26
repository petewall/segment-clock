#ifndef __SEGMENT_CLOCK_DISPLAY_H__
#define __SEGMENT_CLOCK_DISPLAY_H__

#include <PeriodicAction.h>
#include <ctime>
#include <stdint.h>

typedef uint8_t display_mode_t;
const display_mode_t MODE_OFF = 0;
const display_mode_t MODE_TIME = 1;
const display_mode_t MODE_DAY = 2;
const display_mode_t NUMBER_OF_MODES = 3;

class Display : public PeriodicAction {
public:
  explicit Display(unsigned long interval);
  virtual ~Display() {}

  virtual void setCurrentTime(time_t newTime);
  virtual void changeMode();
  display_mode_t getMode();
  virtual bool run() override;

private:
  void display();
  void displayTime();
  void displayDay();

  bool separatorState;
  display_mode_t currentMode;
  display_mode_t defaultMode;

  time_t currentTime;
};

#endif // __SEGMENT_CLOCK_DISPLAY_H__
