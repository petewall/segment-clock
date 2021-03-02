#include "Report.h"

Report::Report(std::vector<Reportable*> reportables)
: reportables(reportables), server(new ESP8266WebServer(80))
{
  this->server->on("/", [this](){ this->serveJSON(); });
  this->server->begin();
}

void Report::update() {
  this->server->handleClient();
}

void Report::serveJSON(void) {
  String output = "{";
  for (unsigned int i = 0; i < this->reportables.size(); i += 1) {
    if (i > 0) {
      output += ",";
    }
    output += this->reportables[i]->report();
  }
  output += "}";

  this->server->send(200, "application/json", output);
}
