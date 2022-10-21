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
#include "math.h"
#include "pid.h"
#define PI 3.141529f

long accumL = 0;
long accumR = 0;
CY_ISR(QD_Read);
unsigned int QD1_Old = 0;
unsigned int QD2_Old = 0;
float vLin_Old, vAng_Old;
float accumLPos, accumRPos;
float w1_Vel, w2_Vel;
float vL,vR;
float pidVelL, pidVelR;
float d = 0.217; //distance between two wheels
float r_wheel = 0.028; // radien of wheels
//float theta = 360/48.0f;
float angVelRotate = 1;
float US_L, US_R; 

// PID Controller Values
#define PID_KP 10.0f
#define PID_KI 20.0f
#define PID_KD 1.5f
#define PID_TAU 0.02f
#define PID_LIM_MIN_INT 0.0f
#define PID_LIM_MAX_INT 254.0f
#define SAMPLE_TIME_S 1.0f
#define SIMULATION_TIME_MAX 100f
#define TOLERANCE 0.01f

// Create PID Controller Struct - All Credit to Phillip Salmony
PIDController pidL = { PID_KP, PID_KI, PID_KD,
                        PID_TAU,
                        PID_LIM_MIN_INT, PID_LIM_MAX_INT,
		                PID_LIM_MIN_INT, PID_LIM_MAX_INT,
                        SAMPLE_TIME_S };
PIDController pidR = { PID_KP, PID_KI, PID_KD,
                        PID_TAU,
                        PID_LIM_MIN_INT, PID_LIM_MAX_INT,
		                PID_LIM_MIN_INT, PID_LIM_MAX_INT,
                        SAMPLE_TIME_S };
PIDController pidV = { PID_KP, PID_KI, PID_KD,
                        PID_TAU,
                        PID_LIM_MIN_INT, PID_LIM_MAX_INT,
		                PID_LIM_MIN_INT, PID_LIM_MAX_INT,
                        SAMPLE_TIME_S };
    
void TB9051_Begin()
{
    QuadPWM_Init();
    for (int i = 1; i <= 4; i++){ 
        QuadPWM_SetDutyCycle(i,0);  // Ensure all PWM signals start low
    }
    TB9051_EN_Write(0x1);           // EN high ENB low
    
    TB9051_QD1_Start();             //Enable Quad Dec. 
    TB9051_QD2_Start();
    QD1_Timer_Start();              //Begin timer that sends QD data to RPi
    QD1_ISR_Start();
    QD1_ISR_ClearPending();
    QD1_ISR_StartEx(QD_Read);
    
    //PID
    PIDController_Init(&pidL);
    PIDController_Init(&pidR);
    PIDController_Init(&pidV);
}

void TB9051_VehForward_PID(float *pVel) {
    float vel = *pVel;
    int i = 0;
    do {
        i++;
        PIDController_Update(&pidV, vel, w1_Vel);
        QuadPWM_SetDutyCycle(1,(int)pidV.out);
        QuadPWM_SetDutyCycle(3,(int)pidV.out);
        char string[50]; sprintf(string, "%d. Vel: %.3f, PID: %0.3f\n", i, w1_Vel, pidV.out);UART_PutString(string);
    } while (!(i > 200 | (w1_Vel < vel + TOLERANCE & w1_Vel > vel - TOLERANCE)));
}

void TB9051_VehReverse_PID(float *pVel) {
    float vel = *pVel;
    int i = 0;
    do {
        i++;      
        PIDController_Update(&pidV, vel, -w1_Vel);
        QuadPWM_SetDutyCycle(2,(int)pidV.out);
        QuadPWM_SetDutyCycle(4,(int)pidV.out);
        char string[40]; sprintf(string, "%d. w1_Vel + vel: %0.3f, tol: %f, PID: %.3f\n", i, w1_Vel + vel, TOLERANCE, pidV.out);UART_PutString(string);
    } while (!(i > 200 | (w1_Vel + vel < TOLERANCE & w1_Vel + vel > 0 - TOLERANCE)));
}

void TB9051_VehBrake() {
    TB9051_Brake(0);
    TB9051_Brake(1);
}

void TB9051_Forward(int motor, int PWM)
{ 
    if (PWM >= QuadPWM_MIN_DUTY_CYCLE & PWM <= QuadPWM_MAX_DUTY_CYCLE) {
    //PWM1 H, PWM2 L
    if (motor == 0) {
        QuadPWM_SetDutyCycle(1,PWM);
        QuadPWM_SetDutyCycle(2,0);
    }
    else {
        QuadPWM_SetDutyCycle(3,PWM);
        QuadPWM_SetDutyCycle(4,0);       
    }
    }
}

