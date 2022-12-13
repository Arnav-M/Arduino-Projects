#define c 958 // 261 Hz
#define d 850 // 294 Hz
#define e 760 // 329 Hz
#define f 716 // 349 Hz
#define g 638 // 392 Hz
#define a 568 // 440 Hz
#define b 507 // 493 Hz
#define C 478 // 523 Hz
#define R 0

#define BIT_3 1<<3

int i;
int melody[] = {e, R, d, R, c, R, d, R, e, R, e, R, e, R, R, R, d, R, d, R, d, R, R, R, e, R, g, R, g, R, R, R, e, R, d, R, c, R, d, R, e, R, e, R, e, R, R, R, e, R, d, R, d, R, e, R, d, R, c, R, c, R, R, R};
unsigned long pointerMillis;
unsigned long currentMillis;
int *p = melody;

void setup() {
  DDRH |= BIT_3;
  TCNT4  = 0;
  i = 0;
  TCCR4A = 0b01000000;   // Toggle OC4A on Compare Match.
  TCCR4B = 0b00001011;    // CTC mode and prescaler of 64
}

void loop() {
  if (i == 64) {
    i = 0;
  }
  currentMillis = millis();
  pointer(); 
}

void pointer()
{
  if (currentMillis - pointerMillis >= 200) {
    i++;
    OCR4A = melody[i];
    pointerMillis = currentMillis;
  }
}
