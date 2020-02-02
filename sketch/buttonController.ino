//************ CONFIG VARIABLES *************
extern int lbsOfForce;
extern int cmDrawlength;
extern int arrowWeightGrains;
//*******************************************

int buttonPin = A15;
int pressCount = 0;
int buttonState = 0; 
int lastButtonState = 0;

void initializeButton(){
  pinMode(buttonPin, INPUT); 
}

int readButtonState(){
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
  int triplePress = pressCount >= 3;
  
  trackInputAmount();
  
  if (singlePress){
    if(getDisplayNumber() == 0){
      requestMeasurement();
    }
  } else if (triplePress) {
    calibrateServo();
    setDisplayNumber(0);
    pressCount = 0;
  }
  handleIncomingData();
}
