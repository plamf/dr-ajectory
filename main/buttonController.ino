void initializeButton(){
  pinMode(buttonPin, INPUT); 
}

int readButtonState(){
/*
    Return values:
    LOW  = Button pressed
    HIGH = Button not pressed
  */  
  int state = digitalRead(buttonPin);
  updateLastDebounceTime(state);
  
  return state; 
}

void updateLastDebounceTime(int state){
  if (state != lastButtonState) {
    lastDebounceTime = millis();
  }
}
