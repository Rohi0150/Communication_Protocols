/*
 * Bit-Banged SPI Driver for ATmega2560
 * SPI Mode 0 (CPOL = 0, CPHA = 0)
 *
 * PF0 -> CS
 * PF1 -> MOSI
 * PF2 -> MISO
 * PF3 -> SCLK
 */

//functions used:
void init_spi(void);

uint8_t spi_transfer(uint8_t tx_data);

void spi_cs_low(void);

void spi_cs_high(void);

//Clk high and low:
void sclk(){
  out_pin(F,3,high);
  delay_us0(1);
  out_pin(F,3,low);
}
/*this is a global variable after a full duplex communication
* check this register for the value form slave 
*/
uint8_t buf_rev = 0x00;

void sclk_high(){
  out_pin(F,3,high);
  delay_us0(1);
}
void sclk_low(){
  out_pin(F,3,low);
  delay_us0(1);
}
// Transmit and receive one byte
void transfb(char bytea){  
  uint8_t temp ;
  for(int i = 7 ; i>=0 ; i--){
    out_pin(F,1,(bytea>>i)&1);
    sclk_high();
    //Miso
    buf_rev >>=1;
    temp = in_pin(F,2) &1;
    buf_rev |= temp<<7;
    //end miso
    sclk_low();
  }
}
// Select slave and transfer data
void snd_slave(char bytess){
  out_pin(F,0,low); // cs = 0
  transfb(bytess);
  out_pin(F,0,high);
  delay_us0(1);
}
// Initialize SPI GPIO pins
void init_spi(){
  init_pin(F,OUT,0); //CS
  init_pin(F,OUT,1); // MOSI
  init_pin(F,INP,2); // MISO 
  init_pin(F,OUT,3);//CLK
  out_pin(F,3,low); //CLK ->Low (Idle)
  }
