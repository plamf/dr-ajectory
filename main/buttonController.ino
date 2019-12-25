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
