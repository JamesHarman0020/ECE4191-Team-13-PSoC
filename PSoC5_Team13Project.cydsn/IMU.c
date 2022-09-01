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
    I2C_1_MasterSendStart(LIS3MDL_I2CADD,I2C_1_WRITE_XFER_MODE);    // Initialize a transaction for writing
    I2C_1_MasterWriteByte(LIS3MDL_REG_CTRL_REG3);                       // Indicate which register you want to write to
    I2C_1_MasterWriteByte(0x00);                                        // Write to register
    I2C_1_MasterSendStop();                    // End of transaction */
}

void LIS3MDL_MasterStatus() {
    I2C_1_MasterStatus();
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
    Err1 = I2C_1_MasterSendStart(LIS3MDL_I2CADD, I2C_1_WRITE_XFER_MODE);     // (M)ST | (M) SAD + W | (S) SAK
    Err2 = I2C_1_MasterWriteByte(LIS3MDL_REG_WHO_AM_I);                           // (M) SUB | (S) SAK
    Err3 = I2C_1_MasterSendRestart(LIS3MDL_I2CADD, I2C_1_READ_XFER_MODE);  // (M) SR | (M) SAD + R | (S)SAK
    uint8 returned = I2C_1_MasterReadByte(I2C_1_NAK_DATA);                   // (S) DATA | (M) NMAK
    Err5 = I2C_1_MasterSendStop();                                                 // (M) SP
    rdPtr = &returned;
    //char string[80]; sprintf(string, "\nErrors %ld %ld %ld %ld %ld ", Err1,Err2,Err3,Err4,Err5); UART_PutString(string); 
}

void LIS3MDL_ReadAxisRaw(uint8 * rdPtrL, uint8 * rdPtrH) {
    /* (M)ST | (M)SAD+W| (S)SAK | (M)SUB | (S)SAK | (M)SR | (M)SAD+R | (S)SAK | (S)DATA | (M)MAK | DATA| MAK | DATA | NMAK | (M)SP |  */
    int32 Err1, Err2, Err3, Err4, Err5, Err6;
    Err1 = I2C_1_MasterSendStart(LIS3MDL_I2CADD, I2C_1_WRITE_XFER_MODE);   // (M)ST | (M) SAD + W | (S) SAK
    Err2 = I2C_1_MasterWriteByte(LIS3MDL_REG_OUT_X_L);                          // (M) SUB | (S) SAK
    Err3 = I2C_1_MasterSendRestart(LIS3MDL_I2CADD, I2C_1_READ_XFER_MODE);  // (M) SR | (M) SAD + R | (S)SAK
    uint8 rtdL = I2C_1_MasterReadByte(I2C_1_ACK_DATA);                   // (S) DATA | (M) NMAK
    uint8 rtdH = I2C_1_MasterReadByte(I2C_1_NAK_DATA);                // (S) DATA | (M) NMAK
    Err6 = I2C_1_MasterSendStop(); 
    rdPtrL = &rtdL; rdPtrH = &rtdH;
    // char string[80]; sprintf(string, "Errors %ld %ld %ld %ld %ld %ld\t", Err1,Err2,Err3,Err4,Err5,Err6); UART_PutString(string); 
    
}
void LIS3MDL_ReadAxisDeg(uint16 * heading) {
    /* (M)ST | (M)SAD+W| (S)SAK | (M)SUB | (S)SAK | (M)SR | (M)SAD+R | (S)SAK | (S)DATA | (M)MAK | DATA| MAK | DATA | NMAK | (M)SP |  */
    int32 Err1, Err2, Err3, Err4, Err5, Err6;
    Err1 = I2C_1_MasterSendStart(LIS3MDL_I2CADD, I2C_1_WRITE_XFER_MODE);   // (M)ST | (M) SAD + W | (S) SAK
    Err2 = I2C_1_MasterWriteByte(LIS3MDL_REG_OUT_X_L);                          // (M) SUB | (S) SAK
    Err3 = I2C_1_MasterSendRestart(LIS3MDL_I2CADD, I2C_1_READ_XFER_MODE);  // (M) SR | (M) SAD + R | (S)SAK
    uint8 rdPtrL, rdPtrH;
    rdPtrL = I2C_1_MasterReadByte(I2C_1_ACK_DATA);                    // (S) DATA | (M) NMAK
    rdPtrH = I2C_1_MasterReadByte(I2C_1_NAK_DATA);                    // (S) DATA | (M) NMAK
    Err6 = I2C_1_MasterSendStop(); 
    // char string[80]; sprintf(string, "Errors %ld %ld %ld %ld %ld %ld\t", Err1,Err2,Err3,Err4,Err5,Err6); UART_PutString(string); 
    
    uint8 rdPtrHS = rdPtrH;
    uint8 rdPtrLS = rdPtrL;
    *heading = (uint16)rdPtrHS << 8 | rdPtrLS; 
    // TO-DO: Calibration script for magnetometer
}

