/*******************************************************************************
* File Name: TB9051_QD.h  
* Version 3.0
*
* Description:
*  This file provides constants and parameter values for the Quadrature
*  Decoder component.
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

#if !defined(CY_QUADRATURE_DECODER_TB9051_QD_H)
#define CY_QUADRATURE_DECODER_TB9051_QD_H

#include "cyfitter.h"
#include "CyLib.h"
#include "cytypes.h"

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component QuadDec_v3_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#define TB9051_QD_COUNTER_SIZE               (16u)
#define TB9051_QD_COUNTER_SIZE_8_BIT         (8u)
#define TB9051_QD_COUNTER_SIZE_16_BIT        (16u)
#define TB9051_QD_COUNTER_SIZE_32_BIT        (32u)

#if (TB9051_QD_COUNTER_SIZE == TB9051_QD_COUNTER_SIZE_8_BIT)
    #include "TB9051_QD_Cnt8.h"
#else 
    /* (TB9051_QD_COUNTER_SIZE == TB9051_QD_COUNTER_SIZE_16_BIT) || 
    *  (TB9051_QD_COUNTER_SIZE == TB9051_QD_COUNTER_SIZE_32_BIT) 
    */
    #include "TB9051_QD_Cnt16.h"
#endif /* TB9051_QD_COUNTER_SIZE == TB9051_QD_COUNTER_SIZE_8_BIT */

extern uint8 TB9051_QD_initVar;


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define TB9051_QD_COUNTER_RESOLUTION         (1u)


/***************************************
*       Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
} TB9051_QD_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  TB9051_QD_Init(void) ;
void  TB9051_QD_Start(void) ;
void  TB9051_QD_Stop(void) ;
void  TB9051_QD_Enable(void) ;
uint8 TB9051_QD_GetEvents(void) ;
void  TB9051_QD_SetInterruptMask(uint8 mask) ;
uint8 TB9051_QD_GetInterruptMask(void) ;
int16 TB9051_QD_GetCounter(void) ;
void  TB9051_QD_SetCounter(int16 value)
;
void  TB9051_QD_Sleep(void) ;
void  TB9051_QD_Wakeup(void) ;
void  TB9051_QD_SaveConfig(void) ;
void  TB9051_QD_RestoreConfig(void) ;

#if (TB9051_QD_COUNTER_SIZE == TB9051_QD_COUNTER_SIZE_32_BIT)
    CY_ISR_PROTO(TB9051_QD_ISR);
#endif /* TB9051_QD_COUNTER_SIZE == TB9051_QD_COUNTER_SIZE_32_BIT */


/***************************************
*           API Constants
***************************************/

#if (TB9051_QD_COUNTER_SIZE == TB9051_QD_COUNTER_SIZE_32_BIT)
    #define TB9051_QD_ISR_NUMBER             ((uint8) TB9051_QD_isr__INTC_NUMBER)
    #define TB9051_QD_ISR_PRIORITY           ((uint8) TB9051_QD_isr__INTC_PRIOR_NUM)
#endif /* TB9051_QD_COUNTER_SIZE == TB9051_QD_COUNTER_SIZE_32_BIT */


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define TB9051_QD_GLITCH_FILTERING           (1u)
#define TB9051_QD_INDEX_INPUT                (0u)


/***************************************
*    Initial Parameter Constants
***************************************/

#if (TB9051_QD_COUNTER_SIZE == TB9051_QD_COUNTER_SIZE_8_BIT)
    #define TB9051_QD_COUNTER_INIT_VALUE    (0x80u)
#else 
    /* (TB9051_QD_COUNTER_SIZE == TB9051_QD_COUNTER_SIZE_16_BIT) ||
    *  (TB9051_QD_COUNTER_SIZE == TB9051_QD_COUNTER_SIZE_32_BIT)
    */
    #define TB9051_QD_COUNTER_INIT_VALUE    (0x8000u)
    #define TB9051_QD_COUNTER_MAX_VALUE     (0x7FFFu)
#endif /* TB9051_QD_COUNTER_SIZE == TB9051_QD_COUNTER_SIZE_8_BIT */


/***************************************
*             Registers
***************************************/

#define TB9051_QD_STATUS_REG                 (* (reg8 *) TB9051_QD_bQuadDec_Stsreg__STATUS_REG)
#define TB9051_QD_STATUS_PTR                 (  (reg8 *) TB9051_QD_bQuadDec_Stsreg__STATUS_REG)
#define TB9051_QD_STATUS_MASK                (* (reg8 *) TB9051_QD_bQuadDec_Stsreg__MASK_REG)
#define TB9051_QD_STATUS_MASK_PTR            (  (reg8 *) TB9051_QD_bQuadDec_Stsreg__MASK_REG)
#define TB9051_QD_SR_AUX_CONTROL             (* (reg8 *) TB9051_QD_bQuadDec_Stsreg__STATUS_AUX_CTL_REG)
#define TB9051_QD_SR_AUX_CONTROL_PTR         (  (reg8 *) TB9051_QD_bQuadDec_Stsreg__STATUS_AUX_CTL_REG)


/***************************************
*        Register Constants
***************************************/

#define TB9051_QD_COUNTER_OVERFLOW_SHIFT     (0x00u)
#define TB9051_QD_COUNTER_UNDERFLOW_SHIFT    (0x01u)
#define TB9051_QD_COUNTER_RESET_SHIFT        (0x02u)
#define TB9051_QD_INVALID_IN_SHIFT           (0x03u)
#define TB9051_QD_COUNTER_OVERFLOW           ((uint8) (0x01u << TB9051_QD_COUNTER_OVERFLOW_SHIFT))
#define TB9051_QD_COUNTER_UNDERFLOW          ((uint8) (0x01u << TB9051_QD_COUNTER_UNDERFLOW_SHIFT))
#define TB9051_QD_COUNTER_RESET              ((uint8) (0x01u << TB9051_QD_COUNTER_RESET_SHIFT))
#define TB9051_QD_INVALID_IN                 ((uint8) (0x01u << TB9051_QD_INVALID_IN_SHIFT))

#define TB9051_QD_INTERRUPTS_ENABLE_SHIFT    (0x04u)
#define TB9051_QD_INTERRUPTS_ENABLE          ((uint8)(0x01u << TB9051_QD_INTERRUPTS_ENABLE_SHIFT))
#define TB9051_QD_INIT_INT_MASK              (0x0Fu)


/******************************************************************************************
* Following code are OBSOLETE and must not be used starting from Quadrature Decoder 2.20
******************************************************************************************/
#define TB9051_QD_DISABLE                    (0x00u)


#endif /* CY_QUADRATURE_DECODER_TB9051_QD_H */


/* [] END OF FILE */
