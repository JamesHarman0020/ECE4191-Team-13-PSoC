/***************************************************************************//**
* \file UART_RPi_PM.c
* \version 4.0
*
* \brief
*  This file provides the source code to the Power Management support for
*  the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UART_RPi.h"
#include "UART_RPi_PVT.h"

#if(UART_RPi_SCB_MODE_I2C_INC)
    #include "UART_RPi_I2C_PVT.h"
#endif /* (UART_RPi_SCB_MODE_I2C_INC) */

#if(UART_RPi_SCB_MODE_EZI2C_INC)
    #include "UART_RPi_EZI2C_PVT.h"
#endif /* (UART_RPi_SCB_MODE_EZI2C_INC) */

#if(UART_RPi_SCB_MODE_SPI_INC || UART_RPi_SCB_MODE_UART_INC)
    #include "UART_RPi_SPI_UART_PVT.h"
#endif /* (UART_RPi_SCB_MODE_SPI_INC || UART_RPi_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(UART_RPi_SCB_MODE_UNCONFIG_CONST_CFG || \
   (UART_RPi_SCB_MODE_I2C_CONST_CFG   && (!UART_RPi_I2C_WAKE_ENABLE_CONST))   || \
   (UART_RPi_SCB_MODE_EZI2C_CONST_CFG && (!UART_RPi_EZI2C_WAKE_ENABLE_CONST)) || \
   (UART_RPi_SCB_MODE_SPI_CONST_CFG   && (!UART_RPi_SPI_WAKE_ENABLE_CONST))   || \
   (UART_RPi_SCB_MODE_UART_CONST_CFG  && (!UART_RPi_UART_WAKE_ENABLE_CONST)))

    UART_RPi_BACKUP_STRUCT UART_RPi_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: UART_RPi_Sleep
****************************************************************************//**
*
*  Prepares the UART_RPi component to enter Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has an influence on this 
*  function implementation:
*  - Checked: configures the component to be wakeup source from Deep Sleep.
*  - Unchecked: stores the current component state (enabled or disabled) and 
*    disables the component. See SCB_Stop() function for details about component 
*    disabling.
*
*  Call the UART_RPi_Sleep() function before calling the 
*  CyPmSysDeepSleep() function. 
*  Refer to the PSoC Creator System Reference Guide for more information about 
*  power management functions and Low power section of this document for the 
*  selected mode.
*
*  This function should not be called before entering Sleep.
*
*******************************************************************************/
void UART_RPi_Sleep(void)
{
#if(UART_RPi_SCB_MODE_UNCONFIG_CONST_CFG)

    if(UART_RPi_SCB_WAKE_ENABLE_CHECK)
    {
        if(UART_RPi_SCB_MODE_I2C_RUNTM_CFG)
        {
            UART_RPi_I2CSaveConfig();
        }
        else if(UART_RPi_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            UART_RPi_EzI2CSaveConfig();
        }
    #if(!UART_RPi_CY_SCBIP_V1)
        else if(UART_RPi_SCB_MODE_SPI_RUNTM_CFG)
        {
            UART_RPi_SpiSaveConfig();
        }
        else if(UART_RPi_SCB_MODE_UART_RUNTM_CFG)
        {
            UART_RPi_UartSaveConfig();
        }
    #endif /* (!UART_RPi_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        UART_RPi_backup.enableState = (uint8) UART_RPi_GET_CTRL_ENABLED;

        if(0u != UART_RPi_backup.enableState)
        {
            UART_RPi_Stop();
        }
    }

#else

    #if (UART_RPi_SCB_MODE_I2C_CONST_CFG && UART_RPi_I2C_WAKE_ENABLE_CONST)
        UART_RPi_I2CSaveConfig();

    #elif (UART_RPi_SCB_MODE_EZI2C_CONST_CFG && UART_RPi_EZI2C_WAKE_ENABLE_CONST)
        UART_RPi_EzI2CSaveConfig();

    #elif (UART_RPi_SCB_MODE_SPI_CONST_CFG && UART_RPi_SPI_WAKE_ENABLE_CONST)
        UART_RPi_SpiSaveConfig();

    #elif (UART_RPi_SCB_MODE_UART_CONST_CFG && UART_RPi_UART_WAKE_ENABLE_CONST)
        UART_RPi_UartSaveConfig();

    #else

        UART_RPi_backup.enableState = (uint8) UART_RPi_GET_CTRL_ENABLED;

        if(0u != UART_RPi_backup.enableState)
        {
            UART_RPi_Stop();
        }

    #endif /* defined (UART_RPi_SCB_MODE_I2C_CONST_CFG) && (UART_RPi_I2C_WAKE_ENABLE_CONST) */

#endif /* (UART_RPi_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: UART_RPi_Wakeup
****************************************************************************//**
*
*  Prepares the UART_RPi component for Active mode operation after 
*  Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has influence on this 
*  function implementation:
*  - Checked: restores the component Active mode configuration.
*  - Unchecked: enables the component if it was enabled before enter Deep Sleep.
*
*  This function should not be called after exiting Sleep.
*
*  \sideeffect
*   Calling the UART_RPi_Wakeup() function without first calling the 
*   UART_RPi_Sleep() function may produce unexpected behavior.
*
*******************************************************************************/
void UART_RPi_Wakeup(void)
{
#if(UART_RPi_SCB_MODE_UNCONFIG_CONST_CFG)

    if(UART_RPi_SCB_WAKE_ENABLE_CHECK)
    {
        if(UART_RPi_SCB_MODE_I2C_RUNTM_CFG)
        {
            UART_RPi_I2CRestoreConfig();
        }
        else if(UART_RPi_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            UART_RPi_EzI2CRestoreConfig();
        }
    #if(!UART_RPi_CY_SCBIP_V1)
        else if(UART_RPi_SCB_MODE_SPI_RUNTM_CFG)
        {
            UART_RPi_SpiRestoreConfig();
        }
        else if(UART_RPi_SCB_MODE_UART_RUNTM_CFG)
        {
            UART_RPi_UartRestoreConfig();
        }
    #endif /* (!UART_RPi_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != UART_RPi_backup.enableState)
        {
            UART_RPi_Enable();
        }
    }

#else

    #if (UART_RPi_SCB_MODE_I2C_CONST_CFG  && UART_RPi_I2C_WAKE_ENABLE_CONST)
        UART_RPi_I2CRestoreConfig();

    #elif (UART_RPi_SCB_MODE_EZI2C_CONST_CFG && UART_RPi_EZI2C_WAKE_ENABLE_CONST)
        UART_RPi_EzI2CRestoreConfig();

    #elif (UART_RPi_SCB_MODE_SPI_CONST_CFG && UART_RPi_SPI_WAKE_ENABLE_CONST)
        UART_RPi_SpiRestoreConfig();

    #elif (UART_RPi_SCB_MODE_UART_CONST_CFG && UART_RPi_UART_WAKE_ENABLE_CONST)
        UART_RPi_UartRestoreConfig();

    #else

        if(0u != UART_RPi_backup.enableState)
        {
            UART_RPi_Enable();
        }

    #endif /* (UART_RPi_I2C_WAKE_ENABLE_CONST) */

#endif /* (UART_RPi_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
