/*******************************************************************************
* File Name: TB9051_QD2.c  
* Version 3.0
*
* Description:
*  This file provides the source code to the API for the Quadrature Decoder
*  component.
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

#include "TB9051_QD2.h"

#if (TB9051_QD2_COUNTER_SIZE == TB9051_QD2_COUNTER_SIZE_32_BIT)
    #include "TB9051_QD2_PVT.h"
#endif /* TB9051_QD2_COUNTER_SIZE == TB9051_QD2_COUNTER_SIZE_32_BIT */

uint8 TB9051_QD2_initVar = 0u;


/*******************************************************************************
* Function Name: TB9051_QD2_Init
********************************************************************************
*
* Summary:
*  Inits/Restores default QuadDec configuration provided with customizer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void TB9051_QD2_Init(void) 
{
    #if (TB9051_QD2_COUNTER_SIZE == TB9051_QD2_COUNTER_SIZE_32_BIT)
        /* Disable Interrupt. */
        CyIntDisable(TB9051_QD2_ISR_NUMBER);
        /* Set the ISR to point to the TB9051_QD2_isr Interrupt. */
        (void) CyIntSetVector(TB9051_QD2_ISR_NUMBER, & TB9051_QD2_ISR);
        /* Set the priority. */
        CyIntSetPriority(TB9051_QD2_ISR_NUMBER, TB9051_QD2_ISR_PRIORITY);
    #endif /* TB9051_QD2_COUNTER_SIZE == TB9051_QD2_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: TB9051_QD2_Enable
