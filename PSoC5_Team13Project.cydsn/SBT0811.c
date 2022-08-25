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


void oneStepCCW(int speed) // One step in the counterclockwise direction, multiplex motor inputs.
{
    StepperDriver_Write(0b1000); // TO-DO: Move this to interrupt based so that it isn't blocking.
    CyDelay(speed);             
    StepperDriver_Write(0b1100);
    CyDelay(speed);
    StepperDriver_Write(0b0100);
    CyDelay(speed);
    StepperDriver_Write(0b0110);
    CyDelay(speed);
    StepperDriver_Write(0b0010);
    CyDelay(speed);
    StepperDriver_Write(0b0011);
    CyDelay(speed);
    StepperDriver_Write(0b0001);
    CyDelay(speed);
    StepperDriver_Write(0b1001);
    CyDelay(speed);
}

void oneStepCW(int speed) // One step in the clockwise direction
{
    StepperDriver_Write(0b1001); // TO-DO: Move this to interrupt based so that it isn't blocking.
    CyDelay(speed);
    StepperDriver_Write(0b0001);
    CyDelay(speed);
    StepperDriver_Write(0b0011);
    CyDelay(speed);
    StepperDriver_Write(0b0010);
    CyDelay(speed);
    StepperDriver_Write(0b0110);
    CyDelay(speed);
    StepperDriver_Write(0b0100);
    CyDelay(speed);
    StepperDriver_Write(0b1100);
    CyDelay(speed);
    StepperDriver_Write(0b1000);
    CyDelay(speed);
}

void moveAngle(float angle){ //angle taken in degrees
    float steps = angle * STEPS_PER_REV / 360;
    int stepsRound = (int)steps; //number of steps to turn that number of degrees
    char string[40];
    sprintf(string, "steps = %d error = %f\n", stepsRound, (float)(steps-stepsRound));
    UART_PutString(string);
    for (int i = 0; i < stepsRound; i++) {
        oneStepCW(3);
    }
}