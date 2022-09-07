/*******************************************************************************
* File Name: BrakeTimer.h
* Version 2.80
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_TIMER_BrakeTimer_H)
#define CY_TIMER_BrakeTimer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 BrakeTimer_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define BrakeTimer_Resolution                 24u
#define BrakeTimer_UsingFixedFunction         0u
#define BrakeTimer_UsingHWCaptureCounter      0u
#define BrakeTimer_SoftwareCaptureMode        0u
#define BrakeTimer_SoftwareTriggerMode        0u
#define BrakeTimer_UsingHWEnable              0u
#define BrakeTimer_EnableTriggerMode          0u
#define BrakeTimer_InterruptOnCaptureCount    0u
#define BrakeTimer_RunModeUsed                1u
#define BrakeTimer_ControlRegRemoved          0u

#if defined(BrakeTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define BrakeTimer_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (BrakeTimer_UsingFixedFunction)
    #define BrakeTimer_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define BrakeTimer_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End BrakeTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!BrakeTimer_UsingFixedFunction)

        uint32 TimerUdb;
        uint8 InterruptMaskValue;
        #if (BrakeTimer_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!BrakeTimer_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}BrakeTimer_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    BrakeTimer_Start(void) ;
void    BrakeTimer_Stop(void) ;

void    BrakeTimer_SetInterruptMode(uint8 interruptMode) ;
uint8   BrakeTimer_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define BrakeTimer_GetInterruptSource() BrakeTimer_ReadStatusRegister()

#if(!BrakeTimer_UDB_CONTROL_REG_REMOVED)
    uint8   BrakeTimer_ReadControlRegister(void) ;
    void    BrakeTimer_WriteControlRegister(uint8 control) ;
#endif /* (!BrakeTimer_UDB_CONTROL_REG_REMOVED) */

uint32  BrakeTimer_ReadPeriod(void) ;
void    BrakeTimer_WritePeriod(uint32 period) ;
uint32  BrakeTimer_ReadCounter(void) ;
void    BrakeTimer_WriteCounter(uint32 counter) ;
uint32  BrakeTimer_ReadCapture(void) ;
void    BrakeTimer_SoftwareCapture(void) ;

#if(!BrakeTimer_UsingFixedFunction) /* UDB Prototypes */
    #if (BrakeTimer_SoftwareCaptureMode)
        void    BrakeTimer_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!BrakeTimer_UsingFixedFunction) */

    #if (BrakeTimer_SoftwareTriggerMode)
        void    BrakeTimer_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (BrakeTimer_SoftwareTriggerMode) */

    #if (BrakeTimer_EnableTriggerMode)
        void    BrakeTimer_EnableTrigger(void) ;
        void    BrakeTimer_DisableTrigger(void) ;
    #endif /* (BrakeTimer_EnableTriggerMode) */


    #if(BrakeTimer_InterruptOnCaptureCount)
        void    BrakeTimer_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (BrakeTimer_InterruptOnCaptureCount) */

    #if (BrakeTimer_UsingHWCaptureCounter)
        void    BrakeTimer_SetCaptureCount(uint8 captureCount) ;
        uint8   BrakeTimer_ReadCaptureCount(void) ;
    #endif /* (BrakeTimer_UsingHWCaptureCounter) */

    void BrakeTimer_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void BrakeTimer_Init(void)          ;
void BrakeTimer_Enable(void)        ;
void BrakeTimer_SaveConfig(void)    ;
void BrakeTimer_RestoreConfig(void) ;
void BrakeTimer_Sleep(void)         ;
void BrakeTimer_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define BrakeTimer__B_TIMER__CM_NONE 0
#define BrakeTimer__B_TIMER__CM_RISINGEDGE 1
#define BrakeTimer__B_TIMER__CM_FALLINGEDGE 2
#define BrakeTimer__B_TIMER__CM_EITHEREDGE 3
#define BrakeTimer__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define BrakeTimer__B_TIMER__TM_NONE 0x00u
#define BrakeTimer__B_TIMER__TM_RISINGEDGE 0x04u
#define BrakeTimer__B_TIMER__TM_FALLINGEDGE 0x08u
#define BrakeTimer__B_TIMER__TM_EITHEREDGE 0x0Cu
#define BrakeTimer__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define BrakeTimer_INIT_PERIOD             251321u
#define BrakeTimer_INIT_CAPTURE_MODE       ((uint8)((uint8)0u << BrakeTimer_CTRL_CAP_MODE_SHIFT))
#define BrakeTimer_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << BrakeTimer_CTRL_TRIG_MODE_SHIFT))
#if (BrakeTimer_UsingFixedFunction)
    #define BrakeTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << BrakeTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << BrakeTimer_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define BrakeTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << BrakeTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << BrakeTimer_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << BrakeTimer_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (BrakeTimer_UsingFixedFunction) */
