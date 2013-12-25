// Include libraries this sketch will use
#include  <Wire.h>
#include  <AD56X2.h>

// Instantiate objects used in this project
AD56X2 theDAC;

void setup() {
  Wire.begin();
  TWBR = 12;  // 400 kHz (maximum)

  theDAC.begin();
  
}

void loop() {
  static uint16_t  i;
  
  theDAC.setOutputLevel(i++);
}