/* 
 Part1.4
 Blinks 3 off board LEDs at 333ms interval.
 Does not use pinMode or digitalWrite.
*/  
#define PORT_49 1<<0
#define PORT_48 1<<1
#define PORT_47 1<<2

void setup() {
    DDRL |= PORT_47;  // bit-wise OR 1<<2 to set pin to output mode
    DDRL |= PORT_48;  // bit-wise OR 1<<1 to set pin to output mode
    DDRL |= PORT_49;  // bit-wise OR 1<<0 to set pin to output mode
}

void loop() {  
  PORTL |= PORT_47; // set bit 2 to “1”
  delay(333);
  PORTL &= !PORT_47;  // clear bit 2
  
  PORTL |= PORT_48; // set bit 1 to “1”
  delay(333);
  PORTL &= !PORT_48;  // clear bit 1 
  
  PORTL |= PORT_49; // set bit 0 to “1”
  delay(333);
  PORTL &= !PORT_49;  // clear bit 0
}
