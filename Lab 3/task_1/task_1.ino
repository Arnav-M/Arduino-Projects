// Arnav Mathur & Zack Martin
// Task 1 flashes an external LED for 250ms every 1 second.

unsigned long blinkMillis;
unsigned long currentMillis;
unsigned long periods[] = {750, 250};
int index = 0;

void setup() {
  pinMode(23, OUTPUT);
}

void loop() {
  currentMillis = millis();
  if (currentMillis - blinkMillis >= periods[index]) {
    digitalWrite(23, !digitalRead(23));
    index++;
    index = index % 2;
    blinkMillis = currentMillis;
  }
}
