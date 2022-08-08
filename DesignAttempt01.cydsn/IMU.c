/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 *  Information taken from the datasheet https://www.st.com/en/mems-and-sensors/lis3mdl.html  
 * ========================================
*/

#include "IMU.h"
#include "stdio.h"
#include <stdlib.h>
#include "project.h"
#include <math.h>


////// Magnetometer /////
void LIS3MDL_Begin() {
    I2C_1_Start(); //Enable I2C In PSOC
    
    // Enable Data conversion in magnetometer by setting Control register 3 to continuous conversion mode
    I2C_1_I2CMasterSendStart(LIS3MDL_I2CADD,I2C_1_I2C_WRITE_XFER_MODE,100);    // Initialize a transaction for writing
    I2C_1_I2CMasterWriteByte(LIS3MDL_REG_CTRL_REG3,100);                       // Indicate which register you want to write to
    I2C_1_I2CMasterWriteByte(0x00,100);                                        // Write to register
    I2C_1_I2CMasterSendStop(100);                    // End of transaction */
}

void LIS3MDL_MasterStatus() {
    I2C_1_I2CMasterStatus();
}

void LIS3MDL_TransferByte() {
    /* (M)ST | (M)SAD + W | (S)SAK | (M)SUB | (S)SAK | (M)DATA | (S)SAK | (M)SP */
} 

void LIS3MDL_TransferMultipleBytes() {
    /* (M)ST | (M)SAD + W | (S)SAK | (M)SUB | (S)SAK | DATA | (S)SAK | (M)DATA | (S)SAK |(M)SP */
    
}

void LIS3MDL_ReadWhoAmIReg(uint8 * rdPtr) {
    /* (M)ST | (M)SAD+W| (S)SAK | (M)SUB | (S)SAK | (M)SR | (M)SAD+R | (S)SAK | (S)DATA | (M)NMAK | (M)SP |  */
    int32 Err1, Err2, Err3, Err4, Err5;
    Err1 = I2C_1_I2CMasterSendStart(LIS3MDL_I2CADD, I2C_1_I2C_WRITE_XFER_MODE, 1000);     // (M)ST | (M) SAD + W | (S) SAK
    Err2 = I2C_1_I2CMasterWriteByte(LIS3MDL_REG_WHO_AM_I,1000);                           // (M) SUB | (S) SAK
    Err3 = I2C_1_I2CMasterSendRestart(LIS3MDL_I2CADD, I2C_1_I2C_READ_XFER_MODE, 1000);  // (M) SR | (M) SAD + R | (S)SAK
    Err4 = I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA, rdPtr, 1000);                   // (S) DATA | (M) NMAK
    Err5 = I2C_1_I2CMasterSendStop(100);                                                 // (M) SP
    //char string[80]; sprintf(string, "\nErrors %ld %ld %ld %ld %ld ", Err1,Err2,Err3,Err4,Err5); UART_PutString(string); 
}

void LIS3MDL_ReadAxisRaw(uint8 * rdPtrL, uint8 * rdPtrH) {
    /* (M)ST | (M)SAD+W| (S)SAK | (M)SUB | (S)SAK | (M)SR | (M)SAD+R | (S)SAK | (S)DATA | (M)MAK | DATA| MAK | DATA | NMAK | (M)SP |  */
    int32 Err1, Err2, Err3, Err4, Err5, Err6;
    Err1 = I2C_1_I2CMasterSendStart(LIS3MDL_I2CADD, I2C_1_I2C_WRITE_XFER_MODE, 1000);   // (M)ST | (M) SAD + W | (S) SAK
    Err2 = I2C_1_I2CMasterWriteByte(LIS3MDL_REG_OUT_X_L,1000);                          // (M) SUB | (S) SAK
    Err3 = I2C_1_I2CMasterSendRestart(LIS3MDL_I2CADD, I2C_1_I2C_READ_XFER_MODE, 1000);  // (M) SR | (M) SAD + R | (S)SAK
    Err4 = I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA, rdPtrL, 1000);                   // (S) DATA | (M) NMAK
    Err5 = I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA, rdPtrH, 1000);                // (S) DATA | (M) NMAK
    Err6 = I2C_1_I2CMasterSendStop(100); 
    // char string[80]; sprintf(string, "Errors %ld %ld %ld %ld %ld %ld\t", Err1,Err2,Err3,Err4,Err5,Err6); UART_PutString(string); 
    
}
void LIS3MDL_ReadAxisDeg(uint16 * heading) {
    /* (M)ST | (M)SAD+W| (S)SAK | (M)SUB | (S)SAK | (M)SR | (M)SAD+R | (S)SAK | (S)DATA | (M)MAK | DATA| MAK | DATA | NMAK | (M)SP |  */
    int32 Err1, Err2, Err3, Err4, Err5, Err6;
    Err1 = I2C_1_I2CMasterSendStart(LIS3MDL_I2CADD, I2C_1_I2C_WRITE_XFER_MODE, 1000);   // (M)ST | (M) SAD + W | (S) SAK
    Err2 = I2C_1_I2CMasterWriteByte(LIS3MDL_REG_OUT_X_L,1000);                          // (M) SUB | (S) SAK
    Err3 = I2C_1_I2CMasterSendRestart(LIS3MDL_I2CADD, I2C_1_I2C_READ_XFER_MODE, 1000);  // (M) SR | (M) SAD + R | (S)SAK
    uint8 rdPtrL, rdPtrH;
    Err4 = I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA, &rdPtrL, 1000);                    // (S) DATA | (M) NMAK
    Err5 = I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA, &rdPtrH, 1000);                    // (S) DATA | (M) NMAK
    Err6 = I2C_1_I2CMasterSendStop(100); 
    // char string[80]; sprintf(string, "Errors %ld %ld %ld %ld %ld %ld\t", Err1,Err2,Err3,Err4,Err5,Err6); UART_PutString(string); 
    
    uint8 rdPtrHS = rdPtrH;
    uint8 rdPtrLS = rdPtrL;
    *heading = (uint16)rdPtrHS << 8 | rdPtrLS; 
    // TO-DO: Calibration script for magnetometer
}

