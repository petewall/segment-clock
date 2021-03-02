#include "FirmwareReport.h"
#include <Arduino.h>

FirmwareReport::FirmwareReport(String currentFirmware, String currentFirmwareVersion)
: data("{"
          "\"firmware\":{"
            "\"type\":\"" + currentFirmware + "\","
            "\"version\":\"" + currentFirmwareVersion + "\","
          "}"
        "}") {}

String FirmwareReport::report() {
  return this->data;
}
