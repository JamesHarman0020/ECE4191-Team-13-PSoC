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

extern void HCSR04_Begin();
extern void distMeasure();
extern void distMeasureL();
extern void distMeasureR();
CY_ISR(CaptureL);
CY_ISR(CaptureR);

#endif

/* [] END OF FILE */
