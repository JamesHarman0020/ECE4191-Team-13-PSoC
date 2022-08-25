/*******************************************************************************
* File Name: E_L.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_E_L_H)
#define CY_ISR_E_L_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void E_L_Start(void);
void E_L_StartEx(cyisraddress address);
void E_L_Stop(void);

CY_ISR_PROTO(E_L_Interrupt);

void E_L_SetVector(cyisraddress address);
cyisraddress E_L_GetVector(void);

void E_L_SetPriority(uint8 priority);
uint8 E_L_GetPriority(void);

void E_L_Enable(void);
uint8 E_L_GetState(void);
void E_L_Disable(void);

void E_L_SetPending(void);
void E_L_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the E_L ISR. */
#define E_L_INTC_VECTOR            ((reg32 *) E_L__INTC_VECT)

/* Address of the E_L ISR priority. */
#define E_L_INTC_PRIOR             ((reg8 *) E_L__INTC_PRIOR_REG)

/* Priority of the E_L interrupt. */
#define E_L_INTC_PRIOR_NUMBER      E_L__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable E_L interrupt. */
#define E_L_INTC_SET_EN            ((reg32 *) E_L__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the E_L interrupt. */
#define E_L_INTC_CLR_EN            ((reg32 *) E_L__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the E_L interrupt state to pending. */
#define E_L_INTC_SET_PD            ((reg32 *) E_L__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the E_L interrupt. */
#define E_L_INTC_CLR_PD            ((reg32 *) E_L__INTC_CLR_PD_REG)


#endif /* CY_ISR_E_L_H */


/* [] END OF FILE */
