#include <SoftwareSerial.h>

int rxPin = A5;
int txPin = A4;

SoftwareSerial SoftSerial = SoftwareSerial(rxPin, txPin);

void initializeSoftwareSerial() {
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  SoftSerial.begin(19200);
}

void requestMeasurement() {
  char autoMaticMode = 'D';

  SoftSerial.print(autoMaticMode);
}
