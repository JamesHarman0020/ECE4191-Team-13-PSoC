/*******************************************************************************
* File Name: PWMS1.h
* Version 3.30
*
* Description:
*  Contains the prototypes and constants for the functions available to the
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PWM_PWMS1_H)
#define CY_PWM_PWMS1_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 PWMS1_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define PWMS1_Resolution                     (16u)
#define PWMS1_UsingFixedFunction             (0u)
#define PWMS1_DeadBandMode                   (0u)
#define PWMS1_KillModeMinTime                (0u)
#define PWMS1_KillMode                       (0u)
#define PWMS1_PWMMode                        (1u)
#define PWMS1_PWMModeIsCenterAligned         (0u)
#define PWMS1_DeadBandUsed                   (0u)
#define PWMS1_DeadBand2_4                    (0u)

#if !defined(PWMS1_PWMUDB_genblk8_stsreg__REMOVED)
    #define PWMS1_UseStatus                  (1u)
#else
    #define PWMS1_UseStatus                  (0u)
#endif /* !defined(PWMS1_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(PWMS1_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define PWMS1_UseControl                 (1u)
#else
    #define PWMS1_UseControl                 (0u)
#endif /* !defined(PWMS1_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define PWMS1_UseOneCompareMode              (0u)
#define PWMS1_MinimumKillTime                (1u)
#define PWMS1_EnableMode                     (0u)

#define PWMS1_CompareMode1SW                 (0u)
#define PWMS1_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define PWMS1__B_PWM__DISABLED 0
#define PWMS1__B_PWM__ASYNCHRONOUS 1
#define PWMS1__B_PWM__SINGLECYCLE 2
#define PWMS1__B_PWM__LATCHED 3
#define PWMS1__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define PWMS1__B_PWM__DBMDISABLED 0
#define PWMS1__B_PWM__DBM_2_4_CLOCKS 1
#define PWMS1__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define PWMS1__B_PWM__ONE_OUTPUT 0
#define PWMS1__B_PWM__TWO_OUTPUTS 1
#define PWMS1__B_PWM__DUAL_EDGE 2
#define PWMS1__B_PWM__CENTER_ALIGN 3
#define PWMS1__B_PWM__DITHER 5
#define PWMS1__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define PWMS1__B_PWM__LESS_THAN 1
#define PWMS1__B_PWM__LESS_THAN_OR_EQUAL 2
#define PWMS1__B_PWM__GREATER_THAN 3
#define PWMS1__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define PWMS1__B_PWM__EQUAL 0
#define PWMS1__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!PWMS1_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!PWMS1_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!PWMS1_PWMModeIsCenterAligned) */
        #if (PWMS1_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (PWMS1_UseStatus) */

        /* Backup for Deadband parameters */
        #if(PWMS1_DeadBandMode == PWMS1__B_PWM__DBM_256_CLOCKS || \
            PWMS1_DeadBandMode == PWMS1__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(PWMS1_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (PWMS1_KillModeMinTime) */

        /* Backup control register */
        #if(PWMS1_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (PWMS1_UseControl) */

    #endif /* (!PWMS1_UsingFixedFunction) */

}PWMS1_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    PWMS1_Start(void) ;
void    PWMS1_Stop(void) ;

#if (PWMS1_UseStatus || PWMS1_UsingFixedFunction)
    void  PWMS1_SetInterruptMode(uint8 interruptMode) ;
    uint8 PWMS1_ReadStatusRegister(void) ;
#endif /* (PWMS1_UseStatus || PWMS1_UsingFixedFunction) */

#define PWMS1_GetInterruptSource() PWMS1_ReadStatusRegister()

#if (PWMS1_UseControl)
    uint8 PWMS1_ReadControlRegister(void) ;
    void  PWMS1_WriteControlRegister(uint8 control)
          ;
#endif /* (PWMS1_UseControl) */

#if (PWMS1_UseOneCompareMode)
   #if (PWMS1_CompareMode1SW)
       void    PWMS1_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (PWMS1_CompareMode1SW) */
#else
    #if (PWMS1_CompareMode1SW)
        void    PWMS1_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (PWMS1_CompareMode1SW) */
    #if (PWMS1_CompareMode2SW)
        void    PWMS1_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (PWMS1_CompareMode2SW) */
#endif /* (PWMS1_UseOneCompareMode) */

