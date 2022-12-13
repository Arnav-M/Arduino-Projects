// Ports for part 1.4
#define PORT_49 1<<0
#define PORT_48 1<<1
#define PORT_47 1<<2

// Ports for part 2
#define BIT_3 1<<3

unsigned long currentMillis;
unsigned long lightsMillis;
unsigned long tasktimer;
unsigned long soundMillis;

void setup() {
  /* Setup for part 1.4 */
  DDRL |= PORT_47;  // bit-wise OR 1<<2 to set pin to output mode
  DDRL |= PORT_48;  // bit-wise OR 1<<1 to set pin to output mode
  DDRL |= PORT_49;  // bit-wise OR 1<<0 to set pin to output mode
  lightsMillis = millis();
  soundMillis = millis();
  tasktimer = millis();
  /* Setup for part 2 */
  DDRH |= BIT_3;
  TCNT4  = 0;
  TCCR4A = 0b01000000;   // Toggle OC4A on Compare Match.
  TCCR4B = 0b00001011;    // CTC mode and prescaler of 1024
}

void loop() {
  // put your main code here, to run repeatedly:
  currentMillis = millis();
  
  if(currentMillis - tasktimer <= 2000) {
      lights();
      PORTL &= !PORT_47;
  }
  else if(currentMillis - tasktimer >= 2000 && currentMillis - tasktimer <= 6000) {
    sound();
  }
  else if(currentMillis - tasktimer >= 7000 && currentMillis - tasktimer <= 17000) {
    lights();
    sound();
  }
  else {
    tasktimer = currentMillis;
  }
}

void lights() {
  if(currentMillis - lightsMillis <= 333) {
    PORTL |= PORT_47; // set bit 2 to “1”
  }
  if(currentMillis - lightsMillis >= 333) {
    PORTL &= !PORT_47;  // clear bit 2
    PORTL |= PORT_48; // set bit 1 to “1”
  }
  if(currentMillis - lightsMillis >= 666) {
     PORTL &= !PORT_48;  // clear bit 1 
     PORTL |= PORT_49; // set bit 0 to “1”
  }
  if(currentMillis - lightsMillis >= 999) {
     PORTL &= !PORT_49;  // clear bit 
     lightsMillis = currentMillis;
  }
}

  void sound() { 
  if(currentMillis - soundMillis < 1000) {
    OCR4A = (625);
  }
  else if((currentMillis - soundMillis >= 1000) && (currentMillis - soundMillis < 2000)) {
    OCR4A = (1000);
  }
  else if((currentMillis - soundMillis >= 2000) && (currentMillis - soundMillis < 3000)) {
    OCR4A = (312);
  }
  else if((currentMillis - soundMillis >= 3000) && (currentMillis - soundMillis < 4000)) {
    TCNT4 = 0;
    TCCR4A = 0b00000000;
  } 
  else {
    TCCR4A = 0b01000000;
    TCNT4 = 0;
    soundMillis = currentMillis;
  }
}
