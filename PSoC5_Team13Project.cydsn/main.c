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
uint16 rxByte;
char string[30];
uint8 rxBuffer[10] = {0};

//Functions
void onRx();
CY_ISR(readBuf);
void DMA_Config();

   /* Defines for rxDMA */
#define rxDMA_BYTES_PER_BURST 1
#define rxDMA_REQUEST_PER_BURST 1
#define rxDMA_SRC_BASE (CYDEV_PERIPH_BASE)
#define rxDMA_DST_BASE (CYDEV_SRAM_BASE)

/* Variable declarations for rxDMA */
/* Move these variable declarations to the top of the function */
uint8 rxDMA_Chan;
uint8 rxDMA_TD[1];


int main(void) // THIS SHOULD BE FREERTOS 
{
    CyGlobalIntEnable;
    UART_Start();
    UART_RPi_Start();
   // UART_RPi_EnableRxInt();
    //LIS3MDL_Begin();
    //LSM6DS3_Begin();
    //SG90_Begin();
    TB9051_Begin();
    HCSR04_Begin();
    DMA_Config();
    
    // Setup the floats for serial receive
    // by putting data at the address of the floats
    B1 = (unsigned char *)&prm1;
    B2 = (unsigned char *)&prm2;
    
    //Setup interrupts
    RXcmplt_Start();
    RXcmplt_ClearPending();
    RXcmplt_StartEx(readBuf);
    
    for(;;)
    {  
        /* // MOTOR TEST
        CyDelay(5000);
        TB9051_VehBrake();
        CyDelay(2000);
        TB9051_VehReverse(125); */
       //char string[20]; sprintf(string, "Main\n"); UART_PutString(string);
       //CyDelay(200);
       //TB9051_VehMoveTo(15.000, 5.000);   
    //distMeasure();
       
    }
}

// User Functions
CY_ISR(readBuf){
    if (rxBuffer[10] == 0x00) {
        fn = (char)rxBuffer[1];
        for (int i = 0; i < 4; i++) {
            B1[i] = (char)rxBuffer[i+2];
            B2[i] = (char)rxBuffer[i+6];
        }
    }
    for (int i = 0; i < 10; i++) {
         sprintf(string,"%x ",rxBuffer[i]); UART_PutString(string);
    }
    sprintf(string,"\t %i: %0.3f %0.3f \n",fn,prm1,prm2); UART_PutString(string);
    fnCall(fn,prm1,prm2);
}

/* DMA Configuration for rxDMA */
void DMA_Config() {
    rxDMA_Chan = rxDMA_DmaInitialize(rxDMA_BYTES_PER_BURST, rxDMA_REQUEST_PER_BURST, 
        HI16(rxDMA_SRC_BASE), HI16(rxDMA_DST_BASE));
    rxDMA_TD[0] = CyDmaTdAllocate();
    CyDmaTdSetConfiguration(rxDMA_TD[0], 10, rxDMA_TD[0], rxDMA__TD_TERMOUT_EN | CY_DMA_TD_INC_DST_ADR);
    CyDmaTdSetAddress(rxDMA_TD[0], LO16((uint32)UART_RPi_RXDATA_PTR), LO16((uint32)rxBuffer));
    CyDmaChSetInitialTd(rxDMA_Chan, rxDMA_TD[0]);
    CyDmaChEnable(rxDMA_Chan, 1);
}