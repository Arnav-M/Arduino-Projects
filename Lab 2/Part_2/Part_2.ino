
// Lab 2
// Part 2
// Produces a square wave which is converted into sound on a speaker

#define BIT_3 1<<3

void setup (){
  DDRH |= BIT_3;
  TCNT4  = 0;
  TCCR4A = 0b01000000;   // Toggle OC4A on Compare Match.
  TCCR4B = 0b00001101;    // CTC mode and prescaler of 1024
}

void loop (){
    OCR4A = (35);
    delay(1000);
    OCR4A = (63);
    delay(1000);
    OCR4A = (20);
    delay(1000);
    TCNT4 = 0;

    // Adds one second delay
    TCCR4A = 0b00000000;
    delay(1000);
    TCCR4A = 0b01000000;
    TCNT4 = 0;
}
