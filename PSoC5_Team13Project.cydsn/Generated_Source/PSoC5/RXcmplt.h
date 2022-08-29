/*******************************************************************************
* File Name: RXcmplt.h
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
#if !defined(CY_ISR_RXcmplt_H)
#define CY_ISR_RXcmplt_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void RXcmplt_Start(void);
void RXcmplt_StartEx(cyisraddress address);
void RXcmplt_Stop(void);

CY_ISR_PROTO(RXcmplt_Interrupt);

void RXcmplt_SetVector(cyisraddress address);
cyisraddress RXcmplt_GetVector(void);

void RXcmplt_SetPriority(uint8 priority);
uint8 RXcmplt_GetPriority(void);

void RXcmplt_Enable(void);
uint8 RXcmplt_GetState(void);
void RXcmplt_Disable(void);

void RXcmplt_SetPending(void);
void RXcmplt_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the RXcmplt ISR. */
#define RXcmplt_INTC_VECTOR            ((reg32 *) RXcmplt__INTC_VECT)

/* Address of the RXcmplt ISR priority. */
#define RXcmplt_INTC_PRIOR             ((reg8 *) RXcmplt__INTC_PRIOR_REG)

/* Priority of the RXcmplt interrupt. */
#define RXcmplt_INTC_PRIOR_NUMBER      RXcmplt__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable RXcmplt interrupt. */
#define RXcmplt_INTC_SET_EN            ((reg32 *) RXcmplt__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the RXcmplt interrupt. */
#define RXcmplt_INTC_CLR_EN            ((reg32 *) RXcmplt__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the RXcmplt interrupt state to pending. */
#define RXcmplt_INTC_SET_PD            ((reg32 *) RXcmplt__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the RXcmplt interrupt. */
#define RXcmplt_INTC_CLR_PD            ((reg32 *) RXcmplt__INTC_CLR_PD_REG)


#endif /* CY_ISR_RXcmplt_H */


/* [] END OF FILE */
