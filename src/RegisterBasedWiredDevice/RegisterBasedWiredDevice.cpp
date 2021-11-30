#include <Arduino.h>
#include <Wire.h>
#include "RegisterBasedWiredDevice.h"

RegisterBasedWiredDevice::RegisterBasedWiredDevice(uint8_t deviceAddress)
    : RegisterBasedDevice(), WiredDevice(deviceAddress) {
}

RegisterBasedWiredDevice::RegisterBasedWiredDevice(uint8_t sdaPin, uint8_t sclPin, uint8_t deviceAddress)
    : RegisterBasedDevice(), WiredDevice(sdaPin, sclPin, deviceAddress) {
}

int16_t RegisterBasedWiredDevice::readRegisterBlock(uint8_t reg, uint8_t *buf, int16_t len) {
  int8_t tries = MAX_RETRIES_ON_READING;
  int16_t i;
  Wire.beginTransmission(getDeviceAddress());
  Wire.write(reg);
  int16_t status = Wire.endTransmission(false);
  if (status > 0) {
    return (int16_t) -status;
  }
  Wire.requestFrom((int16_t) getDeviceAddress(), len);
  while (!Wire.available() && --tries > 0) {
    delayMicroseconds(1);
  }
  if (tries == 0) {
    return -5;
  }
  for (i = 0; i < len && Wire.available(); i++) {
    int16_t r = Wire.read();
    if (r < 0) {
      break;
    }
    buf[i] = r;
  }
  return i;
}

int16_t RegisterBasedWiredDevice::writeRegisterBlock(uint8_t reg, uint8_t *buff, int16_t len) {
  Wire.beginTransmission(getDeviceAddress());
  Wire.write(reg);
  int16_t written = Wire.write(buff, len);
  int16_t eot = Wire.endTransmission();
  if (eot > 0) {
    return (int16_t) -eot;
  }
  return written;
}
