#include "EepromBasedWiredDevice.h"
#include <Arduino.h>
#include <Wire.h>

#ifndef BUFFER_LENGTH
#define BUFFER_LENGTH 32
#endif

EepromBasedWiredDevice::EepromBasedWiredDevice(const uint8_t sdaPin, const uint8_t sclPin, const uint8_t deviceAddress)
	: WiredDevice(sdaPin, sclPin, deviceAddress), addressSize(0), endianness(BIG_ENDIAN), writeCycleTime(WRITE_CYCLE_TIME_MILLS) {
}

EepromBasedWiredDevice::EepromBasedWiredDevice(const uint8_t deviceAddress)
	: WiredDevice(deviceAddress), addressSize(0), endianness(BIG_ENDIAN), writeCycleTime(WRITE_CYCLE_TIME_MILLS) {
}

int32_t EepromBasedWiredDevice::writeBlock(int32_t address, uint8_t *buf, int32_t len) {
	Wire.beginTransmission(getAddress());
	for (int8_t i = addressSize; i > 0; i--) {
		Wire.write((uint8_t) (address >> (i - 1) * 8));
	}
	int32_t written = Wire.write(buf, len);
	uint8_t eot = Wire.endTransmission();
	if (eot != 0) {
		return (int32_t) (-eot);
	}
	delayMicroseconds(writeCycleTime);
	return written;
}

int32_t EepromBasedWiredDevice::readBlock(const int32_t address, uint8_t *buf, int32_t len) {
	int8_t tries = MAX_RETRIES_ON_READING;
	int32_t i, last = len - 1;

	Wire.beginTransmission(getAddress());
	for (i = addressSize; i > 0; i--) {
		Wire.write((uint8_t) (address >> (i - 1) * 8));
	}
	int8_t status = Wire.endTransmission();
	if (status != 0) {
		return (int32_t) (-status);
	}
	delayMicroseconds(writeCycleTime);

	// Underling libraries use a small buffer for i2c read.
	// Also, some implementation use an uint8_t as len type.
	// So, to be safe, lets limit len to BUFFER_LENGTH
	if (len > BUFFER_LENGTH) {
		len = BUFFER_LENGTH;
	}

	Wire.requestFrom((int16_t) getAddress(), len);
	while (!Wire.available() && --tries > 0) {
		delayMicroseconds(RETRIES_DELAY_MICROS);
	}
	if (tries <= 0) {
		return (int32_t) (-TIMEOUT_ERROR_CODE);
	}
	for (i = 0; i < len && Wire.available(); i++) {
		int16_t r = Wire.read();
		if (r < 0) {
			break;
		}
		buf[(endianness == BIG_ENDIAN) ? last - i : i] = r & 0xff;
	}
	return i;
}

void EepromBasedWiredDevice::setAddressSize(const int8_t addressSize) {
	this->addressSize = addressSize;
}

void EepromBasedWiredDevice::setEndianness(const int8_t endianness) {
	this->endianness = endianness;
}

int8_t EepromBasedWiredDevice::getAddressSize() const {
	return addressSize;
}

void EepromBasedWiredDevice::setWriteCycleTime(const uint8_t writeCycleTime) {
	this->writeCycleTime = writeCycleTime;
}

uint8_t EepromBasedWiredDevice::getWriteCycleTime() const {
	return writeCycleTime;
}
