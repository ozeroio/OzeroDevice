#include "EepromBasedWiredDevice.h"
#include <Arduino.h>
#include <Wire.h>

#ifndef I2C_BUFFER_LENGTH
#define I2C_BUFFER_LENGTH 32
#endif

EepromBasedWiredDevice::EepromBasedWiredDevice(const uint8_t deviceAddress)
	: WiredDevice(deviceAddress), addressSize(DEFAULT_ADDRESS_SIZE), writeCycleTime(WRITE_CYCLE_TIME_MICROS) {
}

int32_t EepromBasedWiredDevice::writeBlock(int32_t address, uint8_t *buf, int32_t len) {
	Wire.beginTransmission(dynamicAddress(address));
	for (int8_t i = addressSize; i > 0; i--) {
		Wire.write((uint8_t) (address >> (i - 1) * 8));
	}
	int32_t bufferSpace = I2C_BUFFER_LENGTH - addressSize;
	int32_t written = Wire.write(buf, ozero_min(bufferSpace, len));
	int16_t status = Wire.endTransmission();
	if (status > 0) {
		return (int32_t) -status;
	}
	delayMicroseconds(writeCycleTime);
	return written;
}

int32_t EepromBasedWiredDevice::readBlock(const int32_t address, uint8_t *buf, int32_t len) {
	int8_t tries = MAX_RETRIES_ON_READING;
	int32_t i;

	Wire.beginTransmission(dynamicAddress(address));
	for (i = ((int32_t) addressSize); i > 0; i--) {
		Wire.write((uint8_t) (address >> (i - 1) * 8));
	}
	int16_t status = Wire.endTransmission();
	if (status > 0) {
		return (int32_t) -status;
	}
	delayMicroseconds(writeCycleTime);

	// Underling libraries use a small buffer for i2c read.
	// Also, some implementation use an uint8_t as len type.
	// So, to be safe, lets limit len to BUFFER_LENGTH
	if (len > I2C_BUFFER_LENGTH) {
		len = I2C_BUFFER_LENGTH;
	}

	Wire.requestFrom((int16_t) dynamicAddress(address), len);
	while (Wire.available() == 0 && --tries > 0) {

		// This delay could be smaller than 1 millisecond, but being at least 1 millis
		// allows RTOS systems to yield to other threads while waiting, avoiding
		// unwanted and hard-to-debut watchdog resets.
		delay(RETRIES_DELAY_MILLIS);
	}
	if (tries <= 0) {
		return (int32_t) (-TIMEOUT_ERROR_CODE);
	}
	for (i = 0; i < len && Wire.available() > 0; i++) {
		int16_t r = Wire.read();
		if (r < 0) {
			break;
		}
		buf[i] = r & 0xff;
	}
	return i;
}

// The default behavior of dynamicAddress is to ignore its parameter and return deviceAddress.
// This means, the device address is not dictated by the memoryAddress param.
// Derived classes can use the memoryAddress to derive dynamicAddress by combining
// memoryAddress with deviceAddress. This is useful for memory modules that use the
// deviceAddress pins to index different parts of their internal addresses.
uint8_t EepromBasedWiredDevice::dynamicAddress(int32_t memoryAddress) const {
	return deviceAddress;
}

void EepromBasedWiredDevice::setAddressSize(const int8_t addressSize) {
	this->addressSize = addressSize;
}

int8_t EepromBasedWiredDevice::getAddressSize() const {
	return addressSize;
}

void EepromBasedWiredDevice::setWriteCycleTime(const uint16_t writeCycleTime) {
	this->writeCycleTime = writeCycleTime;
}

uint16_t EepromBasedWiredDevice::getWriteCycleTime() const {
	return writeCycleTime;
}