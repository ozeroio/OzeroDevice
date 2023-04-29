#include "WiredDevice.h"
#include <Wire.h>

WiredDevice::WiredDevice(const uint8_t deviceAddress) : deviceAddress(deviceAddress) {
	if (deviceAddress != OZEROIO_WIRE_NOT_VALID_ADDRESS) {
		Wire.begin();
	}
}

WiredDevice::WiredDevice(const uint8_t sdaPin, const uint8_t sclPin, const uint8_t deviceAddress) : deviceAddress(deviceAddress) {
	if (deviceAddress != OZEROIO_WIRE_NOT_VALID_ADDRESS) {
#ifdef CUSTOM_WIRE_PINS_SUPPORT_ENABLED
		Wire.begin(sdaPin, sclPin);
#else
		Wire.begin();
#endif
	}
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
	Wire.endTransmission();
	return v;
}

uint8_t WiredDevice::write(const uint8_t b) const {
	Wire.beginTransmission(deviceAddress);
	uint8_t v = Wire.write(b);
	Wire.endTransmission();
	return v;
}

uint32_t WiredDevice::write(const uint8_t *b, const uint32_t len) const {
	Wire.beginTransmission(deviceAddress);
	uint32_t v = Wire.write(b, len);
	Wire.endTransmission();
	return v;
}