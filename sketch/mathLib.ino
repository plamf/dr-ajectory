double convertForceIntoNewtons(int pounds){
  const double newtonsPerPound = 4.448;
  
  return pounds * newtonsPerPound;
}

double convertDrawLengthIntoInches(int centimeters){
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

double convertRadiansToDegrees(double radians){
  const double pi = 3.1415;
  
  return radians * (180 / pi);
}

double calculateAngle(double velocity, double distance){
  const double gravity = 9.81;

  double angleInRadians = asin((gravity * distance) / pow(velocity, 2));
  
  return convertRadiansToDegrees(angleInRadians);
}

double calculate(double lbsOfForce, double cmDrawlength, double arrowWeightGrains, double distance){
  double F = convertForceIntoNewtons(lbsOfForce);
  double L = convertDrawLengthIntoInches(cmDrawlength);
  double m = convertProjectileMassIntoKilograms(arrowWeightGrains);
  double v = calculateVelocity(F, L, m, iboRating, additionalWeightOnBowstringInGrams);
    
  return calculateAngle(v, distance);
}
