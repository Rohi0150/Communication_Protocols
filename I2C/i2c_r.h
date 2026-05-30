/* Bit banging I2C : 
 * SDA Pin : PK0
 * SCL Pin : PK1     */
//functions : 
void sda_low(void);
void sda_release(void);

void scl_low(void);
void scl_release(void);

void i2c_start(void);

void write_bit(int x);

char read_ack(void);

void transf_byte(char byte);

void i2c_stop(void);


void sda_low(){
  init_pin(K,OUT,0);
  out_pin(K,0,low);
} //SDA LINE GETS LOW

void sda_release(){
  init_pin(K, INP, 0);
  out_pin(K,0,high); //internal pull up 
} //SDA LINE GETS RELEASED 

void scl_low(){
  init_pin(K,OUT,1);
  out_pin(K,1,low);
} //SCL LINE GETS LOW

void scl_release(){
  init_pin(K, INP, 1);
  out_pin(K,1,high);
}//SDA LINE GETS RELEASED

//I2C START CONDITION  SDA->LOW WHILE SCL IS HIGH 
void i2c_start(){
  sda_release();
  scl_release();
  delay_ms0(10);
  
  sda_low();
  delay_ms0(10);
  
  scl_low();
  delay_ms0(10);
  }

//TRANSMITS A SINGLE BIT ON SDA LINE 
void write_bit(int x){
  if(x) sda_release();
  else sda_low();
  delay_ms0(1);
  
  scl_release();
  delay_ms0(1);

  scl_low();
  delay_ms0(1);
}

//READS ACK(0)/NACK(1) FROM THE SLAVE.. 
char read_ack(){
  sda_release();
  delay_ms0(1);

  scl_release();
  delay_ms0(1);

  char ack = in_pin(K, 0);
  scl_low();
  delay_ms0(1);
  return ack;
}
//TRANSMITS ONE FULL BYTE(MSB FIRST)
void transf_byte(char byyte){
  for(int i = 7 ;i>=0 ; i--){
    write_bit((byyte >> i) & 1);
    }
  }
//STOP CONDITION : SDA LOW-> HIGH WHILE SCL IS HIGH...
void i2c_stop()
{
    sda_low();        // ensure SDA is LOW
    delay_ms0(1);
    scl_release();    // bring SCL HIGH
    delay_ms0(1);
    sda_release();    // SDA LOW → HIGH while SCL HIGH = STOP
    delay_ms0(1);
}
