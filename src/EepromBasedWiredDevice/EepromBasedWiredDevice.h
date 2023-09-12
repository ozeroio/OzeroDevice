/**
 * Ozeroio -  Register Based Wire Device
 *
 * RegisterBasedWireDevice.h
 *
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef OZEROIO_DEVICE_EEPROM_BASED_WIRED_DEVICE_H
#define OZEROIO_DEVICE_EEPROM_BASED_WIRED_DEVICE_H 1

#include <WiredDevice/WiredDevice.h>
#include <stdint.h>

/**
 * EepromBasedWiredDevice represents a WiredDevice (i2c) that is has EEPROM finality.
 */
class EepromBasedWiredDevice : public WiredDevice {

	// Retries when reading eeprom.
	const static uint8_t MAX_RETRIES_ON_READING = 0x7f;

	// Time to sleep after unsuccessful read attempts.
	const static uint8_t RETRIES_DELAY_MICROS = 100;

	// Default address size
	const static uint16_t DEFAULT_ADDRESS_SIZE = 2;

	// Default write cycle time.
	const static uint16_t WRITE_CYCLE_TIME_MICROS = 5000;

	// Timeout error code.
	const static int8_t TIMEOUT_ERROR_CODE = -5;

	// Depending on the size of the eeprom, it might have 1 or 2 bytes of address.
	int8_t addressSize;

	// While timed write cycle all inputs are disabled during this write cycle and the
	// EEPROM will not respond until write is complete.
	uint16_t writeCycleTime;

public:
	/**
	 * Public constructor.
	 *
	 * @param deviceAddress         The wire address.
	 */
	explicit EepromBasedWiredDevice(uint8_t deviceAddress);

	/**
	 * Virtual destructor;
	 */
	virtual ~EepromBasedWiredDevice() = default;

	/**
	 * Writes a block of bytes into the device.
	 *
	 * @param address         The address into the buffer with start be placed.
	 * @param buf             The array of bytes to write into the device.
	 * @param len             The length of the buffer.
	 * @return                If >= 0: How many bytes were written.
	 *                        If < 0: Error code:
	 *                            <ul>
	 *                            <li>-1:data too long to fit in transmit buffer</li>
	 *                            <li>-2:received NACK on transmit of address</li>
	 *                            <li>-3:received NACK on transmit of data</li>
	 *                            <li>-4:other error</li>
	 *                        </ul>
	 */
	virtual int32_t writeBlock(int32_t address, uint8_t *buf, int32_t len);

	/**
	 * Reads a block of bytes from the device.
	 *
	 * Sends the address MSB fist.
	 *
	 * @param address       The register address.
	 * @param buf           The buffer where to place read bytes.
	 * @param len           How many bytes to read.
	 * @return              If >= 0: How many bytes were read.
	 *                      If < 0: Error code:
	 *                      <ul>
	 *                          <li>-1: data too long to fit in transmit buffer</li>
	 *                          <li>-2: received NACK on transmit of address</li>
	 *                          <li>-3: received NACK on transmit of data</li>
	 *                          <li>-4: other error</li>
	 *                          <li>-5: timeout</li>
	 *                      </ul>
	 */
	virtual int32_t readBlock(int32_t address, uint8_t *buf, int32_t len);

	/**
	 * Override when using multiple eeprom on the same bus and willing to dynamically switch
	 * between them using the address pointer.
	 *
	 *  It will combine the deviceAddress and the memoryAddress to determine the final deviceAddress.
	 *
	 * Some devices like 24x08 use the hardware address (deviceAddress) to internally address memory.
	 * So, to be able to access the entire device we must configure the deviceAddress byte.
	 *
	 * @returm addressSize
	 */
	virtual uint8_t dynamicAddress(int32_t memoryAddress) const;

	/**
	 * Sets the address size.
	 *
	 * @param addressSize
	 */
	void setAddressSize(int8_t addressSize);

	/**
	 * Gets the address size.
	 *
	 * @returm addressSize
	 */
	int8_t getAddressSize() const;

	/**
	 * Sets the write cycle time.
	 *
	 * @param writeCycleTime
	 */
	void setWriteCycleTime(uint16_t writeCycleTime);

	/**
	 * Gets the write cycle time.
	 *
	 * @returm writeCycleTime
	 */
	uint16_t getWriteCycleTime() const;
};

#endif // OZEROIO_DEVICE_EEPROM_BASED_WIRED_DEVICE_H
