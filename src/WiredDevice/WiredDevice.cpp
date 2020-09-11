#include "WiredDevice.h"
#include <Wire.h>

WiredDevice::WiredDevice(uint8_t deviceAddress) : deviceAddress(deviceAddress) {
  Wire.begin();
}

WiredDevice::WiredDevice(uint8_t sdaPin, uint8_t sclPin, uint8_t deviceAddress) : deviceAddress(deviceAddress) {

#ifdef CUSTOM_WIRE_PINS_SUPPORT_ENABLED
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
