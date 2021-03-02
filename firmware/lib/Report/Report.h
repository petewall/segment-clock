#ifndef __WALLHOUSE_REPORT_H__
#define __WALLHOUSE_REPORT_H__

#include <ESP8266WebServer.h>
#include <Reportable.h>
#include <stdlib.h>

class Report {
public:
  Report(std::vector<Reportable*> reportables);
  void update();

private:
  std::vector<Reportable*> reportables;
  ESP8266WebServer* server;
  void serveJSON(void);
};

#endif // __WALLHOUSE_REPORT_H__
