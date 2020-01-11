const int iboRating = 300; //not sure if this should be constant or configurable
int additionalWeightOnBowstringInGrams = 5;

double convertForceIntoNewtons(int pounds){
  const double newtonsPerPound = 4.448;
  
  return pounds * newtonsPerPound;
}

double convertDrawLengthIntoMeters(int centimeters){
  const double drawlengthFactor = 2.5;
  const double centimetersPerInch = 2.54;
  
  double inches = centimeters / centimetersPerInch / drawlengthFactor;
  
  return inches;
}

double convertProjectileMassIntoKilograms(int grains){
  const double grainsPerKilogram = 15432;
  
  return grains / grainsPerKilogram;
}

double calculateVelocity(double F, double L, double m, double R, double W){
  const double feetPerMeter = 3.281;
  
  double feetPerSecond = R + (L - 30) * 10 - W / 3 + min(0, -(m - 5 * F) / 3);
  double metersPerSecond = feetPerSecond / feetPerMeter;
  
  return metersPerSecond;
}

int getDistance(){
  //Todo: Determine distance to target in meters
  int distance = 100;

  setDisplayNumber(distance);
  
  return distance;
}

double convertRadiansToDegrees(double radians){
  const double pi = 3.1415;
  
  return radians * (180 / pi);
}

double calculateAngle(double velocity){
  const double gravity = 9.81;

  double angleInRadians = asin((gravity * getDistance()) / pow(velocity, 2));
  
  return convertRadiansToDegrees(angleInRadians);
}

double calculate(double lbsOfForce, double cmDrawlength, double arrowWeightGrains){
  double F = convertForceIntoNewtons(lbsOfForce);
  double L = convertDrawLengthIntoMeters(cmDrawlength);
  double m = convertProjectileMassIntoKilograms(arrowWeightGrains);
  double v = calculateVelocity(F, L, m, iboRating, additionalWeightOnBowstringInGrams);
    
  return calculateAngle(v);
}