void LIS3MDL_ReadCtrlReg(uint8 * CtrlReg1,uint8 * CtrlReg2, uint8 * CtrlReg3, uint8 * CtrlReg4) {
    /* (M)ST | (M)SAD+W| (S)SAK | (M)SUB | (S)SAK | (M)SR | (M)SAD+R | (S)SAK | (S)DATA | (M)MAK | DATA| MAK | DATA | NMAK | (M)SP |  */
    int32 Err1, Err2, Err3, Err4, Err5, Err6;
    Err1 = I2C_1_MasterSendStart(LIS3MDL_I2CADD, I2C_1_WRITE_XFER_MODE);   // (M)ST | (M) SAD + W | (S) SAK
    Err2 = I2C_1_MasterWriteByte(LIS3MDL_REG_CTRL_REG1);                          // (M) SUB | (S) SAK
    Err3 = I2C_1_MasterSendRestart(LIS3MDL_I2CADD, I2C_1_READ_XFER_MODE);  // (M) SR | (M) SAD + R | (S)SAK
    *CtrlReg1 = I2C_1_MasterReadByte(I2C_1_ACK_DATA);                // (S) DATA | (M) MAK
    *CtrlReg2 = I2C_1_MasterReadByte(I2C_1_ACK_DATA);        
    *CtrlReg3 = I2C_1_MasterReadByte(I2C_1_ACK_DATA);                 
    *CtrlReg4 = I2C_1_MasterReadByte(I2C_1_NAK_DATA);                 // (S) DATA | (M) NMAK
    Err6 = I2C_1_MasterSendStop(); 
    char string[80]; sprintf(string, "Errors %ld %ld %ld %ld %ld %ld\t", Err1,Err2,Err3,Err4,Err5,Err6); UART_PutString(string); 
}

