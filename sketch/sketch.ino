void setup(){
  Serial.begin(115200);
  initializeButton();
  initializeServo();
  initializeSevSegDisplay();
  initializeLaser();
}

void loop(){
    turnOnDisplay();
    listenToInput();
    
    handleIncomingData();
}
