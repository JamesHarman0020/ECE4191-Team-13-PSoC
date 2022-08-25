/*******************************************************************************
* File Name: StepperDriver_PM.c
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

#include "StepperDriver.h"

/* Check for removal by optimization */
#if !defined(StepperDriver_Sync_ctrl_reg__REMOVED)

static StepperDriver_BACKUP_STRUCT  StepperDriver_backup = {0u};

    
/*******************************************************************************
* Function Name: StepperDriver_SaveConfig
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
void StepperDriver_SaveConfig(void) 
{
    StepperDriver_backup.controlState = StepperDriver_Control;
}


/*******************************************************************************
* Function Name: StepperDriver_RestoreConfig
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
void StepperDriver_RestoreConfig(void) 
{
     StepperDriver_Control = StepperDriver_backup.controlState;
}


/*******************************************************************************
* Function Name: StepperDriver_Sleep
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
void StepperDriver_Sleep(void) 
{
    StepperDriver_SaveConfig();
}


/*******************************************************************************
* Function Name: StepperDriver_Wakeup
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
void StepperDriver_Wakeup(void)  
{
    StepperDriver_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
