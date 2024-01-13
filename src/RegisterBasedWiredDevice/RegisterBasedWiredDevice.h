/**
 * Ozeroio -  Register Based Wire Device
 *
 * RegisterBasedWiredDevice.h
 *
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef OZERO_DEVICE_REGISTER_BASED_WIRED_DEVICE_H
#define OZERO_DEVICE_REGISTER_BASED_WIRED_DEVICE_H 1

#include <RegisterBasedDevice/RegisterBasedDevice.h>
#include <WiredDevice/WiredDevice.h>

class RegisterBasedWiredDevice : public RegisterBasedDevice, public WiredDevice {

	static const uint8_t MAX_RETRIES_ON_READING = 0x7f;

public:
	/**
	 * Public constructor
	 *
	 * @param deviceAddress       The wire address.
	 */
	explicit RegisterBasedWiredDevice(uint8_t deviceAddress);

	/**
	 * Reads values from the device, starting by the reg register.
	 *
	 * @param reg           The register number.
	 * @param buf           The buffer where to place read bytes.
	 *                      MSB become LSB inside buffer.
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
	int32_t readRegisterBlock(uint8_t reg, uint8_t *buf, int32_t len) override;

	/**
	 * Writes a sequence of values to a sequence of registers, starting by the reg address.
	 *
	 * @param reg           The register number.
	 * @param buf           The buffer.
	 * @param len           Buffer length.
	 * @return              If >= 0: How many bytes were written.
	 *                      If < 0: Error code:
	 *                          <ul>
	 *                          <li>-1:data too long to fit in transmit buffer</li>
	 *                          <li>-2:received NACK on transmit of address</li>
	 *                          <li>-3:received NACK on transmit of data</li>
	 *                          <li>-4:other error</li>
	 *                      </ul>
	 */
	int32_t writeRegisterBlock(uint8_t reg, uint8_t *buf, int32_t len) override;
};

#endif // OZERO_DEVICE_REGISTER_BASED_WIRED_DEVICE_H
