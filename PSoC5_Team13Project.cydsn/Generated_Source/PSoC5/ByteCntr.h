/*******************************************************************************
* File Name: ByteCntr.h  
* Version 3.0
*
*  Description:
*   Contains the function prototypes and constants available to the counter
*   user module.
*
*   Note:
*    None
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
    
#if !defined(CY_COUNTER_ByteCntr_H)
#define CY_COUNTER_ByteCntr_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 ByteCntr_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Counter_v3_0 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Error message for removed ByteCntr_CounterUDB_sCTRLReg_ctrlreg through optimization */
#ifdef ByteCntr_CounterUDB_sCTRLReg_ctrlreg__REMOVED
    #error Counter_v3_0 detected with a constant 0 for the enable, a \
                                constant 0 for the count or constant 1 for \
                                the reset. This will prevent the component from\
                                operating.
#endif /* ByteCntr_CounterUDB_sCTRLReg_ctrlreg__REMOVED */


/**************************************
*           Parameter Defaults        
**************************************/

#define ByteCntr_Resolution            8u
#define ByteCntr_UsingFixedFunction    0u
#define ByteCntr_ControlRegRemoved     1u
#define ByteCntr_COMPARE_MODE_SOFTWARE 0u
#define ByteCntr_CAPTURE_MODE_SOFTWARE 0u
#define ByteCntr_RunModeUsed           0u


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Mode API Support
 * Backup structure for Sleep Wake up operations
 *************************************************************************/
typedef struct
{
    uint8 CounterEnableState; 
    uint8 CounterUdb;         /* Current Counter Value */

    #if (!ByteCntr_ControlRegRemoved)
        uint8 CounterControlRegister;               /* Counter Control Register */
    #endif /* (!ByteCntr_ControlRegRemoved) */

}ByteCntr_backupStruct;


/**************************************
 *  Function Prototypes
 *************************************/
void    ByteCntr_Start(void) ;
void    ByteCntr_Stop(void) ;
void    ByteCntr_SetInterruptMode(uint8 interruptsMask) ;
uint8   ByteCntr_ReadStatusRegister(void) ;
#define ByteCntr_GetInterruptSource() ByteCntr_ReadStatusRegister()
#if(!ByteCntr_ControlRegRemoved)
    uint8   ByteCntr_ReadControlRegister(void) ;
    void    ByteCntr_WriteControlRegister(uint8 control) \
        ;
#endif /* (!ByteCntr_ControlRegRemoved) */
#if (!(ByteCntr_UsingFixedFunction && (CY_PSOC5A)))
    void    ByteCntr_WriteCounter(uint8 counter) \
            ; 
#endif /* (!(ByteCntr_UsingFixedFunction && (CY_PSOC5A))) */
uint8  ByteCntr_ReadCounter(void) ;
uint8  ByteCntr_ReadCapture(void) ;
void    ByteCntr_WritePeriod(uint8 period) \
    ;
uint8  ByteCntr_ReadPeriod( void ) ;
#if (!ByteCntr_UsingFixedFunction)
    void    ByteCntr_WriteCompare(uint8 compare) \
        ;
    uint8  ByteCntr_ReadCompare( void ) \
        ;
#endif /* (!ByteCntr_UsingFixedFunction) */

#if (ByteCntr_COMPARE_MODE_SOFTWARE)
    void    ByteCntr_SetCompareMode(uint8 compareMode) ;
#endif /* (ByteCntr_COMPARE_MODE_SOFTWARE) */
#if (ByteCntr_CAPTURE_MODE_SOFTWARE)
    void    ByteCntr_SetCaptureMode(uint8 captureMode) ;
