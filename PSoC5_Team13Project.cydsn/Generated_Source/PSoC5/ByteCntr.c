/*******************************************************************************
* File Name: ByteCntr.c  
* Version 3.0
*
*  Description:
*     The Counter component consists of a 8, 16, 24 or 32-bit counter with
*     a selectable period between 2 and 2^Width - 1.  
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

uint8 ByteCntr_initVar = 0u;


/*******************************************************************************
* Function Name: ByteCntr_Init
********************************************************************************
* Summary:
*     Initialize to the schematic state
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void ByteCntr_Init(void) 
{
        #if (!ByteCntr_UsingFixedFunction && !ByteCntr_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!ByteCntr_UsingFixedFunction && !ByteCntr_ControlRegRemoved) */
        
        #if(!ByteCntr_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 ByteCntr_interruptState;
        #endif /* (!ByteCntr_UsingFixedFunction) */
        
        #if (ByteCntr_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            ByteCntr_CONTROL &= ByteCntr_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                ByteCntr_CONTROL2 &= ((uint8)(~ByteCntr_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                ByteCntr_CONTROL3 &= ((uint8)(~ByteCntr_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (ByteCntr_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                ByteCntr_CONTROL |= ByteCntr_ONESHOT;
            #endif /* (ByteCntr_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            ByteCntr_CONTROL2 |= ByteCntr_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            ByteCntr_RT1 &= ((uint8)(~ByteCntr_RT1_MASK));
            ByteCntr_RT1 |= ByteCntr_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            ByteCntr_RT1 &= ((uint8)(~ByteCntr_SYNCDSI_MASK));
            ByteCntr_RT1 |= ByteCntr_SYNCDSI_EN;

        #else
            #if(!ByteCntr_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = ByteCntr_CONTROL & ((uint8)(~ByteCntr_CTRL_CMPMODE_MASK));
            ByteCntr_CONTROL = ctrl | ByteCntr_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = ByteCntr_CONTROL & ((uint8)(~ByteCntr_CTRL_CAPMODE_MASK));
            
            #if( 0 != ByteCntr_CAPTURE_MODE_CONF)
                ByteCntr_CONTROL = ctrl | ByteCntr_DEFAULT_CAPTURE_MODE;
            #else
                ByteCntr_CONTROL = ctrl;
            #endif /* 0 != ByteCntr_CAPTURE_MODE */ 
            
            #endif /* (!ByteCntr_ControlRegRemoved) */
        #endif /* (ByteCntr_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!ByteCntr_UsingFixedFunction)
            ByteCntr_ClearFIFO();
        #endif /* (!ByteCntr_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        ByteCntr_WritePeriod(ByteCntr_INIT_PERIOD_VALUE);
        #if (!(ByteCntr_UsingFixedFunction && (CY_PSOC5A)))
            ByteCntr_WriteCounter(ByteCntr_INIT_COUNTER_VALUE);
        #endif /* (!(ByteCntr_UsingFixedFunction && (CY_PSOC5A))) */
        ByteCntr_SetInterruptMode(ByteCntr_INIT_INTERRUPTS_MASK);
        
        #if (!ByteCntr_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)ByteCntr_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            ByteCntr_WriteCompare(ByteCntr_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            ByteCntr_interruptState = CyEnterCriticalSection();
            
            ByteCntr_STATUS_AUX_CTRL |= ByteCntr_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(ByteCntr_interruptState);
            
        #endif /* (!ByteCntr_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ByteCntr_Enable
********************************************************************************
* Summary:
*     Enable the Counter
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: 
*   If the Enable mode is set to Hardware only then this function has no effect 
*   on the operation of the counter.
*
*******************************************************************************/
void ByteCntr_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (ByteCntr_UsingFixedFunction)
        ByteCntr_GLOBAL_ENABLE |= ByteCntr_BLOCK_EN_MASK;
        ByteCntr_GLOBAL_STBY_ENABLE |= ByteCntr_BLOCK_STBY_EN_MASK;
    #endif /* (ByteCntr_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!ByteCntr_ControlRegRemoved || ByteCntr_UsingFixedFunction)
        ByteCntr_CONTROL |= ByteCntr_CTRL_ENABLE;                
    #endif /* (!ByteCntr_ControlRegRemoved || ByteCntr_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: ByteCntr_Start
