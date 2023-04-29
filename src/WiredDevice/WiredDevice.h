/**
 * Ozeroio -  Wired Device
 *
 * WiredDevice.h
 *
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef OZEROIO_DEVICE_WIRED_DEVICE_H
#define OZEROIO_DEVICE_WIRED_DEVICE_H 1

#include <stdint.h>

class WiredDevice {

	// Device address (only 7 LSB).
	uint8_t deviceAddress;

public:
	/**
	 * Public constructor
	 *
	 * @param address       The i2c device address.
	 */
	explicit WiredDevice(uint8_t deviceAddress);

	/**
	 * Public constructor for esp8266 device.
	 *
	 * NOTE: Only for devices that support custom data and clock pins.
	 *
	 * @param sdaPin        The wire data pin.
	 * @param sclPin        The wire clock pin.
	 * @param address       The i2c device address.
	 */
	WiredDevice(uint8_t sdaPin, uint8_t sclPin, uint8_t deviceAddress);

	/**
	 * Gets the device address.
	 *
	 * @return address
	 */
	uint8_t getAddress() const;

	/**
	 * Sets the device address.
	 *
	 * @param address      The device address.
	 */
	void setAddress(uint8_t deviceAddress);

	/**
	 * Reads the amount of available bytes of the device.
	 *
	 * @return
	 */
	uint32_t available();

	/**
	 * Reads a byte from the device.
	 *
	 * @return -1 if not able to communicate with device, byte otherwise.
	 */
	int16_t read() const;

	/**
	 * Writes a byte to the device.
	 *
	 * @param b
	 * @return 0 if not able to write, > 0 otherwise.
	 */
	uint8_t write(uint8_t b) const;

	/**
	 * Writes len bytes to the device.
	 *
	 * @param b
	 * @return len of written bytes.
	 */
	uint32_t write(const uint8_t *b, uint32_t len) const;
};

#endif /* OZEROIO_DEVICE_WIRED_DEVICE_H */
