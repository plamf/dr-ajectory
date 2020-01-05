int buttonPin = 3;
int buttonValue = 0;
int readingState = 0;
int buttonState = HIGH;            
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0; 
unsigned long debounceDelay = 1000; 
  
boolean longPress = (millis() - lastDebounceTime) > debounceDelay;

void initializeButton(){
  pinMode(buttonPin, INPUT); 
}

void readButtonState(){
/*
    Return values:
    LOW  = Button pressed
    HIGH = Button not pressed
  */  
  int state = digitalRead(buttonPin);
  updateLastDebounceTime(state);
  
  readingState = state; 
}

void updateLastDebounceTime(int state){
  if (state != lastButtonState) {
    lastDebounceTime = millis();
  }
}
