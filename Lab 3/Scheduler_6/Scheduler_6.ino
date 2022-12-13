/**Scheduler_4.ino
 * @file   Scheduler_4.ino
 *   @author    Arnav Mathur & Zack Martin
 *   @date      29-May-2022
 *   @brief   This file contains Scheduler 4
 *   
 *  This file uses a SSRI which makes use of an array to 
 *  store information about each task and also uses another array
 *  to keep track of whether a task is sleeping or active or dead. 
 *  Uses the LED, music() and the 7 segment display in a row. The
 *  segement 7 display counts up from 0 to 1000 and resets.
 */
//Define statements for SSRI and DDR
#define NTASKS 5
#define READY 0
#define RUNNING 1
#define SLEEPING 2
#define PENDING 0
#define DONE 1

// Define statements for Speaker
#define d4 853  //293 hz
#define e4 760  //329 hz
#define c4 958  //261 hz
#define c3 1923 //130 hz
#define g3 1276 //196 hz
#define R 0 
#define BIT_3 1<<3 // digital pin 6

// Define statements for 7seg
#define common_cathode 0
#define common_anode 1
#define SegA 11
#define SegB 7
#define SegC 4
#define SegD 2
#define SegE 13
#define SegF 10
#define SegG 5
#define Dig1 12
#define Dig2 9
#define Dig3 8
#define Dig4 22

// Global variables
int task_index;
volatile int sFlag;
void (*readytasks[NTASKS])();


// stores the state of each task
int tasks[] = {0, 0, 0};

// Light function variables
int index = 0;
unsigned long blinkMillis;
unsigned long currentMillis;
unsigned long periods[] = {750, 250};

// Music functions variables
unsigned long pointerMillis;
int i;
int melody[] = {R, R, R, R, d4, e4, c4, c3, g3, R, R, R, R, d4, e4, c4, c3, g3};

// 7seg function variables
byte current_digit;
int count = 10;

void setup() {
  // LED setup
  pinMode(23, OUTPUT);

  // Speaker setup
  DDRH |= BIT_3; // digital pin 6
  TCNT4 = 0;
  i = 0;
  TCCR4A = 0b01000000;
  TCCR4B = 0b00001011;

  // 7 segment displays
  pinMode(SegA, OUTPUT);
  pinMode(SegB, OUTPUT);
  pinMode(SegC, OUTPUT);
  pinMode(SegD, OUTPUT);
  pinMode(SegE, OUTPUT);
  pinMode(SegF, OUTPUT);
  pinMode(SegG, OUTPUT);
  pinMode(Dig1, OUTPUT);
  pinMode(Dig2, OUTPUT);
  pinMode(Dig3, OUTPUT);
  pinMode(Dig4, OUTPUT);

  disp_off();  // turn off the display

  // Timer1 module overflow interrupt configuration
  TCCR1A = 0;
  TCCR1B = 0b000000001;  // enable Timer1 with prescaler = 1 ( 16 ticks each 1 µs)
  TCNT1  = 0;  // set Timer1 preload value to 0 (reset)
  TIMSK1 = 1;  // enable Timer1 overflow interrupt

  // Array setup
  task_index = 0;
  count = 3;
}

void loop() {
  // put your main code here, to run repeatedly:
  currentMillis = millis();
  while(1) {
    light();
    music();
    delayMicroseconds(500);
  }
}