********************************************************************************
*
* Summary:
*  This function enable interrupts from Component and also enable Component's
*  ISR in case of 32-bit counter.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void TB9051_QD2_Enable(void) 
{
    uint8 enableInterrupts;

    TB9051_QD2_SetInterruptMask(TB9051_QD2_INIT_INT_MASK);

    /* Clear pending interrupts. */
    (void) TB9051_QD2_GetEvents();
    
    enableInterrupts = CyEnterCriticalSection();

    /* Enable interrupts from Statusi register */
    TB9051_QD2_SR_AUX_CONTROL |= TB9051_QD2_INTERRUPTS_ENABLE;

    CyExitCriticalSection(enableInterrupts);        

    #if (TB9051_QD2_COUNTER_SIZE == TB9051_QD2_COUNTER_SIZE_32_BIT)
        /* Enable Component interrupts */
        CyIntEnable(TB9051_QD2_ISR_NUMBER);
    #endif /* TB9051_QD2_COUNTER_SIZE == TB9051_QD2_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: TB9051_QD2_Start
********************************************************************************
*
* Summary:
*  Initializes UDBs and other relevant hardware.
*  Resets counter, enables or disables all relevant interrupts.
*  Starts monitoring the inputs and counting.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  TB9051_QD2_initVar - used to check initial configuration, modified on
*  first function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void TB9051_QD2_Start(void) 
{
    #if (TB9051_QD2_COUNTER_SIZE == TB9051_QD2_COUNTER_SIZE_8_BIT)
        TB9051_QD2_Cnt8_Start();
        TB9051_QD2_Cnt8_WriteCounter(TB9051_QD2_COUNTER_INIT_VALUE);
    #else
        /* (TB9051_QD2_COUNTER_SIZE == TB9051_QD2_COUNTER_SIZE_16_BIT) || 
        *  (TB9051_QD2_COUNTER_SIZE == TB9051_QD2_COUNTER_SIZE_32_BIT) 
        */
        TB9051_QD2_Cnt16_Start();
        TB9051_QD2_Cnt16_WriteCounter(TB9051_QD2_COUNTER_INIT_VALUE);
    #endif /* TB9051_QD2_COUNTER_SIZE == TB9051_QD2_COUNTER_SIZE_8_BIT */
    
    #if (TB9051_QD2_COUNTER_SIZE == TB9051_QD2_COUNTER_SIZE_32_BIT)        
       TB9051_QD2_count32SoftPart = 0;
    #endif /* TB9051_QD2_COUNTER_SIZE == TB9051_QD2_COUNTER_SIZE_32_BIT */

    if (TB9051_QD2_initVar == 0u)
    {
        TB9051_QD2_Init();
        TB9051_QD2_initVar = 1u;
    }

    TB9051_QD2_Enable();
}


/*******************************************************************************
* Function Name: TB9051_QD2_Stop
********************************************************************************
*
* Summary:
*  Turns off UDBs and other relevant hardware.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void TB9051_QD2_Stop(void) 
{
    uint8 enableInterrupts;

    #if (TB9051_QD2_COUNTER_SIZE == TB9051_QD2_COUNTER_SIZE_8_BIT)
        TB9051_QD2_Cnt8_Stop();
    #else 
        /* (TB9051_QD2_COUNTER_SIZE == TB9051_QD2_COUNTER_SIZE_16_BIT) ||
        *  (TB9051_QD2_COUNTER_SIZE == TB9051_QD2_COUNTER_SIZE_32_BIT)
        */
        TB9051_QD2_Cnt16_Stop();    /* counter disable */
    #endif /* (TB9051_QD2_COUNTER_SIZE == TB9051_QD2_COUNTER_SIZE_8_BIT) */
 
    enableInterrupts = CyEnterCriticalSection();

    /* Disable interrupts interrupts from Statusi register */
    TB9051_QD2_SR_AUX_CONTROL &= (uint8) (~TB9051_QD2_INTERRUPTS_ENABLE);

    CyExitCriticalSection(enableInterrupts);

    #if (TB9051_QD2_COUNTER_SIZE == TB9051_QD2_COUNTER_SIZE_32_BIT)
        CyIntDisable(TB9051_QD2_ISR_NUMBER);    /* interrupt disable */
    #endif /* TB9051_QD2_COUNTER_SIZE == TB9051_QD2_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: TB9051_QD2_GetCounter
********************************************************************************
*
* Summary:
*  Reports the current value of the counter.
*
* Parameters:
*  None.
*
* Return:
*  The counter value. Return type is signed and per the counter size setting.
*  A positive value indicates clockwise movement (B before A).
*
* Global variables:
*  TB9051_QD2_count32SoftPart - used to get hi 16 bit for current value
*  of the 32-bit counter, when Counter size equal 32-bit.
*
*******************************************************************************/
int16 TB9051_QD2_GetCounter(void) 
{
    int16 count;
    uint16 tmpCnt;

    #if (TB9051_QD2_COUNTER_SIZE == TB9051_QD2_COUNTER_SIZE_32_BIT)
        int16 hwCount;

        CyIntDisable(TB9051_QD2_ISR_NUMBER);

        tmpCnt = TB9051_QD2_Cnt16_ReadCounter();
        hwCount = (int16) ((int32) tmpCnt - (int32) TB9051_QD2_COUNTER_INIT_VALUE);
        count = TB9051_QD2_count32SoftPart + hwCount;

        CyIntEnable(TB9051_QD2_ISR_NUMBER);
    #else 
        /* (TB9051_QD2_COUNTER_SIZE == TB9051_QD2_COUNTER_SIZE_8_BIT) || 
        *  (TB9051_QD2_COUNTER_SIZE == TB9051_QD2_COUNTER_SIZE_16_BIT)
        */
        #if (TB9051_QD2_COUNTER_SIZE == TB9051_QD2_COUNTER_SIZE_8_BIT)
            tmpCnt = TB9051_QD2_Cnt8_ReadCounter();
        #else /* (TB9051_QD2_COUNTER_SIZE == TB9051_QD2_COUNTER_SIZE_16_BIT) */
            tmpCnt = TB9051_QD2_Cnt16_ReadCounter();
        #endif  /* TB9051_QD2_COUNTER_SIZE == TB9051_QD2_COUNTER_SIZE_8_BIT */

        count = (int16) ((int32) tmpCnt -
                (int32) TB9051_QD2_COUNTER_INIT_VALUE);

    #endif /* TB9051_QD2_COUNTER_SIZE == TB9051_QD2_COUNTER_SIZE_32_BIT */ 

    return (count);
}


/*******************************************************************************
* Function Name: TB9051_QD2_SetCounter
********************************************************************************
*
* Summary:
*  Sets the current value of the counter.
*
* Parameters:
*  value:  The new value. Parameter type is signed and per the counter size
*  setting.
*
* Return:
*  None.
*
* Global variables:
*  TB9051_QD2_count32SoftPart - modified to set hi 16 bit for current
*  value of the 32-bit counter, when Counter size equal 32-bit.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void TB9051_QD2_SetCounter(int16 value) 
{
    #if ((TB9051_QD2_COUNTER_SIZE == TB9051_QD2_COUNTER_SIZE_8_BIT) || \
         (TB9051_QD2_COUNTER_SIZE == TB9051_QD2_COUNTER_SIZE_16_BIT))
        uint16 count;
        
        if (value >= 0)
        {
            count = (uint16) value + TB9051_QD2_COUNTER_INIT_VALUE;
        }
        else
        {
            count = TB9051_QD2_COUNTER_INIT_VALUE - (uint16)(-value);
        }
        #if (TB9051_QD2_COUNTER_SIZE == TB9051_QD2_COUNTER_SIZE_8_BIT)
            TB9051_QD2_Cnt8_WriteCounter(count);
        #else /* (TB9051_QD2_COUNTER_SIZE == TB9051_QD2_COUNTER_SIZE_16_BIT) */
            TB9051_QD2_Cnt16_WriteCounter(count);
        #endif  /* TB9051_QD2_COUNTER_SIZE == TB9051_QD2_COUNTER_SIZE_8_BIT */
    #else /* (TB9051_QD2_COUNTER_SIZE == TB9051_QD2_COUNTER_SIZE_32_BIT) */
        CyIntDisable(TB9051_QD2_ISR_NUMBER);

        TB9051_QD2_Cnt16_WriteCounter(TB9051_QD2_COUNTER_INIT_VALUE);
        TB9051_QD2_count32SoftPart = value;

        CyIntEnable(TB9051_QD2_ISR_NUMBER);
    #endif  /* (TB9051_QD2_COUNTER_SIZE == TB9051_QD2_COUNTER_SIZE_8_BIT) ||
             * (TB9051_QD2_COUNTER_SIZE == TB9051_QD2_COUNTER_SIZE_16_BIT)
             */
}


