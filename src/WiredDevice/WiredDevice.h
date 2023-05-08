/**
 * Ozeroio -  Wired Device
 *
 * WiredDevice.h
 *
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef OZEROIO_DEVICE_WIRED_DEVICE_H
#define OZEROIO_DEVICE_WIRED_DEVICE_H 1

#define OZEROIO_WIRE_NOT_VALID_ADDRESS 0xff

#include <ozero.h>
#include <stdint.h>

class WiredDevice {

protected:

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
	 * Reads bytes from the device.
	 *
	 * @return -1 if not able to communicate with device, read len otherwise.
	 */
	int32_t read(uint8_t *b, int32_t len) const;

	/**
	 * Reads a byte from the device.
	 *
	 * @return -1 if not able to communicate with device, byte otherwise.
	 */
	int16_t read() const;

	/**
	 * Writes len bytes to the device.
	 *
	 * @param b
	 * @return len of written bytes.
	 */
	int32_t write(const uint8_t *b, int32_t len) const;

	/**
	 * Writes a byte to the device.
	 *
	 * @param b
	 * @return 0 if not able to write, > 0 otherwise.
	 */
	int16_t write(uint8_t b) const;
};

#endif // OZEROIO_DEVICE_WIRED_DEVICE_H
