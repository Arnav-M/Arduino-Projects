/**   7seg.h.ino
 *   @file   7seg.h.ino
 *   @author Arnav Mathur & Zack Martin
 *   @date   29-May-2022
 *   @brief  This file contains the 7 seg display.
 *   
 *  This header file sets up the entire 7 segment display.
 */

void seven_seg() {
  if(count <= 4 && count > 0) {
    count--;
  }
  else if(count == 0) {
    count = 293;
  }
  else if(count == 293) {
    count = 329;
  }
  else if(count == 329) {
    count = 260;
  }
  else if(count == 260) {
    count = 130;
  }
  else if(count == 130) {
    count = 196;
  }
  else {
    count = 3;
  }
  delay(1000);  // wait 200 milliseconds
}

ISR(TIMER1_OVF_vect)   // Timer1 interrupt service routine (ISR)
{
  disp_off();  // turn off the display

  switch (current_digit)
  {
    case 1:
      disp(count / 1000);   // prepare to display digit 1 (most left)
      digitalWrite(Dig1, LOW);  // turn on digit 1
      break;

    case 2:
      disp( (count / 100) % 10);   // prepare to display digit 2
      digitalWrite(Dig2, LOW);     // turn on digit 2
      break;

    case 3:
      disp( (count / 10) % 10);   // prepare to display digit 3
      digitalWrite(Dig3, LOW);    // turn on digit 3
      break;
    case 4:
      disp(count % 10);   // prepare to display digit 4 (most right)
      digitalWrite(Dig4, LOW);  // turn on digit 4
  }

  current_digit = (current_digit % 4) + 1;
}
void disp(byte number)
{
  switch (number)
  {
    case 0:  // print 0
      digitalWrite(SegA, HIGH);
      digitalWrite(SegB, HIGH);
      digitalWrite(SegC, HIGH);
      digitalWrite(SegD, HIGH);
      digitalWrite(SegE, HIGH);
      digitalWrite(SegF, HIGH);
      digitalWrite(SegG, LOW);
      break;

    case 1:  // print 1
      digitalWrite(SegA, LOW);
      digitalWrite(SegB, HIGH);
      digitalWrite(SegC, HIGH);
      digitalWrite(SegD, LOW);
      digitalWrite(SegE, LOW);
      digitalWrite(SegF, LOW);
      digitalWrite(SegG, LOW);
      break;

    case 2:  // print 2
      digitalWrite(SegA, HIGH);
      digitalWrite(SegB, HIGH);
      digitalWrite(SegC, LOW);
      digitalWrite(SegD, HIGH);
      digitalWrite(SegE, HIGH);
      digitalWrite(SegF, LOW);
      digitalWrite(SegG, HIGH);
      break;

    case 3:  // print 3
      digitalWrite(SegA, HIGH);
      digitalWrite(SegB, HIGH);
      digitalWrite(SegC, HIGH);
      digitalWrite(SegD, HIGH);
      digitalWrite(SegE, LOW);
      digitalWrite(SegF, LOW);
      digitalWrite(SegG, HIGH);
      break;

    case 4:  // print 4
      digitalWrite(SegA, LOW);
      digitalWrite(SegB, HIGH);
      digitalWrite(SegC, HIGH);
      digitalWrite(SegD, LOW);
      digitalWrite(SegE, LOW);
      digitalWrite(SegF, HIGH);
      digitalWrite(SegG, HIGH);
      break;

    case 5:  // print 5
      digitalWrite(SegA, HIGH);
      digitalWrite(SegB, LOW);
      digitalWrite(SegC, HIGH);
      digitalWrite(SegD, HIGH);
      digitalWrite(SegE, LOW);
      digitalWrite(SegF, HIGH);
      digitalWrite(SegG, HIGH);
      break;

    case 6:  // print 6
      digitalWrite(SegA, HIGH);
      digitalWrite(SegB, LOW);
      digitalWrite(SegC, HIGH);
      digitalWrite(SegD, HIGH);
      digitalWrite(SegE, HIGH);
      digitalWrite(SegF, HIGH);
      digitalWrite(SegG, HIGH);
      break;
    
    case 7:  // print 7
      digitalWrite(SegA, HIGH);
      digitalWrite(SegB, HIGH);
      digitalWrite(SegC, HIGH);
      digitalWrite(SegD, LOW);
      digitalWrite(SegE, LOW);
      digitalWrite(SegF, LOW);
      digitalWrite(SegG, LOW);
      break;

    case 8:  // print 8
      digitalWrite(SegA, HIGH);
      digitalWrite(SegB, HIGH);
      digitalWrite(SegC, HIGH);
      digitalWrite(SegD, HIGH);
      digitalWrite(SegE, HIGH);
      digitalWrite(SegF, HIGH);
      digitalWrite(SegG, HIGH);
      break;

    case 9:  // print 9
      digitalWrite(SegA, HIGH);
      digitalWrite(SegB, HIGH);
      digitalWrite(SegC, HIGH);
      digitalWrite(SegD, LOW);
      digitalWrite(SegE, LOW);
      digitalWrite(SegF, HIGH);
      digitalWrite(SegG, HIGH);
      break;
  }
}

void disp_off()
{
   digitalWrite(Dig1, HIGH);
   digitalWrite(Dig2, HIGH);
   digitalWrite(Dig3, HIGH);
   digitalWrite(Dig4, HIGH);
}