/*******************************************************************************
* Function Name: TB9051_QD2_GetEvents
********************************************************************************
* 
* Summary:
*   Reports the current status of events. This function clears the bits of the 
*   status register.
*
* Parameters:
*  None.
*
* Return:
*  The events, as bits in an unsigned 8-bit value:
*    Bit      Description
*     0        Counter overflow.
*     1        Counter underflow.
*     2        Counter reset due to index, if index input is used.
*     3        Invalid A, B inputs state transition.
*
*******************************************************************************/
uint8 TB9051_QD2_GetEvents(void) 
{
    return (TB9051_QD2_STATUS_REG & TB9051_QD2_INIT_INT_MASK);
}


/*******************************************************************************
* Function Name: TB9051_QD2_SetInterruptMask
********************************************************************************
*
* Summary:
*  Enables / disables interrupts due to the events.
*  For the 32-bit counter, the overflow, underflow and reset interrupts cannot
*  be disabled, these bits are ignored.
*
* Parameters:
*  mask: Enable / disable bits in an 8-bit value, where 1 enables the interrupt.
*
* Return:
*  None.
*
*******************************************************************************/
void TB9051_QD2_SetInterruptMask(uint8 mask) 
{
    #if (TB9051_QD2_COUNTER_SIZE == TB9051_QD2_COUNTER_SIZE_32_BIT)
        /* Underflow, Overflow and Reset interrupts for 32-bit Counter are always enable */
        mask |= (TB9051_QD2_COUNTER_OVERFLOW | TB9051_QD2_COUNTER_UNDERFLOW |
                 TB9051_QD2_COUNTER_RESET);
    #endif /* TB9051_QD2_COUNTER_SIZE == TB9051_QD2_COUNTER_SIZE_32_BIT */

    TB9051_QD2_STATUS_MASK = mask;
}


/*******************************************************************************
* Function Name: TB9051_QD2_GetInterruptMask
********************************************************************************
*
* Summary:
*  Reports the current interrupt mask settings.
*
* Parameters:
*  None.
*
* Return:
*  Enable / disable bits in an 8-bit value, where 1 enables the interrupt.
*  For the 32-bit counter, the overflow, underflow and reset enable bits are
*  always set.
*
*******************************************************************************/
uint8 TB9051_QD2_GetInterruptMask(void) 
{
    return (TB9051_QD2_STATUS_MASK & TB9051_QD2_INIT_INT_MASK);
}


/* [] END OF FILE */
