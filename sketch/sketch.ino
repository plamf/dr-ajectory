#include <Servo.h>

void setup() {
  Serial.begin(9600);
  initializeButton();
  initializeServo();
  initializeSevSegDisplay();
}

void loop(){
    listenToInput();
}
