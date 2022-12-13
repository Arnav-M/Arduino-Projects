/**   Scheduler_util.h.ino
 *   @file   Scheduler_util.h.ino
 *   @author Arnav Mathur & Zack Martin
 *   @date   29-May-2022
 *   @brief  This file contains the utility functions for the scheduler
 *   
 *   This header file contains the scheduler that runs in this instance, 
 *   alongside some other helper methods such as sleep_474 and schedule_sync().
 */

 /**
 * @brief
 * Plays music and flashes the LED concurrently using a SRRI.
*/
void scheduler() {
  if(readytasks[task_index] == NULL && task_index != 0) {
    task_index = 0;
  }
  if(tasks[task_index] != SLEEPING) {
    (*readytasks[task_index])();
    task_index++;
  }
}

 /**
 * @brief 
 * Sets a task to sleep if called.
 * @param int t Time left for program to be asleep.
*/
void sleep_474(int t) {
  tasks[task_index] = SLEEPING;
  t = t-2;
}

 /**
 * @brief
 * Syncs the scheduler and updates the flag using an ISR.
 * Sets tasks to READY if they are SLEEPING.
*/
void schedule_sync() {
  while(sFlag != DONE) {
  }
  if(tasks[task_index] == SLEEPING) {
    tasks[task_index] = READY;
  }
  sFlag = PENDING;
  return;
}
