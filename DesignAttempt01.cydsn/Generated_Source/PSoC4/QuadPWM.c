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

#include "QuadPWM.h"

/*******************************************************************************
* Function Name: QuadPWM_Init
********************************************************************************
*
* Summary:
*  Initialize the PWM based on the duty cycles provided in the customizer.
*
* Parameters:
*  None.
*                   
* Return:
*  None.
*
*
*******************************************************************************/
void QuadPWM_Init(void)
{
    /* Initialize the datapath */
    QuadPWM_DP_AUX_CTL = QuadPWM_DP_INIT;
    
    /* Set the duty cycles */
    QuadPWM_REG_D0 = QuadPWM_MAX_DUTY_CYCLE - QuadPWM_DUTYE_CYCLE_1;
    QuadPWM_REG_D1 = QuadPWM_MAX_DUTY_CYCLE - QuadPWM_DUTYE_CYCLE_2;
    QuadPWM_REG_F0 = QuadPWM_MAX_DUTY_CYCLE - QuadPWM_DUTYE_CYCLE_3;
    QuadPWM_REG_F1 = QuadPWM_MAX_DUTY_CYCLE - QuadPWM_DUTYE_CYCLE_4;
}

/*******************************************************************************
* Function Name: QuadPWM_SetDutyCycle
********************************************************************************
*
* Summary:
*  Set the duty cycle for the given PWM output.
*
* Parameters:
*  pwm:       PWM output to be set (from 1 to 4)
*  dutyCycle: new duty cycle value (from 0 to 255)
*                   
* Return:
*  None.
*
*
*******************************************************************************/
void QuadPWM_SetDutyCycle(uint32 pwm, uint32 dutyCycle)
{
    switch (pwm)
    {
        case QuadPWM_PWM_1:
            QuadPWM_REG_D0 = QuadPWM_MAX_DUTY_CYCLE - (uint8) dutyCycle;
            break;
        case QuadPWM_PWM_2:
            QuadPWM_REG_D1 = QuadPWM_MAX_DUTY_CYCLE - (uint8) dutyCycle;
            break;
        case QuadPWM_PWM_3:
            QuadPWM_REG_F0 = QuadPWM_MAX_DUTY_CYCLE - (uint8) dutyCycle;
            break;
        case QuadPWM_PWM_4:
            QuadPWM_REG_F1 = QuadPWM_MAX_DUTY_CYCLE - (uint8) dutyCycle;
            break;
        default:
            break;
    }
}

/* [] END OF FILE */
