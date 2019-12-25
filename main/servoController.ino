void initializeServo(){
  servo.attach(servoPin);
}

void calibrateServo(){
  servo.write(0);
}

void rotateServo(int degree){
  servo.write(degree);
}

void adjustForTarget(){
  int distance = getDistance();
  int degree = calculateTrajectory(distance, 0, 0);
  
  buttonValue = readButtonState();
  if (buttonValue == LOW) {
    if(servo.read() != degree){
      rotateServo(degree);
    }
  }
}
