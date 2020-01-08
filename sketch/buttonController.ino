int buttonPin = 2;
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
  buttonState = digitalRead(buttonPin);
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
  int doublePress = pressCount >= 3;
  int singlePress = pressCount == 1;
  
  trackInputAmount();
  
  if (readButtonState() == HIGH && singlePress){
    int degree = calculate(40, 194, 350);
    adjustServo(degree);
  } else if (doublePress) {
    calibrateServo();
    pressCount = 0;
  }
}
