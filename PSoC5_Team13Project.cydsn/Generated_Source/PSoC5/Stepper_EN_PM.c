/*******************************************************************************
* File Name: Stepper_EN_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Stepper_EN.h"

/* Check for removal by optimization */
#if !defined(Stepper_EN_Sync_ctrl_reg__REMOVED)

static Stepper_EN_BACKUP_STRUCT  Stepper_EN_backup = {0u};

    
/*******************************************************************************
* Function Name: Stepper_EN_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Stepper_EN_SaveConfig(void) 
{
    Stepper_EN_backup.controlState = Stepper_EN_Control;
}


/*******************************************************************************
* Function Name: Stepper_EN_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void Stepper_EN_RestoreConfig(void) 
{
     Stepper_EN_Control = Stepper_EN_backup.controlState;
}


/*******************************************************************************
* Function Name: Stepper_EN_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Stepper_EN_Sleep(void) 
{
    Stepper_EN_SaveConfig();
}


/*******************************************************************************
* Function Name: Stepper_EN_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Stepper_EN_Wakeup(void)  
{
    Stepper_EN_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
