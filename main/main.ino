#include <Servo.h>

void setup() {
  turnOnLed();
  initializeButton();
  initializeServo();
}

void loop(){
  readButtonState();
  
  adjustForTarget();
}
