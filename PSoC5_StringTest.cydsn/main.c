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
#include "string.h"
#include "stdlib.h"
#include "stdio.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        CyDelay(100);
        char string[30] = "002, 0, 180\n";
        char * next, *next2;
        double ret = strtod(string, &next);
        double ret2 = strtod(string, &next2);
        
        
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