#define BrakeTimer_INIT_CAPTURE_COUNT      (2u)
#define BrakeTimer_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << BrakeTimer_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (BrakeTimer_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define BrakeTimer_STATUS         (*(reg8 *) BrakeTimer_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define BrakeTimer_STATUS_MASK    (*(reg8 *) BrakeTimer_TimerHW__SR0 )
    #define BrakeTimer_CONTROL        (*(reg8 *) BrakeTimer_TimerHW__CFG0)
    #define BrakeTimer_CONTROL2       (*(reg8 *) BrakeTimer_TimerHW__CFG1)
    #define BrakeTimer_CONTROL2_PTR   ( (reg8 *) BrakeTimer_TimerHW__CFG1)
    #define BrakeTimer_RT1            (*(reg8 *) BrakeTimer_TimerHW__RT1)
    #define BrakeTimer_RT1_PTR        ( (reg8 *) BrakeTimer_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define BrakeTimer_CONTROL3       (*(reg8 *) BrakeTimer_TimerHW__CFG2)
        #define BrakeTimer_CONTROL3_PTR   ( (reg8 *) BrakeTimer_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define BrakeTimer_GLOBAL_ENABLE  (*(reg8 *) BrakeTimer_TimerHW__PM_ACT_CFG)
    #define BrakeTimer_GLOBAL_STBY_ENABLE  (*(reg8 *) BrakeTimer_TimerHW__PM_STBY_CFG)

    #define BrakeTimer_CAPTURE_LSB         (* (reg16 *) BrakeTimer_TimerHW__CAP0 )
    #define BrakeTimer_CAPTURE_LSB_PTR       ((reg16 *) BrakeTimer_TimerHW__CAP0 )
    #define BrakeTimer_PERIOD_LSB          (* (reg16 *) BrakeTimer_TimerHW__PER0 )
    #define BrakeTimer_PERIOD_LSB_PTR        ((reg16 *) BrakeTimer_TimerHW__PER0 )
    #define BrakeTimer_COUNTER_LSB         (* (reg16 *) BrakeTimer_TimerHW__CNT_CMP0 )
    #define BrakeTimer_COUNTER_LSB_PTR       ((reg16 *) BrakeTimer_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define BrakeTimer_BLOCK_EN_MASK                     BrakeTimer_TimerHW__PM_ACT_MSK
    #define BrakeTimer_BLOCK_STBY_EN_MASK                BrakeTimer_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define BrakeTimer_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define BrakeTimer_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define BrakeTimer_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define BrakeTimer_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define BrakeTimer_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define BrakeTimer_CTRL_ENABLE                        ((uint8)((uint8)0x01u << BrakeTimer_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define BrakeTimer_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define BrakeTimer_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << BrakeTimer_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define BrakeTimer_CTRL_MODE_SHIFT                 0x01u
        #define BrakeTimer_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << BrakeTimer_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define BrakeTimer_CTRL_RCOD_SHIFT        0x02u
        #define BrakeTimer_CTRL_ENBL_SHIFT        0x00u
        #define BrakeTimer_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define BrakeTimer_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << BrakeTimer_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define BrakeTimer_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << BrakeTimer_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define BrakeTimer_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << BrakeTimer_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define BrakeTimer_CTRL_RCOD       ((uint8)((uint8)0x03u << BrakeTimer_CTRL_RCOD_SHIFT))
        #define BrakeTimer_CTRL_ENBL       ((uint8)((uint8)0x80u << BrakeTimer_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define BrakeTimer_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define BrakeTimer_RT1_MASK                        ((uint8)((uint8)0x03u << BrakeTimer_RT1_SHIFT))
    #define BrakeTimer_SYNC                            ((uint8)((uint8)0x03u << BrakeTimer_RT1_SHIFT))
    #define BrakeTimer_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define BrakeTimer_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << BrakeTimer_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define BrakeTimer_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << BrakeTimer_SYNCDSI_SHIFT))

    #define BrakeTimer_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << BrakeTimer_CTRL_MODE_SHIFT))
    #define BrakeTimer_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << BrakeTimer_CTRL_MODE_SHIFT))
    #define BrakeTimer_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << BrakeTimer_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define BrakeTimer_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define BrakeTimer_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define BrakeTimer_STATUS_TC_INT_MASK_SHIFT        (BrakeTimer_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define BrakeTimer_STATUS_CAPTURE_INT_MASK_SHIFT   (BrakeTimer_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define BrakeTimer_STATUS_TC                       ((uint8)((uint8)0x01u << BrakeTimer_STATUS_TC_SHIFT))
    #define BrakeTimer_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << BrakeTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define BrakeTimer_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << BrakeTimer_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define BrakeTimer_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << BrakeTimer_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define BrakeTimer_STATUS              (* (reg8 *) BrakeTimer_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define BrakeTimer_STATUS_MASK         (* (reg8 *) BrakeTimer_TimerUDB_rstSts_stsreg__MASK_REG)
    #define BrakeTimer_STATUS_AUX_CTRL     (* (reg8 *) BrakeTimer_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define BrakeTimer_CONTROL             (* (reg8 *) BrakeTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(BrakeTimer_Resolution <= 8u) /* 8-bit Timer */
        #define BrakeTimer_CAPTURE_LSB         (* (reg8 *) BrakeTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
        #define BrakeTimer_CAPTURE_LSB_PTR       ((reg8 *) BrakeTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
        #define BrakeTimer_PERIOD_LSB          (* (reg8 *) BrakeTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
        #define BrakeTimer_PERIOD_LSB_PTR        ((reg8 *) BrakeTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
        #define BrakeTimer_COUNTER_LSB         (* (reg8 *) BrakeTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
        #define BrakeTimer_COUNTER_LSB_PTR       ((reg8 *) BrakeTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
    #elif(BrakeTimer_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define BrakeTimer_CAPTURE_LSB         (* (reg16 *) BrakeTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
            #define BrakeTimer_CAPTURE_LSB_PTR       ((reg16 *) BrakeTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
            #define BrakeTimer_PERIOD_LSB          (* (reg16 *) BrakeTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
            #define BrakeTimer_PERIOD_LSB_PTR        ((reg16 *) BrakeTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
            #define BrakeTimer_COUNTER_LSB         (* (reg16 *) BrakeTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
            #define BrakeTimer_COUNTER_LSB_PTR       ((reg16 *) BrakeTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define BrakeTimer_CAPTURE_LSB         (* (reg16 *) BrakeTimer_TimerUDB_sT24_timerdp_u0__16BIT_F0_REG )
            #define BrakeTimer_CAPTURE_LSB_PTR       ((reg16 *) BrakeTimer_TimerUDB_sT24_timerdp_u0__16BIT_F0_REG )
            #define BrakeTimer_PERIOD_LSB          (* (reg16 *) BrakeTimer_TimerUDB_sT24_timerdp_u0__16BIT_D0_REG )
            #define BrakeTimer_PERIOD_LSB_PTR        ((reg16 *) BrakeTimer_TimerUDB_sT24_timerdp_u0__16BIT_D0_REG )
            #define BrakeTimer_COUNTER_LSB         (* (reg16 *) BrakeTimer_TimerUDB_sT24_timerdp_u0__16BIT_A0_REG )
            #define BrakeTimer_COUNTER_LSB_PTR       ((reg16 *) BrakeTimer_TimerUDB_sT24_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(BrakeTimer_Resolution <= 24u)/* 24-bit Timer */
        #define BrakeTimer_CAPTURE_LSB         (* (reg32 *) BrakeTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
        #define BrakeTimer_CAPTURE_LSB_PTR       ((reg32 *) BrakeTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
        #define BrakeTimer_PERIOD_LSB          (* (reg32 *) BrakeTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
        #define BrakeTimer_PERIOD_LSB_PTR        ((reg32 *) BrakeTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
        #define BrakeTimer_COUNTER_LSB         (* (reg32 *) BrakeTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
        #define BrakeTimer_COUNTER_LSB_PTR       ((reg32 *) BrakeTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define BrakeTimer_CAPTURE_LSB         (* (reg32 *) BrakeTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
            #define BrakeTimer_CAPTURE_LSB_PTR       ((reg32 *) BrakeTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
            #define BrakeTimer_PERIOD_LSB          (* (reg32 *) BrakeTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
            #define BrakeTimer_PERIOD_LSB_PTR        ((reg32 *) BrakeTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
            #define BrakeTimer_COUNTER_LSB         (* (reg32 *) BrakeTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
            #define BrakeTimer_COUNTER_LSB_PTR       ((reg32 *) BrakeTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define BrakeTimer_CAPTURE_LSB         (* (reg32 *) BrakeTimer_TimerUDB_sT24_timerdp_u0__32BIT_F0_REG )
            #define BrakeTimer_CAPTURE_LSB_PTR       ((reg32 *) BrakeTimer_TimerUDB_sT24_timerdp_u0__32BIT_F0_REG )
            #define BrakeTimer_PERIOD_LSB          (* (reg32 *) BrakeTimer_TimerUDB_sT24_timerdp_u0__32BIT_D0_REG )
            #define BrakeTimer_PERIOD_LSB_PTR        ((reg32 *) BrakeTimer_TimerUDB_sT24_timerdp_u0__32BIT_D0_REG )
            #define BrakeTimer_COUNTER_LSB         (* (reg32 *) BrakeTimer_TimerUDB_sT24_timerdp_u0__32BIT_A0_REG )
            #define BrakeTimer_COUNTER_LSB_PTR       ((reg32 *) BrakeTimer_TimerUDB_sT24_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define BrakeTimer_COUNTER_LSB_PTR_8BIT       ((reg8 *) BrakeTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
    
    #if (BrakeTimer_UsingHWCaptureCounter)
        #define BrakeTimer_CAP_COUNT              (*(reg8 *) BrakeTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define BrakeTimer_CAP_COUNT_PTR          ( (reg8 *) BrakeTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define BrakeTimer_CAPTURE_COUNT_CTRL     (*(reg8 *) BrakeTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define BrakeTimer_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) BrakeTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (BrakeTimer_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define BrakeTimer_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define BrakeTimer_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define BrakeTimer_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define BrakeTimer_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define BrakeTimer_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define BrakeTimer_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << BrakeTimer_CTRL_INTCNT_SHIFT))
    #define BrakeTimer_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << BrakeTimer_CTRL_TRIG_MODE_SHIFT))
    #define BrakeTimer_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << BrakeTimer_CTRL_TRIG_EN_SHIFT))
    #define BrakeTimer_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << BrakeTimer_CTRL_CAP_MODE_SHIFT))
    #define BrakeTimer_CTRL_ENABLE                    ((uint8)((uint8)0x01u << BrakeTimer_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define BrakeTimer_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define BrakeTimer_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define BrakeTimer_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define BrakeTimer_STATUS_TC_INT_MASK_SHIFT       BrakeTimer_STATUS_TC_SHIFT
    #define BrakeTimer_STATUS_CAPTURE_INT_MASK_SHIFT  BrakeTimer_STATUS_CAPTURE_SHIFT
    #define BrakeTimer_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define BrakeTimer_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define BrakeTimer_STATUS_FIFOFULL_INT_MASK_SHIFT BrakeTimer_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define BrakeTimer_STATUS_TC                      ((uint8)((uint8)0x01u << BrakeTimer_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define BrakeTimer_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << BrakeTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define BrakeTimer_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << BrakeTimer_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define BrakeTimer_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << BrakeTimer_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define BrakeTimer_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << BrakeTimer_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define BrakeTimer_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << BrakeTimer_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define BrakeTimer_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << BrakeTimer_STATUS_FIFOFULL_SHIFT))

    #define BrakeTimer_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define BrakeTimer_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define BrakeTimer_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define BrakeTimer_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define BrakeTimer_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define BrakeTimer_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_BrakeTimer_H */


/* [] END OF FILE */
