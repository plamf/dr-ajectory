Servo servo;
int servoPin = 9;
int servoPosition = 90;

void initializeServo(){
  servo.attach(servoPin);
  calibrateServo();
}

void calibrateServo(){
  servo.write(90);
}

void rotateServo(int degree){
  servo.write(degree);
}

void reset(){
  if (readingState != buttonState) {
    buttonState = readingState;
    
    if(readingState == LOW){
      calibrateServo();
    }
  }
}

void set(int degree){
  if (readingState == LOW) {
    if(servo.read() != degree){
      rotateServo(degree);
    }
  }
}

void adjustForTarget(){
  int distance = getDistance();
  int degree = calculateProjectileTrajectory(distance, 0, 0);
  
  if (longPress) {
    reset();
  }else{
    set(degree);
  }
  lastButtonState = readingState;
}