void TB9051_Reverse(int motor, int PWM)
{ 
    TB9051_Brake(motor);
    if (PWM >= QuadPWM_MIN_DUTY_CYCLE & PWM <= QuadPWM_MAX_DUTY_CYCLE) {
        //PWM1 L, PWM2 H
        if (motor == 0) {
            QuadPWM_SetDutyCycle(1,0);
            QuadPWM_SetDutyCycle(2,PWM);
        }
        else {
            QuadPWM_SetDutyCycle(3,0);
            QuadPWM_SetDutyCycle(4,PWM);       
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
    // TO-DO: ADD non-blocking delay here so that the short brake is applied
    CyDelay(20);
}

void TB9051_VehMoveTo(float * px, float * py){
    float x = *px; 
    float y = *py;
    
    ///// DAVID'S MATHS //////
    float angV = 0.1f * 2.0f*atan2(x,y);
    float linV = 0.1f * sqrt(pow(x,2) + pow(y,2));
    linAngToVel(&linV, &angV);
}


void linAngToVel(float * pLinVel, float * pAngVel) {
    float angVel = *pAngVel;
    float linVel = *pLinVel;
    float thetadotL = linVel / r_wheel + (d / 2) * angVel / r_wheel; // Rate of rtotation L. +/- Swapped
    float thetadotR = linVel / r_wheel - (d / 2) * angVel / r_wheel; // Rate of rotation R
    vL = r_wheel * thetadotL; // m/s
    vR = r_wheel * thetadotR; // m/s
    
    /* speed estimation - this can be finetuned */
    float fullSpeedNoLoad = 0.2025; // m/s
    float vL_PWM = round(vL / fullSpeedNoLoad * 255);
    float vR_PWM = round(vR / fullSpeedNoLoad * 255);
    
    if (vL_PWM > 255) { vL_PWM = 255; }
    else if (vL_PWM < -255) { vL_PWM = -255; }
    if (vR_PWM > 255) { vR_PWM = 255; }
    else if (vR_PWM < -255) { vR_PWM = -255; }
    
    if (vL_PWM > 0){ 
        TB9051_Forward(0,vL_PWM); 
    }
    else TB9051_Reverse(0, (int)0-vL_PWM);
    
    if (vR_PWM > 0) {
        TB9051_Forward(1,vR_PWM); 
    }
    else TB9051_Reverse(1, (int)0-vR_PWM);
    //string[20]; sprintf(string,"vL_PWM: %0.3f vR_PWM: %0.3f", vL_PWM, vR_PWM); UART_PutString(string);
    //TB9051_VehForward(&vL,&vR);    
    //char string[40]; sprintf(string,"vL: %f, vR: %f\n",vL, vR); UART_PutString(string);
}

void linAngToVel_PID(float * pLinVel, float * pAngVel) {
    float angVel = *pAngVel;
    float linVel = *pLinVel;
    float thetadotL = linVel / r_wheel + (d / 2) * angVel / r_wheel; // Rate of rtotation L. +/- Swapped
    float thetadotR = linVel / r_wheel - (d / 2) * angVel / r_wheel; // Rate of rotation R
    vL = r_wheel * thetadotL; // m/s
    vR = r_wheel * thetadotR; // m/s
    //char string[20]; sprintf(string,"vL: %0.3f vR: %0.3f", vL, vR); UART_PutString(string);
    pidVelL = vL;
    pidVelR = vR;
    
    int i = 0;
    if (vL >= 0 & vR >= 0) {
        do {
            i++;      
            PIDController_Update(&pidL, pidVelL, w2_Vel);
            PIDController_Update(&pidR, pidVelR, w1_Vel);
            QuadPWM_SetDutyCycle(1,(int)pidL.out);
            QuadPWM_SetDutyCycle(3,(int)pidR.out);
            char string[50]; sprintf(string,"%d. vL: %0.3f vR: %0.3f PIDL: %0.2f, PIDR: %0.2f\n", i, vL, vR, pidL.out, pidR.out); UART_PutString(string);
        } while (!(i > 400));
    }
    else {
        if (vL >= 0) { // vR must be less than zero   
            do {
                i++;
                PIDController_Update(&pidL, pidVelL, w2_Vel);
                PIDController_Update(&pidR, -pidVelR, -w1_Vel);
                QuadPWM_SetDutyCycle(1,(int)pidL.out);
                QuadPWM_SetDutyCycle(4,(int)pidR.out);
            char string[50]; sprintf(string,"%d. vL: %0.3f vR: %0.3f PIDL: %0.2f, PIDR: %0.2f\n", i, w2_Vel, w1_Vel, pidL.out, pidR.out); UART_PutString(string);
            } while (!(i > 400));
        }
        else if (vR >= 0) { //vL must be less than zero
           do {
                PIDController_Update(&pidL, -pidVelL, -w2_Vel);
                PIDController_Update(&pidR, pidVelR, w1_Vel);
                QuadPWM_SetDutyCycle(2,(int)pidL.out);
                QuadPWM_SetDutyCycle(3,(int)pidR.out);
            char string[50]; sprintf(string,"vL: %0.3f vR: %0.3f PIDL: %0.2f, PIDR: %0.2f\n", vL, vR, pidL.out, pidR.out); UART_PutString(string);
            } while (!(i > 400));
        }
        else { // vL & vR must be less than zero
            do {
                PIDController_Update(&pidL, -pidVelL, -w2_Vel);
                PIDController_Update(&pidR, -pidVelR, -w1_Vel);
                QuadPWM_SetDutyCycle(2,(int)pidL.out);
                QuadPWM_SetDutyCycle(4,(int)pidR.out);
            char string[50]; sprintf(string,"vL: %0.3f vR: %0.3f PIDL: %0.2f, PIDR: %0.2f\n", vL, vR, pidL.out, pidR.out); UART_PutString(string);
            } while (!(i > 400));
        }
    }
}

    
void vehForwardDist(float * pDist) { // This function is blocking
    float dist = *pDist;
    long initialL = accumL;
    long initialR = accumR;
    long targL = initialL + dist/(92E-6f);
    long targR = initialR + dist/(92E-6f);
    float linV = 0.1;
    float linA = 0.0;
    
    linAngtoVel(&linV, &linA);
    do {
        //char string[80]; sprintf(string, "displacement: %0.3f %0.3f\n", dispL, dispR); UART_PutString(string);
    }
    while (accumL < targL & accumR < targR); 

    QuadPWM_SetDutyCycle(3,0);    
    QuadPWM_SetDutyCycle(1,0);
}

void staticRotate(float * pAngle){ // in degrees
    float angle = *pAngle;
    long dispL = 0;
    long dispR = 0;
    long origPosL = TB9051_QD1_GetCounter();
    long origPosR = TB9051_QD1_GetCounter();
    float targetCountL, targetCountR; 
    if (angle > 0) {
        targetCountL = (d-0.07) * PI * (angle / 360) / (105E-6f);
        targetCountR = -targetCountL;
        QuadPWM_SetDutyCycle(2,100);
        QuadPWM_SetDutyCycle(3,100);
    }
    if (angle < 0) {
        float targetcountR = (d-0.07) * PI * (angle / 360) / (105E-6f);
        float targetCountL = -targetCountL;
        QuadPWM_SetDutyCycle(1,100);
        QuadPWM_SetDutyCycle(4,100);
    }
    
    do { 
        dispL = TB9051_QD1_GetCounter() - origPosL;
        dispR = TB9051_QD2_GetCounter() - origPosR;
        /* //DEBUG
        char string[80]; sprintf(string, "val: %hd %hd. displacement: %ld %ld. target: %0.3f %0.3f. \n", 
          TB9051_QD1_GetCounter(), TB9051_QD2_GetCounter(), dispL, dispR, targetCountL, targetCountR); UART_PutString(string);
        */
    } while (dispL < targetCountL);// & dispR < targetCountR); 

    QuadPWM_SetDutyCycle(1,0);    
    QuadPWM_SetDutyCycle(2,0);   
    QuadPWM_SetDutyCycle(3,0);   
    QuadPWM_SetDutyCycle(4,0);
    TB9051_QD1_SetCounter(0); 
    TB9051_QD2_SetCounter(0); 
}

void prelimPath() {
    float wP0to1 = 0.845;
    float wP1to2 = 0.6;
    float angle0to1 = 45.0;
    
    float angle1to2 = 135.0;
    
    staticRotate(&angle0to1);
    vehForwardDist(&wP0to1);
    CyDelay(5000);
    staticRotate(&angle1to2);
    vehForwardDist(&wP1to2);
}

CY_ISR(QD_Read) //TO-DO: Resolve the overflow issue that will occur
{
     // Get new positions
    int QD1_New = TB9051_QD1_GetCounter();
    int QD2_New = TB9051_QD2_GetCounter();
    
    int QD1_Delta = QD1_New - QD1_Old; 
    int QD2_Delta = QD2_New - QD2_Old; 
    float w1_Pos = QD1_Delta * (105E-6f);   //found experimentally
    float w2_Pos = QD2_Delta * (105E-6f);    
    w1_Vel = w1_Pos / 0.050;                //TO-DO: Remove Magic Number
    w2_Vel = w2_Pos / 0.050;                //Divide by amount of time elapsed
    float w1_angVel = w1_Vel / r_wheel;
    float w2_angVel = w2_Vel / r_wheel;
    float vLin = r_wheel * (w1_angVel + w2_angVel) / 2.0f;
    float vAng = r_wheel * (w1_angVel - w2_angVel) / d;
    
    // Keep old positions
    accumL += QD1_Delta;
    accumR += QD2_Delta;
    accumLPos += w1_Pos;
    accumRPos += w2_Pos;
    QD1_Old = QD1_New;
    QD2_Old = QD2_New;
    
    if (vLin_Old != vLin | vAng_Old != vAng | vAng == 0 | vLin == 0){ 
        fnSend(8, &vLin, &vAng);
        //fnSend(14, &accumLPos, &accumRPos); //Send the accumulated position in meters
    }   
        
    vLin_Old = vLin;
    vAng_Old = vAng;
}
/* [] END OF FILE */
