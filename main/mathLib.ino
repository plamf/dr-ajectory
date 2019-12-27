double convertForceIntoNewtons(int pounds){
  double newtonsPerPound = 4.448;
  return pounds * newtonsPerPound;
}

double convertDrawLengthInToMeters(int centimeters){
  double drawLengthFactor = 2.5;
  return centimeters / drawLengthFactor / 100;
}

double convertProjectileMassIntoKilograms(int grains){
  double grainsPerKilogram = 15432;
  return grains / grainsPerKilogram;
}

double calculateVelocity(double force, double drawLength, double mass){
  //Todo: actual calculation
  return 0;
}

int getDistance(){
  //Todo: Determine distance to target in meters
  return 50;
}

int calculateProjectileTrajectory(int distance, int arrowWeight, int drawLength, int force){
  double F = convertForceIntoNewtons(force);
  double L = convertDrawLengthInToMeters(drawLength);
  double m = convertProjectileMassIntoKilograms(arrowWeight);
  double v = calculateVelocity(F, L, m);

  //Todo: actual calculation
  return 45;
}
