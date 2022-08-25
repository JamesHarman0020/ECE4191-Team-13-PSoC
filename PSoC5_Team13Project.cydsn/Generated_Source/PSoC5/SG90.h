/*******************************************************************************
* File Name: SG90.h  
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

#if !defined(CY_PINS_SG90_H) /* Pins SG90_H */
#define CY_PINS_SG90_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SG90_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SG90__PORT == 15 && ((SG90__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    SG90_Write(uint8 value);
void    SG90_SetDriveMode(uint8 mode);
uint8   SG90_ReadDataReg(void);
uint8   SG90_Read(void);
void    SG90_SetInterruptMode(uint16 position, uint16 mode);
uint8   SG90_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the SG90_SetDriveMode() function.
     *  @{
     */
        #define SG90_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define SG90_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define SG90_DM_RES_UP          PIN_DM_RES_UP
        #define SG90_DM_RES_DWN         PIN_DM_RES_DWN
        #define SG90_DM_OD_LO           PIN_DM_OD_LO
        #define SG90_DM_OD_HI           PIN_DM_OD_HI
        #define SG90_DM_STRONG          PIN_DM_STRONG
        #define SG90_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define SG90_MASK               SG90__MASK
#define SG90_SHIFT              SG90__SHIFT
#define SG90_WIDTH              1u

/* Interrupt constants */
#if defined(SG90__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SG90_SetInterruptMode() function.
     *  @{
     */
        #define SG90_INTR_NONE      (uint16)(0x0000u)
        #define SG90_INTR_RISING    (uint16)(0x0001u)
        #define SG90_INTR_FALLING   (uint16)(0x0002u)
        #define SG90_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define SG90_INTR_MASK      (0x01u) 
#endif /* (SG90__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SG90_PS                     (* (reg8 *) SG90__PS)
/* Data Register */
#define SG90_DR                     (* (reg8 *) SG90__DR)
/* Port Number */
#define SG90_PRT_NUM                (* (reg8 *) SG90__PRT) 
/* Connect to Analog Globals */                                                  
#define SG90_AG                     (* (reg8 *) SG90__AG)                       
/* Analog MUX bux enable */
#define SG90_AMUX                   (* (reg8 *) SG90__AMUX) 
/* Bidirectional Enable */                                                        
#define SG90_BIE                    (* (reg8 *) SG90__BIE)
/* Bit-mask for Aliased Register Access */
#define SG90_BIT_MASK               (* (reg8 *) SG90__BIT_MASK)
/* Bypass Enable */
#define SG90_BYP                    (* (reg8 *) SG90__BYP)
/* Port wide control signals */                                                   
#define SG90_CTL                    (* (reg8 *) SG90__CTL)
/* Drive Modes */
#define SG90_DM0                    (* (reg8 *) SG90__DM0) 
#define SG90_DM1                    (* (reg8 *) SG90__DM1)
#define SG90_DM2                    (* (reg8 *) SG90__DM2) 
/* Input Buffer Disable Override */
#define SG90_INP_DIS                (* (reg8 *) SG90__INP_DIS)
/* LCD Common or Segment Drive */
#define SG90_LCD_COM_SEG            (* (reg8 *) SG90__LCD_COM_SEG)
/* Enable Segment LCD */
#define SG90_LCD_EN                 (* (reg8 *) SG90__LCD_EN)
/* Slew Rate Control */
#define SG90_SLW                    (* (reg8 *) SG90__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SG90_PRTDSI__CAPS_SEL       (* (reg8 *) SG90__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SG90_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SG90__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SG90_PRTDSI__OE_SEL0        (* (reg8 *) SG90__PRTDSI__OE_SEL0) 
#define SG90_PRTDSI__OE_SEL1        (* (reg8 *) SG90__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SG90_PRTDSI__OUT_SEL0       (* (reg8 *) SG90__PRTDSI__OUT_SEL0) 
#define SG90_PRTDSI__OUT_SEL1       (* (reg8 *) SG90__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SG90_PRTDSI__SYNC_OUT       (* (reg8 *) SG90__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(SG90__SIO_CFG)
    #define SG90_SIO_HYST_EN        (* (reg8 *) SG90__SIO_HYST_EN)
    #define SG90_SIO_REG_HIFREQ     (* (reg8 *) SG90__SIO_REG_HIFREQ)
    #define SG90_SIO_CFG            (* (reg8 *) SG90__SIO_CFG)
    #define SG90_SIO_DIFF           (* (reg8 *) SG90__SIO_DIFF)
#endif /* (SG90__SIO_CFG) */

/* Interrupt Registers */
#if defined(SG90__INTSTAT)
    #define SG90_INTSTAT            (* (reg8 *) SG90__INTSTAT)
    #define SG90_SNAP               (* (reg8 *) SG90__SNAP)
    
	#define SG90_0_INTTYPE_REG 		(* (reg8 *) SG90__0__INTTYPE)
#endif /* (SG90__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SG90_H */


/* [] END OF FILE */
