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
// First development will assume full function calls are sent
// If this is unviable we will then send numbers over serial and simply use a lookup table

#include "project.h"
#include "main.c"
#include "string.h"


typedef struct {char *fn; int val;} fn_struct;
static fn_struct LUT[] = {
      {"TB9051_VehForward", 0001}   
};

/*static fn_struct LUT[] = { // 50 functions with 30 character names
    {"LIS3MDL_Begin", 0001},
    {"LIS3MDL_MasterStatus", 0002},
    {"LIS3MDL_TransferByte", 0003},
"LIS3MDL_TransferMultipleBytes", 0004
"LIS3MDL_ReadAxisRaw",
"LIS3MDL_ReadAxisDeg",
"LIS3MDL_ReadMultipleBytes",    
"LIS3MDL_ReadWhoAmIReg",
"LIS3MDL_ReadCtrlReg",
"LSM6DS3_Begin",
"LSM6DS3_ReadAxisRaw",
"LSM6DS3_ReadAxisDeg",
"LSM6DS3_ReadMultipleBytes",   
"LSM6DS3_ReadWhoAmIReg",
"LSM6DS3_ReadCtrlReg",
"oneStepCCW",
"oneStepCW",
"moveAngle",
"SG90_Begin",
"SG90_ToAngle",
"TB9051_Begin",
"TB9051_Forward",
"TB9051_Reverse",
"TB9051_Brake",
"TB9051_VehForward",
"TB9051_VehReverse",
"TB9051_VehBrake"};*/


    
int ParamLn(char ComString[30]) // Return number of parameters in function call
{
    char *s;                        // start, 
    int n = 0;                      // num. of occurences
    s = strpbrk(ComString, "(");    //Start of parameters
    for (uint8 i = 0; i < strlen(s); i++){
        if (s[i] == ',')
            n++;
    }
    return n+1;
} 

void ParamRet(char ComString[30], int n, int *array){ // Put each parameter into an array
    char *s;                        //start
    s = strpbrk(ComString, "(");    //Start of parameters
    for (int i = 0; i < n; i++) {
        array[i] = atoi(s);
        s = strpbrk(s, ",");
    }
}

void RunFn(char ComString[30], int n, int *array){
    switch (
    
}
/* [] END OF FILE */
