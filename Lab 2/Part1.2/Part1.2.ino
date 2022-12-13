/* 
 Part1.2
 Blinks 3 off board LEDs at 333ms interval.
*/

void setup() {
  pinMode(47, OUTPUT);
  pinMode(48, OUTPUT); 
  pinMode(49, OUTPUT); 
}

void loop() {  
  digitalWrite(47, HIGH); // turn the LED on
  delay(333);             // wait for 333 ms
  digitalWrite(47, LOW);  // turn the LED off

  digitalWrite(48, HIGH); // turn the LED on
  delay(333);             // wait for 333 ms
  digitalWrite(48, LOW);  // turn the LED off

  digitalWrite(49, HIGH); // turn the LED on
  delay(333);             // wait for 333 ms
  digitalWrite(49, LOW);  // turn the LED off
}
