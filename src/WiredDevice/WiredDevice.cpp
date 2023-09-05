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
	auto available = Wire.available();
	if (available < 0) {
		return 0;
	}
	return available;
}

int32_t WiredDevice::read(uint8_t *b, int32_t len) const {
	int32_t readBytes = Wire.requestFrom((int32_t) deviceAddress, len);
	for (int32_t i = 0; i < readBytes; i++) {
		b[i] = Wire.read();
	}
	int16_t status = Wire.endTransmission();
	if (status > 0) {
		return -status;
	}
	return readBytes;
}

int16_t WiredDevice::read() const {
	uint8_t b;
	auto r = (int16_t) read(&b, 1);
	if (r < 0) {
		return r;
	}
	if (r == 0) {
		return -1;
	}
	return b;
}

int32_t WiredDevice::write(const uint8_t *b, const int32_t len) const {
	Wire.beginTransmission(deviceAddress);
	auto written = (int32_t) Wire.write(b, len);
	int16_t status = Wire.endTransmission();
	if (status > 0) {
		return (int32_t) -status;
	}
	return written;
}

int16_t WiredDevice::write(const uint8_t b) const {
	return (int16_t) write(&b, 1);
}