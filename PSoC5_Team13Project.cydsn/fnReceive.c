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
#include "HCSR04.h"

void fnCall(int fn, float * para2, float * para3);
void fnSend(int fn, float * para2, float * para3);
void Uart_Resync(int n);

void fnCall(int fn, float * pPrm1, float * pPrm2) {
    float para2 = *pPrm1;
    float para3 = *pPrm2;
    //char string[20]; sprintf(string, "%i %.3f %.3f", fn, para2, para3); UART_PutString(string);
    //CyExitCriticalSection(InterruptState);
    switch (fn) { 
        case 0: TB9051_VehMoveTo(pPrm1,pPrm2);          break; // Motor Commands
        case 1: TB9051_Begin();                         break;
        case 2: TB9051_Forward((int)para2,0,(int)para3);break;
        case 3: TB9051_Reverse((int)para2,(int)para3);  break;
        case 4: TB9051_Brake((int)para2);               break;
        case 5: TB9051_VehForward(0,pPrm1);             break;
        case 6: TB9051_VehReverse((int)para2);          break;
        case 7: TB9051_VehBrake();                      break;
        case 8: linAngtoVel(&para2, &para3);            break;
        case 50: oneStepCCW((int)para2);                break; // Stepper Commands
        case 51: oneStepCW((int)para2);                 break;
        case 52: moveAngle(para2);                      break;
        //case 60: SG90_Begin();                        break; // Servo Commands
        //case 61: SG90_ToAngle(para2);                 break;
        case 90: Uart_Resync((int)para2);               break;
        case 100: HCSR04_Begin();                       break;
        case 101: distMeasure();                        break;
        case 102: distMeasureL();                       break;
        case 103: distMeasureR();                       break;
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
    }
}

void fnSend(int fn, float * para2, float * para3){
    uint8 txBuffer[15];// = {0x00, 0x65, 0x42, 0xc8, 0x00, 0x00, 0x42, 0xc8, 0x00};
    
    union {
        float a;
        unsigned char Ba[4];
    } BtoFa;
    
    union {
        float b;
        unsigned char Bb[4];
    } BtoFb;
    
    BtoFa.a = *para2;
    BtoFb.b = *para3;
    
    for (int i = 0; i < 3; i++){
        txBuffer[i+4] = BtoFa.Ba[3-i];
        txBuffer[i+8] = BtoFb.Bb[3-i];
    }
    
    txBuffer[0] = 0xff;
    txBuffer[1] = 0xff;
    txBuffer[2] = 0xff;
    txBuffer[3] = (unsigned char)fn;
    txBuffer[12] = 0x55;
    txBuffer[13] = 0x55;
    txBuffer[14] = 0x55;
    
    /* //// DEBUG /////
    UART_PutString("Send: ");
    for (int i = 0; i < 15; i++) {
        char string[10]; sprintf(string, "%x ", txBuffer[i]); UART_PutString(string);
    }
    UART_PutCRLF(); */
    
    UART_RPi_PutArray(txBuffer,15);
    char string[20]; sprintf(string, "T:%i,%0.2f,%0.2f\n", fn, *para2, *para3); UART_PutString(string);
}


void Uart_Resync(int n){
    UART_PutString("resync");
    uint8 resyncBuff[15] = {0};
    if (UART_RPi_GetTxBufferSize() == 0) {
        UART_RPi_PutArray(resyncBuff,n);
    }
}


/* [] END OF FILE */
