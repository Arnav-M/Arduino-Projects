/**Scheduler_2.ino
 * @file   Scheduler_2.ino
 *   @author    Arnav Mathur & Zack Martin
 *   @date      29-May-2022
 *   @brief   This file contains Scheduler 2
 *   
 *  This file uses a Synchronized round robin scheduler with an ISR
 *  to generate a tick every 2ms which allows the light() and music() 
 *  functions to be synchronized. The tasks are stored in an array which
 *  are accessed by a pointer. 
 */

char TCNT2init = 130; 

// Light function variables
int index = 0;
unsigned long blinkMillis;
unsigned long currentMillis;
unsigned long periods[] = {750, 250};

#define NTASKS 4

//Define statements for Speaker
#define d4 853  //293 hz
#define e4 760  //329 hz
#define c4 958  //261 hz
#define c3 1923 //130 hz
#define g3 1276 //196 hz
#define R 0 
#define BIT_3 1<<3 // digital pin 6

// Music functions variables
//unsigned long currentMusicMillis;
unsigned long pointerMillis;
int i;
int melody[] = {d4, e4, c4, c3, g3, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R};

// Global variables
int task_index;
volatile int sFlag;
void (*readytasks[NTASKS])();

// stores the state of each task
int tasks[] = {0, 0};

//Define statements for SSRI and DDR
#define NTASKS 3
#define READY 0
#define RUNNING 1
#define SLEEPING 2
#define PENDING 0
#define DONE 1

/**
 * The standard Arduino setup function used for setup and configuration tasks.
 */
void setup() {
  // put your setup code here, to run once:
  TCCR2B = 0x00;
  TCCR2B |= (1<<CS22) | (1<<CS20); // Prescaler 128
  TCCR2B &= ~(1<<CS21); // CS22 = 1, CS21 = 0, CS20 = 1 -> prescale 128
  TIMSK2 |= (1<<TOIE2);
  
  pinMode(23, OUTPUT);
  DDRH |= BIT_3; // digital pin 6
  TCNT4 = 0;
  i = 0;
  TCCR4A = 0b01000000;
  TCCR4B = 0b00001011;
  
  readytasks[0] = light;
  readytasks[1] = music;
  readytasks[2] = schedule_sync;
  readytasks[3] = NULL; 
  task_index = 0;
}

/**
 * The standard Arduino loop function used for repeating tasks.
 */
void loop() {
  // put your main code here, to run repeatedly:
  currentMillis = millis();
  //currentMusicMillis = millis();
  while(1) {
    scheduler();
    delayMicroseconds(500);
  }
}

ISR(TIMER2_OVF_vect) {
  TCNT2 = TCNT2init;
  sFlag = DONE;
}
