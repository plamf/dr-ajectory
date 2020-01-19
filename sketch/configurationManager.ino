/*
 * This sketch is used to handle all configurable variables and methods used by the Dr. Ajectory Configurator.
 * All variables are referenced as 'extern' where we need to access them.
 */

//*************** VARIABLES ****************
int iboRating = 300;
int additionalWeightOnBowstringInGrams = 0;
int lbsOfForce = 40;
int cmDrawlength = 194;
int arrowWeightGrains = 350;
//******************************************

//********** CONFIGURATIONCODES ************
//******************************************
 
const byte numChars = 32;
char receivedChars[numChars];   // an array to store the received data

boolean newData = false;

int dataNumber = 0;             // new for this version


 void recvWithEndMarker() {
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;
   
    if (Serial.available() > 0) {
        rc = Serial.read();

        if (rc != endMarker) {
            receivedChars[ndx] = rc;
            ndx++;
            if (ndx >= numChars) {
                ndx = numChars - 1;
            }
        }
        else {
            receivedChars[ndx] = '\0'; // terminate the string
            ndx = 0;
            newData = true;
        }
    }
}

void showNewNumber() {
    if (newData == true) {
        dataNumber = 0;             // new for this version
        dataNumber = atoi(receivedChars);   // new for this version
        additionalWeightOnBowstringInGrams = dataNumber;
        setDisplayNumber(additionalWeightOnBowstringInGrams);     // new for this version
        newData = false;
    }
}
