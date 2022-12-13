/*
  Blink
  Blinks on board light at 200ms.
*/

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);  // turn the LED off
  delay(200);
}
