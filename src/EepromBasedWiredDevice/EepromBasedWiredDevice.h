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
#include <cstdint>

#define LITTLE_ENDIAN 0x00
#define BIG_ENDIAN    0x01

/**
 * EepromBasedWiredDevice represents a WiredDevice (i2c) that is has EEPROM finality.
 */
class EepromBasedWiredDevice : public WiredDevice {

  // Retries when reading eeprom.
  const static uint8_t MAX_RETRIES_ON_READING = 0x7f;

  // Time to sleep after unsuccessful read attempts.
  const static uint8_t RETRIES_DELAY_MICROS = 1;

  // Default write cycle time.
  const static uint8_t WRITE_CYCLE_TIME_MILLS = 5;

  // Timeout error code.
  const static int8_t TIMEOUT_ERROR_CODE = -5;

  // Depending on the size of the eeprom, it might have 1 or 2 bytes of address.
  int8_t addressSize;

  // Either one of LITTLE_ENDIAN or BIG_ENDIAN
  uint8_t endianness;

  // While timed write cycle all inputs are disabled during this write cycle and the
  // EEPROM will not respond until write is complete.
  uint8_t writeCycleTime;

public:

  /**
   * Public constructor for devices that support custom data and clock pins.
   *
   * @param sdaPin                The wire data pin.
   * @param sclPin                The wire clock pin.
   * @param deviceAddress         The wire address.
   */
  EepromBasedWiredDevice(uint8_t sdaPin, uint8_t sclPin, uint8_t deviceAddress);

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
   * Sets the address size.
   *
   * @param addressSize
   */
  void setAddressSize(int8_t addressSize);

  /**
   * Sets endianness.
   *
   * @param endianness
   */
  void setEndianness(int8_t endianness);

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
  void setWriteCycleTime(uint8_t writeCycleTime);

  /**
   * Gets the write cycle time.
   *
   * @returm writeCycleTime
   */
  uint8_t getWriteCycleTime() const;
};

#endif /* OZEROIO_DEVICE_EEPROM_BASED_WIRED_DEVICE_H */
