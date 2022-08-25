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


#include "stdio.h"
#include <stdlib.h>
#include "project.h"
#include "HCSR04.h"

CY_ISR(Capture);

void distMeasure(){
    US_Write(0b11);
    CyDelayUs(15);
    US_Write(0b00);
}

     
    //write the trigger pin high for greater than 10microseconds
    
    //Wait for a pulse in
    // calculate time delta and therefore distance


CY_ISR(Capture) //ISR3
{
    uint16 result = Timer_ReadCapture();
    char string[20]; sprintf(string, "%hu\n", result); UART_PutString(string);
}
/* [] END OF FILE */
