/*******************************************************************************
* File Name: TB_PWM4.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_TB_PWM4_H) /* Pins TB_PWM4_H */
#define CY_PINS_TB_PWM4_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "TB_PWM4_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 TB_PWM4__PORT == 15 && ((TB_PWM4__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    TB_PWM4_Write(uint8 value);
void    TB_PWM4_SetDriveMode(uint8 mode);
uint8   TB_PWM4_ReadDataReg(void);
uint8   TB_PWM4_Read(void);
void    TB_PWM4_SetInterruptMode(uint16 position, uint16 mode);
uint8   TB_PWM4_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the TB_PWM4_SetDriveMode() function.
     *  @{
     */
        #define TB_PWM4_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define TB_PWM4_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define TB_PWM4_DM_RES_UP          PIN_DM_RES_UP
        #define TB_PWM4_DM_RES_DWN         PIN_DM_RES_DWN
        #define TB_PWM4_DM_OD_LO           PIN_DM_OD_LO
        #define TB_PWM4_DM_OD_HI           PIN_DM_OD_HI
        #define TB_PWM4_DM_STRONG          PIN_DM_STRONG
        #define TB_PWM4_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define TB_PWM4_MASK               TB_PWM4__MASK
#define TB_PWM4_SHIFT              TB_PWM4__SHIFT
#define TB_PWM4_WIDTH              1u

/* Interrupt constants */
#if defined(TB_PWM4__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in TB_PWM4_SetInterruptMode() function.
     *  @{
     */
        #define TB_PWM4_INTR_NONE      (uint16)(0x0000u)
        #define TB_PWM4_INTR_RISING    (uint16)(0x0001u)
        #define TB_PWM4_INTR_FALLING   (uint16)(0x0002u)
        #define TB_PWM4_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define TB_PWM4_INTR_MASK      (0x01u) 
#endif /* (TB_PWM4__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define TB_PWM4_PS                     (* (reg8 *) TB_PWM4__PS)
/* Data Register */
#define TB_PWM4_DR                     (* (reg8 *) TB_PWM4__DR)
/* Port Number */
#define TB_PWM4_PRT_NUM                (* (reg8 *) TB_PWM4__PRT) 
/* Connect to Analog Globals */                                                  
#define TB_PWM4_AG                     (* (reg8 *) TB_PWM4__AG)                       
/* Analog MUX bux enable */
#define TB_PWM4_AMUX                   (* (reg8 *) TB_PWM4__AMUX) 
/* Bidirectional Enable */                                                        
#define TB_PWM4_BIE                    (* (reg8 *) TB_PWM4__BIE)
/* Bit-mask for Aliased Register Access */
#define TB_PWM4_BIT_MASK               (* (reg8 *) TB_PWM4__BIT_MASK)
/* Bypass Enable */
#define TB_PWM4_BYP                    (* (reg8 *) TB_PWM4__BYP)
/* Port wide control signals */                                                   
#define TB_PWM4_CTL                    (* (reg8 *) TB_PWM4__CTL)
/* Drive Modes */
#define TB_PWM4_DM0                    (* (reg8 *) TB_PWM4__DM0) 
#define TB_PWM4_DM1                    (* (reg8 *) TB_PWM4__DM1)
#define TB_PWM4_DM2                    (* (reg8 *) TB_PWM4__DM2) 
/* Input Buffer Disable Override */
#define TB_PWM4_INP_DIS                (* (reg8 *) TB_PWM4__INP_DIS)
/* LCD Common or Segment Drive */
#define TB_PWM4_LCD_COM_SEG            (* (reg8 *) TB_PWM4__LCD_COM_SEG)
/* Enable Segment LCD */
#define TB_PWM4_LCD_EN                 (* (reg8 *) TB_PWM4__LCD_EN)
/* Slew Rate Control */
#define TB_PWM4_SLW                    (* (reg8 *) TB_PWM4__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define TB_PWM4_PRTDSI__CAPS_SEL       (* (reg8 *) TB_PWM4__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define TB_PWM4_PRTDSI__DBL_SYNC_IN    (* (reg8 *) TB_PWM4__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define TB_PWM4_PRTDSI__OE_SEL0        (* (reg8 *) TB_PWM4__PRTDSI__OE_SEL0) 
#define TB_PWM4_PRTDSI__OE_SEL1        (* (reg8 *) TB_PWM4__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define TB_PWM4_PRTDSI__OUT_SEL0       (* (reg8 *) TB_PWM4__PRTDSI__OUT_SEL0) 
#define TB_PWM4_PRTDSI__OUT_SEL1       (* (reg8 *) TB_PWM4__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define TB_PWM4_PRTDSI__SYNC_OUT       (* (reg8 *) TB_PWM4__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(TB_PWM4__SIO_CFG)
    #define TB_PWM4_SIO_HYST_EN        (* (reg8 *) TB_PWM4__SIO_HYST_EN)
    #define TB_PWM4_SIO_REG_HIFREQ     (* (reg8 *) TB_PWM4__SIO_REG_HIFREQ)
    #define TB_PWM4_SIO_CFG            (* (reg8 *) TB_PWM4__SIO_CFG)
    #define TB_PWM4_SIO_DIFF           (* (reg8 *) TB_PWM4__SIO_DIFF)
#endif /* (TB_PWM4__SIO_CFG) */

/* Interrupt Registers */
#if defined(TB_PWM4__INTSTAT)
    #define TB_PWM4_INTSTAT            (* (reg8 *) TB_PWM4__INTSTAT)
    #define TB_PWM4_SNAP               (* (reg8 *) TB_PWM4__SNAP)
    
	#define TB_PWM4_0_INTTYPE_REG 		(* (reg8 *) TB_PWM4__0__INTTYPE)
#endif /* (TB_PWM4__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_TB_PWM4_H */


/* [] END OF FILE */
