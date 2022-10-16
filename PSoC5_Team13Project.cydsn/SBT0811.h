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
#ifndef SBT0811
#define SBT0811

#define STEPS_PER_REV 512

void Stepper_On();
void Stepper_Off();
void Stepper_OneRot();
extern void moveAngle(float angle);

#endif    
/* [] END OF FILE */
