#include <Compatibility.h>
#include <Clock.h>
#include "gmock/gmock.h"
#include "gtest/gtest.h"
using ::testing::Return;

DS3231* rtc;
MockDisplay* display;

extern uint8_t mock_interrupt_pin;
extern int mock_interrupt_mode;
extern volatile bool tick;

class ClockTest : public ::testing::Test {
 protected:
  ClockTest() {}
  ~ClockTest() override {}

  void SetUp() override {
    display = new MockDisplay();
    rtc = new DS3231();
    EXPECT_CALL(*rtc, begin()).Times(1).WillOnce(Return(true));
    EXPECT_CALL(*rtc, disable32K()).Times(1);
    EXPECT_CALL(*rtc, writeSqwPinMode(DS3231_SquareWave1Hz)).Times(1);
  }

  void TearDown() override {
    delete rtc;
    delete display;
  }
};

TEST_F(ClockTest, InterruptAttached) {
  Clock* clock = new Clock(display, rtc);

  EXPECT_EQ(mock_interrupt_pin, D3);
  EXPECT_EQ(mock_interrupt_mode, FALLING);
}

TEST_F(ClockTest, GettingTimeCallsRTC) {
  Clock* clock = new Clock(display, rtc);
  EXPECT_CALL(*rtc, now).Times(1).WillOnce(Return(DateTime(1234567890)));

  time_t now = clock->getTime();

  EXPECT_EQ(now, 1234567890);
}

TEST_F(ClockTest, GettingTemperatureCallsRTC) {
  Clock* clock = new Clock(display, rtc);
  EXPECT_CALL(*rtc, getTemperature).Times(1).WillOnce(Return(12.3));

  float temperature = clock->getTemperature();

  EXPECT_FLOAT_EQ(temperature, 12.3);
}

TEST_F(ClockTest, SettingTheTimeCallsTheRTC) {
  Clock* clock = new Clock(display, rtc);
  EXPECT_CALL(*rtc, adjust(DateTime(1234567890))).Times(1);

  clock->setTime(1234567890);
}

TEST_F(ClockTest, CallingCheckOffInterruptDoesNothing) {
  tick = false;
  Clock* clock = new Clock(display, rtc);
  EXPECT_CALL(*rtc, lostPower).Times(0);

  clock->check();
}

TEST_F(ClockTest, CallingCheckWhenPowerLostDoesNotSetDisplay) {
  Clock* clock = new Clock(display, rtc);
  EXPECT_CALL(*rtc, lostPower).Times(1).WillOnce(Return(true));

  tick = true; // Simulate RTC interrupt call
  clock->check();
}

TEST_F(ClockTest, CallingCheckWillUpdateDisplayTime) {
  Clock* clock = new Clock(display, rtc);

  EXPECT_CALL(*rtc, lostPower).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*rtc, now()).Times(1).WillOnce(Return(DateTime(1234567890)));
  EXPECT_CALL(*display, setCurrentTime(1234567890)).Times(1);

  tick = true; // Simulate RTC interrupt call
  clock->check();

  EXPECT_EQ(tick, false);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
