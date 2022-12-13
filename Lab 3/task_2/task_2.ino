// Arnav Mathur & Zack Martin
// Task 2 Plays the theme "Close encounters of the Third Kind"
// The notes are d4 e4 c4 c3 g3
#define d4 853  //293 hz
#define e4 760  //329 hz
#define c4 958  //261 hz
#define c3 1923 //130 hz
#define g3 1276 //196 hz
#define R 0 

#define BIT_3 1<<3 // digital pin 6

int melody[] = {d4, e4, c4, c3, g3, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R};
unsigned long pointerMillis;
unsigned long currentMillis;
int i;

void setup() {
  DDRH |= BIT_3; // digital pin 6
  TCNT4 = 0;
  i = 0;
  TCCR4A = 0b01000000;
  TCCR4B = 0b00001011;
}

void loop() {
  if (i == 25) {
    i = 0;
  }
  currentMillis = millis();
  pointer();
}

void pointer() {
  if(currentMillis - pointerMillis >= 200) {
    i++;
    OCR4A = melody[i];
    pointerMillis = currentMillis;
  }
}
