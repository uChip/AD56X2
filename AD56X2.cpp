/**************************************************************************/
/*! 
    @file     AD56X2.cpp
    @author   C. Schnarel
	@license  BSD (see license.txt)
	
    This is part of an Arduino library to interface with the Analog Devices
    AD56X2 series of Digital-to-Analog converters which are connected
    via the I2C bus.

    AD56X2 I2C device class file
    Based on Analog Devices datasheets for the following part numbers
        AD5602 (8-bit), AD5612 (10-bit), AD5622 (12-bit)
    These parts share a common programming interface

    (c) Copyright 2013 by Chip Schnarel <schnarel@hotmail.com>
    Updates should (hopefully) always be available at
        https://github.com/schnarel/AD56X2

	@section  HISTORY

    2013-Dec-24  - First release, C. Schnarel
*/
/**************************************************************************/

#include "AD56X2.h"

/** Default constructor, uses default I2C address.
 * @see AD56X2_ADDR_GND
 */
AD56X2::AD56X2() {
    devAddr = AD56X2_ADDR_GND;
}

/** Specific address constructor.
 * @param address I2C address
 * @see AD56X2_ADDR_GND
 * @see AD56X2_ADDR_FLT
 * @see AD56X2_ADDR_VCC
 */
AD56X2::AD56X2(uint8_t address) {
    devAddr = address;
}

/** Power on and prepare for general usage.
 * This device is ready to use automatically upon power-up. The DAC
 * register defaults at power up to zero.  The begin()
 * function sets these same values since a reset of the microcontroller
 * did not necessarily restart the device.
 */
bool AD56X2::begin() {
  return setOutputLevel((uint16_t) 0x00);	
}

/** Verify the I2C connection.
 * Make sure the device is connected and responds as expected.
 * @return true if connection is valid, false otherwise
 */
bool AD56X2::testConnection() {
    Wire.beginTransmission(devAddr);
    return (Wire.endTransmission() == 0);
}

/** Set DAC value
 * Valid range is 0x000 to 0xFFF for all parts.
 * For the AD5622 all 4096 steps are used.
 * For the AD5612 only 1024 steps are used. The two LSBs are not used.
 * (i.e. value & 0xFFC)
 * For the AD5602 only 256 steps are used. The four LSBs are not used.
 * (i.e. value & 0xFF0)
 */
bool AD56X2::setOutputLevel(uint16_t value) {
  Wire.beginTransmission(devAddr);
  uint8_t temp = (value >> 8 & 0x0F);
  Wire.write(temp);
  temp = (value & 0xFF);
  Wire.write(temp);
  return (Wire.endTransmission() == 0);
}
 
/** If a byte value is sent the value is automatically scaled.
 * Value is multiplied by 16 and sent to the DAC
 * resulting in 256 steps of 16 from 0 to 0xFF0.
 */
bool AD56X2::setOutputLevel(uint8_t value) {
  return setOutputLevel(uint16_t (value << 4));
}

/** Read the value from the DAC
 * 
 */
bool AD56X2::getOutputLevel(uint16_t *data) {
  if(Wire.requestFrom(devAddr, (uint8_t) 2) == 2) {
    ((char*)data)[1] = Wire.read();
    ((char*)data)[0] = Wire.read();
    return true;
  }
  return false;
}

/** Put the DAC into a low power state
 * Note: setting the output level returns the DAC
 * to the awake power state.
 * 
 */
bool AD56X2::powerDown(uint8_t mode) {
  uint16_t value;
  getOutputLevel(&value);

  Wire.beginTransmission(devAddr);
  uint8_t temp = ((value >> 8 & 0x0F) | mode);
  Wire.write(temp);
  temp = (value & 0xFF);
  Wire.write(temp);
  return (Wire.endTransmission() == 0);
}

/* End of AD56X2.cpp */