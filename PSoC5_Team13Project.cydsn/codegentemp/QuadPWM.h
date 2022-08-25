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

#ifndef QuadPWM_H
#define QuadPWM_H

#include <cytypes.h>
    
/*******************************************************************************
* Datapath registers and pointers
*******************************************************************************/
#define QuadPWM_REG_A0  (*(reg8 *)  QuadPWM_PwmDatapath_u0__A0_REG)
#define QuadPWM_PTR_A0  ( (reg8 *)  QuadPWM_PwmDatapath_u0__A0_REG)

#define QuadPWM_REG_A1  (*(reg8 *)  QuadPWM_PwmDatapath_u0__A1_REG)
#define QuadPWM_PTR_A1  ( (reg8 *)  QuadPWM_PwmDatapath_u0__A1_REG)

#define QuadPWM_REG_D0  (*(reg8 *)  QuadPWM_PwmDatapath_u0__D0_REG)
#define QuadPWM_PTR_D0  ( (reg8 *)  QuadPWM_PwmDatapath_u0__D0_REG)

#define QuadPWM_REG_D1  (*(reg8 *)  QuadPWM_PwmDatapath_u0__D1_REG)
#define QuadPWM_PTR_D1  ( (reg8 *)  QuadPWM_PwmDatapath_u0__D1_REG)

#define QuadPWM_REG_F0  (*(reg8 *)  QuadPWM_PwmDatapath_u0__F0_REG)
#define QuadPWM_PTR_F0  ( (reg8 *)  QuadPWM_PwmDatapath_u0__F0_REG)

#define QuadPWM_REG_F1  (*(reg8 *)  QuadPWM_PwmDatapath_u0__F1_REG)
#define QuadPWM_PTR_F1  ( (reg8 *)  QuadPWM_PwmDatapath_u0__F1_REG)

#define QuadPWM_DP_AUX_CTL (*(reg8 *)QuadPWM_PwmDatapath_u0__DP_AUX_CTL_REG)

/*******************************************************************************
* Parameter Constants from the Customizer
*******************************************************************************/
#define QuadPWM_DUTYE_CYCLE_1  255u
#define QuadPWM_DUTYE_CYCLE_2  128u
#define QuadPWM_DUTYE_CYCLE_3  64u
#define QuadPWM_DUTYE_CYCLE_4  0u

/*******************************************************************************
* Auxiliary Constants
*******************************************************************************/
#define QuadPWM_MAX_DUTY_CYCLE     255u
#define QuadPWM_MIN_DUTY_CYCLE     0u    
#define QuadPWM_PWM_1              1u
#define QuadPWM_PWM_2              2u
#define QuadPWM_PWM_3              3u
#define QuadPWM_PWM_4              4u
#define QuadPWM_DP_INIT            0x3u
    
/*******************************************************************************
* Prototype Functions
*******************************************************************************/
void QuadPWM_Init(void);
void QuadPWM_SetDutyCycle(uint32 pwm, uint32 dutyCyle);

#endif /* QuadPWM_H */

/* [] END OF FILE */