void LIS3MDL_ReadCtrlReg(uint8 * CtrlReg1,uint8 * CtrlReg2, uint8 * CtrlReg3, uint8 * CtrlReg4) {
    /* (M)ST | (M)SAD+W| (S)SAK | (M)SUB | (S)SAK | (M)SR | (M)SAD+R | (S)SAK | (S)DATA | (M)MAK | DATA| MAK | DATA | NMAK | (M)SP |  */
    int32 Err1, Err2, Err3, Err4, Err5, Err6;
    Err1 = I2C_1_I2CMasterSendStart(LIS3MDL_I2CADD, I2C_1_I2C_WRITE_XFER_MODE, 1000);   // (M)ST | (M) SAD + W | (S) SAK
    Err2 = I2C_1_I2CMasterWriteByte(LIS3MDL_REG_CTRL_REG1,1000);                          // (M) SUB | (S) SAK
    Err3 = I2C_1_I2CMasterSendRestart(LIS3MDL_I2CADD, I2C_1_I2C_READ_XFER_MODE, 1000);  // (M) SR | (M) SAD + R | (S)SAK
    Err4 = I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA, CtrlReg1, 1000);                 // (S) DATA | (M) MAK
    Err4 = I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA, CtrlReg2, 1000);        
    Err4 = I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA, CtrlReg3, 1000);                 
    Err5 = I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA, CtrlReg4, 1000);                 // (S) DATA | (M) NMAK
    Err6 = I2C_1_I2CMasterSendStop(100); 
    char string[80]; sprintf(string, "Errors %ld %ld %ld %ld %ld %ld\t", Err1,Err2,Err3,Err4,Err5,Err6); UART_PutString(string); 
}

