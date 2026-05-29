#include "spi_r.h"

void setup(){
    init_spi();   
}
void loop(){
  snd_slave(0xA5);
  delay_ms0(100);
}
