/*******************************************************************************
* File Name: UART_RPiINT.c
* Version 2.50
*
* Description:
*  This file provides all Interrupt Service functionality of the UART component
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UART_RPi.h"
#include "cyapicallbacks.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if (UART_RPi_RX_INTERRUPT_ENABLED && (UART_RPi_RX_ENABLED || UART_RPi_HD_ENABLED))
    /*******************************************************************************
    * Function Name: UART_RPi_RXISR
    ********************************************************************************
    *
    * Summary:
    *  Interrupt Service Routine for RX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  UART_RPi_rxBuffer - RAM buffer pointer for save received data.
    *  UART_RPi_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  UART_RPi_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  UART_RPi_rxBufferOverflow - software overflow flag. Set to one
    *     when UART_RPi_rxBufferWrite index overtakes
    *     UART_RPi_rxBufferRead index.
    *  UART_RPi_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when UART_RPi_rxBufferWrite is equal to
    *    UART_RPi_rxBufferRead
    *  UART_RPi_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  UART_RPi_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(UART_RPi_RXISR)
    {
        uint8 readData;
        uint8 readStatus;
        uint8 increment_pointer = 0u;

    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef UART_RPi_RXISR_ENTRY_CALLBACK
        UART_RPi_RXISR_EntryCallback();
    #endif /* UART_RPi_RXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START UART_RPi_RXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        do
        {
            /* Read receiver status register */
            readStatus = UART_RPi_RXSTATUS_REG;
            /* Copy the same status to readData variable for backward compatibility support 
            *  of the user code in UART_RPi_RXISR_ERROR` section. 
            */
            readData = readStatus;

            if((readStatus & (UART_RPi_RX_STS_BREAK | 
                            UART_RPi_RX_STS_PAR_ERROR |
                            UART_RPi_RX_STS_STOP_ERROR | 
                            UART_RPi_RX_STS_OVERRUN)) != 0u)
            {
                /* ERROR handling. */
                UART_RPi_errorStatus |= readStatus & ( UART_RPi_RX_STS_BREAK | 
                                                            UART_RPi_RX_STS_PAR_ERROR | 
                                                            UART_RPi_RX_STS_STOP_ERROR | 
                                                            UART_RPi_RX_STS_OVERRUN);
                /* `#START UART_RPi_RXISR_ERROR` */

                /* `#END` */
                
            #ifdef UART_RPi_RXISR_ERROR_CALLBACK
                UART_RPi_RXISR_ERROR_Callback();
            #endif /* UART_RPi_RXISR_ERROR_CALLBACK */
            }
            
            if((readStatus & UART_RPi_RX_STS_FIFO_NOTEMPTY) != 0u)
            {
                /* Read data from the RX data register */
                readData = UART_RPi_RXDATA_REG;
            #if (UART_RPi_RXHW_ADDRESS_ENABLED)
                if(UART_RPi_rxAddressMode == (uint8)UART_RPi__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readStatus & UART_RPi_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readStatus & UART_RPi_RX_STS_ADDR_MATCH) != 0u)
                        {
                            UART_RPi_rxAddressDetected = 1u;
                        }
                        else
                        {
                            UART_RPi_rxAddressDetected = 0u;
                        }
                    }
                    if(UART_RPi_rxAddressDetected != 0u)
                    {   /* Store only addressed data */
                        UART_RPi_rxBuffer[UART_RPi_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* Without software addressing */
                {
                    UART_RPi_rxBuffer[UART_RPi_rxBufferWrite] = readData;
                    increment_pointer = 1u;
                }
            #else  /* Without addressing */
                UART_RPi_rxBuffer[UART_RPi_rxBufferWrite] = readData;
                increment_pointer = 1u;
            #endif /* (UART_RPi_RXHW_ADDRESS_ENABLED) */

                /* Do not increment buffer pointer when skip not addressed data */
                if(increment_pointer != 0u)
                {
                    if(UART_RPi_rxBufferLoopDetect != 0u)
                    {   /* Set Software Buffer status Overflow */
                        UART_RPi_rxBufferOverflow = 1u;
                    }
                    /* Set next pointer. */
                    UART_RPi_rxBufferWrite++;

                    /* Check pointer for a loop condition */
                    if(UART_RPi_rxBufferWrite >= UART_RPi_RX_BUFFER_SIZE)
                    {
                        UART_RPi_rxBufferWrite = 0u;
                    }

                    /* Detect pre-overload condition and set flag */
                    if(UART_RPi_rxBufferWrite == UART_RPi_rxBufferRead)
                    {
                        UART_RPi_rxBufferLoopDetect = 1u;
                        /* When Hardware Flow Control selected */
                        #if (UART_RPi_FLOW_CONTROL != 0u)
                            /* Disable RX interrupt mask, it is enabled when user read data from the buffer using APIs */
                            UART_RPi_RXSTATUS_MASK_REG  &= (uint8)~UART_RPi_RX_STS_FIFO_NOTEMPTY;
                            CyIntClearPending(UART_RPi_RX_VECT_NUM);
                            break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                        #endif /* (UART_RPi_FLOW_CONTROL != 0u) */
                    }
                }
            }
        }while((readStatus & UART_RPi_RX_STS_FIFO_NOTEMPTY) != 0u);

        /* User code required at end of ISR (Optional) */
        /* `#START UART_RPi_RXISR_END` */

        /* `#END` */

    #ifdef UART_RPi_RXISR_EXIT_CALLBACK
        UART_RPi_RXISR_ExitCallback();
    #endif /* UART_RPi_RXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }
    
#endif /* (UART_RPi_RX_INTERRUPT_ENABLED && (UART_RPi_RX_ENABLED || UART_RPi_HD_ENABLED)) */


#if (UART_RPi_TX_INTERRUPT_ENABLED && UART_RPi_TX_ENABLED)
    /*******************************************************************************
    * Function Name: UART_RPi_TXISR
    ********************************************************************************
    *
    * Summary:
    * Interrupt Service Routine for the TX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  UART_RPi_txBuffer - RAM buffer pointer for transmit data from.
    *  UART_RPi_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmitted byte.
    *  UART_RPi_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(UART_RPi_TXISR)
    {
    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef UART_RPi_TXISR_ENTRY_CALLBACK
        UART_RPi_TXISR_EntryCallback();
    #endif /* UART_RPi_TXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START UART_RPi_TXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        while((UART_RPi_txBufferRead != UART_RPi_txBufferWrite) &&
             ((UART_RPi_TXSTATUS_REG & UART_RPi_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer wrap around */
            if(UART_RPi_txBufferRead >= UART_RPi_TX_BUFFER_SIZE)
            {
                UART_RPi_txBufferRead = 0u;
            }

            UART_RPi_TXDATA_REG = UART_RPi_txBuffer[UART_RPi_txBufferRead];

            /* Set next pointer */
            UART_RPi_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START UART_RPi_TXISR_END` */

        /* `#END` */

    #ifdef UART_RPi_TXISR_EXIT_CALLBACK
        UART_RPi_TXISR_ExitCallback();
    #endif /* UART_RPi_TXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
   }
#endif /* (UART_RPi_TX_INTERRUPT_ENABLED && UART_RPi_TX_ENABLED) */


/* [] END OF FILE */
