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
#include "HCSR04.h"

// Global Variables
char rxString[30] = {0};
int rxCount = 0;
char comString[30] = {0};
int fn; 
float prm1, prm2;
unsigned char *B1, *B2;
int mask = 0xff;
int startFlag = 0;

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
    TB9051_Begin();
    UART_RPi_SetCustomInterruptHandler(&onRx);
    Timer2_Start();
    
    // Setup the floats for serial receive
    // by putting data at the address of the floats
    B1 = (unsigned char *)&prm1;
    B2 = (unsigned char *)&prm2;
    
    //Setup interrupts for ultrasonics
    E1_Start();
    E2_Start();
    E1_ClearPending();
    E1_StartEx(Capture);
    
    for(;;)
    {  
        /* // MOTOR TEST
        CyDelay(5000);
        TB9051_VehBrake();
        CyDelay(2000);
        TB9051_VehReverse(125); */
       //char string[20]; sprintf(string, "Main\n"); UART_PutString(string);
        CyDelay(1000);
        distMeasure();
    }
}

// User Functions
void onRx() 
{   
    uint32 rxByte = UART_RPi_UartGetByte();
    rxByte = rxByte & mask;                 // rxByte only contains data in bits 7-0       
    if (rxByte == 0xff) {                   // Start byte
        startFlag = 1;
    }
    
    if (startFlag) {
        char string[10]; sprintf(string,"%lx ",rxByte); UART_PutString(string);
        switch (rxCount) {
            case 1: fn = (char)rxByte;      //fn byte
            case 2: B1[0] = (char)rxByte;   //float 1 [4 bytes]
            case 3: B1[1] = (char)rxByte;
            case 4: B1[2] = (char)rxByte;
            case 5: B1[3] = (char)rxByte;
            case 6: B2[0] = (char)rxByte;   //float 2 [4 bytes]
            case 7: B2[1] = (char)rxByte;
            case 8: B2[2] = (char)rxByte;
            case 9: B2[3] = (char)rxByte;
        }
    }
       
    if (rxCount < 9) rxCount++; 
    else {
        rxCount = 0; startFlag = 0;         // Reset and wait for start bit
        char string[40]; sprintf(string,": %i %0.6f %0.6f \n",fn,prm1,prm2); UART_PutString(string);
    }
}

