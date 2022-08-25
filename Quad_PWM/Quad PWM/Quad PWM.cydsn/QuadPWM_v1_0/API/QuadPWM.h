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

#ifndef `$INSTANCE_NAME`_H
#define `$INSTANCE_NAME`_H

#include <cytypes.h>
    
/*******************************************************************************
* Datapath registers and pointers
*******************************************************************************/
#define `$INSTANCE_NAME`_REG_A0  (*(reg8 *)  `$INSTANCE_NAME`_PwmDatapath_u0__A0_REG)
#define `$INSTANCE_NAME`_PTR_A0  ( (reg8 *)  `$INSTANCE_NAME`_PwmDatapath_u0__A0_REG)

#define `$INSTANCE_NAME`_REG_A1  (*(reg8 *)  `$INSTANCE_NAME`_PwmDatapath_u0__A1_REG)
#define `$INSTANCE_NAME`_PTR_A1  ( (reg8 *)  `$INSTANCE_NAME`_PwmDatapath_u0__A1_REG)

#define `$INSTANCE_NAME`_REG_D0  (*(reg8 *)  `$INSTANCE_NAME`_PwmDatapath_u0__D0_REG)
#define `$INSTANCE_NAME`_PTR_D0  ( (reg8 *)  `$INSTANCE_NAME`_PwmDatapath_u0__D0_REG)

#define `$INSTANCE_NAME`_REG_D1  (*(reg8 *)  `$INSTANCE_NAME`_PwmDatapath_u0__D1_REG)
#define `$INSTANCE_NAME`_PTR_D1  ( (reg8 *)  `$INSTANCE_NAME`_PwmDatapath_u0__D1_REG)

#define `$INSTANCE_NAME`_REG_F0  (*(reg8 *)  `$INSTANCE_NAME`_PwmDatapath_u0__F0_REG)
#define `$INSTANCE_NAME`_PTR_F0  ( (reg8 *)  `$INSTANCE_NAME`_PwmDatapath_u0__F0_REG)

#define `$INSTANCE_NAME`_REG_F1  (*(reg8 *)  `$INSTANCE_NAME`_PwmDatapath_u0__F1_REG)
#define `$INSTANCE_NAME`_PTR_F1  ( (reg8 *)  `$INSTANCE_NAME`_PwmDatapath_u0__F1_REG)

#define `$INSTANCE_NAME`_DP_AUX_CTL (*(reg8 *)`$INSTANCE_NAME`_PwmDatapath_u0__DP_AUX_CTL_REG)

/*******************************************************************************
* Parameter Constants from the Customizer
*******************************************************************************/
#define `$INSTANCE_NAME`_DUTYE_CYCLE_1  `$DutyCycle1`u
#define `$INSTANCE_NAME`_DUTYE_CYCLE_2  `$DutyCycle2`u
#define `$INSTANCE_NAME`_DUTYE_CYCLE_3  `$DutyCycle3`u
#define `$INSTANCE_NAME`_DUTYE_CYCLE_4  `$DutyCycle4`u

/*******************************************************************************
* Auxiliary Constants
*******************************************************************************/
#define `$INSTANCE_NAME`_MAX_DUTY_CYCLE     255u
#define `$INSTANCE_NAME`_MIN_DUTY_CYCLE     0u    
#define `$INSTANCE_NAME`_PWM_1              1u
#define `$INSTANCE_NAME`_PWM_2              2u
#define `$INSTANCE_NAME`_PWM_3              3u
#define `$INSTANCE_NAME`_PWM_4              4u
#define `$INSTANCE_NAME`_DP_INIT            0x3u
    
/*******************************************************************************
* Prototype Functions
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void);
void `$INSTANCE_NAME`_SetDutyCycle(uint32 pwm, uint32 dutyCyle);

#endif /* `$INSTANCE_NAME`_H */

/* [] END OF FILE */