********************************************************************************
* Summary:
*  Enables the counter for operation 
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Global variables:
*  ByteCntr_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void ByteCntr_Start(void) 
{
    if(ByteCntr_initVar == 0u)
    {
        ByteCntr_Init();
        
        ByteCntr_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    ByteCntr_Enable();        
}


/*******************************************************************************
* Function Name: ByteCntr_Stop
********************************************************************************
* Summary:
* Halts the counter, but does not change any modes or disable interrupts.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: If the Enable mode is set to Hardware only then this function
*               has no effect on the operation of the counter.
*
*******************************************************************************/
void ByteCntr_Stop(void) 
{
    /* Disable Counter */
    #if(!ByteCntr_ControlRegRemoved || ByteCntr_UsingFixedFunction)
        ByteCntr_CONTROL &= ((uint8)(~ByteCntr_CTRL_ENABLE));        
    #endif /* (!ByteCntr_ControlRegRemoved || ByteCntr_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (ByteCntr_UsingFixedFunction)
        ByteCntr_GLOBAL_ENABLE &= ((uint8)(~ByteCntr_BLOCK_EN_MASK));
        ByteCntr_GLOBAL_STBY_ENABLE &= ((uint8)(~ByteCntr_BLOCK_STBY_EN_MASK));
    #endif /* (ByteCntr_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ByteCntr_SetInterruptMode
********************************************************************************
* Summary:
* Configures which interrupt sources are enabled to generate the final interrupt
*
* Parameters:  
*  InterruptsMask: This parameter is an or'd collection of the status bits
*                   which will be allowed to generate the counters interrupt.   
*
* Return: 
*  void
*
*******************************************************************************/
void ByteCntr_SetInterruptMode(uint8 interruptsMask) 
{
    ByteCntr_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: ByteCntr_ReadStatusRegister
********************************************************************************
* Summary:
*   Reads the status register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the status register
*
* Side Effects:
*   Status register bits may be clear on read. 
*
*******************************************************************************/
uint8   ByteCntr_ReadStatusRegister(void) 
{
    return ByteCntr_STATUS;
}


#if(!ByteCntr_ControlRegRemoved)
/*******************************************************************************
* Function Name: ByteCntr_ReadControlRegister
********************************************************************************
* Summary:
*   Reads the control register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
uint8   ByteCntr_ReadControlRegister(void) 
{
    return ByteCntr_CONTROL;
}


/*******************************************************************************
* Function Name: ByteCntr_WriteControlRegister
********************************************************************************
* Summary:
*   Sets the bit-field of the control register.  This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
void    ByteCntr_WriteControlRegister(uint8 control) 
{
    ByteCntr_CONTROL = control;
}

#endif  /* (!ByteCntr_ControlRegRemoved) */


#if (!(ByteCntr_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: ByteCntr_WriteCounter
********************************************************************************
* Summary:
*   This funtion is used to set the counter to a specific value
*
* Parameters:  
*  counter:  New counter value. 
*
* Return: 
*  void 
*
*******************************************************************************/
void ByteCntr_WriteCounter(uint8 counter) \
                                   
{
    #if(ByteCntr_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (ByteCntr_GLOBAL_ENABLE & ByteCntr_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        ByteCntr_GLOBAL_ENABLE |= ByteCntr_BLOCK_EN_MASK;
        CY_SET_REG16(ByteCntr_COUNTER_LSB_PTR, (uint16)counter);
        ByteCntr_GLOBAL_ENABLE &= ((uint8)(~ByteCntr_BLOCK_EN_MASK));
    #else
        CY_SET_REG8(ByteCntr_COUNTER_LSB_PTR, counter);
    #endif /* (ByteCntr_UsingFixedFunction) */
}
#endif /* (!(ByteCntr_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: ByteCntr_ReadCounter
********************************************************************************
* Summary:
* Returns the current value of the counter.  It doesn't matter
* if the counter is enabled or running.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint8) The present value of the counter.
*
*******************************************************************************/
uint8 ByteCntr_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(ByteCntr_UsingFixedFunction)
		(void)CY_GET_REG16(ByteCntr_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(ByteCntr_COUNTER_LSB_PTR_8BIT);
	#endif/* (ByteCntr_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(ByteCntr_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(ByteCntr_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG8(ByteCntr_STATICCOUNT_LSB_PTR));
    #endif /* (ByteCntr_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ByteCntr_ReadCapture
********************************************************************************
* Summary:
*   This function returns the last value captured.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) Present Capture value.
*
*******************************************************************************/
uint8 ByteCntr_ReadCapture(void) 
{
    #if(ByteCntr_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(ByteCntr_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG8(ByteCntr_STATICCOUNT_LSB_PTR));
    #endif /* (ByteCntr_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ByteCntr_WritePeriod
********************************************************************************
* Summary:
* Changes the period of the counter.  The new period 
* will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period: (uint8) A value of 0 will result in
*         the counter remaining at zero.  
*
* Return: 
*  void
*
*******************************************************************************/
void ByteCntr_WritePeriod(uint8 period) 
{
    #if(ByteCntr_UsingFixedFunction)
        CY_SET_REG16(ByteCntr_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG8(ByteCntr_PERIOD_LSB_PTR, period);
    #endif /* (ByteCntr_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ByteCntr_ReadPeriod
********************************************************************************
* Summary:
* Reads the current period value without affecting counter operation.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint8) Present period value.
*
*******************************************************************************/
uint8 ByteCntr_ReadPeriod(void) 
{
    #if(ByteCntr_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(ByteCntr_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG8(ByteCntr_PERIOD_LSB_PTR));
    #endif /* (ByteCntr_UsingFixedFunction) */
}


#if (!ByteCntr_UsingFixedFunction)
/*******************************************************************************
* Function Name: ByteCntr_WriteCompare
********************************************************************************
* Summary:
* Changes the compare value.  The compare output will 
* reflect the new value on the next UDB clock.  The compare output will be 
* driven high when the present counter value compares true based on the 
* configured compare mode setting. 
*
* Parameters:  
*  Compare:  New compare value. 
*
* Return: 
*  void
*
*******************************************************************************/
void ByteCntr_WriteCompare(uint8 compare) \
                                   
{
    #if(ByteCntr_UsingFixedFunction)
        CY_SET_REG16(ByteCntr_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG8(ByteCntr_COMPARE_LSB_PTR, compare);
    #endif /* (ByteCntr_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ByteCntr_ReadCompare
********************************************************************************
* Summary:
* Returns the compare value.
*
* Parameters:  
*  void:
*
* Return: 
*  (uint8) Present compare value.
*
*******************************************************************************/
uint8 ByteCntr_ReadCompare(void) 
{
    return (CY_GET_REG8(ByteCntr_COMPARE_LSB_PTR));
}


#if (ByteCntr_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: ByteCntr_SetCompareMode
********************************************************************************
* Summary:
*  Sets the software controlled Compare Mode.
*
* Parameters:
*  compareMode:  Compare Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void ByteCntr_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    ByteCntr_CONTROL &= ((uint8)(~ByteCntr_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    ByteCntr_CONTROL |= compareMode;
}
#endif  /* (ByteCntr_COMPARE_MODE_SOFTWARE) */


#if (ByteCntr_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: ByteCntr_SetCaptureMode
********************************************************************************
* Summary:
*  Sets the software controlled Capture Mode.
*
* Parameters:
*  captureMode:  Capture Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void ByteCntr_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    ByteCntr_CONTROL &= ((uint8)(~ByteCntr_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    ByteCntr_CONTROL |= ((uint8)((uint8)captureMode << ByteCntr_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (ByteCntr_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: ByteCntr_ClearFIFO
********************************************************************************
* Summary:
*   This function clears all capture data from the capture FIFO
*
* Parameters:  
*  void:
*
* Return: 
*  None
*
*******************************************************************************/
void ByteCntr_ClearFIFO(void) 
{

    while(0u != (ByteCntr_ReadStatusRegister() & ByteCntr_STATUS_FIFONEMP))
    {
        (void)ByteCntr_ReadCapture();
    }

}
#endif  /* (!ByteCntr_UsingFixedFunction) */


/* [] END OF FILE */

