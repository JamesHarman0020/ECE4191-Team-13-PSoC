/*******************************************************************************
* File Name: US_Timer_PM.c
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

#include "US_Timer.h"

static US_Timer_backupStruct US_Timer_backup;


/*******************************************************************************
* Function Name: US_Timer_SaveConfig
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
*  US_Timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void US_Timer_SaveConfig(void) 
{
    #if (!US_Timer_UsingFixedFunction)
        US_Timer_backup.TimerUdb = US_Timer_ReadCounter();
        US_Timer_backup.InterruptMaskValue = US_Timer_STATUS_MASK;
        #if (US_Timer_UsingHWCaptureCounter)
            US_Timer_backup.TimerCaptureCounter = US_Timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!US_Timer_UDB_CONTROL_REG_REMOVED)
            US_Timer_backup.TimerControlRegister = US_Timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: US_Timer_RestoreConfig
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
*  US_Timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void US_Timer_RestoreConfig(void) 
{   
    #if (!US_Timer_UsingFixedFunction)

        US_Timer_WriteCounter(US_Timer_backup.TimerUdb);
        US_Timer_STATUS_MASK =US_Timer_backup.InterruptMaskValue;
        #if (US_Timer_UsingHWCaptureCounter)
            US_Timer_SetCaptureCount(US_Timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!US_Timer_UDB_CONTROL_REG_REMOVED)
            US_Timer_WriteControlRegister(US_Timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: US_Timer_Sleep
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
*  US_Timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void US_Timer_Sleep(void) 
{
    #if(!US_Timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(US_Timer_CTRL_ENABLE == (US_Timer_CONTROL & US_Timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            US_Timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            US_Timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    US_Timer_Stop();
    US_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: US_Timer_Wakeup
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
*  US_Timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void US_Timer_Wakeup(void) 
{
    US_Timer_RestoreConfig();
    #if(!US_Timer_UDB_CONTROL_REG_REMOVED)
        if(US_Timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                US_Timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
