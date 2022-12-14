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
void TB9051_VehForward_PID(float * pVel);
void TB9051_VehReverse_PID(float * pVel);
void TB9051_VehBrake();
void TB9051_Forward(int motor, int PWM);
void TB9051_Reverse(int motor, int speed);
void TB9051_Brake(int motor);
void TB9051_VehMoveTo(float * x, float * y); // TO-DO
void linAngToVel(float * pLinVel, float * pAngVel);
void linAngToVel_PID(float * pLinVel, float * pAngVel);
void vehForwardDist(float * pDist);
void staticRotate(float * angle);
void Veh_RotateTo(float * pTheta);
void prelimPath();

#endif

/* [] END OF FILE */
