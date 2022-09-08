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
float w1_Vel;
float w2_Vel;
float vL,vR;
float pidVelL, pidVelR;
float d = 0.29; //distance between two wheels
float r_wheel = 0.028; // radien of wheels
//float theta = 360/48.0f;
float angVelRotate = 1;
float US_L, US_R; 

// PID Controller Values
#define PID_KP 5.0f
#define PID_KI 2.5f
#define PID_KD 0.25f
#define PID_TAU 0.02f
#define PID_LIM_MIN_INT -254.0f
#define PID_LIM_MAX_INT 254.0f
#define SAMPLE_TIME_S 1.0f
#define SIMULATION_TIME_MAX 100f
#define TOLERANCE 0.1f

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
    
void TB9051_Begin()
{
    QuadPWM_Init();
    for (int i = 1; i <= 4; i++){ 
        QuadPWM_SetDutyCycle(i,0);  // Ensure all PWM signals start low
    }
    TB9051_EN_Write(0x2);           // EN high ENB low
    
    TB9051_QD1_Start();             //Enable Quad Dec. 
    TB9051_QD2_Start();
    QD1_Timer_Start();              //Begin timer that sends QD data to RPi
    QD1_ISR_Start();
    QD1_ISR_ClearPending();
    QD1_ISR_StartEx(QD_Read);
    
    //PID
    PIDController_Init(&pidL);
    PIDController_Init(&pidR);
}

void TB9051_VehForward(float * pVelL, float * pVelR) {
    pidVelL = *pVelL;
    pidVelR = *pVelR;
    
    // PID Control
    /*int i = 0;
    do {
        i++;
        if (pidVelL > 0) {
            PIDController_Update(&pidL, pidVelL, w1_Vel);
            UART_PutString("F");
            QuadPWM_SetDutyCycle(3,(int)pidL.out);
        }
        else{            
            PIDController_Update(&pidL, -pidVelL, -w1_Vel);
            QuadPWM_SetDutyCycle(4,(int)pidL.out);
        }
        if (pidVelR > 0){
            PIDController_Update(&pidR, pidVelR, w2_Vel);
            QuadPWM_SetDutyCycle(1,(int)pidR.out);
        }
        else {
            PIDController_Update(&pidR, -pidVelR, -w2_Vel);
            QuadPWM_SetDutyCycle(2,(int)pidR.out);
        }
        char string[60]; sprintf(string, "t: %0.3f %0.3f. pid: %d %d. vel, w1: %0.3f w2: %0.3f\n", pidVelL, pidVelR, (int)pidL.out, (int)pidR.out, w1_Vel,w2_Vel); UART_PutString(string);
    } while ((i < 100) & (w1_Vel + TOLERANCE < pidVelL | w1_Vel - TOLERANCE > pidVelL | w2_Vel + TOLERANCE < pidVelR | w2_Vel - TOLERANCE > pidVelR));
    */
    }

void TB9051_VehReverse(int speed) {
    TB9051_Reverse(0,speed);
    TB9051_Reverse(1,speed);
}

void TB9051_VehBrake() {
    TB9051_Brake(0);
    TB9051_Brake(1);
}