#if (!PWMS1_UsingFixedFunction)
    uint16   PWMS1_ReadCounter(void) ;
    uint16 PWMS1_ReadCapture(void) ;

    #if (PWMS1_UseStatus)
            void PWMS1_ClearFIFO(void) ;
    #endif /* (PWMS1_UseStatus) */

    void    PWMS1_WriteCounter(uint16 counter)
            ;
#endif /* (!PWMS1_UsingFixedFunction) */

void    PWMS1_WritePeriod(uint16 period)
        ;
uint16 PWMS1_ReadPeriod(void) ;

#if (PWMS1_UseOneCompareMode)
    void    PWMS1_WriteCompare(uint16 compare)
            ;
    uint16 PWMS1_ReadCompare(void) ;
#else
    void    PWMS1_WriteCompare1(uint16 compare)
            ;
    uint16 PWMS1_ReadCompare1(void) ;
    void    PWMS1_WriteCompare2(uint16 compare)
            ;
    uint16 PWMS1_ReadCompare2(void) ;
#endif /* (PWMS1_UseOneCompareMode) */


#if (PWMS1_DeadBandUsed)
    void    PWMS1_WriteDeadTime(uint8 deadtime) ;
    uint8   PWMS1_ReadDeadTime(void) ;
#endif /* (PWMS1_DeadBandUsed) */

#if ( PWMS1_KillModeMinTime)
    void PWMS1_WriteKillTime(uint8 killtime) ;
    uint8 PWMS1_ReadKillTime(void) ;
#endif /* ( PWMS1_KillModeMinTime) */

void PWMS1_Init(void) ;
void PWMS1_Enable(void) ;
void PWMS1_Sleep(void) ;
void PWMS1_Wakeup(void) ;
void PWMS1_SaveConfig(void) ;
void PWMS1_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define PWMS1_INIT_PERIOD_VALUE          (3200u)
#define PWMS1_INIT_COMPARE_VALUE1        (1270u)
#define PWMS1_INIT_COMPARE_VALUE2        (63u)
#define PWMS1_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    PWMS1_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    PWMS1_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    PWMS1_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    PWMS1_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define PWMS1_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  PWMS1_CTRL_CMPMODE2_SHIFT)
#define PWMS1_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  PWMS1_CTRL_CMPMODE1_SHIFT)
#define PWMS1_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (PWMS1_UsingFixedFunction)
   #define PWMS1_PERIOD_LSB              (*(reg16 *) PWMS1_PWMHW__PER0)
   #define PWMS1_PERIOD_LSB_PTR          ( (reg16 *) PWMS1_PWMHW__PER0)
   #define PWMS1_COMPARE1_LSB            (*(reg16 *) PWMS1_PWMHW__CNT_CMP0)
   #define PWMS1_COMPARE1_LSB_PTR        ( (reg16 *) PWMS1_PWMHW__CNT_CMP0)
   #define PWMS1_COMPARE2_LSB            (0x00u)
   #define PWMS1_COMPARE2_LSB_PTR        (0x00u)
   #define PWMS1_COUNTER_LSB             (*(reg16 *) PWMS1_PWMHW__CNT_CMP0)
   #define PWMS1_COUNTER_LSB_PTR         ( (reg16 *) PWMS1_PWMHW__CNT_CMP0)
   #define PWMS1_CAPTURE_LSB             (*(reg16 *) PWMS1_PWMHW__CAP0)
   #define PWMS1_CAPTURE_LSB_PTR         ( (reg16 *) PWMS1_PWMHW__CAP0)
   #define PWMS1_RT1                     (*(reg8 *)  PWMS1_PWMHW__RT1)
   #define PWMS1_RT1_PTR                 ( (reg8 *)  PWMS1_PWMHW__RT1)

