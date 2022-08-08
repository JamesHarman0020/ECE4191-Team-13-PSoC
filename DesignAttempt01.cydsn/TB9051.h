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
#ifndef TB9051
#define TB9051
    
    
void TB9051_Begin();
void TB9051_Forward(int motor, int speed);
void TB9051_Reverse(int motor, int speed);
void TB9051_Brake();
void TB9051_VehForward(int speed);
void TB9051_VehReverse(int speed);
void TB9051_VehBrake();
#endif

/* [] END OF FILE */
