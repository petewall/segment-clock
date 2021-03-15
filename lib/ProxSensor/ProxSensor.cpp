#include "ProxSensor.h"
#include <Arduino.h>
#include <VCNL4010.h>

#define PROXIMITY_ACTION_INTERRUPT_PIN D4

VCNL4010 *sensor;

// const float    PERCENT_CHANGE{0.10};  ///< Trigger percentage change

volatile bool action = false;
ICACHE_RAM_ATTR void proximityAction() {
  action = true;
}

ProxSensor::ProxSensor(unsigned long interval)
: PeriodicAction(interval) {
  sensor = new VCNL4010();
  while (!sensor->begin()) {
    Serial.println("[ProxSensor] Failed to start VCNL4010");
  }
  // sensor->setAmbientLight(8, 128);
  sensor->setAmbientContinuous(true);
  sensor->setProximityContinuous(true);
  // sensor->setLEDmA(200);         // Boost power to Proximity sensor
  // sensor.setProximityFreq(32);  // Sample 32 times per second
  // uint16_t ProximityVal  = sensor.getProximity();  // Get the proximity reading
  // uint16_t lowThreshold  = ProximityVal - (ProximityVal * PERCENT_CHANGE);  // low threshold value
  // uint16_t highThreshold = ProximityVal + (ProximityVal * PERCENT_CHANGE);  // high threshold value
  // sensor.setInterrupt(1,                // Trigger after 1 event
  //                     false,            // Nothing on Proximity reading
  //                     false,            // Nothing on Ambient light reading
  //                     true,             // Interrupt on Proximity threshold
  //                     false,            // Nothing on Ambient threshold
  //                     lowThreshold,     // Low value is 90% of first reading
  //                     highThreshold);   // High value is 110% of first value
  // sensor.setProximityContinuous(true);  // Turn on continuous Proximity
  // sensor.clearInterrupt(0);  // Reset status on VCNL4010
  pinMode(PROXIMITY_ACTION_INTERRUPT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(D0), proximityAction, LOW); // jump to vector when pin goes LOW
}

bool ProxSensor::run() {
  Serial.print("Ambient: ");
  Serial.println(sensor->getAmbientLight());

  Serial.print("Proximity: ");
  Serial.println(sensor->getProximity());

  // if (action) {
  //   sensor.clearInterrupt(0);
  //   action = false;
  //   Serial.println("I saw that!");
  // }
  return true;
}

