void setup(){
  Serial.begin(9600);
  initializeButton();
  initializeServo();
  initializeSevSegDisplay();
  initializeLaser();
}

void loop(){
    turnOnDisplay();
    listenToInput();
}
