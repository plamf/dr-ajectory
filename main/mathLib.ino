const int iboRating = 300; //not sure if this should be constant or configurable
int additionalWeightOnBowstringInGrams = 5;

double convertForceIntoNewtons(int pounds){
  double newtonsPerPound = 4.448;
  
  return pounds * newtonsPerPound;
}

double convertDrawLengthIntoMeters(int centimeters){
  double drawlengthFactor = 2.5;
  double centimetersPerInch = 2.54;
  double inches = centimeters / centimetersPerInch / drawlengthFactor;
  
  return inches;
}

double convertProjectileMassIntoKilograms(int grains){
  double grainsPerKilogram = 15432;
  
  return grains / grainsPerKilogram;
}

double calculateVelocity(double F, double L, double m, double R, double W){
  double feetPerSecond = R + (L - 30) * 10 - W / 3 + min(0, -(m - 5 * F) / 3);
  double metersPerSecond = feetPerSecond / 3.281;
  
  return metersPerSecond;
}

int getDistance(){
  //Todo: Determine distance to target in meters
  return 50;
}

int calculateProjectileTrajectory(double lbsOfForce, double cmDrawlength, double arrowWeightGrains){
  double F = convertForceIntoNewtons(lbsOfForce);
  double L = convertDrawLengthIntoMeters(cmDrawlength);
  double m = convertProjectileMassIntoKilograms(arrowWeightGrains);
  double v = calculateVelocity(F, L, m, iboRating, additionalWeightOnBowstringInGrams);

  //Todo: actual calculation
  return 45;
}
