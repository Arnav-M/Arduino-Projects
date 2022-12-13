/**   Light.h.ino
 *   @file   Light.h.ino
 *   @author Arnav Mathur & Zack Martin
 *   @date   29-May-2022
 *   @brief  This file contains the LED program.
 *   
 *  This header file contains light() which is a function that
 *  keeps an LED on for 250ms and off for 750ms.
 */
void light() {
  tasks[task_index] = RUNNING;
  if (currentMillis - blinkMillis >= periods[index]) {
    digitalWrite(23, !digitalRead(23));
    index++;
    index = index % 2;
    blinkMillis = currentMillis;
  }
}
