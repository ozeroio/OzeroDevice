#include "RegisterBasedWiredDevice.h"
#include <Arduino.h>
#include <Wire.h>

RegisterBasedWiredDevice::RegisterBasedWiredDevice(uint8_t deviceAddress)
	: RegisterBasedDevice(), WiredDevice(deviceAddress) {
}

int32_t RegisterBasedWiredDevice::readRegisterBlock(uint8_t reg, uint8_t *buf, int32_t len) {
	int8_t tries = MAX_RETRIES_ON_READING;
	int32_t i;
	Wire.beginTransmission(getAddress());
	Wire.write(reg);
	int16_t status = Wire.endTransmission(false);
	if (status > 0) {
		return (int32_t) -status;
	}
	Wire.requestFrom((int16_t) getAddress(), len);
	while (!Wire.available() && --tries > 0) {
		delayMicroseconds(1);
	}
	if (tries == 0) {
		return -5;
	}
	for (i = 0; i < len && Wire.available(); i++) {
		auto r = (int16_t) Wire.read();
		if (r < 0) {
			break;
		}
		buf[i] = r;
	}
	return i;
}

int32_t RegisterBasedWiredDevice::writeRegisterBlock(uint8_t reg, uint8_t *buff, int32_t len) {
	Wire.beginTransmission(getAddress());
	Wire.write(reg);
	auto written = (int32_t) Wire.write(buff, len);
	int16_t status = Wire.endTransmission();
	if (status > 0) {
		return (int32_t) -status;
	}
	return written;
}
