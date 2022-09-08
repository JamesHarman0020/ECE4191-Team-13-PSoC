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
void TB9051_Forward(int motor, float * velocity, int speed);
void TB9051_Reverse(int motor, int speed);
void TB9051_Brake();
void TB9051_VehForward(float * pVelL, float * pVelR);
void TB9051_VehReverse(int speed);
void TB9051_VehBrake();
void TB9051_VehMoveTo(float * x, float * y); // TO-DO
void linAngtoVel(float * pLinVel, float * pAngVel);
void Veh_RotateTo(float * pTheta);
void vehForwardDist(float * pDist);
void staticRotate(float * angle);
void prelimPath();
void prelimPath_Avoid();

#endif

/* [] END OF FILE */