#endif /* (ByteCntr_CAPTURE_MODE_SOFTWARE) */
void ByteCntr_ClearFIFO(void)     ;
void ByteCntr_Init(void)          ;
void ByteCntr_Enable(void)        ;
void ByteCntr_SaveConfig(void)    ;
void ByteCntr_RestoreConfig(void) ;
void ByteCntr_Sleep(void)         ;
void ByteCntr_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Counter__CompareModes, Used in Compare Mode retained for backward compatibility of tests*/
#define ByteCntr__B_COUNTER__LESS_THAN 1
#define ByteCntr__B_COUNTER__LESS_THAN_OR_EQUAL 2
#define ByteCntr__B_COUNTER__EQUAL 0
#define ByteCntr__B_COUNTER__GREATER_THAN 3
#define ByteCntr__B_COUNTER__GREATER_THAN_OR_EQUAL 4
#define ByteCntr__B_COUNTER__SOFTWARE 5

/* Enumerated Type Counter_CompareModes */
#define ByteCntr_CMP_MODE_LT 1u
#define ByteCntr_CMP_MODE_LTE 2u
#define ByteCntr_CMP_MODE_EQ 0u
#define ByteCntr_CMP_MODE_GT 3u
#define ByteCntr_CMP_MODE_GTE 4u
#define ByteCntr_CMP_MODE_SOFTWARE_CONTROLLED 5u

/* Enumerated Type B_Counter__CaptureModes, Used in Capture Mode retained for backward compatibility of tests*/
#define ByteCntr__B_COUNTER__NONE 0
#define ByteCntr__B_COUNTER__RISING_EDGE 1
#define ByteCntr__B_COUNTER__FALLING_EDGE 2
#define ByteCntr__B_COUNTER__EITHER_EDGE 3
#define ByteCntr__B_COUNTER__SOFTWARE_CONTROL 4

/* Enumerated Type Counter_CompareModes */
#define ByteCntr_CAP_MODE_NONE 0u
#define ByteCntr_CAP_MODE_RISE 1u
#define ByteCntr_CAP_MODE_FALL 2u
#define ByteCntr_CAP_MODE_BOTH 3u
#define ByteCntr_CAP_MODE_SOFTWARE_CONTROLLED 4u


/***************************************
 *  Initialization Values
 **************************************/
#define ByteCntr_CAPTURE_MODE_CONF       0u
#define ByteCntr_INIT_PERIOD_VALUE       254u
#define ByteCntr_INIT_COUNTER_VALUE      0u
#if (ByteCntr_UsingFixedFunction)
#define ByteCntr_INIT_INTERRUPTS_MASK    ((uint8)((uint8)0u << ByteCntr_STATUS_ZERO_INT_EN_MASK_SHIFT))
#else
#define ByteCntr_INIT_COMPARE_VALUE      15u
#define ByteCntr_INIT_INTERRUPTS_MASK ((uint8)((uint8)0u << ByteCntr_STATUS_ZERO_INT_EN_MASK_SHIFT) | \
        ((uint8)((uint8)0u << ByteCntr_STATUS_CAPTURE_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << ByteCntr_STATUS_CMP_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << ByteCntr_STATUS_OVERFLOW_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << ByteCntr_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT)))
#define ByteCntr_DEFAULT_COMPARE_MODE    4u

#if( 0 != ByteCntr_CAPTURE_MODE_CONF)
    #define ByteCntr_DEFAULT_CAPTURE_MODE    ((uint8)((uint8)0u << ByteCntr_CTRL_CAPMODE0_SHIFT))
#else    
    #define ByteCntr_DEFAULT_CAPTURE_MODE    (0u )
#endif /* ( 0 != ByteCntr_CAPTURE_MODE_CONF) */

#endif /* (ByteCntr_UsingFixedFunction) */


/**************************************
 *  Registers
 *************************************/
