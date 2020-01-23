/*
 * This sketch is used to handle all configurable variables and methods used by the Dr. Ajectory Configurator.
 * Recommended reading about best-practices for communicating over serial ports: https://forum.arduino.cc/index.php?topic=396450.0
 * Note that you will have to change the corresponding variables/commands in the Dr. Ajectory Configurator if
 * you change them here and vice versa.
 * 
 * 1) COMMUNICATION-FLAGS:
 * We use single characters/numbers to communicate in order to minimize bandwidth usage and
 * maximize transferspeed over the serial port.
 * Example: Serial.print('O'); signals to the configurator than an operation was successful.
 * 
 * 2) CONFIG-VARIABLES:
 * These variables can be changed by using the Dr. Ajectory Configurator GUI.
 * All variables are referenced again as 'extern' where we need to access them.
 * 
 */

//********* COMMUNICATION-FLAGS ************
// O = OK Result
//******************************************

//*********** CONFIG-VARIABLES *************
int iboRating = 0;
int additionalWeightOnBowstringInGrams = 0;
int lbsOfForce = 0;
int cmDrawlength = 0;
int arrowWeightGrains = 0;
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
                receivedChars[ndx] = '\0';
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

void parseData() {
    char * strtokIndx;

    strtokIndx = strtok(tempChars,",");
    iboRating = atoi(strtokIndx); 
 
    strtokIndx = strtok(NULL, ",");
    additionalWeightOnBowstringInGrams = atoi(strtokIndx); 
 
    strtokIndx = strtok(NULL, ",");
    lbsOfForce = atoi(strtokIndx); 
 
    strtokIndx = strtok(NULL, ",");
    cmDrawlength = atoi(strtokIndx); 
 
    strtokIndx = strtok(NULL, ",");
    arrowWeightGrains = atoi(strtokIndx); 
    
    Serial.print('O');
}

void handleIncomingData(){
    listenOnSerialPort();
    
    if (newData == true) {
        strcpy(tempChars, receivedChars);
        parseData();
        newData = false;
    }
}
