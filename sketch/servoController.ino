#include <Servo.h>

Servo servo;
int servoPin = 13;

void initializeServo(){
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