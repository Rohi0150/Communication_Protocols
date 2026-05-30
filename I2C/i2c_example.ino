#include "gpio.h"
#include "i2c_r.h"

void setup() { 
  sda_release();
  scl_release();
}

void loop()
{
  i2c_start();
  transf_byte(0x27 << 1);   // address byte = 0x4E
  char ack = read_ack(); // not used in this case can be checked if ack is received or not    
  i2c_stop();
  delay_ms0(100);
}
