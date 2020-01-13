void initializeLaser(){
  int laserPin = 2;

  pinMode(laserPin, OUTPUT);
  digitalWrite(laserPin, HIGH);
}