/////// Accelerometer and Gyrometer //////
// Gyrometer is unlikely to be that useful for us, so we focus on the accelerometer
void LSM6DS3_Begin() {
    int32 Err1, Err2, Err3, Err4, Err5;
    uint8 rdBfr;
    
    I2C_1_Start(); //Enable I2C In PSOC
    
    // TO-DO: Pre start up calibration, MUST BE PERFORMED IN POWER DOWN MODE
    /*I2C_1_MasterSendStart(LSM6DS3_I2CADD,I2C_1_WRITE_XFER_MODE,100);    // Initialize a transaction for writing
    I2C_1_MasterWriteByte(LSM6DS3_REG_CTRL1_XL,100);                       // Indicate which register you want to write to
    I2C_1_MasterWriteByte(0x00,100);                                        // Write to register
    I2C_1_MasterSendStop(100);                                                 // End of transaction 
    // Write to FUNC_CFG_ACCESS to allow access to embedded registers
    I2C_1_MasterSendStart(LSM6DS3_I2CADD,I2C_1_WRITE_XFER_MODE,100);    // Initialize a transaction for writing
    I2C_1_MasterWriteByte(0x01,100);                       // Indicate which register you want to write to
    I2C_1_MasterWriteByte(0x80,100);                                        // Write to register
    I2C_1_MasterSendStop(100); 
    // Write to change magnitude offset register
    I2C_1_MasterSendStart(LSM6DS3_I2CADD,I2C_1_WRITE_XFER_MODE,100);    // Initialize a transaction for writing
    I2C_1_MasterWriteByte(0x2D,100);                       // Indicate which register you want to write to
    I2C_1_MasterWriteByte(0xAA,100);
    I2C_1_MasterWriteByte(0xAA,100);                                        // Write to register
    I2C_1_MasterSendStop(100); 
    // Write to FUNC_CFG_ACCESS to disallow access to embedded registers
    I2C_1_MasterSendStart(LSM6DS3_I2CADD,I2C_1_WRITE_XFER_MODE,100);    // Initialize a transaction for writing
    I2C_1_MasterWriteByte(0x01,100);                       // Indicate which register you want to write to
    I2C_1_MasterWriteByte(0x00,100);                                        // Write to register
    I2C_1_MasterSendStop(100); 
        //Enable embedded register functions/filters
    I2C_1_MasterSendStart(LSM6DS3_I2CADD,I2C_1_WRITE_XFER_MODE,100);    // Initialize a transaction for writing
    I2C_1_MasterWriteByte(LSM6DS3_REG_CTRL10_C,100);                       // Indicate which register you want to write to
    I2C_1_MasterWriteByte(0x3C,100);                                        // Write to register
    I2C_1_MasterSendStop(100);
    // Enable hard-iron compensation in MASTER_CONFIG
    I2C_1_MasterSendStart(LSM6DS3_I2CADD,I2C_1_WRITE_XFER_MODE,100);    // Initialize a transaction for writing
    I2C_1_MasterWriteByte(LSM6DS3_REG_MASTER_CONFIG,100);                       // Indicate which register you want to write to
    I2C_1_MasterWriteByte(0x02,100);                                        // Write to register
    I2C_1_MasterSendStop(100);*/

    
    // Enable Data conversion in magnetometer by setting Control register 1 to continuous conversion mode
    I2C_1_MasterSendStart(LSM6DS3_I2CADD,I2C_1_WRITE_XFER_MODE);    // Initialize a transaction for writing
    I2C_1_MasterWriteByte(LSM6DS3_REG_CTRL1_XL);                       // Indicate which register you want to write to
    I2C_1_MasterWriteByte(0x50);                                        // Write to register
    I2C_1_MasterSendStop();                    // End of transaction */
}
void LSM6DS3_ReadWhoAmIReg(uint8 * rdPtr) {
    /* (M)ST | (M)SAD+W| (S)SAK | (M)SUB | (S)SAK | (M)SR | (M)SAD+R | (S)SAK | (S)DATA | (M)NMAK | (M)SP |  */
    int32 Err1, Err2, Err3, Err4, Err5;
    Err1 = I2C_1_MasterSendStart(LSM6DS3_I2CADD, I2C_1_WRITE_XFER_MODE);     // (M)ST | (M) SAD + W | (S) SAK
    Err2 = I2C_1_MasterWriteByte(LSM6DS3_REG_WHO_AM_I);                           // (M) SUB | (S) SAK
    Err3 = I2C_1_MasterSendRestart(LSM6DS3_I2CADD, I2C_1_READ_XFER_MODE);  // (M) SR | (M) SAD + R | (S)SAK
    *rdPtr = I2C_1_MasterReadByte(I2C_1_NAK_DATA);                   // (S) DATA | (M) NMAK
    Err5 = I2C_1_MasterSendStop();                                                 // (M) SP
    char string[80]; sprintf(string, "\nErrors %ld %ld %ld %ld %ld ", Err1,Err2,Err3,Err4,Err5); UART_PutString(string); 
}