#else
   #if (PWMS1_Resolution == 8u) /* 8bit - PWM */

       #if(PWMS1_PWMModeIsCenterAligned)
           #define PWMS1_PERIOD_LSB      (*(reg8 *)  PWMS1_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define PWMS1_PERIOD_LSB_PTR  ((reg8 *)   PWMS1_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define PWMS1_PERIOD_LSB      (*(reg8 *)  PWMS1_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define PWMS1_PERIOD_LSB_PTR  ((reg8 *)   PWMS1_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (PWMS1_PWMModeIsCenterAligned) */

       #define PWMS1_COMPARE1_LSB        (*(reg8 *)  PWMS1_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define PWMS1_COMPARE1_LSB_PTR    ((reg8 *)   PWMS1_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define PWMS1_COMPARE2_LSB        (*(reg8 *)  PWMS1_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define PWMS1_COMPARE2_LSB_PTR    ((reg8 *)   PWMS1_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define PWMS1_COUNTERCAP_LSB      (*(reg8 *)  PWMS1_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define PWMS1_COUNTERCAP_LSB_PTR  ((reg8 *)   PWMS1_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define PWMS1_COUNTER_LSB         (*(reg8 *)  PWMS1_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define PWMS1_COUNTER_LSB_PTR     ((reg8 *)   PWMS1_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define PWMS1_CAPTURE_LSB         (*(reg8 *)  PWMS1_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define PWMS1_CAPTURE_LSB_PTR     ((reg8 *)   PWMS1_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(PWMS1_PWMModeIsCenterAligned)
               #define PWMS1_PERIOD_LSB      (*(reg16 *) PWMS1_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define PWMS1_PERIOD_LSB_PTR  ((reg16 *)  PWMS1_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define PWMS1_PERIOD_LSB      (*(reg16 *) PWMS1_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define PWMS1_PERIOD_LSB_PTR  ((reg16 *)  PWMS1_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (PWMS1_PWMModeIsCenterAligned) */

            #define PWMS1_COMPARE1_LSB       (*(reg16 *) PWMS1_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define PWMS1_COMPARE1_LSB_PTR   ((reg16 *)  PWMS1_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define PWMS1_COMPARE2_LSB       (*(reg16 *) PWMS1_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define PWMS1_COMPARE2_LSB_PTR   ((reg16 *)  PWMS1_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define PWMS1_COUNTERCAP_LSB     (*(reg16 *) PWMS1_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define PWMS1_COUNTERCAP_LSB_PTR ((reg16 *)  PWMS1_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define PWMS1_COUNTER_LSB        (*(reg16 *) PWMS1_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define PWMS1_COUNTER_LSB_PTR    ((reg16 *)  PWMS1_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define PWMS1_CAPTURE_LSB        (*(reg16 *) PWMS1_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define PWMS1_CAPTURE_LSB_PTR    ((reg16 *)  PWMS1_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(PWMS1_PWMModeIsCenterAligned)
               #define PWMS1_PERIOD_LSB      (*(reg16 *) PWMS1_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define PWMS1_PERIOD_LSB_PTR  ((reg16 *)  PWMS1_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define PWMS1_PERIOD_LSB      (*(reg16 *) PWMS1_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define PWMS1_PERIOD_LSB_PTR  ((reg16 *)  PWMS1_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (PWMS1_PWMModeIsCenterAligned) */

            #define PWMS1_COMPARE1_LSB       (*(reg16 *) PWMS1_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define PWMS1_COMPARE1_LSB_PTR   ((reg16 *)  PWMS1_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define PWMS1_COMPARE2_LSB       (*(reg16 *) PWMS1_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define PWMS1_COMPARE2_LSB_PTR   ((reg16 *)  PWMS1_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define PWMS1_COUNTERCAP_LSB     (*(reg16 *) PWMS1_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define PWMS1_COUNTERCAP_LSB_PTR ((reg16 *)  PWMS1_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define PWMS1_COUNTER_LSB        (*(reg16 *) PWMS1_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define PWMS1_COUNTER_LSB_PTR    ((reg16 *)  PWMS1_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define PWMS1_CAPTURE_LSB        (*(reg16 *) PWMS1_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define PWMS1_CAPTURE_LSB_PTR    ((reg16 *)  PWMS1_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define PWMS1_AUX_CONTROLDP1          (*(reg8 *)  PWMS1_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define PWMS1_AUX_CONTROLDP1_PTR      ((reg8 *)   PWMS1_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (PWMS1_Resolution == 8) */

   #define PWMS1_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  PWMS1_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define PWMS1_AUX_CONTROLDP0          (*(reg8 *)  PWMS1_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define PWMS1_AUX_CONTROLDP0_PTR      ((reg8 *)   PWMS1_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (PWMS1_UsingFixedFunction) */

#if(PWMS1_KillModeMinTime )
    #define PWMS1_KILLMODEMINTIME        (*(reg8 *)  PWMS1_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define PWMS1_KILLMODEMINTIME_PTR    ((reg8 *)   PWMS1_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (PWMS1_KillModeMinTime ) */

