void setup() {
  Serial.begin(9600);
  initializeButton();
  initializeServo();
  initializeSevSegDisplay();
}

void loop(){
    turnOnDisplay();
    listenToInput();
}
