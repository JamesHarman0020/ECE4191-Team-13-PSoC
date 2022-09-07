/*******************************************************************************
* File Name: BrakeCounterTrig_PM.c
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

#include "BrakeCounterTrig.h"

/* Check for removal by optimization */
#if !defined(BrakeCounterTrig_Sync_ctrl_reg__REMOVED)

static BrakeCounterTrig_BACKUP_STRUCT  BrakeCounterTrig_backup = {0u};

    
/*******************************************************************************
* Function Name: BrakeCounterTrig_SaveConfig
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
void BrakeCounterTrig_SaveConfig(void) 
{
    BrakeCounterTrig_backup.controlState = BrakeCounterTrig_Control;
}


/*******************************************************************************
* Function Name: BrakeCounterTrig_RestoreConfig
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
void BrakeCounterTrig_RestoreConfig(void) 
{
     BrakeCounterTrig_Control = BrakeCounterTrig_backup.controlState;
}


/*******************************************************************************
* Function Name: BrakeCounterTrig_Sleep
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
void BrakeCounterTrig_Sleep(void) 
{
    BrakeCounterTrig_SaveConfig();
}


/*******************************************************************************
* Function Name: BrakeCounterTrig_Wakeup
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
void BrakeCounterTrig_Wakeup(void)  
{
    BrakeCounterTrig_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
