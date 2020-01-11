#include <Servo.h>

void setup() {
  Serial.begin(9600);
  turnOnLed();
  initializeButton();
  initializeServo();
  initializeSevSegDisplay();
}

void loop(){
    listenToInput();
}