/////// Accelerometer and Gyrometer //////
// Gyrometer is unlikely to be that useful for us, so we focus on the accelerometer
void LSM6DS3_Begin() {
    int32 Err1, Err2, Err3, Err4, Err5;
    uint8 rdBfr;
    
    I2C_1_Start(); //Enable I2C In PSOC
    
    // TO-DO: Pre start up calibration, MUST BE PERFORMED IN POWER DOWN MODE
    /*I2C_1_I2CMasterSendStart(LSM6DS3_I2CADD,I2C_1_I2C_WRITE_XFER_MODE,100);    // Initialize a transaction for writing
    I2C_1_I2CMasterWriteByte(LSM6DS3_REG_CTRL1_XL,100);                       // Indicate which register you want to write to
    I2C_1_I2CMasterWriteByte(0x00,100);                                        // Write to register
    I2C_1_I2CMasterSendStop(100);                                                 // End of transaction 
    // Write to FUNC_CFG_ACCESS to allow access to embedded registers
    I2C_1_I2CMasterSendStart(LSM6DS3_I2CADD,I2C_1_I2C_WRITE_XFER_MODE,100);    // Initialize a transaction for writing
    I2C_1_I2CMasterWriteByte(0x01,100);                       // Indicate which register you want to write to
    I2C_1_I2CMasterWriteByte(0x80,100);                                        // Write to register
    I2C_1_I2CMasterSendStop(100); 
    // Write to change magnitude offset register
    I2C_1_I2CMasterSendStart(LSM6DS3_I2CADD,I2C_1_I2C_WRITE_XFER_MODE,100);    // Initialize a transaction for writing
    I2C_1_I2CMasterWriteByte(0x2D,100);                       // Indicate which register you want to write to
    I2C_1_I2CMasterWriteByte(0xAA,100);
    I2C_1_I2CMasterWriteByte(0xAA,100);                                        // Write to register
    I2C_1_I2CMasterSendStop(100); 
    // Write to FUNC_CFG_ACCESS to disallow access to embedded registers
    I2C_1_I2CMasterSendStart(LSM6DS3_I2CADD,I2C_1_I2C_WRITE_XFER_MODE,100);    // Initialize a transaction for writing
    I2C_1_I2CMasterWriteByte(0x01,100);                       // Indicate which register you want to write to
    I2C_1_I2CMasterWriteByte(0x00,100);                                        // Write to register
    I2C_1_I2CMasterSendStop(100); 
        //Enable embedded register functions/filters
    I2C_1_I2CMasterSendStart(LSM6DS3_I2CADD,I2C_1_I2C_WRITE_XFER_MODE,100);    // Initialize a transaction for writing
    I2C_1_I2CMasterWriteByte(LSM6DS3_REG_CTRL10_C,100);                       // Indicate which register you want to write to
    I2C_1_I2CMasterWriteByte(0x3C,100);                                        // Write to register
    I2C_1_I2CMasterSendStop(100);
    // Enable hard-iron compensation in MASTER_CONFIG
    I2C_1_I2CMasterSendStart(LSM6DS3_I2CADD,I2C_1_I2C_WRITE_XFER_MODE,100);    // Initialize a transaction for writing
    I2C_1_I2CMasterWriteByte(LSM6DS3_REG_MASTER_CONFIG,100);                       // Indicate which register you want to write to
    I2C_1_I2CMasterWriteByte(0x02,100);                                        // Write to register
    I2C_1_I2CMasterSendStop(100);*/

    
    // Enable Data conversion in magnetometer by setting Control register 1 to continuous conversion mode
    I2C_1_I2CMasterSendStart(LSM6DS3_I2CADD,I2C_1_I2C_WRITE_XFER_MODE,100);    // Initialize a transaction for writing
    I2C_1_I2CMasterWriteByte(LSM6DS3_REG_CTRL1_XL,100);                       // Indicate which register you want to write to
    I2C_1_I2CMasterWriteByte(0x50,100);                                        // Write to register
    I2C_1_I2CMasterSendStop(100);                    // End of transaction */
}
void LSM6DS3_ReadWhoAmIReg(uint8 * rdPtr) {
    /* (M)ST | (M)SAD+W| (S)SAK | (M)SUB | (S)SAK | (M)SR | (M)SAD+R | (S)SAK | (S)DATA | (M)NMAK | (M)SP |  */
    int32 Err1, Err2, Err3, Err4, Err5;
    Err1 = I2C_1_I2CMasterSendStart(LSM6DS3_I2CADD, I2C_1_I2C_WRITE_XFER_MODE, 1000);     // (M)ST | (M) SAD + W | (S) SAK
    Err2 = I2C_1_I2CMasterWriteByte(LSM6DS3_REG_WHO_AM_I,1000);                           // (M) SUB | (S) SAK
    Err3 = I2C_1_I2CMasterSendRestart(LSM6DS3_I2CADD, I2C_1_I2C_READ_XFER_MODE, 1000);  // (M) SR | (M) SAD + R | (S)SAK
    Err4 = I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA, rdPtr, 1000);                   // (S) DATA | (M) NMAK
    Err5 = I2C_1_I2CMasterSendStop(100);                                                 // (M) SP
    char string[80]; sprintf(string, "\nErrors %ld %ld %ld %ld %ld ", Err1,Err2,Err3,Err4,Err5); UART_PutString(string); 
}

