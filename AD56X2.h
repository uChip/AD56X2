/**************************************************************************/
/*! 
    @file     AD56X2.h
    @author   C. Schnarel
	@license  BSD (see license.txt)
	
    This is part of an Arduino library to interface with the Analog Devices
    AD56X2 series of Digital-to-Analog converters which are connected
    via the I2C bus.

    AD56X2 I2C device class header file
    Based on Analog Devices datasheets for the following part numbers
        AD5602 (8-bit), AD5612 (10-bit), AD5622 (12-bit)
    These parts share a common programming interface

    (c) Copyright 2013 by Chip Schnarel <schnarel@hotmail.com>
    Updates should (hopefully) always be available at
        https://github.com/uchip/AD56X2

	@section  HISTORY

    2013-Dec-24  - First release, C. Schnarel
*/
/**************************************************************************/

#ifndef _AD56X2_H_
#define _AD56X2_H_

#ifdef ARDUINO
    #if ARDUINO < 100
        #include "WProgram.h"
    #else
        #include "Arduino.h"
    #endif
#else
    #include "ArduinoWrapper.h"
#endif

#include <Wire.h>

// AD5602, AD5612 & AD5622 addresses are controlled by the ADDR pin
// The pin can be low (GND), high (VCC) or floating (FLT)
#define AD56X2_ADDR_GND		0x0F
#define AD56X2_ADDR_FLT		0x0E
#define AD56X2_ADDR_VCC		0x0C

// Power Down modes
#define AD56X2_PD_1K		0x10
#define AD56X2_PD_100K		0x20
#define AD56X2_PD_TS		0x30

class AD56X2 {
    public:
        AD56X2();
        AD56X2(uint8_t address);
        
        bool testConnection(void);

        // Initialize the DAC
        bool begin(void);

        // Start a conversion
        bool setOutputLevel(uint8_t value);
        bool setOutputLevel(uint16_t value);
        
        // Read the DAC register
        bool getOutputLevel(uint16_t *data);

        // Go to the low power state
        // Note: sending a new DAC value via setOutputLevel() brings the
        // DAC out of low power state
        bool powerDown(uint8_t mode);

    private:
        uint8_t devAddr;
};

#endif /* _AD56X2_H_ */
