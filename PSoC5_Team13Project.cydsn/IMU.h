/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CODE FROM Adafruit_LIS3MDL Library
 *
 * ========================================
*/
// This is the driver for the Adafruit LSM6DSTR-C + LIS3MDL 9 DoF IMU
#ifndef IMU
#define IMU  
#include "stdio.h"
#include <stdlib.h>
    
    
// Magnetometer Definitions    
#define LIS3MDL_I2CADD (0x1E)   
#define LIS3MDL_REG_WHO_AM_I    0x0F   
#define LIS3MDL_REG_CTRL_REG1   0x20  
#define LIS3MDL_REG_CTRL_REG2   0x21  
#define LIS3MDL_REG_CTRL_REG3   0x22  
#define LIS3MDL_REG_CTRL_REG4   0x23  
#define LIS3MDL_REG_STATUS      0x27    
#define LIS3MDL_REG_OUT_X_L     0x28    
#define LIS3MDL_REG_OUT_X_H     0x29    
#define LIS3MDL_REG_OUT_Y_L     0x2A   
#define LIS3MDL_REG_OUT_Y_H     0x2B    
#define LIS3MDL_REG_OUT_Z_L     0x2c    
#define LIS3MDL_REG_OUT_Z_H     0x2d   
#define LIS3MDL_REG_INT_CFG     0x30   
#define LIS3MDL_REG_INT_THS_L   0x32 
    
//Acclereometer & Gyrometer Definitions
#define LSM6DS3_I2CADD (0x6A)   
#define LSM6DS3_REG_WHO_AM_I    0x0F
#define LSM6DS3_REG_CTRL1_XL    0x10
#define LSM6DS3_REG_CTRL2_G     0x11 
#define LSM6DS3_REG_CTRL3_C     0x12 
#define LSM6DS3_REG_CTRL4_C     0x13
#define LSM6DS3_REG_CTRL5_C     0x14   
#define LSM6DS3_REG_CTRL6_C     0x15
#define LSM6DS3_REG_CTRL7_G     0x16
#define LSM6DS3_REG_CTRL8_XL    0x17
#define LSM6DS3_REG_CTRL9_XL    0x18
#define LSM6DS3_REG_CTRL10_C    0x19
#define LSM6DS3_REG_MASTER_CONFIG    0x1A
#define LSM6DS3_REG_STATUS      0x1E
#define LSM6DS3_REG_OUTX_L_G    0x22    
#define LSM6DS3_REG_OUTX_H_G    0x23   
#define LSM6DS3_REG_OUTY_L_G    0x24   
#define LSM6DS3_REG_OUTY_H_G    0x25    
#define LSM6DS3_REG_OUTZ_L_G    0x26    
#define LSM6DS3_REG_OUTZ_H_G    0x27   
#define LSM6DS3_REG_OUTX_L_XL   0x28    
#define LSM6DS3_REG_OUTX_H_XL   0x29   
#define LSM6DS3_REG_OUTY_L_XL   0x2A   
#define LSM6DS3_REG_OUTY_H_XL   0x2B   
#define LSM6DS3_REG_OUTZ_L_XL   0x2C   
#define LSM6DS3_REG_OUTZ_H_XL   0x2D
   
void LIS3MDL_Begin();
void LIS3MDL_MasterStatus();
void LIS3MDL_TransferByte();
void LIS3MDL_TransferMultipleBytes();
void LIS3MDL_ReadAxisRaw(uint8_t * rdPtrL, uint8_t * rdPtrH);
void LIS3MDL_ReadAxisDeg(uint16_t * heading);
void LIS3MDL_ReadMultipleBytes();    
void LIS3MDL_ReadWhoAmIReg(uint8_t * rdPtr);
void LIS3MDL_ReadCtrlReg();

void LSM6DS3_Begin();
void LSM6DS3_ReadAxisRaw(uint8_t * rdPtrL, uint8_t * rdPtrH);
void LSM6DS3_ReadAxisDeg(uint16_t * heading);
void LSM6DS3_ReadMultipleBytes();    
void LSM6DS3_ReadWhoAmIReg(uint8_t * rdPtr);
void LSM6DS3_ReadCtrlReg(uint8_t ControlReg[10]);

/** The magnetometer ranges */
typedef enum {
  LIS3MDL_RANGE_4_GAUSS = 0b00,  ///< +/- 4g (default value)
  LIS3MDL_RANGE_8_GAUSS = 0b01,  ///< +/- 8g
  LIS3MDL_RANGE_12_GAUSS = 0b10, ///< +/- 12g
  LIS3MDL_RANGE_16_GAUSS = 0b11, ///< +/- 16g
} lis3mdl_range_t;

/** The magnetometer data rate, includes FAST_ODR bit */
typedef enum {
  LIS3MDL_DATARATE_0_625_HZ = 0b0000, ///<  0.625 Hz
  LIS3MDL_DATARATE_1_25_HZ = 0b0010,  ///<  1.25 Hz
  LIS3MDL_DATARATE_2_5_HZ = 0b0100,   ///<  2.5 Hz
  LIS3MDL_DATARATE_5_HZ = 0b0110,     ///<  5 Hz
  LIS3MDL_DATARATE_10_HZ = 0b1000,    ///<  10 Hz
  LIS3MDL_DATARATE_20_HZ = 0b1010,    ///<  20 Hz
  LIS3MDL_DATARATE_40_HZ = 0b1100,    ///<  40 Hz
  LIS3MDL_DATARATE_80_HZ = 0b1110,    ///<  80 Hz
  LIS3MDL_DATARATE_155_HZ = 0b0001,   ///<  155 Hz (FAST_ODR + UHP)
  LIS3MDL_DATARATE_300_HZ = 0b0011,   ///<  300 Hz (FAST_ODR + HP)
  LIS3MDL_DATARATE_560_HZ = 0b0101,   ///<  560 Hz (FAST_ODR + MP)
  LIS3MDL_DATARATE_1000_HZ = 0b0111,  ///<  1000 Hz (FAST_ODR + LP)
} lis3mdl_dataRate_t;

/** The magnetometer performance mode */
typedef enum {
  LIS3MDL_LOWPOWERMODE = 0b00,  ///< Low power mode
  LIS3MDL_MEDIUMMODE = 0b01,    ///< Medium performance mode
  LIS3MDL_HIGHMODE = 0b10,      ///< High performance mode
  LIS3MDL_ULTRAHIGHMODE = 0b11, ///< Ultra-high performance mode
} lis3mdl_performancemode_t;

/** The magnetometer operation mode */
typedef enum {
  LIS3MDL_CONTINUOUSMODE = 0b00, ///< Continuous conversion
  LIS3MDL_SINGLEMODE = 0b01,     ///< Single-shot conversion
  LIS3MDL_POWERDOWNMODE = 0b11,  ///< Powered-down mode
} lis3mdl_operationmode_t;    
    



    
#endif
/* [] END OF FILE */
