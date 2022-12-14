/*******************************************************************************
* File Name: Quad1B.h  
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

#if !defined(CY_PINS_Quad1B_H) /* Pins Quad1B_H */
#define CY_PINS_Quad1B_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Quad1B_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Quad1B__PORT == 15 && ((Quad1B__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Quad1B_Write(uint8 value);
void    Quad1B_SetDriveMode(uint8 mode);
uint8   Quad1B_ReadDataReg(void);
uint8   Quad1B_Read(void);
void    Quad1B_SetInterruptMode(uint16 position, uint16 mode);
uint8   Quad1B_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Quad1B_SetDriveMode() function.
     *  @{
     */
        #define Quad1B_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Quad1B_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Quad1B_DM_RES_UP          PIN_DM_RES_UP
        #define Quad1B_DM_RES_DWN         PIN_DM_RES_DWN
        #define Quad1B_DM_OD_LO           PIN_DM_OD_LO
        #define Quad1B_DM_OD_HI           PIN_DM_OD_HI
        #define Quad1B_DM_STRONG          PIN_DM_STRONG
        #define Quad1B_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Quad1B_MASK               Quad1B__MASK
#define Quad1B_SHIFT              Quad1B__SHIFT
#define Quad1B_WIDTH              1u

/* Interrupt constants */
#if defined(Quad1B__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Quad1B_SetInterruptMode() function.
     *  @{
     */
        #define Quad1B_INTR_NONE      (uint16)(0x0000u)
        #define Quad1B_INTR_RISING    (uint16)(0x0001u)
        #define Quad1B_INTR_FALLING   (uint16)(0x0002u)
        #define Quad1B_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Quad1B_INTR_MASK      (0x01u) 
#endif /* (Quad1B__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Quad1B_PS                     (* (reg8 *) Quad1B__PS)
/* Data Register */
#define Quad1B_DR                     (* (reg8 *) Quad1B__DR)
/* Port Number */
#define Quad1B_PRT_NUM                (* (reg8 *) Quad1B__PRT) 
/* Connect to Analog Globals */                                                  
#define Quad1B_AG                     (* (reg8 *) Quad1B__AG)                       
/* Analog MUX bux enable */
#define Quad1B_AMUX                   (* (reg8 *) Quad1B__AMUX) 
/* Bidirectional Enable */                                                        
#define Quad1B_BIE                    (* (reg8 *) Quad1B__BIE)
/* Bit-mask for Aliased Register Access */
#define Quad1B_BIT_MASK               (* (reg8 *) Quad1B__BIT_MASK)
/* Bypass Enable */
#define Quad1B_BYP                    (* (reg8 *) Quad1B__BYP)
/* Port wide control signals */                                                   
#define Quad1B_CTL                    (* (reg8 *) Quad1B__CTL)
/* Drive Modes */
#define Quad1B_DM0                    (* (reg8 *) Quad1B__DM0) 
#define Quad1B_DM1                    (* (reg8 *) Quad1B__DM1)
#define Quad1B_DM2                    (* (reg8 *) Quad1B__DM2) 
/* Input Buffer Disable Override */
#define Quad1B_INP_DIS                (* (reg8 *) Quad1B__INP_DIS)
/* LCD Common or Segment Drive */
#define Quad1B_LCD_COM_SEG            (* (reg8 *) Quad1B__LCD_COM_SEG)
/* Enable Segment LCD */
#define Quad1B_LCD_EN                 (* (reg8 *) Quad1B__LCD_EN)
/* Slew Rate Control */
#define Quad1B_SLW                    (* (reg8 *) Quad1B__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Quad1B_PRTDSI__CAPS_SEL       (* (reg8 *) Quad1B__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Quad1B_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Quad1B__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Quad1B_PRTDSI__OE_SEL0        (* (reg8 *) Quad1B__PRTDSI__OE_SEL0) 
#define Quad1B_PRTDSI__OE_SEL1        (* (reg8 *) Quad1B__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Quad1B_PRTDSI__OUT_SEL0       (* (reg8 *) Quad1B__PRTDSI__OUT_SEL0) 
#define Quad1B_PRTDSI__OUT_SEL1       (* (reg8 *) Quad1B__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Quad1B_PRTDSI__SYNC_OUT       (* (reg8 *) Quad1B__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Quad1B__SIO_CFG)
    #define Quad1B_SIO_HYST_EN        (* (reg8 *) Quad1B__SIO_HYST_EN)
    #define Quad1B_SIO_REG_HIFREQ     (* (reg8 *) Quad1B__SIO_REG_HIFREQ)
    #define Quad1B_SIO_CFG            (* (reg8 *) Quad1B__SIO_CFG)
    #define Quad1B_SIO_DIFF           (* (reg8 *) Quad1B__SIO_DIFF)
#endif /* (Quad1B__SIO_CFG) */

/* Interrupt Registers */
#if defined(Quad1B__INTSTAT)
    #define Quad1B_INTSTAT            (* (reg8 *) Quad1B__INTSTAT)
    #define Quad1B_SNAP               (* (reg8 *) Quad1B__SNAP)
    
	#define Quad1B_0_INTTYPE_REG 		(* (reg8 *) Quad1B__0__INTTYPE)
#endif /* (Quad1B__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Quad1B_H */


/* [] END OF FILE */
