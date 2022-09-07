/*******************************************************************************
* File Name: US_LED_PM.c
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

#include "US_LED.h"

/* Check for removal by optimization */
#if !defined(US_LED_Sync_ctrl_reg__REMOVED)

static US_LED_BACKUP_STRUCT  US_LED_backup = {0u};

    
/*******************************************************************************
* Function Name: US_LED_SaveConfig
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
void US_LED_SaveConfig(void) 
{
    US_LED_backup.controlState = US_LED_Control;
}


/*******************************************************************************
* Function Name: US_LED_RestoreConfig
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
void US_LED_RestoreConfig(void) 
{
     US_LED_Control = US_LED_backup.controlState;
}


/*******************************************************************************
* Function Name: US_LED_Sleep
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
void US_LED_Sleep(void) 
{
    US_LED_SaveConfig();
}


/*******************************************************************************
* Function Name: US_LED_Wakeup
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
void US_LED_Wakeup(void)  
{
    US_LED_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
