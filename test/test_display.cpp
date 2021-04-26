#include <Compatibility.h>
#include <Display.h>
#include "gmock/gmock.h"
#include "gtest/gtest.h"
using ::testing::Return;

class DisplayTest : public ::testing::Test {
 protected:
  Display* display;

  DisplayTest() {}
  ~DisplayTest() override {}
  void SetUp() override {
    display = new Display(5000);
  }
  void TearDown() override {
    delete display;
  }
};

TEST_F(DisplayTest, DefaultModeIsOff) {
  ASSERT_EQ(display->getMode(), MODE_OFF);
}

// TEST_F(DisplayTest, SettingTimeBlinksTheSeparators) {
//   Display* display = new Display(5000);
//   FAIL() << "Not yet implemented";
// }

TEST_F(DisplayTest, ChangingModeShowsTime) {
  display->changeMode();
  ASSERT_EQ(display->getMode(), MODE_TIME);
}

// Changing mode once shows time
// Changing mode twice shows date
// Changing mode thrice shows internal temp
// Changing mode thrice shows external temp
// Changing mode thrice shows external high
// Changing mode thrice shows external Low
// Changing mode will wrap around back to time (skipping off)

// After interval, return to off
// Changing mode resets the timer