#if (ByteCntr_UsingFixedFunction)
    #define ByteCntr_STATICCOUNT_LSB     (*(reg16 *) ByteCntr_CounterHW__CAP0 )
    #define ByteCntr_STATICCOUNT_LSB_PTR ( (reg16 *) ByteCntr_CounterHW__CAP0 )
    #define ByteCntr_PERIOD_LSB          (*(reg16 *) ByteCntr_CounterHW__PER0 )
    #define ByteCntr_PERIOD_LSB_PTR      ( (reg16 *) ByteCntr_CounterHW__PER0 )
    /* MODE must be set to 1 to set the compare value */
    #define ByteCntr_COMPARE_LSB         (*(reg16 *) ByteCntr_CounterHW__CNT_CMP0 )
    #define ByteCntr_COMPARE_LSB_PTR     ( (reg16 *) ByteCntr_CounterHW__CNT_CMP0 )
    /* MODE must be set to 0 to get the count */
    #define ByteCntr_COUNTER_LSB         (*(reg16 *) ByteCntr_CounterHW__CNT_CMP0 )
    #define ByteCntr_COUNTER_LSB_PTR     ( (reg16 *) ByteCntr_CounterHW__CNT_CMP0 )
    #define ByteCntr_RT1                 (*(reg8 *) ByteCntr_CounterHW__RT1)
    #define ByteCntr_RT1_PTR             ( (reg8 *) ByteCntr_CounterHW__RT1)
