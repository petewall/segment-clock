// #include <unity.h>
#include <Compatibility.h>
#include <ProxSensor.h>
#include "gmock/gmock.h"
#include "gtest/gtest.h"
using ::testing::Return;

VCNL4010* sensor;
MockDisplay* display;

class ProxSensorTest : public ::testing::Test {
 protected:
  ProxSensorTest() {}
  ~ProxSensorTest() override {}

  void SetUp() override {
    display = new MockDisplay();
    sensor = new VCNL4010();
    EXPECT_CALL(*sensor, begin()).Times(1).WillOnce(Return(true));
    EXPECT_CALL(*sensor, setLEDcurrent(200)).Times(1);
    EXPECT_CALL(*sensor, setFrequency(VCNL4010_31_25)).Times(1);
  }

  void TearDown() override {
    delete sensor;
    delete display;
  }
};

TEST_F(ProxSensorTest, SensorCorrectlyInitialized) {
  ProxSensor* prox = new ProxSensor(0, display, sensor);
}

TEST_F(ProxSensorTest, RunPutsAmbientMeasurementsIntoArray) {
  ProxSensor* prox = new ProxSensor(0, display, sensor);
  ADD_FAILURE() << "Not yet implemented";
}

TEST_F(ProxSensorTest, GetAmbientLightReturnsAverageMeasurement) {
  ProxSensor* prox = new ProxSensor(0, display, sensor);
  ADD_FAILURE() << "Not yet implemented";
}

TEST_F(ProxSensorTest, RunEvaluatesProximityDistance) {
  ProxSensor* prox = new ProxSensor(0, display, sensor);
  ADD_FAILURE() << "Not yet implemented";
}

TEST_F(ProxSensorTest, ProximityOnlyTriggersOnce) {
  ProxSensor* prox = new ProxSensor(0, display, sensor);
  ADD_FAILURE() << "Not yet implemented";
}

TEST_F(ProxSensorTest, ProximityTriggerResetsProperly) {
  ProxSensor* prox = new ProxSensor(0, display, sensor);
  ADD_FAILURE() << "Not yet implemented";
}

TEST_F(ProxSensorTest, GetProximityReturnsLastMeasurement) {
  ProxSensor* prox = new ProxSensor(0, display, sensor);
  ADD_FAILURE() << "Not yet implemented";
}

TEST_F(ProxSensorTest, IsProximityTriggeredReturnsState) {
  ProxSensor* prox = new ProxSensor(0, display, sensor);
  ADD_FAILURE() << "Not yet implemented";
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
