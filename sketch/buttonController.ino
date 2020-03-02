int buttonPin = A0;
int pressCount = 0;
int buttonState = 0;
int lastButtonState = 0;

void initializeButton() {
  pinMode(buttonPin, INPUT_PULLUP);
  digitalWrite(buttonPin, HIGH);
}

int readButtonState() {
  return digitalRead(buttonPin);
}

void trackInputAmount() {
  buttonState = readButtonState();

  if (buttonState != lastButtonState) {
    if (buttonState == LOW) {
      pressCount++;
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }

  lastButtonState = buttonState;
}

void listenToInput() {
  int singlePress = readButtonState() == LOW && pressCount == 1;
  int triplePress = pressCount >= 3;

  trackInputAmount();

  if (singlePress) {
    if (getDisplayNumber() == 0) {
      requestMeasurement();
    }
    //Serial.print(" - Pressed - ");
  } else if (triplePress) {
    calibrateServo();
    setDisplayNumber(0);
    pressCount = 0;
   // Serial.print(" - Triple Pressed - ");
  }
  handleIncomingData();
}
