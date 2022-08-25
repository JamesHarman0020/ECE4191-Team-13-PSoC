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
#include <project.h>

int main()
{
    QuadPWM_Init();
    
    QuadPWM_SetDutyCycle(QuadPWM_PWM_1, 64);
    QuadPWM_SetDutyCycle(QuadPWM_PWM_2, 128);
    QuadPWM_SetDutyCycle(QuadPWM_PWM_3, 255);
    QuadPWM_SetDutyCycle(QuadPWM_PWM_4, 0);
    
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
