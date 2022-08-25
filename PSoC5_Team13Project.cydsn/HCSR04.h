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
#ifndef HCSR04
#define HCSR04

void distMeasure();
void distMeasureL();
void distMeasureR();
CY_ISR(CaptureL);
CY_ISR(CaptureR);

#endif

/* [] END OF FILE */
