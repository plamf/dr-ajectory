#include <Servo.h>

int ledPin = 2;
int buttonPin = 3;
int buttonValue = 0;

Servo servo;
int servoPin = 9;
int servoPosition = 90;

int readingState = 0;
int buttonState = HIGH;            
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0; 
unsigned long debounceDelay = 1000; 
  
boolean longPress = (millis() - lastDebounceTime) > debounceDelay;

void setup() {
  turnOnLed();
  initializeButton();
  initializeServo();
}

void loop(){
  readingState = readButtonState();
  
  adjustForTarget();
}
