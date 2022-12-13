// Lab 2
// Part 4
// Uses a 8x8 LED board with a joystick to set LED position.
// Plays Mary had a little lamb in the background.

#define OP_DECODEMODE  8
#define OP_SCANLIMIT   10
#define OP_SHUTDOWN    11
#define OP_DISPLAYTEST 14
#define OP_INTENSITY   10

// Notes for Mary had a little lamb
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
// Stores the notes for the song
int melody[] = {e, R, d, R, c, R, d, R, e, R, e, R, e, R, R, R, d, R, d, R, d, R, R, R, e, R, g, R, g, R, R, R, e, R, d, R, c, R, d, R, e, R, e, R, e, R, R, R, e, R, d, R, d, R, e, R, d, R, c, R, c, R, R, R};

// Stores time
unsigned long pointerMillis;
unsigned long currentMillis;

//Transfers 1 SPI command to LED Matrix for given row
//Input: row - row in LED matrix
//       data - bit representation of LEDs in a given row; 1 indicates ON, 0 indicates OFF
void spiTransfer(volatile byte row, volatile byte data);

//Converts joystic data to correct ranges
void convert(int UD, int LR);

// Pin assignment
int DIN = 37;
int CS =  36;
int CLK = 35;
int UD = 0;
int LR = 0;
int UD_converted = 0;
int LR_converted = 0;

byte spidata[2]; //spi shift register uses 16 bits, 8 for ctrl and 8 for data

void setup(){
  pinMode(DIN, OUTPUT);
  pinMode(CS, OUTPUT);
  pinMode(CLK, OUTPUT);
  digitalWrite(CS, HIGH);
  
  spiTransfer(OP_DISPLAYTEST,0);
  spiTransfer(OP_SCANLIMIT,7);
  spiTransfer(OP_DECODEMODE,0);
  spiTransfer(OP_SHUTDOWN,1);

  DDRH |= BIT_3;
  TCNT4  = 0; // Resets the counter
  i = 0; // Counter for notes played
  TCCR4A = 0b01000000;   // Toggle OC4A on Compare Match.
  TCCR4B = 0b00001011;    // CTC mode and prescaler of 1024
}

void loop(){ 
  int j = 0;
  
  UD = analogRead(A1); // Up and down position
  LR = analogRead(A0); // Left and right position
  
  convert(UD, LR); // Adjust joystick position values to correct range for LED board
  spiTransfer(UD_converted, 1<<(7-LR_converted)); // set led to joystick position
  
  delay(1);
  
  for (j = 0; j < 8; j++){ //for each row, clear the LEDs
    spiTransfer(j, 0b00000000);
  }

  if (i >= 63) {
    i = 0;
  }
  currentMillis = millis();
  pointer();
}

void pointer() {
  if (currentMillis - pointerMillis >= 200)
  {
    i++;
    OCR4A = melody[i];
    pointerMillis = currentMillis;
  }
}

void convert(int UD, int LR) {
  UD_converted = UD / 95;
  LR_converted = LR / 95;
}


void spiTransfer(volatile byte opcode, volatile byte data){
  int offset = 0; //only 1 device
  int maxbytes = 2; //16 bits per SPI command
  
  for(int i = 0; i < maxbytes; i++) { //zero out spi data
    spidata[i] = (byte)0;
  }
  //load in spi data
  spidata[offset+1] = opcode+1;
  spidata[offset] = data;
  digitalWrite(CS, LOW); //
  for(int i=maxbytes;i>0;i--)
    shiftOut(DIN,CLK,MSBFIRST,spidata[i-1]); //shift out 1 byte of data starting with leftmost bit
  digitalWrite(CS,HIGH);
}
