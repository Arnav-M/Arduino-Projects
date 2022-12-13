/*
  Blink
  Blinks on board LED, then speaker clicks and finally blinks off board LED.
*/
int speaker = 2;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(speaker, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);  // turn the LED off

  digitalWrite(speaker, HIGH); 
  delay(200);
  digitalWrite(speaker, LOW);

  digitalWrite(10, HIGH);
  delay(200);
  digitalWrite(10, LOW);

  digitalWrite(speaker, HIGH); 
  delay(200);
  digitalWrite(speaker, LOW);
}
