#include <Compatibility.h>
#include <MockDisplay.h>
#include <ProxSensor.h>
#include "gmock/gmock.h"
#include "gtest/gtest.h"
using ::testing::Return;


class ProxSensorTest : public ::testing::Test {
 protected:
  VCNL4010* sensor;
  MockDisplay* display;

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

TEST_F(ProxSensorTest, GetAmbientLightReturnsAverageMeasurement) {
  ProxSensor* prox = new ProxSensor(0, display, sensor);
  EXPECT_CALL(*sensor, readProximity).Times(17).WillRepeatedly(Return(0));
  EXPECT_CALL(*sensor, readAmbient).Times(17)
    .WillOnce(Return(10)).WillOnce(Return(15))
    .WillOnce(Return(20)).WillOnce(Return(25))
    .WillOnce(Return(30)).WillOnce(Return(35))
    .WillOnce(Return(40)).WillOnce(Return(45))
    .WillOnce(Return(50)).WillOnce(Return(55))
    .WillOnce(Return(60)).WillOnce(Return(65))
    .WillOnce(Return(70)).WillOnce(Return(75))
    .WillOnce(Return(80)).WillOnce(Return(85)).WillOnce(Return(90));

  for (int i = 0; i < 17; i += 1)
    prox->run();

  uint16_t ambient = prox->getAmbientLight();
  EXPECT_EQ(ambient, 52);
}

TEST_F(ProxSensorTest, RunEvaluatesProximityDistance) {
  ProxSensor* prox = new ProxSensor(0, display, sensor);
  EXPECT_CALL(*sensor, readProximity).Times(1).WillOnce(Return(1000));
  EXPECT_CALL(*sensor, readAmbient).Times(1).WillOnce(Return(0));

  prox->run();

  uint16_t proximity = prox->getProximity();
  bool triggered = prox->isProximityTriggered();

  EXPECT_EQ(proximity, 1000);
  EXPECT_EQ(triggered, false);
}

TEST_F(ProxSensorTest, ProximityOnlyTriggersOnce) {
  ProxSensor* prox = new ProxSensor(0, display, sensor);
  EXPECT_CALL(*sensor, readProximity).Times(3)
    .WillOnce(Return(1000))
    .WillOnce(Return(3000))
    .WillOnce(Return(3000));
  EXPECT_CALL(*sensor, readAmbient).Times(3).WillRepeatedly(Return(0));

  prox->run();
  bool triggered1 = prox->isProximityTriggered();

  EXPECT_CALL(*display, changeMode).Times(1);
  prox->run();
  bool triggered2 = prox->isProximityTriggered();
  prox->run();
  bool triggered3 = prox->isProximityTriggered();

  EXPECT_EQ(triggered1, false);
  EXPECT_EQ(triggered2, true);
  EXPECT_EQ(triggered3, true);
}

TEST_F(ProxSensorTest, ProximityTriggerResetsProperly) {
  ProxSensor* prox = new ProxSensor(0, display, sensor);
  EXPECT_CALL(*sensor, readProximity).Times(3)
    .WillOnce(Return(1000))
    .WillOnce(Return(3000))
    .WillOnce(Return(1000));
  EXPECT_CALL(*sensor, readAmbient).Times(3).WillRepeatedly(Return(0));

  prox->run();
  bool triggered1 = prox->isProximityTriggered();

  EXPECT_CALL(*display, changeMode).Times(1);
  prox->run();
  bool triggered2 = prox->isProximityTriggered();
  prox->run();
  bool triggered3 = prox->isProximityTriggered();

  EXPECT_EQ(triggered1, false);
  EXPECT_EQ(triggered2, true);
  EXPECT_EQ(triggered3, false);
}