#if(PWMS1_DeadBandMode == PWMS1__B_PWM__DBM_256_CLOCKS)
    #define PWMS1_DEADBAND_COUNT         (*(reg8 *)  PWMS1_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define PWMS1_DEADBAND_COUNT_PTR     ((reg8 *)   PWMS1_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define PWMS1_DEADBAND_LSB_PTR       ((reg8 *)   PWMS1_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define PWMS1_DEADBAND_LSB           (*(reg8 *)  PWMS1_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(PWMS1_DeadBandMode == PWMS1__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (PWMS1_UsingFixedFunction)
        #define PWMS1_DEADBAND_COUNT         (*(reg8 *)  PWMS1_PWMHW__CFG0)
        #define PWMS1_DEADBAND_COUNT_PTR     ((reg8 *)   PWMS1_PWMHW__CFG0)
        #define PWMS1_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << PWMS1_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define PWMS1_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define PWMS1_DEADBAND_COUNT         (*(reg8 *)  PWMS1_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define PWMS1_DEADBAND_COUNT_PTR     ((reg8 *)   PWMS1_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define PWMS1_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << PWMS1_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define PWMS1_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (PWMS1_UsingFixedFunction) */
#endif /* (PWMS1_DeadBandMode == PWMS1__B_PWM__DBM_256_CLOCKS) */



#if (PWMS1_UsingFixedFunction)
    #define PWMS1_STATUS                 (*(reg8 *) PWMS1_PWMHW__SR0)
    #define PWMS1_STATUS_PTR             ((reg8 *) PWMS1_PWMHW__SR0)
    #define PWMS1_STATUS_MASK            (*(reg8 *) PWMS1_PWMHW__SR0)
    #define PWMS1_STATUS_MASK_PTR        ((reg8 *) PWMS1_PWMHW__SR0)
    #define PWMS1_CONTROL                (*(reg8 *) PWMS1_PWMHW__CFG0)
    #define PWMS1_CONTROL_PTR            ((reg8 *) PWMS1_PWMHW__CFG0)
    #define PWMS1_CONTROL2               (*(reg8 *) PWMS1_PWMHW__CFG1)
    #define PWMS1_CONTROL3               (*(reg8 *) PWMS1_PWMHW__CFG2)
    #define PWMS1_GLOBAL_ENABLE          (*(reg8 *) PWMS1_PWMHW__PM_ACT_CFG)
    #define PWMS1_GLOBAL_ENABLE_PTR      ( (reg8 *) PWMS1_PWMHW__PM_ACT_CFG)
    #define PWMS1_GLOBAL_STBY_ENABLE     (*(reg8 *) PWMS1_PWMHW__PM_STBY_CFG)
    #define PWMS1_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) PWMS1_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define PWMS1_BLOCK_EN_MASK          (PWMS1_PWMHW__PM_ACT_MSK)
    #define PWMS1_BLOCK_STBY_EN_MASK     (PWMS1_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define PWMS1_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define PWMS1_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define PWMS1_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define PWMS1_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define PWMS1_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define PWMS1_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define PWMS1_CTRL_ENABLE            (uint8)((uint8)0x01u << PWMS1_CTRL_ENABLE_SHIFT)
    #define PWMS1_CTRL_RESET             (uint8)((uint8)0x01u << PWMS1_CTRL_RESET_SHIFT)
    #define PWMS1_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << PWMS1_CTRL_CMPMODE2_SHIFT)
    #define PWMS1_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << PWMS1_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define PWMS1_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define PWMS1_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << PWMS1_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define PWMS1_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define PWMS1_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define PWMS1_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define PWMS1_STATUS_TC_INT_EN_MASK_SHIFT            (PWMS1_STATUS_TC_SHIFT - 4u)
    #define PWMS1_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define PWMS1_STATUS_CMP1_INT_EN_MASK_SHIFT          (PWMS1_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define PWMS1_STATUS_TC              (uint8)((uint8)0x01u << PWMS1_STATUS_TC_SHIFT)
    #define PWMS1_STATUS_CMP1            (uint8)((uint8)0x01u << PWMS1_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define PWMS1_STATUS_TC_INT_EN_MASK              (uint8)((uint8)PWMS1_STATUS_TC >> 4u)
    #define PWMS1_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)PWMS1_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define PWMS1_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define PWMS1_RT1_MASK              (uint8)((uint8)0x03u << PWMS1_RT1_SHIFT)
    #define PWMS1_SYNC                  (uint8)((uint8)0x03u << PWMS1_RT1_SHIFT)
    #define PWMS1_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define PWMS1_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << PWMS1_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define PWMS1_SYNCDSI_EN            (uint8)((uint8)0x0Fu << PWMS1_SYNCDSI_SHIFT)


