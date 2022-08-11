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

// User Functions
void onRx() 
{   
    uint32 rxByte = UART_RPi_UartGetByte();
    char rxChar = (char)rxByte;
    rxString[rxCount] = rxChar;
    rxCount++;
    
    if (rxChar == '\n')
    {
        strcpy(comString, rxString);
        UART_PutString(comString);
        memset(rxString,0,sizeof(rxString));  
        rxCount = 0;
        UART_PutString(rxString);
    }
   
    
}

// Main
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
    //TB9051_Begin();
        
    for(;;)
    {  
       //char string[20]; sprintf(string, "Main\n"); UART_PutString(string);
    }
}

