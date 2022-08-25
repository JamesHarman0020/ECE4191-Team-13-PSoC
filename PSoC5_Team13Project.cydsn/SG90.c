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
#include "SG90.h"
#include "stdio.h"
#include <stdlib.h>
#include "project.h"
#include <math.h>
/* [] END OF FILE */


void SG90_Begin() {
    PWM_Start();
    PWM_WritePeriod(6400); // MAGIC NUMBER
    PWM_WriteCompare(480);
    PWM_SetCompareMode(PWM__B_PWM__LESS_THAN_OR_EQUAL);    
}

void SG90_ToAngle(float angle) { //On datasheet the PWM should be between 1-2ms, in practice it's a bit larger.
    if (angle >= -90 & angle <= 90) {
        // 0 = 480. 1 Degree = 3.5PWM.
        int PWMAngle = 480 - angle*(float)3.5;
        PWM_WriteCompare(PWMAngle);
    }
    else
    {
        char string[40]; sprintf(string,"Error: Angle out of Servo range [90:90]"); UART_PutString(string);
    }
}