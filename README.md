AD56X2 Digital-to-Analog Converter Library
===============

This is an Arduino library for interfacing to Analog Devices AD56X2 series of DACs.  The following devices are supported.

    AD5602	8-bit
    AD5612	10-bit
    AD5622	12-bit

The DACs communicate over the I2C bus.  This library uses the Arduino Wire.h library for that communication.

The devices support three power down modes which reduce current consumption to a couple hundred nano amps.

This code is (c) copyright 2013, C. Schnarel.  See the attached license.txt file for distribution and derivative permissions.
