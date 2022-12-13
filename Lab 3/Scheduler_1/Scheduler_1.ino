/**Scheduler_1.ino
 * @file   Scheduler_1.ino
 *   @author    Arnav Mathur & Zack Martin
 *   @date      29-May-2022
 *   @brief   This file contains Scheduler 1
 *   
 *  This file use a Round Robin scheduler to flash an
 *  LED and also play a music theme at the same time.
 *  It contains task 1 & 2.
 */

// Light function variables
int index = 0;
unsigned long blinkMillis;
//unsigned long currentLightMillis;
unsigned long periods[] = {750, 250};
unsigned long currentMillis;

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

/**
 * The standard Arduino setup function used for setup and configuration tasks.
 */
void setup() {
  // put your setup code here, to run once:
  pinMode(23, OUTPUT);
  DDRH |= BIT_3; // digital pin 6
  TCNT4 = 0;
  i = 0;
  TCCR4A = 0b01000000;
  TCCR4B = 0b00001011;
}

/**
 * The standard Arduino loop function used for repeating tasks.
 */
void loop() {
  // put your main code here, to run repeatedly:
  //currentLightMillis = millis();
  //currentMusicMillis = millis();
  currentMillis = millis();
  while(1) {
    light();
    music();
    delayMicroseconds(500);
  }
}
