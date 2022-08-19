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
#include <string.h>

// Custom Drivers
#include "SBT0811.h"
#include "IMU.h"
#include "SG90.h"
#include "TB9051.h"

// Global Variables
char rxString[30] = {0};
int rxCount = 0;
char comString[30] = {0};

//Functions
void onRx();


int main(void) // THIS SHOULD BE FREERTOS 
{
    CyGlobalIntEnable;
    UART_Start();
    UART_RPi_Start();
    UART_RPi_EnableInt();
    //LIS3MDL_Begin();
    //LSM6DS3_Begin();
    //SG90_Begin();
    //float angle = 0;
    //SG90_ToAngle(angle);
    UART_RPi_SetCustomInterruptHandler(&onRx);
    TB9051_Begin();
        
    for(;;)
    {  
        /* // MOTOR TEST
        CyDelay(5000);
        TB9051_VehBrake();
        CyDelay(2000);
        TB9051_VehReverse(125); */
        
        
       //char string[20]; sprintf(string, "Main\n"); UART_PutString(string);
    }
}

// User Functions
void onRx() 
{   
    uint32 rxByte = UART_RPi_UartGetByte();
    char rxChar = (char)rxByte; 
    rxString[rxCount] = rxChar;
    rxCount++;

    if (rxChar == '\n')                         // TO-DO: Terminate all functions after 9 bytes
    {
        strcpy(comString, rxString);            // copy received string into complete string
        RunFn(&comString);
        memset(rxString,0,sizeof(rxString));    // "Empty" rxString
        rxCount = 0;                            // Reset Counter          
    }
}
