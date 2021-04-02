#ifndef __SEGMENT_CLOCK_PERIODIC_ACTION_H__
#define __SEGMENT_CLOCK_PERIODIC_ACTION_H__

class PeriodicAction {
public:
  explicit PeriodicAction(unsigned long interval);
  virtual void check(unsigned long millis);

protected:
  void resetTimer();
  virtual bool run() = 0;

private:
  unsigned long interval;
  unsigned long next;
  bool reset;
};

#endif // __SEGMENT_CLOCK_PERIODIC_ACTION_H__