void LSM6DS3_ReadAxisRaw(uint8 * rdPtrL, uint8 * rdPtrH) {
    /* (M)ST | (M)SAD+W| (S)SAK | (M)SUB | (S)SAK | (M)SR | (M)SAD+R | (S)SAK | (S)DATA | (M)MAK | DATA| MAK | DATA | NMAK | (M)SP |  */
    int32 Err1, Err2, Err3, Err4, Err5, Err6;
    Err1 = I2C_1_MasterSendStart(LSM6DS3_I2CADD, I2C_1_WRITE_XFER_MODE);   // (M)ST | (M) SAD + W | (S) SAK
    Err2 = I2C_1_MasterWriteByte(LSM6DS3_REG_OUTX_H_XL);                          // (M) SUB | (S) SAK
    Err3 = I2C_1_MasterSendRestart(LSM6DS3_I2CADD, I2C_1_READ_XFER_MODE);  // (M) SR | (M) SAD + R | (S)SAK
    *rdPtrL = I2C_1_MasterReadByte(I2C_1_ACK_DATA);                   // (S) DATA | (M) NMAK
    *rdPtrH = I2C_1_MasterReadByte(I2C_1_NAK_DATA);                // (S) DATA | (M) NMAK
    Err6 = I2C_1_MasterSendStop(); 
    // char string[80]; sprintf(string, "Errors %ld %ld %ld %ld %ld %ld\t", Err1,Err2,Err3,Err4,Err5,Err6); UART_PutString(string); 
    
}
void LSM6DS3_ReadAxisDeg(uint16 * heading) {
    /* (M)ST | (M)SAD+W| (S)SAK | (M)SUB | (S)SAK | (M)SR | (M)SAD+R | (S)SAK | (S)DATA | (M)MAK | DATA| MAK | DATA | NMAK | (M)SP |  */
    int32 Err1, Err2, Err3, Err4, Err5, Err6;
    Err1 = I2C_1_MasterSendStart(LIS3MDL_I2CADD, I2C_1_WRITE_XFER_MODE);   // (M)ST | (M) SAD + W | (S) SAK
    Err2 = I2C_1_MasterWriteByte(LIS3MDL_REG_OUT_X_L);                          // (M) SUB | (S) SAK
    Err3 = I2C_1_MasterSendRestart(LIS3MDL_I2CADD, I2C_1_READ_XFER_MODE);  // (M) SR | (M) SAD + R | (S)SAK
    uint8 rdPtrL, rdPtrH;
    rdPtrL = I2C_1_MasterReadByte(I2C_1_ACK_DATA);                    // (S) DATA | (M) NMAK
    rdPtrH = I2C_1_MasterReadByte(I2C_1_NAK_DATA);                    // (S) DATA | (M) NMAK
    Err6 = I2C_1_MasterSendStop(); 
    // char string[80]; sprintf(string, "Errors %ld %ld %ld %ld %ld %ld\t", Err1,Err2,Err3,Err4,Err5,Err6); UART_PutString(string); 
    
    uint8 rdPtrHS = rdPtrH;
    uint8 rdPtrLS = rdPtrL;
    *heading = (uint16)rdPtrHS << 8 | rdPtrLS; 
    // Convert this heading to degrees.
    // TO-DO: Calibration script for magnetometer
}

void LSM6DS3_ReadCtrlReg(uint8 CtrlReg[10]) {
    /* (M)ST | (M)SAD+W| (S)SAK | (M)SUB | (S)SAK | (M)SR | (M)SAD+R | (S)SAK | (S)DATA | (M)MAK | DATA| MAK | DATA | NMAK | (M)SP |  */
    I2C_1_MasterSendStart(LSM6DS3_I2CADD, I2C_1_WRITE_XFER_MODE);   // (M)ST | (M) SAD + W | (S) SAK
    I2C_1_MasterWriteByte(LSM6DS3_REG_CTRL1_XL); //(M) SUB | (S) SAK         
    I2C_1_MasterSendRestart(LSM6DS3_I2CADD, I2C_1_READ_XFER_MODE);  // (M) SR | (M) SAD + R | (S)SAK
    CtrlReg[0] = I2C_1_MasterReadByte(I2C_1_ACK_DATA);                 // (S) DATA | (M) MAK
    CtrlReg[0] = I2C_1_MasterReadByte(I2C_1_ACK_DATA);        
    CtrlReg[0] = I2C_1_MasterReadByte(I2C_1_ACK_DATA);
    CtrlReg[0] = I2C_1_MasterReadByte(I2C_1_ACK_DATA);                 
    CtrlReg[0] = I2C_1_MasterReadByte(I2C_1_ACK_DATA);        
    CtrlReg[0] = I2C_1_MasterReadByte(I2C_1_ACK_DATA);
    CtrlReg[0] = I2C_1_MasterReadByte(I2C_1_ACK_DATA);                 
    CtrlReg[0] = I2C_1_MasterReadByte(I2C_1_ACK_DATA);        
    CtrlReg[0] = I2C_1_MasterReadByte(I2C_1_ACK_DATA);
    CtrlReg[0] = I2C_1_MasterReadByte(I2C_1_NAK_DATA);                 // (S) DATA | (M) NMAK
    CtrlReg[0] = I2C_1_MasterSendStop(); 
    //char string[80]; sprintf(string, "Errors %ld %ld %ld %ld %ld %ld\t", Err1,Err2,Err3,Err4,Err5,Err6); UART_PutString(string); 
}