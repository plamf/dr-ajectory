/*
 * This sketch is used to handle all configurable variables and methods used by the Dr. Ajectory Configurator.
 * Recommended reading about best-practices for communicating over serial ports: https://forum.arduino.cc/index.php?topic=396450.0
 * Note that you will have to change the corresponding variables/commands in the Dr. Ajectory Configurator if
 * you change them here and vice versa.
 * 
 * 1) COMMANDS:
 * We use single characters to communicate in order to minimize bandwidth usage and
 * maximize transferspeed over the serial port.
 * 
 * 2) CONFIG-VARIABLES:
 * These variables can be changed by using the Dr. Ajectory Configurator GUI.
 * All variables are referenced again as 'extern' where we need to access them.
 * 
 */

//*************** COMMANDS *****************
// I = sets iboRating
// A = sets additionalWeightOnBowstringInGrams
// L = sets lbsOfForce
// C = sets cmDrawlength
// W = sets arrowWeightGrains
//******************************************

//*********** CONFIG-VARIABLES *************
int iboRating = 300;
int additionalWeightOnBowstringInGrams = 0;
int lbsOfForce = 40;
int cmDrawlength = 194;
int arrowWeightGrains = 350;
//******************************************

const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];
char messageFromPC[numChars] = {0};
int integerFromPC = 0;
float floatFromPC = 0.0;
boolean newData = false;

void listenOnSerialPort() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

void parseData() {      // split the data into its parts

    char * strtokIndx; // this is used by strtok() as an index

    strtokIndx = strtok(NULL,",");
    iboRating = atoi(strtokIndx); 
 
    strtokIndx = strtok(NULL, ",");
    additionalWeightOnBowstringInGrams = atoi(strtokIndx); 
 
    strtokIndx = strtok(NULL, ",");
    lbsOfForce = atoi(strtokIndx); 
 
    strtokIndx = strtok(NULL, ",");
    cmDrawlength = atoi(strtokIndx); 
 
    strtokIndx = strtok(NULL, ",");
    arrowWeightGrains = atoi(strtokIndx);     

}

void setVariables() {
    setDisplayNumber(lbsOfForce);
}

void handleIncomingData(){
      listenOnSerialPort();
    if (newData == true) {
        strcpy(tempChars, receivedChars);
            // this temporary copy is necessary to protect the original data
            //   because strtok() used in parseData() replaces the commas with \0
        parseData();
        setVariables();
        newData = false;
    }
}
