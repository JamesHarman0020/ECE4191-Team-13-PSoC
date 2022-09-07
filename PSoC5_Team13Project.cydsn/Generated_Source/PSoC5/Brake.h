/*******************************************************************************
* File Name: Brake.h
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
#if !defined(CY_ISR_Brake_H)
#define CY_ISR_Brake_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Brake_Start(void);
void Brake_StartEx(cyisraddress address);
void Brake_Stop(void);

CY_ISR_PROTO(Brake_Interrupt);

void Brake_SetVector(cyisraddress address);
cyisraddress Brake_GetVector(void);

void Brake_SetPriority(uint8 priority);
uint8 Brake_GetPriority(void);

void Brake_Enable(void);
uint8 Brake_GetState(void);
void Brake_Disable(void);

void Brake_SetPending(void);
void Brake_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Brake ISR. */
#define Brake_INTC_VECTOR            ((reg32 *) Brake__INTC_VECT)

/* Address of the Brake ISR priority. */
#define Brake_INTC_PRIOR             ((reg8 *) Brake__INTC_PRIOR_REG)

/* Priority of the Brake interrupt. */
#define Brake_INTC_PRIOR_NUMBER      Brake__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Brake interrupt. */
#define Brake_INTC_SET_EN            ((reg32 *) Brake__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Brake interrupt. */
#define Brake_INTC_CLR_EN            ((reg32 *) Brake__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Brake interrupt state to pending. */
#define Brake_INTC_SET_PD            ((reg32 *) Brake__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Brake interrupt. */
#define Brake_INTC_CLR_PD            ((reg32 *) Brake__INTC_CLR_PD_REG)


#endif /* CY_ISR_Brake_H */


/* [] END OF FILE */
