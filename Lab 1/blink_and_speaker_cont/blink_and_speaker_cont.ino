unsigned long blinkStartMillis;
unsigned long noteStartMillis;
unsigned long startMillis;
unsigned long currentMillis;
const unsigned long blinkPeriod = 200;
const unsigned long notePeriod = 4;
const unsigned long duration = 3000;
const byte blinkLedPin = 10;
const byte noteLedPin = 2;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(2, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  blinkStartMillis = millis();
  noteStartMillis = millis();
  startMillis = millis();
}

// the loop function runs over and over again forever
void loop() {
  currentMillis = millis();
  blink();
  note();
}

void blink()
{
  if (currentMillis - blinkStartMillis >= blinkPeriod)
  {
    digitalWrite(blinkLedPin, !digitalRead(blinkLedPin));
    blinkStartMillis = currentMillis;
  }
}

void note()
{
  if (currentMillis - noteStartMillis >= notePeriod && currentMillis - startMillis <= duration)
  {
    digitalWrite(noteLedPin, !digitalRead(noteLedPin));
    noteStartMillis = currentMillis;
  }
  else
  {
    digitalWrite(noteLedPin, LOW);
  }
}
