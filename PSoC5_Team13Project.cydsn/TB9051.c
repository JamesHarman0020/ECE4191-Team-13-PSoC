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
#include "TB9051.h"
#include "project.h"
#define PI 3.141529

CY_ISR(QD_Read);
unsigned int QD1_Old = 0;
unsigned int QD2_Old = 0;
float d = 0.19; //distance between two wheels
float r_wheel = 0.028; // radien of wheels
float theta = 360/48.0f;

void TB9051_Begin()
{
    QuadPWM_Init();
    for (int i = 1; i <= 4; i++){ 
        QuadPWM_SetDutyCycle(i,0);
    }
    TB9051_EN_Write(0x2); // EN high ENB low
    
    //Enable Quad Dec. 
    TB9051_QD1_Start();
    TB9051_QD2_Start();
    QD1_Timer_Start();
    QD1_ISR_Start();
    QD1_ISR_ClearPending();
    QD1_ISR_StartEx(QD_Read);
    
}

void TB9051_VehForward(int speed) {
    TB9051_Forward(0,speed);
    TB9051_Forward(1,speed);
}

void TB9051_VehReverse(int speed) {
    TB9051_Reverse(0,speed);
    TB9051_Reverse(1,speed);
}

void TB9051_VehBrake() {
    TB9051_Brake(0);
    TB9051_Brake(1);
}

void TB9051_Forward(int motor, int speed)
{ 
    TB9051_Brake(motor);
    if (speed >= QuadPWM_MIN_DUTY_CYCLE & speed <= QuadPWM_MAX_DUTY_CYCLE) {
    //PWM1 H, PWM2 L
    if (motor == 0) {
        QuadPWM_SetDutyCycle(1,speed);
        QuadPWM_SetDutyCycle(2,0);
    }
    else {
        QuadPWM_SetDutyCycle(3,speed);
        QuadPWM_SetDutyCycle(4,0);       
    }
    }
}

void TB9051_Reverse(int motor, int speed)
{ 
    TB9051_Brake(motor);
    if (speed >= QuadPWM_MIN_DUTY_CYCLE & speed <= QuadPWM_MAX_DUTY_CYCLE) {
        //PWM1 L, PWM2 H
        if (motor == 0) {
            QuadPWM_SetDutyCycle(1,0);
            QuadPWM_SetDutyCycle(2,speed);
        }
        else {
            QuadPWM_SetDutyCycle(3,0);
            QuadPWM_SetDutyCycle(4,speed);       
        }
    }
}

void TB9051_Brake(int motor)
{ // To avoid damaging motors, a brake is applied between forward and reverse movements
    if (motor == 0) { // Motor 0
        if (QuadPWM_REG_D0 != 255 & QuadPWM_REG_D1 == 255){ // motor is moving forward
            QuadPWM_SetDutyCycle(1,0);
            QuadPWM_SetDutyCycle(2,0);
        }
        else if (QuadPWM_REG_D0 == 255 & QuadPWM_REG_D1 != 255) // motor is moving backward
        {
            QuadPWM_SetDutyCycle(1,25);
            QuadPWM_SetDutyCycle(2,25);
        }
    }
    else // Motor 1
    {
        if (QuadPWM_REG_F0 != 255 & QuadPWM_REG_F1 == 255){ // motor is moving forward
            QuadPWM_SetDutyCycle(3,0);
            QuadPWM_SetDutyCycle(4,0);
        }
        else if (QuadPWM_REG_F0 == 255 & QuadPWM_REG_F1 != 255) // motor is moving backward
        {
            QuadPWM_SetDutyCycle(3,25);
            QuadPWM_SetDutyCycle(4,25);
        }
    }    
    // TO-DO: ADD non-blocking delay here so that the short brake is applied for a suitable period of time (e.g. 100ms)
    CyDelay(100);
}

void TB9051_VehMoveTo(float x, float y){
    ///// JINGWEI NAVIGATION /////
    // float r,d，v,w;
    // int ticks_per_rev, ticks_l, ticks_r;
    // float S_l = 2*PI*r*ticks_l/ticks_per_rev;
    // float S_r = 2*PI*r*ticks_r/ticks_per_rev;

    // float fai = (S_r - S_l)/d;

    
    float t = 2; // time to reach the destination
    //float a[2] = {0, 0},b[2] = {x, y}; //oringinal opint and destination point
    float theta = atan(y/x);
    float r = (pow(x,2)+pow(y,2))/(2*sqrt((pow(x,2)+pow(y,2)))*cos(theta)); //radien of mid point
    float r_right = r - d/2;
    float r_left = r + d/2;
    float v_right = theta*2*PI*r_right/(360*theta); // linear speed of right wheel
    float v_left = theta*2*PI*r_left/(360*theta); // linear speed of left wheel
    float w_r = v_right/r_wheel; // angular speed of right wheel
    float w_l = v_left/r_wheel; // angular speed of left wheel
    float vRel_left = round(v_left * 255);    // REPLACE THESE
    float vRel_right = round(v_right * 255);
    char string[20]; sprintf(string, "R: %f. L: %f \n", vRel_right, vRel_left); UART_PutString(string);
    
    TB9051_Forward(0, vRel_right);
    TB9051_Forward(1, vRel_left);
}

CY_ISR(QD_Read)
{
    // Get new positions
    int QD1_New = TB9051_QD1_GetCounter();
    int QD2_New = TB9051_QD2_GetCounter();
    
    int QD1_Delta = QD1_New - QD1_Old; 
    int QD2_Delta = QD2_New - QD2_Old; 
    float QD1_Ratio = QD1_Delta / 34.014f;
    float QD2_Ratio = QD2_Delta / 34.014f;
    float w1_Pos = QD1_Ratio * 2 * PI * r_wheel * theta / 360;
    float w2_Pos = QD2_Ratio * 2 * PI * r_wheel * theta / 360;
    float w1_Vel = w1_Pos / 0.020;
    float w2_Vel = w2_Pos / 0.020;
    
    //char string[20]; sprintf(string, "W1: %0.3f W2: %0.3f\n", w1_Vel, w2_Vel); UART_PutString(string);
    fnSend(10, &w1_Vel, &w2_Vel);
    //int QD1_Theta = 0;
    //int QD2_Theta = 0;
    
    //float velocity = 2*PI*r_wheel*
    
    // Keep old positions
    QD1_Old = QD1_New;
    QD2_Old = QD2_New;
}


/* [] END OF FILE */
