/*******************************************************************************
* File Name: TB9051_QD_Cnt16_PM.c  
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

#include "TB9051_QD_Cnt16.h"

static TB9051_QD_Cnt16_backupStruct TB9051_QD_Cnt16_backup;


/*******************************************************************************
* Function Name: TB9051_QD_Cnt16_SaveConfig
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
*  TB9051_QD_Cnt16_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void TB9051_QD_Cnt16_SaveConfig(void) 
{
    #if (!TB9051_QD_Cnt16_UsingFixedFunction)

        TB9051_QD_Cnt16_backup.CounterUdb = TB9051_QD_Cnt16_ReadCounter();

        #if(!TB9051_QD_Cnt16_ControlRegRemoved)
            TB9051_QD_Cnt16_backup.CounterControlRegister = TB9051_QD_Cnt16_ReadControlRegister();
        #endif /* (!TB9051_QD_Cnt16_ControlRegRemoved) */

    #endif /* (!TB9051_QD_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: TB9051_QD_Cnt16_RestoreConfig
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
*  TB9051_QD_Cnt16_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void TB9051_QD_Cnt16_RestoreConfig(void) 
{      
    #if (!TB9051_QD_Cnt16_UsingFixedFunction)

       TB9051_QD_Cnt16_WriteCounter(TB9051_QD_Cnt16_backup.CounterUdb);

        #if(!TB9051_QD_Cnt16_ControlRegRemoved)
            TB9051_QD_Cnt16_WriteControlRegister(TB9051_QD_Cnt16_backup.CounterControlRegister);
        #endif /* (!TB9051_QD_Cnt16_ControlRegRemoved) */

    #endif /* (!TB9051_QD_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: TB9051_QD_Cnt16_Sleep
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
*  TB9051_QD_Cnt16_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void TB9051_QD_Cnt16_Sleep(void) 
{
    #if(!TB9051_QD_Cnt16_ControlRegRemoved)
        /* Save Counter's enable state */
        if(TB9051_QD_Cnt16_CTRL_ENABLE == (TB9051_QD_Cnt16_CONTROL & TB9051_QD_Cnt16_CTRL_ENABLE))
        {
            /* Counter is enabled */
            TB9051_QD_Cnt16_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            TB9051_QD_Cnt16_backup.CounterEnableState = 0u;
        }
    #else
        TB9051_QD_Cnt16_backup.CounterEnableState = 1u;
        if(TB9051_QD_Cnt16_backup.CounterEnableState != 0u)
        {
            TB9051_QD_Cnt16_backup.CounterEnableState = 0u;
        }
    #endif /* (!TB9051_QD_Cnt16_ControlRegRemoved) */
    
    TB9051_QD_Cnt16_Stop();
    TB9051_QD_Cnt16_SaveConfig();
}


/*******************************************************************************
* Function Name: TB9051_QD_Cnt16_Wakeup
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
*  TB9051_QD_Cnt16_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void TB9051_QD_Cnt16_Wakeup(void) 
{
    TB9051_QD_Cnt16_RestoreConfig();
    #if(!TB9051_QD_Cnt16_ControlRegRemoved)
        if(TB9051_QD_Cnt16_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            TB9051_QD_Cnt16_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!TB9051_QD_Cnt16_ControlRegRemoved) */
    
}


/* [] END OF FILE */
