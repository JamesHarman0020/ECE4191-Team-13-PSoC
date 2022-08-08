/*******************************************************************************
* File Name: TB9051_EN.c  
* Version 1.80
*
* Description:
*  This file contains API to enable firmware control of a Control Register.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "TB9051_EN.h"

/* Check for removal by optimization */
#if !defined(TB9051_EN_Sync_ctrl_reg__REMOVED)

    
/*******************************************************************************
* Function Name: TB9051_EN_Write
********************************************************************************
*
* Summary:
*  Write a byte to the Control Register.
*
* Parameters:
*  control:  The value to be assigned to the Control Register.
*
* Return:
*  None.
*
*******************************************************************************/
void TB9051_EN_Write(uint8 control) 
{
    TB9051_EN_Control = control;
}


/*******************************************************************************
* Function Name: TB9051_EN_Read
********************************************************************************
*
* Summary:
*  Reads the current value assigned to the Control Register.
*
* Parameters:
*  None.
*
* Return:
*  Returns the current value in the Control Register.
*
*******************************************************************************/
uint8 TB9051_EN_Read(void) 
{
    return TB9051_EN_Control;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
