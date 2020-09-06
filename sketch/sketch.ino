void setup() {
  Serial.begin(9200);
  initializeSoftwareSerial();
  initializeButton();
  initializeServo();
  initializeSevSegDisplay();
  initializeLaser();
}

void loop() {
  updateDisplay();
  listenToInput();
}
