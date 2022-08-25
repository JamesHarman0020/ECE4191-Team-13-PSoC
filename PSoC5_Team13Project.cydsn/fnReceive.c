/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
// This file will interpret function calls that come over serial

#include "project.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include "SBT0811.h"
#include "IMU.h"
#include "SG90.h"
#include "TB9051.h"

void fnCall(int fn, float para2, float para3);

void RunFn(char * comString){
    ///// This interprets incoming serial as strings, trying to bypass that /////
    /*char *pEnd;
    
    int b = strlen(comString);
    for (int i = 0 ; i<b-1; i++) 
    { 
        if (comString[i] == 44) {
            comString[i] = 32;
        }
    }
    float para1 = strtof(comString, &pEnd);
    float para2 = strtof(pEnd, &pEnd);
    float para3 = strtof(pEnd, &pEnd);
    fnCall(para1, para2, para3);*/
    
    //char string[20]; sprintf(string, "%f, ", para1); UART_PutString(string);
    //sprintf(string, "%f, ", para2); UART_PutString(string);
    //sprintf(string, "%f\n", para3); UART_PutString(string);
}

void fnCall(int fn, float para2, float para3) {
    uint8 InterruptState = CyEnterCriticalSection();
    char string[20]; sprintf(string, "%i %.3f %.3f", fn, para2, para3); UART_PutString(string);
    CyExitCriticalSection(InterruptState);
    /*switch (fn) { 
        case 0: TB9051_VehMoveTo(para2,para3);          break; // Motor Commands
        case 1: TB9051_Begin();                         break;
        case 2: TB9051_Forward((int)para2,(int)para3);  break;
        case 3: TB9051_Reverse((int)para2,(int)para3);  break;
        case 4: TB9051_Brake((int)para2);               break;
        case 5: TB9051_VehForward((int)para2);          break;
        case 6: TB9051_VehReverse((int)para2);          break;
        case 7: TB9051_VehBrake();                      break;
        case 50: oneStepCCW((int)para2);                break; // Stepper Commands
        case 51: oneStepCW((int)para2);                 break;
        case 52: moveAngle(para2);                      break;
        case 60: SG90_Begin();                          break; // Servo Commands
        case 61: SG90_ToAngle(para2);                   break;
        case 200: LIS3MDL_Begin();                      break; // Accelerometer
        case 201: LIS3MDL_MasterStatus();               break;
        case 202: LIS3MDL_TransferByte();               break;
        case 203: LIS3MDL_TransferMultipleBytes();      break;
        //case 204: LIS3MDL_ReadAxisRaw(uint8 * (&para2))); TO-DO; break;
        //case 205: LIS3MDL_ReadAxisDeg(uint16_t * (&para2))); TO-DO; break;
        //case 206: LIS3MDL_ReadMultipleBytes();          break;
        //case 207: LIS3MDL_ReadWhoAmIReg(uint8 * rdPtr) TO-DO; break; 
        case 208: LSM6DS3_Begin();                        break;
        //case 211: LSM6DS3_ReadAxisRaw TO-DO
        //case 212 LSM6DS3_ReadAxisDeg TO-DO
        //case 213: LSM6DS3_ReadMultipleBytes();          break;
        //case 214: LSM6DS3_ReadWhoAmIReg() TO-DO;      break;
        //case 215: LSM6DS3_ReadCtrlReg(); TO-DO:       break; 
    }*/
}









/* [] END OF FILE */
