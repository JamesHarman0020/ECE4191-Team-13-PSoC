/*******************************************************************************
* File Name: US_Trig.h
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
#if !defined(CY_ISR_US_Trig_H)
#define CY_ISR_US_Trig_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void US_Trig_Start(void);
void US_Trig_StartEx(cyisraddress address);
void US_Trig_Stop(void);

CY_ISR_PROTO(US_Trig_Interrupt);

void US_Trig_SetVector(cyisraddress address);
cyisraddress US_Trig_GetVector(void);

void US_Trig_SetPriority(uint8 priority);
uint8 US_Trig_GetPriority(void);

void US_Trig_Enable(void);
uint8 US_Trig_GetState(void);
void US_Trig_Disable(void);

void US_Trig_SetPending(void);
void US_Trig_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the US_Trig ISR. */
#define US_Trig_INTC_VECTOR            ((reg32 *) US_Trig__INTC_VECT)

/* Address of the US_Trig ISR priority. */
#define US_Trig_INTC_PRIOR             ((reg8 *) US_Trig__INTC_PRIOR_REG)

/* Priority of the US_Trig interrupt. */
#define US_Trig_INTC_PRIOR_NUMBER      US_Trig__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable US_Trig interrupt. */
#define US_Trig_INTC_SET_EN            ((reg32 *) US_Trig__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the US_Trig interrupt. */
#define US_Trig_INTC_CLR_EN            ((reg32 *) US_Trig__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the US_Trig interrupt state to pending. */
#define US_Trig_INTC_SET_PD            ((reg32 *) US_Trig__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the US_Trig interrupt. */
#define US_Trig_INTC_CLR_PD            ((reg32 *) US_Trig__INTC_CLR_PD_REG)


#endif /* CY_ISR_US_Trig_H */


/* [] END OF FILE */
