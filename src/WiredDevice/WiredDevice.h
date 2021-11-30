/**
 * Ozeroio -  Wired Device
 *
 * WiredDevice.h
 *
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __OZEROIO_DEVICE_WIRED_DEVICE_H__
#define __OZEROIO_DEVICE_WIRED_DEVICE_H__ 1

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
  WiredDevice(uint8_t deviceAddress);

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
  uint8_t getDeviceAddress();

  /**
   * Sets the device address.
   *
   * @param address      The device address.
   */
  void setDeviceAddress(uint8_t deviceAddress);
};

#endif /* __OZEROIO_DEVICE_WIRED_DEVICE_H__ */
