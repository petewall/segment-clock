#include "ProxSensor.h"
#include "Compatibility.h"
#include <VCNL4010.h>

#define PROXIMITY_ACTION_INTERRUPT_PIN D4

VCNL4010 *sensor;

#define PROXIMITY_LED_POWER 200
#define PROXIMITY_THRESHOLD 2300

#define AMBIENT_LIGHT_AVERAGING 16
unsigned short ambientLightMeasurementIndex = 0;
uint16_t ambientLightMeasurements[AMBIENT_LIGHT_AVERAGING] = {0};

ProxSensor::ProxSensor(unsigned long interval, Display* display)
: PeriodicAction(interval), display(display), lastProximity(0), proximityTriggered(false) {
  sensor = new VCNL4010();
  while (!sensor->begin()) {
    printf("[ProxSensor] Failed to start VCNL4010\n");
  }

  sensor->setLEDcurrent(PROXIMITY_LED_POWER);
  sensor->setFrequency(VCNL4010_31_25);
}

bool ProxSensor::run() {
  ambientLightMeasurements[ambientLightMeasurementIndex] = sensor->readAmbient();
  ambientLightMeasurementIndex = (ambientLightMeasurementIndex + 1) % AMBIENT_LIGHT_AVERAGING;

  this->lastProximity = sensor->readProximity();
  if (this->lastProximity > PROXIMITY_THRESHOLD) {
    if (!this->proximityTriggered) {
      this->proximityTriggered = true;
      this->display->changeMode();
    }
  } else {
    this->proximityTriggered = false;
  }

  return true;
}

uint16_t ProxSensor::getAmbientLight() {
  uint16_t sum = 0;
  for (int i = 0; i < AMBIENT_LIGHT_AVERAGING; i += 1) {
    sum += ambientLightMeasurements[i];
  }
  return sum / AMBIENT_LIGHT_AVERAGING;
}

uint16_t ProxSensor::getProximity() {
  return this->lastProximity;
}

bool ProxSensor::isProximityTriggered() {
  return this->proximityTriggered;
}
