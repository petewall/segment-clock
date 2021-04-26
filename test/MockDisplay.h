#ifndef __SEGMENT_CLOCK__TEST_MOCK_DISPLAY_H__
#define __SEGMENT_CLOCK__TEST_MOCK_DISPLAY_H__

#include <Display.h>
#include "gmock/gmock.h"

class MockDisplay : public Display {
public:
  MockDisplay() : Display(0) {}
  MOCK_METHOD(void, setCurrentTime, (time_t newTime), (override));
  MOCK_METHOD(void, changeMode, (), (override));
};

#endif // __SEGMENT_CLOCK__TEST_MOCK_DISPLAY_H__
