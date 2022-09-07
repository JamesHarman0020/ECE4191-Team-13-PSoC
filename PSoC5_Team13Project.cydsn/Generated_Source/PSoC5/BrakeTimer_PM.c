/*******************************************************************************
* File Name: BrakeTimer_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "BrakeTimer.h"

static BrakeTimer_backupStruct BrakeTimer_backup;


/*******************************************************************************
* Function Name: BrakeTimer_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  BrakeTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void BrakeTimer_SaveConfig(void) 
{
    #if (!BrakeTimer_UsingFixedFunction)
        BrakeTimer_backup.TimerUdb = BrakeTimer_ReadCounter();
        BrakeTimer_backup.InterruptMaskValue = BrakeTimer_STATUS_MASK;
        #if (BrakeTimer_UsingHWCaptureCounter)
            BrakeTimer_backup.TimerCaptureCounter = BrakeTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!BrakeTimer_UDB_CONTROL_REG_REMOVED)
            BrakeTimer_backup.TimerControlRegister = BrakeTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: BrakeTimer_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  BrakeTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void BrakeTimer_RestoreConfig(void) 
{   
    #if (!BrakeTimer_UsingFixedFunction)

        BrakeTimer_WriteCounter(BrakeTimer_backup.TimerUdb);
        BrakeTimer_STATUS_MASK =BrakeTimer_backup.InterruptMaskValue;
        #if (BrakeTimer_UsingHWCaptureCounter)
            BrakeTimer_SetCaptureCount(BrakeTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!BrakeTimer_UDB_CONTROL_REG_REMOVED)
            BrakeTimer_WriteControlRegister(BrakeTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: BrakeTimer_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  BrakeTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void BrakeTimer_Sleep(void) 
{
    #if(!BrakeTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(BrakeTimer_CTRL_ENABLE == (BrakeTimer_CONTROL & BrakeTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            BrakeTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            BrakeTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    BrakeTimer_Stop();
    BrakeTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: BrakeTimer_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  BrakeTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void BrakeTimer_Wakeup(void) 
{
    BrakeTimer_RestoreConfig();
    #if(!BrakeTimer_UDB_CONTROL_REG_REMOVED)
        if(BrakeTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                BrakeTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
