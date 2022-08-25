/*******************************************************************************
* File Name: TB_PWM2.h  
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

#if !defined(CY_PINS_TB_PWM2_H) /* Pins TB_PWM2_H */
#define CY_PINS_TB_PWM2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "TB_PWM2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 TB_PWM2__PORT == 15 && ((TB_PWM2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    TB_PWM2_Write(uint8 value);
void    TB_PWM2_SetDriveMode(uint8 mode);
uint8   TB_PWM2_ReadDataReg(void);
uint8   TB_PWM2_Read(void);
void    TB_PWM2_SetInterruptMode(uint16 position, uint16 mode);
uint8   TB_PWM2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the TB_PWM2_SetDriveMode() function.
     *  @{
     */
        #define TB_PWM2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define TB_PWM2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define TB_PWM2_DM_RES_UP          PIN_DM_RES_UP
        #define TB_PWM2_DM_RES_DWN         PIN_DM_RES_DWN
        #define TB_PWM2_DM_OD_LO           PIN_DM_OD_LO
        #define TB_PWM2_DM_OD_HI           PIN_DM_OD_HI
        #define TB_PWM2_DM_STRONG          PIN_DM_STRONG
        #define TB_PWM2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define TB_PWM2_MASK               TB_PWM2__MASK
#define TB_PWM2_SHIFT              TB_PWM2__SHIFT
#define TB_PWM2_WIDTH              1u

/* Interrupt constants */
#if defined(TB_PWM2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in TB_PWM2_SetInterruptMode() function.
     *  @{
     */
        #define TB_PWM2_INTR_NONE      (uint16)(0x0000u)
        #define TB_PWM2_INTR_RISING    (uint16)(0x0001u)
        #define TB_PWM2_INTR_FALLING   (uint16)(0x0002u)
        #define TB_PWM2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define TB_PWM2_INTR_MASK      (0x01u) 
#endif /* (TB_PWM2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define TB_PWM2_PS                     (* (reg8 *) TB_PWM2__PS)
/* Data Register */
#define TB_PWM2_DR                     (* (reg8 *) TB_PWM2__DR)
/* Port Number */
#define TB_PWM2_PRT_NUM                (* (reg8 *) TB_PWM2__PRT) 
/* Connect to Analog Globals */                                                  
#define TB_PWM2_AG                     (* (reg8 *) TB_PWM2__AG)                       
/* Analog MUX bux enable */
#define TB_PWM2_AMUX                   (* (reg8 *) TB_PWM2__AMUX) 
/* Bidirectional Enable */                                                        
#define TB_PWM2_BIE                    (* (reg8 *) TB_PWM2__BIE)
/* Bit-mask for Aliased Register Access */
#define TB_PWM2_BIT_MASK               (* (reg8 *) TB_PWM2__BIT_MASK)
/* Bypass Enable */
#define TB_PWM2_BYP                    (* (reg8 *) TB_PWM2__BYP)
/* Port wide control signals */                                                   
#define TB_PWM2_CTL                    (* (reg8 *) TB_PWM2__CTL)
/* Drive Modes */
#define TB_PWM2_DM0                    (* (reg8 *) TB_PWM2__DM0) 
#define TB_PWM2_DM1                    (* (reg8 *) TB_PWM2__DM1)
#define TB_PWM2_DM2                    (* (reg8 *) TB_PWM2__DM2) 
/* Input Buffer Disable Override */
#define TB_PWM2_INP_DIS                (* (reg8 *) TB_PWM2__INP_DIS)
/* LCD Common or Segment Drive */
#define TB_PWM2_LCD_COM_SEG            (* (reg8 *) TB_PWM2__LCD_COM_SEG)
/* Enable Segment LCD */
#define TB_PWM2_LCD_EN                 (* (reg8 *) TB_PWM2__LCD_EN)
/* Slew Rate Control */
#define TB_PWM2_SLW                    (* (reg8 *) TB_PWM2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define TB_PWM2_PRTDSI__CAPS_SEL       (* (reg8 *) TB_PWM2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define TB_PWM2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) TB_PWM2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define TB_PWM2_PRTDSI__OE_SEL0        (* (reg8 *) TB_PWM2__PRTDSI__OE_SEL0) 
#define TB_PWM2_PRTDSI__OE_SEL1        (* (reg8 *) TB_PWM2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define TB_PWM2_PRTDSI__OUT_SEL0       (* (reg8 *) TB_PWM2__PRTDSI__OUT_SEL0) 
#define TB_PWM2_PRTDSI__OUT_SEL1       (* (reg8 *) TB_PWM2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define TB_PWM2_PRTDSI__SYNC_OUT       (* (reg8 *) TB_PWM2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(TB_PWM2__SIO_CFG)
    #define TB_PWM2_SIO_HYST_EN        (* (reg8 *) TB_PWM2__SIO_HYST_EN)
    #define TB_PWM2_SIO_REG_HIFREQ     (* (reg8 *) TB_PWM2__SIO_REG_HIFREQ)
    #define TB_PWM2_SIO_CFG            (* (reg8 *) TB_PWM2__SIO_CFG)
    #define TB_PWM2_SIO_DIFF           (* (reg8 *) TB_PWM2__SIO_DIFF)
#endif /* (TB_PWM2__SIO_CFG) */

/* Interrupt Registers */
#if defined(TB_PWM2__INTSTAT)
    #define TB_PWM2_INTSTAT            (* (reg8 *) TB_PWM2__INTSTAT)
    #define TB_PWM2_SNAP               (* (reg8 *) TB_PWM2__SNAP)
    
	#define TB_PWM2_0_INTTYPE_REG 		(* (reg8 *) TB_PWM2__0__INTTYPE)
#endif /* (TB_PWM2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_TB_PWM2_H */


/* [] END OF FILE */