void TB9051_Forward(int motor, float * pvelocity, int PWM)
{ //Should be a controller based on feedback from motors
    float velocity = *pvelocity;
    
    //TB9051_Brake(motor);
    /*if (motor == 0) {    
        do { 
            PIDController_Update(&pidL, velocity, w1_Vel);
            QuadPWM_SetDutyCycle(3,(int)pidL.out);
            CyDelay(100);
        }
        while (w1_Vel + TOLERANCE < velocity | w1_Vel - TOLERANCE > velocity);
    }
    else if (motor == 1) {
        do { 
            PIDController_Update(&pidR, velocity, w2_Vel);
            QuadPWM_SetDutyCycle(1,(int)pidR.out);
            CyDelay(100);
        }
        while (w2_Vel + TOLERANCE < velocity | w2_Vel - TOLERANCE > velocity);
    }*/
    
    
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

void TB9051_VehMoveTo(float * px, float * py){
    ///// JINGWEI NAVIGATION /////
    // float r,d，v,w;
    // int ticks_per_rev, ticks_l, ticks_r;
    // float S_l = 2*PI*r*ticks_l/ticks_per_rev;
    // float S_r = 2*PI*r*ticks_r/ticks_per_rev;

    // float fai = (S_r - S_l)/d;
    float x = *px; 
    float y = *py;
    
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
    //char string[20]; sprintf(string, "R: %f. L: %f \n", vRel_right, vRel_left); UART_PutString(string);
    
    //TB9051_Forward(0, vRel_right);
    //TB9051_Forward(1, vRel_left);
}

TB9051_VehMoveToBasic(float * pX, float * pY) { //TO-DO
    float x = *pX;          
    float y = *pY;
    float theta = atan(y/x);
    
}

CY_ISR(QD_Read)
{
     // Get new positions
    int QD1_New = TB9051_QD1_GetCounter();
    int QD2_New = TB9051_QD2_GetCounter();
    
    int QD1_Delta = QD1_New - QD1_Old; 
    int QD2_Delta = QD2_New - QD2_Old; 
    float w1_Pos = QD1_Delta * (130E-6f); //found experimentally
    float w2_Pos = QD2_Delta * (130E-6f);    
    w1_Vel = w1_Pos / 0.050;                //TO-DO: Remove Magic Number
    w2_Vel = w2_Pos / 0.050; 
    float w1_angVel = w1_Vel / r_wheel;
    float w2_angVel = w2_Vel / r_wheel;
    float vLin = r_wheel * (w1_angVel + w2_angVel) / 2.0f;
    float vAng = r_wheel * (w1_angVel - w2_angVel) / 2.0f;
    
    //float QD1_Ratio = QD1_Delta / 34.014f; //Gear Ratio
    //float QD2_Ratio = QD2_Delta / 34.014f; //Gear Ratio
    //float w1_Pos = QD1_Ratio * 2 * PI * r_wheel * theta / 360;
    //float w2_Pos = QD2_Ratio * 2 * PI * r_wheel * theta / 360;

    
    // Keep old positions
    accumL += QD1_Delta;
    accumR += QD2_Delta;
    QD1_Old = QD1_New;
    QD2_Old = QD2_New;
    
    //TB9051_QD1_SetCounter(0);
    //TB9051_QD2_SetCounter(0);
    
    
    //char string[50]; sprintf(string, "accum: %ld %ld\n", accumL, accumR); UART_PutString(string);
    if (vLin_Old != vLin | vAng_Old != vAng){ 
        fnSend(8, &vLin, &vAng);
    }   
        
    vLin_Old = vLin;
    vAng_Old = vAng;
}


void linAngtoVel(float * pLinVel, float * pAngVel) {
    float angVel = *pAngVel;
    float linVel = *pLinVel;
    float thetadotL = linVel / r_wheel + (d / 2) * angVel / r_wheel; // Rate of rtotation L. + & - have been swapped
    float thetadotR = linVel / r_wheel - (d / 2) * angVel / r_wheel; // Rate of rotation R
    vL = r_wheel * thetadotL; // m/s
    vR = r_wheel * thetadotR; // m/s
    //char string[20]; sprintf(string,"vL: %0.3f vR: %0.3f", vL, vR); UART_PutString(string);
    pidVelL = vL;
    pidVelR = vR;
    
    /* speed estimation - this can be finetuned */
    float fullSpeedNoLoad = 0.2814784; // m/s
    float vL_PWM = round(vL / fullSpeedNoLoad * 255);
    float vR_PWM = round(vR / fullSpeedNoLoad * 255);
    
    if (vL_PWM > 255) {
        vL_PWM = 255;
    }
    else if (vL_PWM < -255) { 
        vL_PWM = -255; 
    }
    if (vR_PWM > 255) {
        vR_PWM = 255;
    }
    else if (vR_PWM < -255) { 
        vR_PWM = -255; 
    }
    
    if (vL_PWM > 0){ 
        TB9051_Forward(0,0,vL_PWM); 
    }
    else TB9051_Reverse(0, (int)0-vL_PWM);
    
    if (vR_PWM > 0) {
        TB9051_Forward(1,0,vR_PWM); 
    }
    else TB9051_Reverse(1, (int)0-vR_PWM);
    //string[20]; sprintf(string,"vL_PWM: %0.3f vR_PWM: %0.3f", vL_PWM, vR_PWM); UART_PutString(string);
    //TB9051_VehForward(&vL,&vR);    
    //char string[40]; sprintf(string,"vL: %f, vR: %f\n",vL, vR); UART_PutString(string);
}


void LinAngtoPos(float * linVel, float * angVel, float * time)
{ // 3 Parameters. Troubling.
    // TO-DO  
    
}

void vehForwardDist(float * pDist) { // This function is blocking
    float dist = *pDist;
    float dispL = 0;
    float dispR = 0;
    float origPosL = TB9051_QD1_GetCounter();
    float origPosR = TB9051_QD1_GetCounter();
    QuadPWM_SetDutyCycle(3,200);
    QuadPWM_SetDutyCycle(1,200);
    float targetCount = dist / (92E-6f);
    do { 
        dispL = TB9051_QD1_GetCounter() - origPosL;
        dispR = TB9051_QD2_GetCounter() - origPosR;
        //char string[80]; sprintf(string, "displacement: %0.3f %0.3f\n", dispL, dispR); UART_PutString(string);
    }
    while (dispL < targetCount & dispR < targetCount); 

    QuadPWM_SetDutyCycle(3,0);    
    QuadPWM_SetDutyCycle(1,0);
    TB9051_QD1_SetCounter(0); 
    TB9051_QD2_SetCounter(0); 
}

void staticRotate(float * pAngle){ // in degrees
    float angle = *pAngle;
    long dispL = 0;
    long dispR = 0;
    long origPosL = TB9051_QD1_GetCounter();
    long origPosR = TB9051_QD1_GetCounter();
    float targetCountL, targetCountR; 
    if (angle > 0) {
        targetCountL = (d-0.07) * PI * (angle / 360) / (92E-6);
        targetCountR = -targetCountL;
        QuadPWM_SetDutyCycle(2,100);
        QuadPWM_SetDutyCycle(3,100);
    }
    if (angle < 0) {
        float targetcountR = (d-0.07) * PI * (angle / 360) / (92E-6);
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
    float wP0to1 = 0.6;
    float wP1to2 = 0.6;
    float angle0to1 = 90.0;
    vehForwardDist(&wP0to1);
    staticRotate(&angle0to1);
    CyDelay(5000);
    vehForwardDist(&wP1to2);
}

void prelimPath_Avoid(){
    float wP0to1 = 0.6;
    float wP1to2 = 0.6;
    float angle0to1 = 90.0;
    vehForwardDist(&wP0to1);
    staticRotate(&angle0to1);
    CyDelay(5000);
    
    // Begin avoidance in the route
    float angleAvoidR = -10;
    float angleAvoidL = 10;
    do {
        if (US_L < 0.2)
            staticRotate(&angleAvoidL); 
        else if (US_R < 0.2)
            staticRotate(&angleAvoidR);
    } while (US_L < 0.4 | US_R < 0.4);
        
}
/* [] END OF FILE */
