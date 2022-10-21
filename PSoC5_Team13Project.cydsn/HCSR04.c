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
#include "project.h"
#include "HCSR04.h"
#include "stdio.h"
#include <stdlib.h>
#include "HCSR04.h"
#define AV_Ln 5

float spSound = 331.5;
CY_ISR(Capture2);
CY_ISR(Trigger);
int mCounterR = 0;
int mCounterL = 0;
int initFlag = 0;
int compLFlag = 0;
int compRFlag = 0;
float distL[AV_Ln] = {0};
float distAvL = 0;
float distAvR = 0;
float distR[AV_Ln] = {0};
extern float US_L, US_R;
int lockoutCount = 0;

void HCSR04_Begin(){
    E_R_Start();                // Begin interrupts
    E_L_Start();
    E_R_ClearPending();
    E_R_StartEx(CaptureR);
    E_L_ClearPending();
    E_L_StartEx(CaptureL);
    US_Trig_Start();
    US_Trig_ClearPending();
    US_Trig_StartEx(Trigger);
    Timer_R_Start();            //Begin Timers
    Timer_L_Start();
    US_Timer_Start();
    initFlag = 1;
}

void distMeasure(){
    if (initFlag){
        compLFlag = 0; compRFlag = 0;
        distMeasureL();
        distMeasureR();
        int i = 0;
        do {
            CyDelayUs(10);
            i++;
        } while((i < 500) & (compLFlag == 0 & compRFlag == 0));
        if (distAvL < 0.1 | distAvR < 0.1) {
            lockoutCount++;
            if (lockoutCount == 3) {
                if (distAvL < distAvR)
                    MotorStop(0);
                else
                    MotorStop(1);  
            lockoutCount = 0;
            }
        }
            
            
        if (distAvL < 0.5 | distAvR < 0.5)
            fnSend(101, &distAvL ,&distAvR);
            
            
    }
    else HCSR04_Begin();
}

void distMeasureL(){
    US_L_Write(1); //write the trigger pin high for greater than 10microseconds
    CyDelayUs(15);
    US_L_Write(0);
}

void distMeasureR(){
    US_R_Write(1); //write the trigger pin high for greater than 10microseconds
    CyDelayUs(15);
    US_R_Write(0);   
}
     
CY_ISR(CaptureR) //ISR3
{
    uint32 clicks = Timer_R_ReadPeriod() - Timer_R_ReadCapture();
    float pulseLength = clicks / (24E6);            // Frequency  
    distR[mCounterR] =  spSound * pulseLength / 2;  // distance to an object = ((speed of sound in the air)*time)/2
    mCounterR++;
    
    if (mCounterR == 3) {                           
        distAvR = (distR[0] + distR[1] + distR[2]) / AV_Ln;
        mCounterR = 0;
    }
    else distMeasureR();                           // Want to take the average of three measurements
    compRFlag = 1;  
}


CY_ISR(CaptureL) //ISR3
{
    uint32 clicks = Timer_L_ReadPeriod() - Timer_L_ReadCapture();
    float pulseLength = clicks / (24E6);
    distL[mCounterL] =  spSound * pulseLength / 2;//distance to an object = ((speed of sound in the air)*time)/2
    mCounterL++;
    
    if (mCounterL == 3) {
        distAvL = (distL[0] + distL[1] + distL[2]) / AV_Ln;
        US_L = distAvL;
        US_R = distAvR;
        mCounterL = 0;
    }
    else distMeasureL();
    compLFlag = 1;
}

CY_ISR(Trigger)
{
    distMeasure();
}

void MotorStop(int us)
{
   UART_PutString("\n\n\nLOCKOUT TRIGGERED\n\n\n");
   uint8 j = CyEnterCriticalSection();
     
    if (us == 1) { //Obstacle was on the left
        QuadPWM_SetDutyCycle(1,00); //Reverse
        QuadPWM_SetDutyCycle(2,100);
        QuadPWM_SetDutyCycle(3,00);
        QuadPWM_SetDutyCycle(4, 100);
        CyDelay(500);
        
        QuadPWM_SetDutyCycle(1,00); //Turn
        QuadPWM_SetDutyCycle(2,100);
        QuadPWM_SetDutyCycle(3,100);
        QuadPWM_SetDutyCycle(4,00);
        CyDelay(2000);
        QuadPWM_SetDutyCycle(2,00); 
        QuadPWM_SetDutyCycle(3,00);   
    }
    
    else { // Obstacle was on the right
        QuadPWM_SetDutyCycle(1,00); //Reverse
        QuadPWM_SetDutyCycle(2,100);
        QuadPWM_SetDutyCycle(3,00);
        QuadPWM_SetDutyCycle(4, 100);
        CyDelay(500);
        
        QuadPWM_SetDutyCycle(1,100); //Turn
        QuadPWM_SetDutyCycle(2,00);
        QuadPWM_SetDutyCycle(3,00);
        QuadPWM_SetDutyCycle(4,100);
        CyDelay(2000);
        QuadPWM_SetDutyCycle(1,00);
        QuadPWM_SetDutyCycle(4,00);
    }
    CyExitCriticalSection(j);
}


/* [] END OF FILE */
