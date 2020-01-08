Servo servo;
int servoPin = 9;

void initializeServo(){
  servo.attach(servoPin);
  calibrateServo();
}

void calibrateServo(){
  const int initialServoPosition = 90;
  servo.write(initialServoPosition);
}

void rotateServo(int degree){
  servo.write(degree);
}

void adjustServo(int degree){
    if(servo.read() != degree){
      rotateServo(degree);
  }
}
