/*******************************************************************************
* File Name: TB_ENB.h  
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

#if !defined(CY_PINS_TB_ENB_H) /* Pins TB_ENB_H */
#define CY_PINS_TB_ENB_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "TB_ENB_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 TB_ENB__PORT == 15 && ((TB_ENB__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    TB_ENB_Write(uint8 value);
void    TB_ENB_SetDriveMode(uint8 mode);
uint8   TB_ENB_ReadDataReg(void);
uint8   TB_ENB_Read(void);
void    TB_ENB_SetInterruptMode(uint16 position, uint16 mode);
uint8   TB_ENB_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the TB_ENB_SetDriveMode() function.
     *  @{
     */
        #define TB_ENB_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define TB_ENB_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define TB_ENB_DM_RES_UP          PIN_DM_RES_UP
        #define TB_ENB_DM_RES_DWN         PIN_DM_RES_DWN
        #define TB_ENB_DM_OD_LO           PIN_DM_OD_LO
        #define TB_ENB_DM_OD_HI           PIN_DM_OD_HI
        #define TB_ENB_DM_STRONG          PIN_DM_STRONG
        #define TB_ENB_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define TB_ENB_MASK               TB_ENB__MASK
#define TB_ENB_SHIFT              TB_ENB__SHIFT
#define TB_ENB_WIDTH              1u

/* Interrupt constants */
#if defined(TB_ENB__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in TB_ENB_SetInterruptMode() function.
     *  @{
     */
        #define TB_ENB_INTR_NONE      (uint16)(0x0000u)
        #define TB_ENB_INTR_RISING    (uint16)(0x0001u)
        #define TB_ENB_INTR_FALLING   (uint16)(0x0002u)
        #define TB_ENB_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define TB_ENB_INTR_MASK      (0x01u) 
#endif /* (TB_ENB__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define TB_ENB_PS                     (* (reg8 *) TB_ENB__PS)
/* Data Register */
#define TB_ENB_DR                     (* (reg8 *) TB_ENB__DR)
/* Port Number */
#define TB_ENB_PRT_NUM                (* (reg8 *) TB_ENB__PRT) 
/* Connect to Analog Globals */                                                  
#define TB_ENB_AG                     (* (reg8 *) TB_ENB__AG)                       
/* Analog MUX bux enable */
#define TB_ENB_AMUX                   (* (reg8 *) TB_ENB__AMUX) 
/* Bidirectional Enable */                                                        
#define TB_ENB_BIE                    (* (reg8 *) TB_ENB__BIE)
/* Bit-mask for Aliased Register Access */
#define TB_ENB_BIT_MASK               (* (reg8 *) TB_ENB__BIT_MASK)
/* Bypass Enable */
#define TB_ENB_BYP                    (* (reg8 *) TB_ENB__BYP)
/* Port wide control signals */                                                   
#define TB_ENB_CTL                    (* (reg8 *) TB_ENB__CTL)
/* Drive Modes */
#define TB_ENB_DM0                    (* (reg8 *) TB_ENB__DM0) 
#define TB_ENB_DM1                    (* (reg8 *) TB_ENB__DM1)
#define TB_ENB_DM2                    (* (reg8 *) TB_ENB__DM2) 
/* Input Buffer Disable Override */
#define TB_ENB_INP_DIS                (* (reg8 *) TB_ENB__INP_DIS)
/* LCD Common or Segment Drive */
#define TB_ENB_LCD_COM_SEG            (* (reg8 *) TB_ENB__LCD_COM_SEG)
/* Enable Segment LCD */
#define TB_ENB_LCD_EN                 (* (reg8 *) TB_ENB__LCD_EN)
/* Slew Rate Control */
#define TB_ENB_SLW                    (* (reg8 *) TB_ENB__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define TB_ENB_PRTDSI__CAPS_SEL       (* (reg8 *) TB_ENB__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define TB_ENB_PRTDSI__DBL_SYNC_IN    (* (reg8 *) TB_ENB__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define TB_ENB_PRTDSI__OE_SEL0        (* (reg8 *) TB_ENB__PRTDSI__OE_SEL0) 
#define TB_ENB_PRTDSI__OE_SEL1        (* (reg8 *) TB_ENB__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define TB_ENB_PRTDSI__OUT_SEL0       (* (reg8 *) TB_ENB__PRTDSI__OUT_SEL0) 
#define TB_ENB_PRTDSI__OUT_SEL1       (* (reg8 *) TB_ENB__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define TB_ENB_PRTDSI__SYNC_OUT       (* (reg8 *) TB_ENB__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(TB_ENB__SIO_CFG)
    #define TB_ENB_SIO_HYST_EN        (* (reg8 *) TB_ENB__SIO_HYST_EN)
    #define TB_ENB_SIO_REG_HIFREQ     (* (reg8 *) TB_ENB__SIO_REG_HIFREQ)
    #define TB_ENB_SIO_CFG            (* (reg8 *) TB_ENB__SIO_CFG)
    #define TB_ENB_SIO_DIFF           (* (reg8 *) TB_ENB__SIO_DIFF)
#endif /* (TB_ENB__SIO_CFG) */

/* Interrupt Registers */
#if defined(TB_ENB__INTSTAT)
    #define TB_ENB_INTSTAT            (* (reg8 *) TB_ENB__INTSTAT)
    #define TB_ENB_SNAP               (* (reg8 *) TB_ENB__SNAP)
    
	#define TB_ENB_0_INTTYPE_REG 		(* (reg8 *) TB_ENB__0__INTTYPE)
#endif /* (TB_ENB__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_TB_ENB_H */


/* [] END OF FILE */
