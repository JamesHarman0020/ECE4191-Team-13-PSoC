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
//#include "HCSR04.h"
#include "pid.h"

// Global Variables
float fullSpeedNoLoad = 0.2814784; // m/s
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
uint8 rxBuffer[15] = {0};
uint8 rxBufferOld[15] = {0};

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
    
    B1 = (unsigned char *)&prm1;    // Setup the floats for serial receive
    B2 = (unsigned char *)&prm2;    // by putting data at the address of the floats
    
    //Setup interrupts
    RXcmplt_Start();
    RXcmplt_ClearPending();
    RXcmplt_StartEx(readBuf);
    
    /* // DESYNC TEST -- To test the robustness of the UART buffer
    for (int i = 0; i < 8; i++)
        UART_RPi_PutChar('c');
    */    
    for(;;)
    {          
    }
}

// User Functions
int fn_old, param1_old, param2_old;
CY_ISR(readBuf){ // Read Incoming serial data
    int diffFlag = 0;
    for (int i = 3; i < 12; i++) {
        if (rxBuffer[i] != rxBufferOld[i]) {
            diffFlag = 1;
        }
    }
    memcpy(rxBufferOld,rxBuffer,15);
    if (diffFlag) {        
        // A packet should arrive within a matter of us -> could be used as an error check
        int stopPres = 0;
        int startPres = 0;
        int startPos = 0;
        int deSyncFlg = 0;   
        
        for (int i = 14; i >= 0; i--) { // Search for the stop byte
            if (rxBuffer[i] == 0x55) {
                stopPres = 1; 
            }
            // If we have a stop byte, begin searching for a start byte
            else if (stopPres == 0 & rxBuffer[i] == 0xff & i <= 12) { //Search for the start byte
                startPres = 1;
                startPos = i;
            }
        }
        
        if (startPos >= 4) { //If out of sync, call RPi to adjust.
            deSyncFlg = 1;
            float p1 = 15 - startPos; // This requires fine tuning
            float p2 = 0;
            UART_PutString("Frame Error: ");
             for (int i = 0; i < 15; i++) { 
                sprintf(string,"%x ",rxBuffer[i]); UART_PutString(string);
            }
            UART_PutCRLF();
            fnSend(90, &p1, &p2);
        }
        
        if (deSyncFlg == 0) {  // If insync (Bye, Bye, Bye) read the data and assign it to function, param1, param2 
            fn = (char)rxBuffer[startPos + 1];
            for (int i = 0; i < 4; i++) {
                B1[i] = (char)rxBuffer[startPos + 2 + i];
                B2[i] = (char)rxBuffer[startPos + i + 6];
            }
            
            // DEBUG FOR INCOMING SERIAL - PRINT DATA IN HEX / DEC
            sprintf(string,"R:%i %0.3f %0.3f \n",fn,prm1,prm2); UART_PutString(string);
            if (fn_old != fn | param1_old != prm1 | param2_old != prm2) {
                fnCall(fn,&prm1,&prm2);
            }
        }
    }    
}


/* DMA Configuration for rxDMA */
void DMA_Config() {
    rxDMA_Chan = rxDMA_DmaInitialize(rxDMA_BYTES_PER_BURST, rxDMA_REQUEST_PER_BURST, 
        HI16(rxDMA_SRC_BASE), HI16(rxDMA_DST_BASE));
    rxDMA_TD[0] = CyDmaTdAllocate();
    CyDmaTdSetConfiguration(rxDMA_TD[0], 15, rxDMA_TD[0], rxDMA__TD_TERMOUT_EN | CY_DMA_TD_INC_DST_ADR);
    CyDmaTdSetAddress(rxDMA_TD[0], LO16((uint32)UART_RPi_RXDATA_PTR), LO16((uint32)rxBuffer));
    CyDmaChSetInitialTd(rxDMA_Chan, rxDMA_TD[0]);
    CyDmaChEnable(rxDMA_Chan, 1);
}