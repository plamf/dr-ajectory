#include <SevSeg.h>

SevSeg sevseg;
int displayNumber = 0;

void initializeSevSegDisplay() {
  byte numDigits = 3;
  byte digitPins[] = {12, 11, 10};
  byte segmentPins[] = {9, 7, 4, 5, 6, 8, 3}; // In order of segments a-b-c-d-e-f-g
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_ANODE;
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = false;
  bool disableDecPoint = true;

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros, disableDecPoint);
}

void setDisplayNumber(int number) {
  displayNumber = number;
}

int getDisplayNumber() {
  return displayNumber;
}

void updateDisplay() {
  sevseg.setNumber(displayNumber);
  sevseg.refreshDisplay();
}
