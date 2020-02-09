void setup() {
  Serial.begin(19200); //115200
  initializeButton();
  initializeServo();
  initializeSevSegDisplay();
  initializeLaser();
}

void loop() {
  turnOnDisplay();
  listenToInput();
}
