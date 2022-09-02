/*******************************************************************************
* File Name: TB9051_QD1_PM.c
* Version 3.0
*
* Description:
*  This file contains the setup, control and status commands to support 
*  component operations in low power mode.  
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "TB9051_QD1.h"

static TB9051_QD1_BACKUP_STRUCT TB9051_QD1_backup = {0u};


/*******************************************************************************
* Function Name: TB9051_QD1_SaveConfig
********************************************************************************
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void TB9051_QD1_SaveConfig(void) 
{
    #if (TB9051_QD1_COUNTER_SIZE == TB9051_QD1_COUNTER_SIZE_8_BIT)
        TB9051_QD1_Cnt8_SaveConfig();
    #else 
        /* (TB9051_QD1_COUNTER_SIZE == TB9051_QD1_COUNTER_SIZE_16_BIT) || 
         * (TB9051_QD1_COUNTER_SIZE == TB9051_QD1_COUNTER_SIZE_32_BIT)
         */
        TB9051_QD1_Cnt16_SaveConfig();
    #endif /* (TB9051_QD1_COUNTER_SIZE == TB9051_QD1_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: TB9051_QD1_RestoreConfig
********************************************************************************
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void TB9051_QD1_RestoreConfig(void) 
{
    #if (TB9051_QD1_COUNTER_SIZE == TB9051_QD1_COUNTER_SIZE_8_BIT)
        TB9051_QD1_Cnt8_RestoreConfig();
    #else 
        /* (TB9051_QD1_COUNTER_SIZE == TB9051_QD1_COUNTER_SIZE_16_BIT) || 
         * (TB9051_QD1_COUNTER_SIZE == TB9051_QD1_COUNTER_SIZE_32_BIT) 
         */
        TB9051_QD1_Cnt16_RestoreConfig();
    #endif /* (TB9051_QD1_COUNTER_SIZE == TB9051_QD1_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: TB9051_QD1_Sleep
********************************************************************************
* 
* Summary:
*  Prepare Quadrature Decoder Component goes to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  TB9051_QD1_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void TB9051_QD1_Sleep(void) 
{
    if (0u != (TB9051_QD1_SR_AUX_CONTROL & TB9051_QD1_INTERRUPTS_ENABLE))
    {
        TB9051_QD1_backup.enableState = 1u;
    }
    else /* The Quadrature Decoder Component is disabled */
    {
        TB9051_QD1_backup.enableState = 0u;
    }

    TB9051_QD1_Stop();
    TB9051_QD1_SaveConfig();
}


/*******************************************************************************
* Function Name: TB9051_QD1_Wakeup
********************************************************************************
*
* Summary:
*  Prepare Quadrature Decoder Component to wake up.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  TB9051_QD1_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void TB9051_QD1_Wakeup(void) 
{
    TB9051_QD1_RestoreConfig();

    if (TB9051_QD1_backup.enableState != 0u)
    {
        #if (TB9051_QD1_COUNTER_SIZE == TB9051_QD1_COUNTER_SIZE_8_BIT)
            TB9051_QD1_Cnt8_Enable();
        #else 
            /* (TB9051_QD1_COUNTER_SIZE == TB9051_QD1_COUNTER_SIZE_16_BIT) || 
            *  (TB9051_QD1_COUNTER_SIZE == TB9051_QD1_COUNTER_SIZE_32_BIT) 
            */
            TB9051_QD1_Cnt16_Enable();
        #endif /* (TB9051_QD1_COUNTER_SIZE == TB9051_QD1_COUNTER_SIZE_8_BIT) */

        /* Enable component's operation */
        TB9051_QD1_Enable();
    } /* Do nothing if component's block was disabled before */
}


/* [] END OF FILE */

