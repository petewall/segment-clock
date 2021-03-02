#ifndef __WALLHOUSE_OTA_H__
#define __WALLHOUSE_OTA_H__

#include <PeriodicAction.h>
#include <stdlib.h>

class OTA : public PeriodicAction {
public:
  OTA(unsigned long interval, String otaHost, String currentFirmware, String currentFirmwareVersion);
  void run();

private:
  String otaURL;
};

#endif // __WALLHOUSE_OTA_H__