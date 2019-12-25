#include <Servo.h>

int ledPin = 2;
int buttonPin = 3;
int buttonValue = 0;

Servo servo;
int servoPin = 9;
int servoPosition = 0;

void setup() {
  turnOnLed();
  initializeButton();
  initializeServo();
}

void loop(){
  adjustForTarget();
}