void LSM6DS3_ReadAxisRaw(uint8 * rdPtrL, uint8 * rdPtrH) {
    /* (M)ST | (M)SAD+W| (S)SAK | (M)SUB | (S)SAK | (M)SR | (M)SAD+R | (S)SAK | (S)DATA | (M)MAK | DATA| MAK | DATA | NMAK | (M)SP |  */
    int32 Err1, Err2, Err3, Err4, Err5, Err6;
    Err1 = I2C_1_I2CMasterSendStart(LSM6DS3_I2CADD, I2C_1_I2C_WRITE_XFER_MODE, 1000);   // (M)ST | (M) SAD + W | (S) SAK
    Err2 = I2C_1_I2CMasterWriteByte(LSM6DS3_REG_OUTX_H_XL,1000);                          // (M) SUB | (S) SAK
    Err3 = I2C_1_I2CMasterSendRestart(LSM6DS3_I2CADD, I2C_1_I2C_READ_XFER_MODE, 1000);  // (M) SR | (M) SAD + R | (S)SAK
    Err4 = I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA, rdPtrL, 1000);                   // (S) DATA | (M) NMAK
    Err5 = I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA, rdPtrH, 1000);                // (S) DATA | (M) NMAK
    Err6 = I2C_1_I2CMasterSendStop(100); 
    // char string[80]; sprintf(string, "Errors %ld %ld %ld %ld %ld %ld\t", Err1,Err2,Err3,Err4,Err5,Err6); UART_PutString(string); 
    
}
void LSM6DS3_ReadAxisDeg(uint16 * heading) {
    /* (M)ST | (M)SAD+W| (S)SAK | (M)SUB | (S)SAK | (M)SR | (M)SAD+R | (S)SAK | (S)DATA | (M)MAK | DATA| MAK | DATA | NMAK | (M)SP |  */
    int32 Err1, Err2, Err3, Err4, Err5, Err6;
    Err1 = I2C_1_I2CMasterSendStart(LIS3MDL_I2CADD, I2C_1_I2C_WRITE_XFER_MODE, 1000);   // (M)ST | (M) SAD + W | (S) SAK
    Err2 = I2C_1_I2CMasterWriteByte(LIS3MDL_REG_OUT_X_L,1000);                          // (M) SUB | (S) SAK
    Err3 = I2C_1_I2CMasterSendRestart(LIS3MDL_I2CADD, I2C_1_I2C_READ_XFER_MODE, 1000);  // (M) SR | (M) SAD + R | (S)SAK
    uint8 rdPtrL, rdPtrH;
    Err4 = I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA, &rdPtrL, 1000);                    // (S) DATA | (M) NMAK
    Err5 = I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA, &rdPtrH, 1000);                    // (S) DATA | (M) NMAK
    Err6 = I2C_1_I2CMasterSendStop(100); 
    // char string[80]; sprintf(string, "Errors %ld %ld %ld %ld %ld %ld\t", Err1,Err2,Err3,Err4,Err5,Err6); UART_PutString(string); 
    
    uint8 rdPtrHS = rdPtrH;
    uint8 rdPtrLS = rdPtrL;
    *heading = (uint16)rdPtrHS << 8 | rdPtrLS; 
    // Convert this heading to degrees.
    // TO-DO: Calibration script for magnetometer
}

void LSM6DS3_ReadCtrlReg(uint8 CtrlReg[10]) {
    /* (M)ST | (M)SAD+W| (S)SAK | (M)SUB | (S)SAK | (M)SR | (M)SAD+R | (S)SAK | (S)DATA | (M)MAK | DATA| MAK | DATA | NMAK | (M)SP |  */
    I2C_1_I2CMasterSendStart(LSM6DS3_I2CADD, I2C_1_I2C_WRITE_XFER_MODE, 1000);   // (M)ST | (M) SAD + W | (S) SAK
    I2C_1_I2CMasterWriteByte(LSM6DS3_REG_CTRL1_XL,1000); //(M) SUB | (S) SAK         
    I2C_1_I2CMasterSendRestart(LSM6DS3_I2CADD, I2C_1_I2C_READ_XFER_MODE, 1000);  // (M) SR | (M) SAD + R | (S)SAK
    I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA, &CtrlReg[0], 1000);                 // (S) DATA | (M) MAK
    I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA, &CtrlReg[1], 1000);        
    I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA, &CtrlReg[2], 1000);
    I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA, &CtrlReg[3], 1000);                 
    I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA, &CtrlReg[4], 1000);        
    I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA, &CtrlReg[5], 1000);
    I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA, &CtrlReg[6], 1000);                 
    I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA, &CtrlReg[7], 1000);        
    I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA, &CtrlReg[8], 1000);
    I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA, &CtrlReg[9], 1000);                 // (S) DATA | (M) NMAK
    I2C_1_I2CMasterSendStop(100); 
    //char string[80]; sprintf(string, "Errors %ld %ld %ld %ld %ld %ld\t", Err1,Err2,Err3,Err4,Err5,Err6); UART_PutString(string); 
}