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
#include "SBT0811.h"
#include "stdio.h"
#include <stdlib.h>
#include "project.h"
#include <math.h>


void Stepper_On() {
    Stepper_EN_Write(1);   
}

void Stepper_Off() {
    Stepper_EN_Write(0);
        
}

void Stepper_OneRot(){
    Stepper_On();
    CyDelay(900);
    Stepper_Off();
}

void moveAngle(float angle){ // TO-DO:
   /* float steps = angle * STEPS_PER_REV / 360;
    int stepsRound = (int)steps; //number of steps to turn that number of degrees
    char string[40];
    sprintf(string, "steps = %d error = %f\n", stepsRound, (float)(steps-stepsRound));
    UART_PutString(string);
    for (int i = 0; i < stepsRound; i++) {
        oneStepCW(3);
    }*/
}