#include <Compatibility.h>
#include <Display.h>
#include "gmock/gmock.h"
#include "gtest/gtest.h"
using ::testing::Return;

extern uint8_t mock_interrupt_pin;
extern int mock_interrupt_mode;
extern volatile bool tick;

class DisplayTest : public ::testing::Test {
 protected:
  DisplayTest() {}
  ~DisplayTest() override {}
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(DisplayTest, DefaultModeIsOff) {
  Display* display = new Display(5000);
  FAIL() << "Not yet implemented";
}

TEST_F(DisplayTest, SettingTimeBlinksTheSeparators) {
  Display* display = new Display(5000);
  FAIL() << "Not yet implemented";
}

// Changing mode once shows time
// Changing mode twice shows date
// Changing mode thrice shows internal temp
// Changing mode thrice shows external temp
// Changing mode thrice shows external high
// Changing mode thrice shows external Low

// After interval, return to off

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
