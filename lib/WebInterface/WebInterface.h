#ifndef __SEGMENT_CLOCK_WEB_INTERFACE_H__
#define __SEGMENT_CLOCK_WEB_INTERFACE_H__

#include <Clock.h>
#include <ESP8266WebServer.h>

class WebInterface {
public:
  explicit WebInterface(Clock* clock);
  void check();

private:
  Clock* clock;
  ESP8266WebServer* server;
};

#endif // __SEGMENT_CLOCK_WEB_INTERFACE_H__
