#include "RegisterBasedDevice.h"

RegisterBasedDevice::RegisterBasedDevice() = default;

int16_t RegisterBasedDevice::configureRegisterBits(const uint8_t reg, const uint8_t mask, const uint8_t d) {
  int16_t n = readRegister(reg);
  if (n < 0) {
    return n;
  }

  // Clears bits marked by bask.
  n &= ~mask;

  // Sets bits marked by bask and data.
  n |= d & mask;
  return writeRegister(reg, (uint8_t) n);
}

int16_t RegisterBasedDevice::writeRegister(uint8_t reg, uint8_t d) {
  return writeRegisterBlock(reg, &d, 1);
}

int16_t RegisterBasedDevice::readRegister(const uint8_t reg) {
  uint8_t c;
  int16_t r = readRegisterBlock(reg, &c, 1);
  if (r < 0) {
    return r;
  }
  return (int16_t) c;
}
