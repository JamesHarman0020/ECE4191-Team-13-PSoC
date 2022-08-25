/*******************************************************************************
* File Name: TB_PWM1.h  
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

#if !defined(CY_PINS_TB_PWM1_H) /* Pins TB_PWM1_H */
#define CY_PINS_TB_PWM1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "TB_PWM1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 TB_PWM1__PORT == 15 && ((TB_PWM1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    TB_PWM1_Write(uint8 value);
void    TB_PWM1_SetDriveMode(uint8 mode);
uint8   TB_PWM1_ReadDataReg(void);
uint8   TB_PWM1_Read(void);
void    TB_PWM1_SetInterruptMode(uint16 position, uint16 mode);
uint8   TB_PWM1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the TB_PWM1_SetDriveMode() function.
     *  @{
     */
        #define TB_PWM1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define TB_PWM1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define TB_PWM1_DM_RES_UP          PIN_DM_RES_UP
        #define TB_PWM1_DM_RES_DWN         PIN_DM_RES_DWN
        #define TB_PWM1_DM_OD_LO           PIN_DM_OD_LO
        #define TB_PWM1_DM_OD_HI           PIN_DM_OD_HI
        #define TB_PWM1_DM_STRONG          PIN_DM_STRONG
        #define TB_PWM1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define TB_PWM1_MASK               TB_PWM1__MASK
#define TB_PWM1_SHIFT              TB_PWM1__SHIFT
#define TB_PWM1_WIDTH              1u

/* Interrupt constants */
#if defined(TB_PWM1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in TB_PWM1_SetInterruptMode() function.
     *  @{
     */
        #define TB_PWM1_INTR_NONE      (uint16)(0x0000u)
        #define TB_PWM1_INTR_RISING    (uint16)(0x0001u)
        #define TB_PWM1_INTR_FALLING   (uint16)(0x0002u)
        #define TB_PWM1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define TB_PWM1_INTR_MASK      (0x01u) 
#endif /* (TB_PWM1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define TB_PWM1_PS                     (* (reg8 *) TB_PWM1__PS)
/* Data Register */
#define TB_PWM1_DR                     (* (reg8 *) TB_PWM1__DR)
/* Port Number */
#define TB_PWM1_PRT_NUM                (* (reg8 *) TB_PWM1__PRT) 
/* Connect to Analog Globals */                                                  
#define TB_PWM1_AG                     (* (reg8 *) TB_PWM1__AG)                       
/* Analog MUX bux enable */
#define TB_PWM1_AMUX                   (* (reg8 *) TB_PWM1__AMUX) 
/* Bidirectional Enable */                                                        
#define TB_PWM1_BIE                    (* (reg8 *) TB_PWM1__BIE)
/* Bit-mask for Aliased Register Access */
#define TB_PWM1_BIT_MASK               (* (reg8 *) TB_PWM1__BIT_MASK)
/* Bypass Enable */
#define TB_PWM1_BYP                    (* (reg8 *) TB_PWM1__BYP)
/* Port wide control signals */                                                   
#define TB_PWM1_CTL                    (* (reg8 *) TB_PWM1__CTL)
/* Drive Modes */
#define TB_PWM1_DM0                    (* (reg8 *) TB_PWM1__DM0) 
#define TB_PWM1_DM1                    (* (reg8 *) TB_PWM1__DM1)
#define TB_PWM1_DM2                    (* (reg8 *) TB_PWM1__DM2) 
/* Input Buffer Disable Override */
#define TB_PWM1_INP_DIS                (* (reg8 *) TB_PWM1__INP_DIS)
/* LCD Common or Segment Drive */
#define TB_PWM1_LCD_COM_SEG            (* (reg8 *) TB_PWM1__LCD_COM_SEG)
/* Enable Segment LCD */
#define TB_PWM1_LCD_EN                 (* (reg8 *) TB_PWM1__LCD_EN)
/* Slew Rate Control */
#define TB_PWM1_SLW                    (* (reg8 *) TB_PWM1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define TB_PWM1_PRTDSI__CAPS_SEL       (* (reg8 *) TB_PWM1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define TB_PWM1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) TB_PWM1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define TB_PWM1_PRTDSI__OE_SEL0        (* (reg8 *) TB_PWM1__PRTDSI__OE_SEL0) 
#define TB_PWM1_PRTDSI__OE_SEL1        (* (reg8 *) TB_PWM1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define TB_PWM1_PRTDSI__OUT_SEL0       (* (reg8 *) TB_PWM1__PRTDSI__OUT_SEL0) 
#define TB_PWM1_PRTDSI__OUT_SEL1       (* (reg8 *) TB_PWM1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define TB_PWM1_PRTDSI__SYNC_OUT       (* (reg8 *) TB_PWM1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(TB_PWM1__SIO_CFG)
    #define TB_PWM1_SIO_HYST_EN        (* (reg8 *) TB_PWM1__SIO_HYST_EN)
    #define TB_PWM1_SIO_REG_HIFREQ     (* (reg8 *) TB_PWM1__SIO_REG_HIFREQ)
    #define TB_PWM1_SIO_CFG            (* (reg8 *) TB_PWM1__SIO_CFG)
    #define TB_PWM1_SIO_DIFF           (* (reg8 *) TB_PWM1__SIO_DIFF)
#endif /* (TB_PWM1__SIO_CFG) */

/* Interrupt Registers */
#if defined(TB_PWM1__INTSTAT)
    #define TB_PWM1_INTSTAT            (* (reg8 *) TB_PWM1__INTSTAT)
    #define TB_PWM1_SNAP               (* (reg8 *) TB_PWM1__SNAP)
    
	#define TB_PWM1_0_INTTYPE_REG 		(* (reg8 *) TB_PWM1__0__INTTYPE)
#endif /* (TB_PWM1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_TB_PWM1_H */


/* [] END OF FILE */