#else
    
    #if (ByteCntr_Resolution <= 8u) /* 8-bit Counter */
    
        #define ByteCntr_STATICCOUNT_LSB     (*(reg8 *) \
            ByteCntr_CounterUDB_sC8_counterdp_u0__F0_REG )
        #define ByteCntr_STATICCOUNT_LSB_PTR ( (reg8 *) \
            ByteCntr_CounterUDB_sC8_counterdp_u0__F0_REG )
        #define ByteCntr_PERIOD_LSB          (*(reg8 *) \
            ByteCntr_CounterUDB_sC8_counterdp_u0__D0_REG )
        #define ByteCntr_PERIOD_LSB_PTR      ( (reg8 *) \
            ByteCntr_CounterUDB_sC8_counterdp_u0__D0_REG )
        #define ByteCntr_COMPARE_LSB         (*(reg8 *) \
            ByteCntr_CounterUDB_sC8_counterdp_u0__D1_REG )
        #define ByteCntr_COMPARE_LSB_PTR     ( (reg8 *) \
            ByteCntr_CounterUDB_sC8_counterdp_u0__D1_REG )
        #define ByteCntr_COUNTER_LSB         (*(reg8 *) \
            ByteCntr_CounterUDB_sC8_counterdp_u0__A0_REG )  
        #define ByteCntr_COUNTER_LSB_PTR     ( (reg8 *)\
            ByteCntr_CounterUDB_sC8_counterdp_u0__A0_REG )
    
    #elif(ByteCntr_Resolution <= 16u) /* 16-bit Counter */
        #if(CY_PSOC3) /* 8-bit address space */ 
            #define ByteCntr_STATICCOUNT_LSB     (*(reg16 *) \
                ByteCntr_CounterUDB_sC8_counterdp_u0__F0_REG )
            #define ByteCntr_STATICCOUNT_LSB_PTR ( (reg16 *) \
                ByteCntr_CounterUDB_sC8_counterdp_u0__F0_REG )
            #define ByteCntr_PERIOD_LSB          (*(reg16 *) \
                ByteCntr_CounterUDB_sC8_counterdp_u0__D0_REG )
            #define ByteCntr_PERIOD_LSB_PTR      ( (reg16 *) \
                ByteCntr_CounterUDB_sC8_counterdp_u0__D0_REG )
            #define ByteCntr_COMPARE_LSB         (*(reg16 *) \
                ByteCntr_CounterUDB_sC8_counterdp_u0__D1_REG )
            #define ByteCntr_COMPARE_LSB_PTR     ( (reg16 *) \
                ByteCntr_CounterUDB_sC8_counterdp_u0__D1_REG )
            #define ByteCntr_COUNTER_LSB         (*(reg16 *) \
                ByteCntr_CounterUDB_sC8_counterdp_u0__A0_REG )  
            #define ByteCntr_COUNTER_LSB_PTR     ( (reg16 *)\
                ByteCntr_CounterUDB_sC8_counterdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define ByteCntr_STATICCOUNT_LSB     (*(reg16 *) \
                ByteCntr_CounterUDB_sC8_counterdp_u0__16BIT_F0_REG )
            #define ByteCntr_STATICCOUNT_LSB_PTR ( (reg16 *) \
                ByteCntr_CounterUDB_sC8_counterdp_u0__16BIT_F0_REG )
            #define ByteCntr_PERIOD_LSB          (*(reg16 *) \
                ByteCntr_CounterUDB_sC8_counterdp_u0__16BIT_D0_REG )
            #define ByteCntr_PERIOD_LSB_PTR      ( (reg16 *) \
                ByteCntr_CounterUDB_sC8_counterdp_u0__16BIT_D0_REG )
            #define ByteCntr_COMPARE_LSB         (*(reg16 *) \
                ByteCntr_CounterUDB_sC8_counterdp_u0__16BIT_D1_REG )
            #define ByteCntr_COMPARE_LSB_PTR     ( (reg16 *) \
                ByteCntr_CounterUDB_sC8_counterdp_u0__16BIT_D1_REG )
            #define ByteCntr_COUNTER_LSB         (*(reg16 *) \
                ByteCntr_CounterUDB_sC8_counterdp_u0__16BIT_A0_REG )  
            #define ByteCntr_COUNTER_LSB_PTR     ( (reg16 *)\
                ByteCntr_CounterUDB_sC8_counterdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */   
    #elif(ByteCntr_Resolution <= 24u) /* 24-bit Counter */
        
        #define ByteCntr_STATICCOUNT_LSB     (*(reg32 *) \
            ByteCntr_CounterUDB_sC8_counterdp_u0__F0_REG )
        #define ByteCntr_STATICCOUNT_LSB_PTR ( (reg32 *) \
            ByteCntr_CounterUDB_sC8_counterdp_u0__F0_REG )
        #define ByteCntr_PERIOD_LSB          (*(reg32 *) \
            ByteCntr_CounterUDB_sC8_counterdp_u0__D0_REG )
        #define ByteCntr_PERIOD_LSB_PTR      ( (reg32 *) \
            ByteCntr_CounterUDB_sC8_counterdp_u0__D0_REG )
        #define ByteCntr_COMPARE_LSB         (*(reg32 *) \
            ByteCntr_CounterUDB_sC8_counterdp_u0__D1_REG )
        #define ByteCntr_COMPARE_LSB_PTR     ( (reg32 *) \
            ByteCntr_CounterUDB_sC8_counterdp_u0__D1_REG )
        #define ByteCntr_COUNTER_LSB         (*(reg32 *) \
            ByteCntr_CounterUDB_sC8_counterdp_u0__A0_REG )  
        #define ByteCntr_COUNTER_LSB_PTR     ( (reg32 *)\
            ByteCntr_CounterUDB_sC8_counterdp_u0__A0_REG )
    
    #else /* 32-bit Counter */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define ByteCntr_STATICCOUNT_LSB     (*(reg32 *) \
                ByteCntr_CounterUDB_sC8_counterdp_u0__F0_REG )
            #define ByteCntr_STATICCOUNT_LSB_PTR ( (reg32 *) \
                ByteCntr_CounterUDB_sC8_counterdp_u0__F0_REG )
            #define ByteCntr_PERIOD_LSB          (*(reg32 *) \
                ByteCntr_CounterUDB_sC8_counterdp_u0__D0_REG )
            #define ByteCntr_PERIOD_LSB_PTR      ( (reg32 *) \
                ByteCntr_CounterUDB_sC8_counterdp_u0__D0_REG )
            #define ByteCntr_COMPARE_LSB         (*(reg32 *) \
                ByteCntr_CounterUDB_sC8_counterdp_u0__D1_REG )
            #define ByteCntr_COMPARE_LSB_PTR     ( (reg32 *) \
                ByteCntr_CounterUDB_sC8_counterdp_u0__D1_REG )
            #define ByteCntr_COUNTER_LSB         (*(reg32 *) \
                ByteCntr_CounterUDB_sC8_counterdp_u0__A0_REG )  
            #define ByteCntr_COUNTER_LSB_PTR     ( (reg32 *)\
                ByteCntr_CounterUDB_sC8_counterdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define ByteCntr_STATICCOUNT_LSB     (*(reg32 *) \
                ByteCntr_CounterUDB_sC8_counterdp_u0__32BIT_F0_REG )
            #define ByteCntr_STATICCOUNT_LSB_PTR ( (reg32 *) \
                ByteCntr_CounterUDB_sC8_counterdp_u0__32BIT_F0_REG )
            #define ByteCntr_PERIOD_LSB          (*(reg32 *) \
                ByteCntr_CounterUDB_sC8_counterdp_u0__32BIT_D0_REG )
            #define ByteCntr_PERIOD_LSB_PTR      ( (reg32 *) \
                ByteCntr_CounterUDB_sC8_counterdp_u0__32BIT_D0_REG )
            #define ByteCntr_COMPARE_LSB         (*(reg32 *) \
                ByteCntr_CounterUDB_sC8_counterdp_u0__32BIT_D1_REG )
            #define ByteCntr_COMPARE_LSB_PTR     ( (reg32 *) \
                ByteCntr_CounterUDB_sC8_counterdp_u0__32BIT_D1_REG )
            #define ByteCntr_COUNTER_LSB         (*(reg32 *) \
                ByteCntr_CounterUDB_sC8_counterdp_u0__32BIT_A0_REG )  
            #define ByteCntr_COUNTER_LSB_PTR     ( (reg32 *)\
                ByteCntr_CounterUDB_sC8_counterdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */   
    #endif

	#define ByteCntr_COUNTER_LSB_PTR_8BIT     ( (reg8 *)\
                ByteCntr_CounterUDB_sC8_counterdp_u0__A0_REG )
				
    #define ByteCntr_AUX_CONTROLDP0 \
        (*(reg8 *) ByteCntr_CounterUDB_sC8_counterdp_u0__DP_AUX_CTL_REG)
    
    #define ByteCntr_AUX_CONTROLDP0_PTR \
        ( (reg8 *) ByteCntr_CounterUDB_sC8_counterdp_u0__DP_AUX_CTL_REG)
    
    #if (ByteCntr_Resolution == 16 || ByteCntr_Resolution == 24 || ByteCntr_Resolution == 32)
       #define ByteCntr_AUX_CONTROLDP1 \
           (*(reg8 *) ByteCntr_CounterUDB_sC8_counterdp_u1__DP_AUX_CTL_REG)
       #define ByteCntr_AUX_CONTROLDP1_PTR \
           ( (reg8 *) ByteCntr_CounterUDB_sC8_counterdp_u1__DP_AUX_CTL_REG)
    #endif /* (ByteCntr_Resolution == 16 || ByteCntr_Resolution == 24 || ByteCntr_Resolution == 32) */
    
    #if (ByteCntr_Resolution == 24 || ByteCntr_Resolution == 32)
       #define ByteCntr_AUX_CONTROLDP2 \
           (*(reg8 *) ByteCntr_CounterUDB_sC8_counterdp_u2__DP_AUX_CTL_REG)
       #define ByteCntr_AUX_CONTROLDP2_PTR \
           ( (reg8 *) ByteCntr_CounterUDB_sC8_counterdp_u2__DP_AUX_CTL_REG)
    #endif /* (ByteCntr_Resolution == 24 || ByteCntr_Resolution == 32) */
    
    #if (ByteCntr_Resolution == 32)
       #define ByteCntr_AUX_CONTROLDP3 \
           (*(reg8 *) ByteCntr_CounterUDB_sC8_counterdp_u3__DP_AUX_CTL_REG)
       #define ByteCntr_AUX_CONTROLDP3_PTR \
           ( (reg8 *) ByteCntr_CounterUDB_sC8_counterdp_u3__DP_AUX_CTL_REG)
    #endif /* (ByteCntr_Resolution == 32) */

