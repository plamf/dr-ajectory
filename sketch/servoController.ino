#include <Servo.h>

Servo servo;

void initializeServo(){
  int servoPin = 13;

  servo.attach(servoPin);
  calibrateServo();
}

void calibrateServo(){
  const int initialServoPosition = 90;
  servo.write(initialServoPosition);
}

void rotateServo(int degree){
  if(servo.read() != degree){
    servo.write(degree);
  }
}

void adjustAim(int displayDistance, double calculationDistance){
    int degree = calculate(lbsOfForce, cmDrawlength, arrowWeightGrains, calculationDistance);
    
    setDisplayNumber(displayDistance);
    rotateServo(degree);
}
