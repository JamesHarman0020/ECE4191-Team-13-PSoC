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
#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Custom Drivers
#include "SBT0811.h"
#include "IMU.h"
#include "SG90.h"
#include "TB9051.h"

int main(void) // THIS SHOULD BE FREERTOS 
{
    CyGlobalIntEnable;
    UART_Start();
    //LIS3MDL_Begin();
    LSM6DS3_Begin();
    SG90_Begin();
    float angle = 0;
    SG90_ToAngle(angle);
    // moveAngle((float)180); TEST
    
    TB9051_Begin();
        
    for(;;)
    {  
        TB9051_VehForward(200);
        CyDelay(1000);
        TB9051_VehReverse(200);
        CyDelay(1000);
        
        
        
        //uint8 rdBuffer, rdPtrL, rdPtrH;
        //uint16 heading; 
        //int16 headingS = (int16)heading;
        //uint8 ctrlReg[10]; 
        //LSM6DS3_ReadAxisRaw(&rdPtrL, &rdPtrH);
        //int16 word = (uint16)(rdPtrL<<8)|rdPtrH;
        //int16 wordOS = word + 330; // TO-DO: Perform this calibration in hardware rather than software 
        //float scaled = (float)2*wordOS / INT16_MAX;
        //TO-DO: Run this data through a filter
        //char string[80]; sprintf(string, "Bytes: %d %d\tWord: %d\tScaled: %1.4f\n", rdPtrL, rdPtrH, wordOS, scaled); UART_PutString(string);
        
        //uint8 CtrlReg1, CtrlReg2, CtrlReg3, CtrlReg4;
        //LIS3MDL_ReadCtrlReg(&CtrlReg1,&CtrlReg2,&CtrlReg3, &CtrlReg4);
        //char string[80]; sprintf(string, "CtrlReg: %d, %d, %d, %d\n", CtrlReg1, CtrlReg2, CtrlReg3, CtrlReg4); UART_PutString(string); 
        
        //LIS3MDL_ReadAxisDeg(&heading);
        //char string[80]; sprintf(string, "Compass: %hd\n", headingS); UART_PutString(string);
    }
}