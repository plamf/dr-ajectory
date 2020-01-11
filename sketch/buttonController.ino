int buttonPin = A15;
int pressCount = 0;
int buttonState = 0; 
int lastButtonState = 0;

void initializeButton(){
  pinMode(buttonPin, INPUT); 
}

int readButtonState(){
/*
    Return values:
    LOW  = Button pressed
    HIGH = Button not pressed
  */    
  return digitalRead(buttonPin);
}

void trackInputAmount(){
  buttonState = readButtonState();
  
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      pressCount++;
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  
  lastButtonState = buttonState;
}

void listenToInput(){
  int singlePress = readButtonState() == HIGH && pressCount == 1;
  int doublePress = pressCount >= 3;
  
  trackInputAmount();
  
  if (singlePress){
    int degree = calculate(40, 194, 350);
    rotateServo(degree);
  } else if (doublePress) {
    calibrateServo();
    setDisplayNumber(0);
    pressCount = 0;
  }
}
