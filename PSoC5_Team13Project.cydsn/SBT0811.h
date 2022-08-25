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

void oneStepCCW(int speed);
void oneStepCW(int speed);
extern void moveAngle(float angle);

#endif    
/* [] END OF FILE */
