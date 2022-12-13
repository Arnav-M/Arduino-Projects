/**   Music.h.ino
 *   @file   Music.h.ino
 *   @author Arnav Mathur & Zack Martin
 *   @date   29-May-2022
 *   @brief  This file contains the Music program.
 *   
 *  This header file contains music() which is a function that
 *  plays a song theme from "Close Encounters of the third kind"
 */

 /**
 * @brief
 * Plays the overall song makes use of the pointer() function which
 * allows it to play the  5 notes from the theme. It also has a gap of
 * 4 seconds between runs.
*/
void music() {
  TaskList[task_index].state = RUNNING;
  if (i == 25) {
    i = 0;
  }
  currentMillis = millis();
  pointer();
}

/**
 * @brief
 * Helper function to music(), plays one note for every 200ms.
 * The output is wired to a speaker on digital pin 6.
*/
void pointer() {
  if(currentMillis - pointerMillis >= 200) {
    i++;
    OCR4A = melody[i];
    pointerMillis = currentMillis;
  }
}
