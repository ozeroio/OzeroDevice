#include "WiredDevice.h"
#include <Wire.h>

WiredDevice::WiredDevice(uint8_t deviceAddress)
    : deviceAddress(deviceAddress) {

  // Begins the i2c module.
  Wire.begin();
}

WiredDevice::WiredDevice(uint8_t sdaPin, uint8_t sclPin, uint8_t deviceAddress) : deviceAddress(deviceAddress) {

#ifdef TARGET_ESP8266

  // Begins the i2c module for esp8266 using custom pins.
  Wire.begin(sdaPin, sclPin);
#else
  Wire.begin();
#endif
}

uint8_t WiredDevice::getDeviceAddress() {
  return deviceAddress;
}

void WiredDevice::setDeviceAddress(uint8_t deviceAddress) {
  this->deviceAddress = deviceAddress;
}
