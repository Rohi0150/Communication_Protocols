#include "gpio.h"
#include "uart_r.h"
void setup() {
  uart_init();
}

void loop()
{
    tx_str1("UART");
    tx_char1('\n');
    delay_ms0(100);
}