#endif  /* (ByteCntr_UsingFixedFunction) */

#if (ByteCntr_UsingFixedFunction)
    #define ByteCntr_STATUS         (*(reg8 *) ByteCntr_CounterHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define ByteCntr_STATUS_MASK             (*(reg8 *) ByteCntr_CounterHW__SR0 )
    #define ByteCntr_STATUS_MASK_PTR         ( (reg8 *) ByteCntr_CounterHW__SR0 )
    #define ByteCntr_CONTROL                 (*(reg8 *) ByteCntr_CounterHW__CFG0)
    #define ByteCntr_CONTROL_PTR             ( (reg8 *) ByteCntr_CounterHW__CFG0)
    #define ByteCntr_CONTROL2                (*(reg8 *) ByteCntr_CounterHW__CFG1)
    #define ByteCntr_CONTROL2_PTR            ( (reg8 *) ByteCntr_CounterHW__CFG1)
    #if (CY_PSOC3 || CY_PSOC5LP)
        #define ByteCntr_CONTROL3       (*(reg8 *) ByteCntr_CounterHW__CFG2)
        #define ByteCntr_CONTROL3_PTR   ( (reg8 *) ByteCntr_CounterHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define ByteCntr_GLOBAL_ENABLE           (*(reg8 *) ByteCntr_CounterHW__PM_ACT_CFG)
    #define ByteCntr_GLOBAL_ENABLE_PTR       ( (reg8 *) ByteCntr_CounterHW__PM_ACT_CFG)
    #define ByteCntr_GLOBAL_STBY_ENABLE      (*(reg8 *) ByteCntr_CounterHW__PM_STBY_CFG)
    #define ByteCntr_GLOBAL_STBY_ENABLE_PTR  ( (reg8 *) ByteCntr_CounterHW__PM_STBY_CFG)
    

    /********************************
    *    Constants
    ********************************/

    /* Fixed Function Block Chosen */
    #define ByteCntr_BLOCK_EN_MASK          ByteCntr_CounterHW__PM_ACT_MSK
    #define ByteCntr_BLOCK_STBY_EN_MASK     ByteCntr_CounterHW__PM_STBY_MSK 
    
    /* Control Register Bit Locations */    
    /* As defined in Register Map, part of TMRX_CFG0 register */
    #define ByteCntr_CTRL_ENABLE_SHIFT      0x00u
    #define ByteCntr_ONESHOT_SHIFT          0x02u
    /* Control Register Bit Masks */
    #define ByteCntr_CTRL_ENABLE            ((uint8)((uint8)0x01u << ByteCntr_CTRL_ENABLE_SHIFT))         
    #define ByteCntr_ONESHOT                ((uint8)((uint8)0x01u << ByteCntr_ONESHOT_SHIFT))

    /* Control2 Register Bit Masks */
    /* Set the mask for run mode */
    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        #define ByteCntr_CTRL_MODE_SHIFT        0x01u    
        #define ByteCntr_CTRL_MODE_MASK         ((uint8)((uint8)0x07u << ByteCntr_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Use CFG2 Mode bits to set run mode */
        #define ByteCntr_CTRL_MODE_SHIFT        0x00u    
        #define ByteCntr_CTRL_MODE_MASK         ((uint8)((uint8)0x03u << ByteCntr_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    /* Set the mask for interrupt (raw/status register) */
    #define ByteCntr_CTRL2_IRQ_SEL_SHIFT     0x00u
    #define ByteCntr_CTRL2_IRQ_SEL          ((uint8)((uint8)0x01u << ByteCntr_CTRL2_IRQ_SEL_SHIFT))     
    
    /* Status Register Bit Locations */
    #define ByteCntr_STATUS_ZERO_SHIFT      0x07u  /* As defined in Register Map, part of TMRX_SR0 register */ 

    /* Status Register Interrupt Enable Bit Locations */
    #define ByteCntr_STATUS_ZERO_INT_EN_MASK_SHIFT      (ByteCntr_STATUS_ZERO_SHIFT - 0x04u)

    /* Status Register Bit Masks */                           
    #define ByteCntr_STATUS_ZERO            ((uint8)((uint8)0x01u << ByteCntr_STATUS_ZERO_SHIFT))

    /* Status Register Interrupt Bit Masks*/
    #define ByteCntr_STATUS_ZERO_INT_EN_MASK       ((uint8)((uint8)ByteCntr_STATUS_ZERO >> 0x04u))
    
    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define ByteCntr_RT1_SHIFT            0x04u
    #define ByteCntr_RT1_MASK             ((uint8)((uint8)0x03u << ByteCntr_RT1_SHIFT))  /* Sync TC and CMP bit masks */
    #define ByteCntr_SYNC                 ((uint8)((uint8)0x03u << ByteCntr_RT1_SHIFT))
    #define ByteCntr_SYNCDSI_SHIFT        0x00u
    #define ByteCntr_SYNCDSI_MASK         ((uint8)((uint8)0x0Fu << ByteCntr_SYNCDSI_SHIFT)) /* Sync all DSI inputs */
    #define ByteCntr_SYNCDSI_EN           ((uint8)((uint8)0x0Fu << ByteCntr_SYNCDSI_SHIFT)) /* Sync all DSI inputs */
    
