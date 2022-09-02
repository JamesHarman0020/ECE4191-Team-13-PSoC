/*******************************************************************************
* File Name: QuadA.h  
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

#if !defined(CY_PINS_QuadA_H) /* Pins QuadA_H */
#define CY_PINS_QuadA_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "QuadA_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 QuadA__PORT == 15 && ((QuadA__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    QuadA_Write(uint8 value);
void    QuadA_SetDriveMode(uint8 mode);
uint8   QuadA_ReadDataReg(void);
uint8   QuadA_Read(void);
void    QuadA_SetInterruptMode(uint16 position, uint16 mode);
uint8   QuadA_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the QuadA_SetDriveMode() function.
     *  @{
     */
        #define QuadA_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define QuadA_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define QuadA_DM_RES_UP          PIN_DM_RES_UP
        #define QuadA_DM_RES_DWN         PIN_DM_RES_DWN
        #define QuadA_DM_OD_LO           PIN_DM_OD_LO
        #define QuadA_DM_OD_HI           PIN_DM_OD_HI
        #define QuadA_DM_STRONG          PIN_DM_STRONG
        #define QuadA_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define QuadA_MASK               QuadA__MASK
#define QuadA_SHIFT              QuadA__SHIFT
#define QuadA_WIDTH              1u

/* Interrupt constants */
#if defined(QuadA__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in QuadA_SetInterruptMode() function.
     *  @{
     */
        #define QuadA_INTR_NONE      (uint16)(0x0000u)
        #define QuadA_INTR_RISING    (uint16)(0x0001u)
        #define QuadA_INTR_FALLING   (uint16)(0x0002u)
        #define QuadA_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define QuadA_INTR_MASK      (0x01u) 
#endif /* (QuadA__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define QuadA_PS                     (* (reg8 *) QuadA__PS)
/* Data Register */
#define QuadA_DR                     (* (reg8 *) QuadA__DR)
/* Port Number */
#define QuadA_PRT_NUM                (* (reg8 *) QuadA__PRT) 
/* Connect to Analog Globals */                                                  
#define QuadA_AG                     (* (reg8 *) QuadA__AG)                       
/* Analog MUX bux enable */
#define QuadA_AMUX                   (* (reg8 *) QuadA__AMUX) 
/* Bidirectional Enable */                                                        
#define QuadA_BIE                    (* (reg8 *) QuadA__BIE)
/* Bit-mask for Aliased Register Access */
#define QuadA_BIT_MASK               (* (reg8 *) QuadA__BIT_MASK)
/* Bypass Enable */
#define QuadA_BYP                    (* (reg8 *) QuadA__BYP)
/* Port wide control signals */                                                   
#define QuadA_CTL                    (* (reg8 *) QuadA__CTL)
/* Drive Modes */
#define QuadA_DM0                    (* (reg8 *) QuadA__DM0) 
#define QuadA_DM1                    (* (reg8 *) QuadA__DM1)
#define QuadA_DM2                    (* (reg8 *) QuadA__DM2) 
/* Input Buffer Disable Override */
#define QuadA_INP_DIS                (* (reg8 *) QuadA__INP_DIS)
/* LCD Common or Segment Drive */
#define QuadA_LCD_COM_SEG            (* (reg8 *) QuadA__LCD_COM_SEG)
/* Enable Segment LCD */
#define QuadA_LCD_EN                 (* (reg8 *) QuadA__LCD_EN)
/* Slew Rate Control */
#define QuadA_SLW                    (* (reg8 *) QuadA__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define QuadA_PRTDSI__CAPS_SEL       (* (reg8 *) QuadA__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define QuadA_PRTDSI__DBL_SYNC_IN    (* (reg8 *) QuadA__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define QuadA_PRTDSI__OE_SEL0        (* (reg8 *) QuadA__PRTDSI__OE_SEL0) 
#define QuadA_PRTDSI__OE_SEL1        (* (reg8 *) QuadA__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define QuadA_PRTDSI__OUT_SEL0       (* (reg8 *) QuadA__PRTDSI__OUT_SEL0) 
#define QuadA_PRTDSI__OUT_SEL1       (* (reg8 *) QuadA__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define QuadA_PRTDSI__SYNC_OUT       (* (reg8 *) QuadA__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(QuadA__SIO_CFG)
    #define QuadA_SIO_HYST_EN        (* (reg8 *) QuadA__SIO_HYST_EN)
    #define QuadA_SIO_REG_HIFREQ     (* (reg8 *) QuadA__SIO_REG_HIFREQ)
    #define QuadA_SIO_CFG            (* (reg8 *) QuadA__SIO_CFG)
    #define QuadA_SIO_DIFF           (* (reg8 *) QuadA__SIO_DIFF)
#endif /* (QuadA__SIO_CFG) */

/* Interrupt Registers */
#if defined(QuadA__INTSTAT)
    #define QuadA_INTSTAT            (* (reg8 *) QuadA__INTSTAT)
    #define QuadA_SNAP               (* (reg8 *) QuadA__SNAP)
    
	#define QuadA_0_INTTYPE_REG 		(* (reg8 *) QuadA__0__INTTYPE)
#endif /* (QuadA__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_QuadA_H */


/* [] END OF FILE */
