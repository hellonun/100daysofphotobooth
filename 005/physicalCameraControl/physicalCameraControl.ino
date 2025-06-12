const int pins[] = {2, 3, 4};
bool prevState[] = {HIGH, HIGH, HIGH};
int outputs[3] = {0, 0, 0};
bool justTriggered = false;

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(pins[i], INPUT_PULLUP);
  }
  Serial.begin(9600);
}

void loop() {
  bool triggered = false;

  for (int i = 0; i < 3; i++) {
    int currentState = digitalRead(pins[i]);

    if (prevState[i] == HIGH && currentState == LOW) {
      outputs[i] = 1;
      triggered = true;
    }

    prevState[i] = currentState;
  }

  if (triggered) {
    Serial.print(outputs[0]);
    Serial.print(",");
    Serial.print(outputs[1]);
    Serial.print(",");
    Serial.println(outputs[2]);
    justTriggered = true;
  } else if (justTriggered) {
    // Reset line to 0,0,0 after a trigger
    Serial.println("0,0,0");
    for (int i = 0; i < 3; i++) outputs[i] = 0;
    justTriggered = false;
  }

  delay(10); // debounce time
}
