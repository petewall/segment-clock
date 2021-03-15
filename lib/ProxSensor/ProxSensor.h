#ifndef __SEGMENT_CLOCK_PROX_SENSOR_H__
#define __SEGMENT_CLOCK_PROX_SENSOR_H__

#include <PeriodicAction.h>

class ProxSensor : public PeriodicAction {
public:
  explicit ProxSensor(unsigned long interval);

  virtual bool run() override;
};

#endif // __SEGMENT_CLOCK_PROX_SENSOR_H__