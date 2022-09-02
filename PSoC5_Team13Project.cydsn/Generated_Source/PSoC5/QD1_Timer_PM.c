/*******************************************************************************
* File Name: QD1_Timer_PM.c
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

#include "QD1_Timer.h"

static QD1_Timer_backupStruct QD1_Timer_backup;


/*******************************************************************************
* Function Name: QD1_Timer_SaveConfig
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
*  QD1_Timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void QD1_Timer_SaveConfig(void) 
{
    #if (!QD1_Timer_UsingFixedFunction)
        QD1_Timer_backup.TimerUdb = QD1_Timer_ReadCounter();
        QD1_Timer_backup.InterruptMaskValue = QD1_Timer_STATUS_MASK;
        #if (QD1_Timer_UsingHWCaptureCounter)
            QD1_Timer_backup.TimerCaptureCounter = QD1_Timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!QD1_Timer_UDB_CONTROL_REG_REMOVED)
            QD1_Timer_backup.TimerControlRegister = QD1_Timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: QD1_Timer_RestoreConfig
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
*  QD1_Timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void QD1_Timer_RestoreConfig(void) 
{   
    #if (!QD1_Timer_UsingFixedFunction)

        QD1_Timer_WriteCounter(QD1_Timer_backup.TimerUdb);
        QD1_Timer_STATUS_MASK =QD1_Timer_backup.InterruptMaskValue;
        #if (QD1_Timer_UsingHWCaptureCounter)
            QD1_Timer_SetCaptureCount(QD1_Timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!QD1_Timer_UDB_CONTROL_REG_REMOVED)
            QD1_Timer_WriteControlRegister(QD1_Timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: QD1_Timer_Sleep
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
*  QD1_Timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void QD1_Timer_Sleep(void) 
{
    #if(!QD1_Timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(QD1_Timer_CTRL_ENABLE == (QD1_Timer_CONTROL & QD1_Timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            QD1_Timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            QD1_Timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    QD1_Timer_Stop();
    QD1_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: QD1_Timer_Wakeup
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
*  QD1_Timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void QD1_Timer_Wakeup(void) 
{
    QD1_Timer_RestoreConfig();
    #if(!QD1_Timer_UDB_CONTROL_REG_REMOVED)
        if(QD1_Timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                QD1_Timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
