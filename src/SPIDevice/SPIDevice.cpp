#include "SPIDevice.h"
#include <SPI.h>

SPIDevice::SPIDevice() {
  SPI.begin();
}