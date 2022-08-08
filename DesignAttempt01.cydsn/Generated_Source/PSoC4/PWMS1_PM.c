/*******************************************************************************
* File Name: PWMS1_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWMS1.h"

static PWMS1_backupStruct PWMS1_backup;


/*******************************************************************************
* Function Name: PWMS1_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWMS1_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWMS1_SaveConfig(void) 
{

    #if(!PWMS1_UsingFixedFunction)
        #if(!PWMS1_PWMModeIsCenterAligned)
            PWMS1_backup.PWMPeriod = PWMS1_ReadPeriod();
        #endif /* (!PWMS1_PWMModeIsCenterAligned) */
        PWMS1_backup.PWMUdb = PWMS1_ReadCounter();
        #if (PWMS1_UseStatus)
            PWMS1_backup.InterruptMaskValue = PWMS1_STATUS_MASK;
        #endif /* (PWMS1_UseStatus) */

        #if(PWMS1_DeadBandMode == PWMS1__B_PWM__DBM_256_CLOCKS || \
            PWMS1_DeadBandMode == PWMS1__B_PWM__DBM_2_4_CLOCKS)
            PWMS1_backup.PWMdeadBandValue = PWMS1_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWMS1_KillModeMinTime)
             PWMS1_backup.PWMKillCounterPeriod = PWMS1_ReadKillTime();
        #endif /* (PWMS1_KillModeMinTime) */

        #if(PWMS1_UseControl)
            PWMS1_backup.PWMControlRegister = PWMS1_ReadControlRegister();
        #endif /* (PWMS1_UseControl) */
    #endif  /* (!PWMS1_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWMS1_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWMS1_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWMS1_RestoreConfig(void) 
{
        #if(!PWMS1_UsingFixedFunction)
            #if(!PWMS1_PWMModeIsCenterAligned)
                PWMS1_WritePeriod(PWMS1_backup.PWMPeriod);
            #endif /* (!PWMS1_PWMModeIsCenterAligned) */

            PWMS1_WriteCounter(PWMS1_backup.PWMUdb);

            #if (PWMS1_UseStatus)
                PWMS1_STATUS_MASK = PWMS1_backup.InterruptMaskValue;
            #endif /* (PWMS1_UseStatus) */

            #if(PWMS1_DeadBandMode == PWMS1__B_PWM__DBM_256_CLOCKS || \
                PWMS1_DeadBandMode == PWMS1__B_PWM__DBM_2_4_CLOCKS)
                PWMS1_WriteDeadTime(PWMS1_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWMS1_KillModeMinTime)
                PWMS1_WriteKillTime(PWMS1_backup.PWMKillCounterPeriod);
            #endif /* (PWMS1_KillModeMinTime) */

            #if(PWMS1_UseControl)
                PWMS1_WriteControlRegister(PWMS1_backup.PWMControlRegister);
            #endif /* (PWMS1_UseControl) */
        #endif  /* (!PWMS1_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWMS1_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWMS1_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWMS1_Sleep(void) 
{
    #if(PWMS1_UseControl)
        if(PWMS1_CTRL_ENABLE == (PWMS1_CONTROL & PWMS1_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWMS1_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWMS1_backup.PWMEnableState = 0u;
        }
    #endif /* (PWMS1_UseControl) */

    /* Stop component */
    PWMS1_Stop();

    /* Save registers configuration */
    PWMS1_SaveConfig();
}


/*******************************************************************************
* Function Name: PWMS1_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWMS1_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWMS1_Wakeup(void) 
{
     /* Restore registers values */
    PWMS1_RestoreConfig();

    if(PWMS1_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWMS1_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
