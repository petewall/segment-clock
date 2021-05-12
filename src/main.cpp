#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Clock.h>
#include <Display.h>
#include <NTP.h>
#include <OTAClient.h>
#include <ProxSensor.h>
#include <ReliableNetwork.h>
#include <WebInterface.h>

Clock* rtClock;
Display* display;
NTP* ntp;
OTAClient* ota;
ProxSensor* proxSensor;
ReliableNetwork *network;
WebInterface* webInterface;
bool wifiState = false;

#define FIVE_SECONDS 5 * 1000
#define TEN_MINUTES 10 * 60 * 1000
#define ONE_DAY 24 * 60 * 60 * 1000

// cppcheck-suppress unusedFunction
void setup() {
  Serial.begin(115200);

  network = new ReliableNetwork(WIFI_SSID, WIFI_PASSWORD);
  network->connect();

  display = new Display(FIVE_SECONDS);
  rtClock = new Clock(display, new DS3231());
  ntp = new NTP(ONE_DAY, rtClock);
  ota = new OTAClient(TEN_MINUTES, OTA_HOSTNAME, OTA_PORT, network);
  proxSensor = new ProxSensor(20, display, new VCNL4010());

  webInterface = new WebInterface(rtClock);
}

// cppcheck-suppress unusedFunction
void loop() {
  unsigned long now = millis();

  display->check(now);
  network->check(now);
  ntp->check(now);
  ota->check(now);
  proxSensor->check(now);
  rtClock->check();
  webInterface->check();
}
