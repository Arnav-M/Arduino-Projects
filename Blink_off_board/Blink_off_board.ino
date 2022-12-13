/* 
 Blink_off_board 
 Blinks off board LED at 200ms.
*/
void setup() {
  pinMode(10, OUTPUT);
}

void loop() {  
  digitalWrite(10, HIGH); // turn the LED on
  delay(200);             // wait for 200 ms
  digitalWrite(10, LOW);  // turn the LED off
}
