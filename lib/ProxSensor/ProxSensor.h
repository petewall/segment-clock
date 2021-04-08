#ifndef __SEGMENT_CLOCK_PROX_SENSOR_H__
#define __SEGMENT_CLOCK_PROX_SENSOR_H__

#include <PeriodicAction.h>
#include <Display.h>
#include <VCNL4010.h>
#include <stdint.h>

class ProxSensor : public PeriodicAction {
public:
  explicit ProxSensor(unsigned long interval, Display* display, VCNL4010* sensor);

  virtual bool run() override;

  uint16_t getAmbientLight();
  uint16_t getProximity();
  bool isProximityTriggered();

private:
  Display* display;
  VCNL4010* sensor;
  uint16_t lastProximity;
  bool proximityTriggered;
};

#endif // __SEGMENT_CLOCK_PROX_SENSOR_H__