#else /* !ByteCntr_UsingFixedFunction */
    #define ByteCntr_STATUS               (* (reg8 *) ByteCntr_CounterUDB_sSTSReg_stsreg__STATUS_REG )
    #define ByteCntr_STATUS_PTR           (  (reg8 *) ByteCntr_CounterUDB_sSTSReg_stsreg__STATUS_REG )
    #define ByteCntr_STATUS_MASK          (* (reg8 *) ByteCntr_CounterUDB_sSTSReg_stsreg__MASK_REG )
    #define ByteCntr_STATUS_MASK_PTR      (  (reg8 *) ByteCntr_CounterUDB_sSTSReg_stsreg__MASK_REG )
    #define ByteCntr_STATUS_AUX_CTRL      (*(reg8 *) ByteCntr_CounterUDB_sSTSReg_stsreg__STATUS_AUX_CTL_REG)
    #define ByteCntr_STATUS_AUX_CTRL_PTR  ( (reg8 *) ByteCntr_CounterUDB_sSTSReg_stsreg__STATUS_AUX_CTL_REG)
    #define ByteCntr_CONTROL              (* (reg8 *) ByteCntr_CounterUDB_sCTRLReg_ctrlreg__CONTROL_REG )
    #define ByteCntr_CONTROL_PTR          (  (reg8 *) ByteCntr_CounterUDB_sCTRLReg_ctrlreg__CONTROL_REG )


    /********************************
    *    Constants
    ********************************/
    /* Control Register Bit Locations */
    #define ByteCntr_CTRL_CAPMODE0_SHIFT    0x03u       /* As defined by Verilog Implementation */
    #define ByteCntr_CTRL_RESET_SHIFT       0x06u       /* As defined by Verilog Implementation */
    #define ByteCntr_CTRL_ENABLE_SHIFT      0x07u       /* As defined by Verilog Implementation */
    /* Control Register Bit Masks */
    #define ByteCntr_CTRL_CMPMODE_MASK      0x07u 
    #define ByteCntr_CTRL_CAPMODE_MASK      0x03u  
    #define ByteCntr_CTRL_RESET             ((uint8)((uint8)0x01u << ByteCntr_CTRL_RESET_SHIFT))  
    #define ByteCntr_CTRL_ENABLE            ((uint8)((uint8)0x01u << ByteCntr_CTRL_ENABLE_SHIFT)) 

    /* Status Register Bit Locations */
    #define ByteCntr_STATUS_CMP_SHIFT       0x00u       /* As defined by Verilog Implementation */
    #define ByteCntr_STATUS_ZERO_SHIFT      0x01u       /* As defined by Verilog Implementation */
    #define ByteCntr_STATUS_OVERFLOW_SHIFT  0x02u       /* As defined by Verilog Implementation */
    #define ByteCntr_STATUS_UNDERFLOW_SHIFT 0x03u       /* As defined by Verilog Implementation */
    #define ByteCntr_STATUS_CAPTURE_SHIFT   0x04u       /* As defined by Verilog Implementation */
    #define ByteCntr_STATUS_FIFOFULL_SHIFT  0x05u       /* As defined by Verilog Implementation */
    #define ByteCntr_STATUS_FIFONEMP_SHIFT  0x06u       /* As defined by Verilog Implementation */
    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define ByteCntr_STATUS_CMP_INT_EN_MASK_SHIFT       ByteCntr_STATUS_CMP_SHIFT       
    #define ByteCntr_STATUS_ZERO_INT_EN_MASK_SHIFT      ByteCntr_STATUS_ZERO_SHIFT      
    #define ByteCntr_STATUS_OVERFLOW_INT_EN_MASK_SHIFT  ByteCntr_STATUS_OVERFLOW_SHIFT  
    #define ByteCntr_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT ByteCntr_STATUS_UNDERFLOW_SHIFT 
    #define ByteCntr_STATUS_CAPTURE_INT_EN_MASK_SHIFT   ByteCntr_STATUS_CAPTURE_SHIFT   
    #define ByteCntr_STATUS_FIFOFULL_INT_EN_MASK_SHIFT  ByteCntr_STATUS_FIFOFULL_SHIFT  
    #define ByteCntr_STATUS_FIFONEMP_INT_EN_MASK_SHIFT  ByteCntr_STATUS_FIFONEMP_SHIFT  
    /* Status Register Bit Masks */                
    #define ByteCntr_STATUS_CMP             ((uint8)((uint8)0x01u << ByteCntr_STATUS_CMP_SHIFT))  
    #define ByteCntr_STATUS_ZERO            ((uint8)((uint8)0x01u << ByteCntr_STATUS_ZERO_SHIFT)) 
    #define ByteCntr_STATUS_OVERFLOW        ((uint8)((uint8)0x01u << ByteCntr_STATUS_OVERFLOW_SHIFT)) 
    #define ByteCntr_STATUS_UNDERFLOW       ((uint8)((uint8)0x01u << ByteCntr_STATUS_UNDERFLOW_SHIFT)) 
    #define ByteCntr_STATUS_CAPTURE         ((uint8)((uint8)0x01u << ByteCntr_STATUS_CAPTURE_SHIFT)) 
    #define ByteCntr_STATUS_FIFOFULL        ((uint8)((uint8)0x01u << ByteCntr_STATUS_FIFOFULL_SHIFT))
    #define ByteCntr_STATUS_FIFONEMP        ((uint8)((uint8)0x01u << ByteCntr_STATUS_FIFONEMP_SHIFT))
    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define ByteCntr_STATUS_CMP_INT_EN_MASK            ByteCntr_STATUS_CMP                    
    #define ByteCntr_STATUS_ZERO_INT_EN_MASK           ByteCntr_STATUS_ZERO            
    #define ByteCntr_STATUS_OVERFLOW_INT_EN_MASK       ByteCntr_STATUS_OVERFLOW        
    #define ByteCntr_STATUS_UNDERFLOW_INT_EN_MASK      ByteCntr_STATUS_UNDERFLOW       
    #define ByteCntr_STATUS_CAPTURE_INT_EN_MASK        ByteCntr_STATUS_CAPTURE         
    #define ByteCntr_STATUS_FIFOFULL_INT_EN_MASK       ByteCntr_STATUS_FIFOFULL        
    #define ByteCntr_STATUS_FIFONEMP_INT_EN_MASK       ByteCntr_STATUS_FIFONEMP         
    

    /* StatusI Interrupt Enable bit Location in the Auxilliary Control Register */
    #define ByteCntr_STATUS_ACTL_INT_EN     0x10u /* As defined for the ACTL Register */
    
    /* Datapath Auxillary Control Register definitions */
    #define ByteCntr_AUX_CTRL_FIFO0_CLR         0x01u   /* As defined by Register map */
    #define ByteCntr_AUX_CTRL_FIFO1_CLR         0x02u   /* As defined by Register map */
    #define ByteCntr_AUX_CTRL_FIFO0_LVL         0x04u   /* As defined by Register map */
    #define ByteCntr_AUX_CTRL_FIFO1_LVL         0x08u   /* As defined by Register map */
    #define ByteCntr_STATUS_ACTL_INT_EN_MASK    0x10u   /* As defined for the ACTL Register */
    
#endif /* ByteCntr_UsingFixedFunction */

#endif  /* CY_COUNTER_ByteCntr_H */


/* [] END OF FILE */

