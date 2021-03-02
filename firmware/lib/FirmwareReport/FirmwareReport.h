#ifndef __WALLHOUSE_FIRMWARE_REPORT_H__
#define __WALLHOUSE_FIRMWARE_REPORT_H__

#include <PeriodicAction.h>
#include <Reportable.h>

class FirmwareReport : public Reportable {
public:
  FirmwareReport(String currentFirmware, String currentFirmwareVersion);
  virtual String report();

private:
  String data;
};

#endif // __WALLHOUSE_FIRMWARE_REPORT_H__