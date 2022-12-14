/*******************************************************************************
* File Name: Quad2B.h  
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

#if !defined(CY_PINS_Quad2B_H) /* Pins Quad2B_H */
#define CY_PINS_Quad2B_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Quad2B_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Quad2B__PORT == 15 && ((Quad2B__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Quad2B_Write(uint8 value);
void    Quad2B_SetDriveMode(uint8 mode);
uint8   Quad2B_ReadDataReg(void);
uint8   Quad2B_Read(void);
void    Quad2B_SetInterruptMode(uint16 position, uint16 mode);
uint8   Quad2B_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Quad2B_SetDriveMode() function.
     *  @{
     */
        #define Quad2B_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Quad2B_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Quad2B_DM_RES_UP          PIN_DM_RES_UP
        #define Quad2B_DM_RES_DWN         PIN_DM_RES_DWN
        #define Quad2B_DM_OD_LO           PIN_DM_OD_LO
        #define Quad2B_DM_OD_HI           PIN_DM_OD_HI
        #define Quad2B_DM_STRONG          PIN_DM_STRONG
        #define Quad2B_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Quad2B_MASK               Quad2B__MASK
#define Quad2B_SHIFT              Quad2B__SHIFT
#define Quad2B_WIDTH              1u

/* Interrupt constants */
#if defined(Quad2B__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Quad2B_SetInterruptMode() function.
     *  @{
     */
        #define Quad2B_INTR_NONE      (uint16)(0x0000u)
        #define Quad2B_INTR_RISING    (uint16)(0x0001u)
        #define Quad2B_INTR_FALLING   (uint16)(0x0002u)
        #define Quad2B_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Quad2B_INTR_MASK      (0x01u) 
#endif /* (Quad2B__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Quad2B_PS                     (* (reg8 *) Quad2B__PS)
/* Data Register */
#define Quad2B_DR                     (* (reg8 *) Quad2B__DR)
/* Port Number */
#define Quad2B_PRT_NUM                (* (reg8 *) Quad2B__PRT) 
/* Connect to Analog Globals */                                                  
#define Quad2B_AG                     (* (reg8 *) Quad2B__AG)                       
/* Analog MUX bux enable */
#define Quad2B_AMUX                   (* (reg8 *) Quad2B__AMUX) 
/* Bidirectional Enable */                                                        
#define Quad2B_BIE                    (* (reg8 *) Quad2B__BIE)
/* Bit-mask for Aliased Register Access */
#define Quad2B_BIT_MASK               (* (reg8 *) Quad2B__BIT_MASK)
/* Bypass Enable */
#define Quad2B_BYP                    (* (reg8 *) Quad2B__BYP)
/* Port wide control signals */                                                   
#define Quad2B_CTL                    (* (reg8 *) Quad2B__CTL)
/* Drive Modes */
#define Quad2B_DM0                    (* (reg8 *) Quad2B__DM0) 
#define Quad2B_DM1                    (* (reg8 *) Quad2B__DM1)
#define Quad2B_DM2                    (* (reg8 *) Quad2B__DM2) 
/* Input Buffer Disable Override */
#define Quad2B_INP_DIS                (* (reg8 *) Quad2B__INP_DIS)
/* LCD Common or Segment Drive */
#define Quad2B_LCD_COM_SEG            (* (reg8 *) Quad2B__LCD_COM_SEG)
/* Enable Segment LCD */
#define Quad2B_LCD_EN                 (* (reg8 *) Quad2B__LCD_EN)
/* Slew Rate Control */
#define Quad2B_SLW                    (* (reg8 *) Quad2B__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Quad2B_PRTDSI__CAPS_SEL       (* (reg8 *) Quad2B__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Quad2B_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Quad2B__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Quad2B_PRTDSI__OE_SEL0        (* (reg8 *) Quad2B__PRTDSI__OE_SEL0) 
#define Quad2B_PRTDSI__OE_SEL1        (* (reg8 *) Quad2B__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Quad2B_PRTDSI__OUT_SEL0       (* (reg8 *) Quad2B__PRTDSI__OUT_SEL0) 
#define Quad2B_PRTDSI__OUT_SEL1       (* (reg8 *) Quad2B__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Quad2B_PRTDSI__SYNC_OUT       (* (reg8 *) Quad2B__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Quad2B__SIO_CFG)
    #define Quad2B_SIO_HYST_EN        (* (reg8 *) Quad2B__SIO_HYST_EN)
    #define Quad2B_SIO_REG_HIFREQ     (* (reg8 *) Quad2B__SIO_REG_HIFREQ)
    #define Quad2B_SIO_CFG            (* (reg8 *) Quad2B__SIO_CFG)
    #define Quad2B_SIO_DIFF           (* (reg8 *) Quad2B__SIO_DIFF)
#endif /* (Quad2B__SIO_CFG) */

/* Interrupt Registers */
#if defined(Quad2B__INTSTAT)
    #define Quad2B_INTSTAT            (* (reg8 *) Quad2B__INTSTAT)
    #define Quad2B_SNAP               (* (reg8 *) Quad2B__SNAP)
    
	#define Quad2B_0_INTTYPE_REG 		(* (reg8 *) Quad2B__0__INTTYPE)
#endif /* (Quad2B__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Quad2B_H */


/* [] END OF FILE */
