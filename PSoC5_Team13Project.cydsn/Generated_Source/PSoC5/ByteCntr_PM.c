/*******************************************************************************
* File Name: ByteCntr_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "ByteCntr.h"

static ByteCntr_backupStruct ByteCntr_backup;


/*******************************************************************************
* Function Name: ByteCntr_SaveConfig
********************************************************************************
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
*  ByteCntr_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void ByteCntr_SaveConfig(void) 
{
    #if (!ByteCntr_UsingFixedFunction)

        ByteCntr_backup.CounterUdb = ByteCntr_ReadCounter();

        #if(!ByteCntr_ControlRegRemoved)
            ByteCntr_backup.CounterControlRegister = ByteCntr_ReadControlRegister();
        #endif /* (!ByteCntr_ControlRegRemoved) */

    #endif /* (!ByteCntr_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ByteCntr_RestoreConfig
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
*  ByteCntr_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void ByteCntr_RestoreConfig(void) 
{      
    #if (!ByteCntr_UsingFixedFunction)

       ByteCntr_WriteCounter(ByteCntr_backup.CounterUdb);

        #if(!ByteCntr_ControlRegRemoved)
            ByteCntr_WriteControlRegister(ByteCntr_backup.CounterControlRegister);
        #endif /* (!ByteCntr_ControlRegRemoved) */

    #endif /* (!ByteCntr_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ByteCntr_Sleep
********************************************************************************
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
*  ByteCntr_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void ByteCntr_Sleep(void) 
{
    #if(!ByteCntr_ControlRegRemoved)
        /* Save Counter's enable state */
        if(ByteCntr_CTRL_ENABLE == (ByteCntr_CONTROL & ByteCntr_CTRL_ENABLE))
        {
            /* Counter is enabled */
            ByteCntr_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            ByteCntr_backup.CounterEnableState = 0u;
        }
    #else
        ByteCntr_backup.CounterEnableState = 1u;
        if(ByteCntr_backup.CounterEnableState != 0u)
        {
            ByteCntr_backup.CounterEnableState = 0u;
        }
    #endif /* (!ByteCntr_ControlRegRemoved) */
    
    ByteCntr_Stop();
    ByteCntr_SaveConfig();
}


/*******************************************************************************
* Function Name: ByteCntr_Wakeup
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
*  ByteCntr_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void ByteCntr_Wakeup(void) 
{
    ByteCntr_RestoreConfig();
    #if(!ByteCntr_ControlRegRemoved)
        if(ByteCntr_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            ByteCntr_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!ByteCntr_ControlRegRemoved) */
    
}


/* [] END OF FILE */
