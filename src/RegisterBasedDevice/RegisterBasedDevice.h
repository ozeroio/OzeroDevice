/**
 * Ozeroio -  Register Based Device
 *
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef OZEROIO_DEVICE_REGISTER_BASED_DEVICE_H
#define OZEROIO_DEVICE_REGISTER_BASED_DEVICE_H 1

#include <stdint.h>

class RegisterBasedDevice {

public:

  /**
   * Public constructor
   *
   * @param address       The wire address.
   */
  RegisterBasedDevice();

  /**
   * Configures a register.
   *
   * @param reg           The register number.
   * @param mask          The mask to be used.
   * @param d             The value to be used.
   * @return              If >= 0: Success.
   *                      If < 0: Error (see specific implementation)
   */
  int16_t configureRegisterBits(uint8_t reg, uint8_t mask, uint8_t d);

  /**
   * Configures a register activating the bits.
   *
   * @param reg           The register number.
   * @param mask          The mask to be used.
   * @return              If >= 0: Success.
   *                      If < 0: Error (see specific implementation)
   */
  inline int16_t setRegisterBits(uint8_t reg, uint8_t mask) {
    return configureRegisterBits(reg, mask, 0xff);
  }

  /**
   * Configures a register clearing the bits.
   *
   * @param reg           The register number.
   * @param mask          The mask to be used.
   * @return              If >= 0: Success.
   *                      If < 0: Error (see specific implementation)
   */
  inline int16_t clearRegisterBits(uint8_t reg, uint8_t mask) {
    return configureRegisterBits(reg, mask, 0x00);
  }

  /**
   * Writes a value to a register.
   *
   * @param reg           The register number.
   * @param d             The value to be used.
   * @param d             The value to be used.
   * @return              If >= 0: Success.
   *                      If < 0: Error (see specific implementation)
   */
  int16_t writeRegister(uint8_t reg, uint8_t d);

  /**
   * Reads a value from a register.
   *
   * @param reg           The register number.
   * @return              If >= 0: The register value.
   *                      If < 0: Error (see specific implementation)
   */
  int16_t readRegister(uint8_t reg);

  /**
   * Reads values from the device, starting by the reg register.
   *
   * @param reg           The register number.
   * @param buf           The buffer where to place read bytes.
   *                      MSB become LSB inside buffer.
   * @param len           How many bytes to read.
   * @return              If >= 0: How many bytes were read.
   *                      If < 0: Error (see specific implementation)
   */
  virtual int16_t readRegisterBlock(uint8_t reg, uint8_t *buf, int16_t len) = 0;

  /**
   * Writes a sequence of values to a sequence of registers, starting by the reg address.
   *
   * @param reg           The register number.
   * @param buf           The buffer.
   * @param len           Buffer length.
   * @return              If >= 0: The number of bytes written into the register block.
   *                      If < 0: Error (see specific implementation)
   */
  virtual int16_t writeRegisterBlock(uint8_t reg, uint8_t *buf, int16_t len) = 0;
};

#endif /* OZEROIO_DEVICE_REGISTER_BASED_DEVICE_H */
