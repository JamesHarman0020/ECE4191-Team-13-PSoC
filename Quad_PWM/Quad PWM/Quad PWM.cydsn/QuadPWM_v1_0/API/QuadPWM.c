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

#include "`$INSTANCE_NAME`.h"

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
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
void `$INSTANCE_NAME`_Init(void)
{
    /* Initialize the datapath */
    `$INSTANCE_NAME`_DP_AUX_CTL = `$INSTANCE_NAME`_DP_INIT;
    
    /* Set the duty cycles */
    `$INSTANCE_NAME`_REG_D0 = `$INSTANCE_NAME`_MAX_DUTY_CYCLE - `$INSTANCE_NAME`_DUTYE_CYCLE_1;
    `$INSTANCE_NAME`_REG_D1 = `$INSTANCE_NAME`_MAX_DUTY_CYCLE - `$INSTANCE_NAME`_DUTYE_CYCLE_2;
    `$INSTANCE_NAME`_REG_F0 = `$INSTANCE_NAME`_MAX_DUTY_CYCLE - `$INSTANCE_NAME`_DUTYE_CYCLE_3;
    `$INSTANCE_NAME`_REG_F1 = `$INSTANCE_NAME`_MAX_DUTY_CYCLE - `$INSTANCE_NAME`_DUTYE_CYCLE_4;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetDutyCycle
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
void `$INSTANCE_NAME`_SetDutyCycle(uint32 pwm, uint32 dutyCycle)
{
    switch (pwm)
    {
        case `$INSTANCE_NAME`_PWM_1:
            `$INSTANCE_NAME`_REG_D0 = `$INSTANCE_NAME`_MAX_DUTY_CYCLE - (uint8) dutyCycle;
            break;
        case `$INSTANCE_NAME`_PWM_2:
            `$INSTANCE_NAME`_REG_D1 = `$INSTANCE_NAME`_MAX_DUTY_CYCLE - (uint8) dutyCycle;
            break;
        case `$INSTANCE_NAME`_PWM_3:
            `$INSTANCE_NAME`_REG_F0 = `$INSTANCE_NAME`_MAX_DUTY_CYCLE - (uint8) dutyCycle;
            break;
        case `$INSTANCE_NAME`_PWM_4:
            `$INSTANCE_NAME`_REG_F1 = `$INSTANCE_NAME`_MAX_DUTY_CYCLE - (uint8) dutyCycle;
            break;
        default:
            break;
    }
}

/* [] END OF FILE */
