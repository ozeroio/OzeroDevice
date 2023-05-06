#include "WiredDevice.h"
#include <Wire.h>

WiredDevice::WiredDevice(const uint8_t deviceAddress) : deviceAddress(deviceAddress) {
}

uint8_t WiredDevice::getAddress() const {
	return deviceAddress;
}

void WiredDevice::setAddress(const uint8_t deviceAddress) {
	this->deviceAddress = deviceAddress;
}

uint32_t WiredDevice::available() {
	return Wire.available();
}

int16_t WiredDevice::read() const {
	Wire.requestFrom(deviceAddress, (uint8_t) 1);
	int16_t v = Wire.read();
	int16_t status = Wire.endTransmission();
	if (status > 0) {
		return -status;
	}
	return v;
}

int16_t WiredDevice::write(const uint8_t b) const {
	Wire.beginTransmission(deviceAddress);
	int16_t v = Wire.write(b);
	int16_t status = Wire.endTransmission();
	if (status > 0) {
		return -status;
	}
	return v;
}

int32_t WiredDevice::write(const uint8_t *b, const int32_t len) const {
	Wire.beginTransmission(deviceAddress);
	int32_t written = Wire.write(b, len);
	int16_t status = Wire.endTransmission();
	if (status != 0) {
		return (int32_t) -status;
	}
	return written;
}