#else
    #define PWMS1_STATUS                (*(reg8 *)   PWMS1_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define PWMS1_STATUS_PTR            ((reg8 *)    PWMS1_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define PWMS1_STATUS_MASK           (*(reg8 *)   PWMS1_PWMUDB_genblk8_stsreg__MASK_REG)
    #define PWMS1_STATUS_MASK_PTR       ((reg8 *)    PWMS1_PWMUDB_genblk8_stsreg__MASK_REG)
    #define PWMS1_STATUS_AUX_CTRL       (*(reg8 *)   PWMS1_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define PWMS1_CONTROL               (*(reg8 *)   PWMS1_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define PWMS1_CONTROL_PTR           ((reg8 *)    PWMS1_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define PWMS1_CTRL_ENABLE_SHIFT      (0x07u)
    #define PWMS1_CTRL_RESET_SHIFT       (0x06u)
    #define PWMS1_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define PWMS1_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define PWMS1_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define PWMS1_CTRL_ENABLE            (uint8)((uint8)0x01u << PWMS1_CTRL_ENABLE_SHIFT)
    #define PWMS1_CTRL_RESET             (uint8)((uint8)0x01u << PWMS1_CTRL_RESET_SHIFT)
    #define PWMS1_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << PWMS1_CTRL_CMPMODE2_SHIFT)
    #define PWMS1_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << PWMS1_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define PWMS1_STATUS_KILL_SHIFT          (0x05u)
    #define PWMS1_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define PWMS1_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define PWMS1_STATUS_TC_SHIFT            (0x02u)
    #define PWMS1_STATUS_CMP2_SHIFT          (0x01u)
    #define PWMS1_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define PWMS1_STATUS_KILL_INT_EN_MASK_SHIFT          (PWMS1_STATUS_KILL_SHIFT)
    #define PWMS1_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (PWMS1_STATUS_FIFONEMPTY_SHIFT)
    #define PWMS1_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (PWMS1_STATUS_FIFOFULL_SHIFT)
    #define PWMS1_STATUS_TC_INT_EN_MASK_SHIFT            (PWMS1_STATUS_TC_SHIFT)
    #define PWMS1_STATUS_CMP2_INT_EN_MASK_SHIFT          (PWMS1_STATUS_CMP2_SHIFT)
    #define PWMS1_STATUS_CMP1_INT_EN_MASK_SHIFT          (PWMS1_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define PWMS1_STATUS_KILL            (uint8)((uint8)0x00u << PWMS1_STATUS_KILL_SHIFT )
    #define PWMS1_STATUS_FIFOFULL        (uint8)((uint8)0x01u << PWMS1_STATUS_FIFOFULL_SHIFT)
    #define PWMS1_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << PWMS1_STATUS_FIFONEMPTY_SHIFT)
    #define PWMS1_STATUS_TC              (uint8)((uint8)0x01u << PWMS1_STATUS_TC_SHIFT)
    #define PWMS1_STATUS_CMP2            (uint8)((uint8)0x01u << PWMS1_STATUS_CMP2_SHIFT)
    #define PWMS1_STATUS_CMP1            (uint8)((uint8)0x01u << PWMS1_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define PWMS1_STATUS_KILL_INT_EN_MASK            (PWMS1_STATUS_KILL)
    #define PWMS1_STATUS_FIFOFULL_INT_EN_MASK        (PWMS1_STATUS_FIFOFULL)
    #define PWMS1_STATUS_FIFONEMPTY_INT_EN_MASK      (PWMS1_STATUS_FIFONEMPTY)
    #define PWMS1_STATUS_TC_INT_EN_MASK              (PWMS1_STATUS_TC)
    #define PWMS1_STATUS_CMP2_INT_EN_MASK            (PWMS1_STATUS_CMP2)
    #define PWMS1_STATUS_CMP1_INT_EN_MASK            (PWMS1_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define PWMS1_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define PWMS1_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define PWMS1_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define PWMS1_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define PWMS1_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* PWMS1_UsingFixedFunction */

#endif  /* CY_PWM_PWMS1_H */


/* [] END OF FILE */
