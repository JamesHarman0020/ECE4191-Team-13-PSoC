/***************************************************************************
* File Name: rxDMA_dma.c  
* Version 1.70
*
*  Description:
*   Provides an API for the DMAC component. The API includes functions
*   for the DMA controller, DMA channels and Transfer Descriptors.
*
*
*   Note:
*     This module requires the developer to finish or fill in the auto
*     generated funcions and setup the dma channel and TD's.
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/
#include <CYLIB.H>
#include <CYDMAC.H>
#include <rxDMA_dma.H>



/****************************************************************************
* 
* The following defines are available in Cyfitter.h
* 
* 
* 
* rxDMA__DRQ_CTL_REG
* 
* 
* rxDMA__DRQ_NUMBER
* 
* Number of TD's used by this channel.
* rxDMA__NUMBEROF_TDS
* 
* Priority of this channel.
* rxDMA__PRIORITY
* 
* True if rxDMA_TERMIN_SEL is used.
* rxDMA__TERMIN_EN
* 
* TERMIN interrupt line to signal terminate.
* rxDMA__TERMIN_SEL
* 
* 
* True if rxDMA_TERMOUT0_SEL is used.
* rxDMA__TERMOUT0_EN
* 
* 
* TERMOUT0 interrupt line to signal completion.
* rxDMA__TERMOUT0_SEL
* 
* 
* True if rxDMA_TERMOUT1_SEL is used.
* rxDMA__TERMOUT1_EN
* 
* 
* TERMOUT1 interrupt line to signal completion.
* rxDMA__TERMOUT1_SEL
* 
****************************************************************************/


/* Zero based index of rxDMA dma channel */
uint8 rxDMA_DmaHandle = DMA_INVALID_CHANNEL;

/*********************************************************************
* Function Name: uint8 rxDMA_DmaInitalize
**********************************************************************
* Summary:
*   Allocates and initialises a channel of the DMAC to be used by the
*   caller.
*
* Parameters:
*   BurstCount.
*       
*       
*   ReqestPerBurst.
*       
*       
*   UpperSrcAddress.
*       
*       
*   UpperDestAddress.
*       
*
* Return:
*   The channel that can be used by the caller for DMA activity.
*   DMA_INVALID_CHANNEL (0xFF) if there are no channels left. 
*
*
*******************************************************************/
uint8 rxDMA_DmaInitialize(uint8 BurstCount, uint8 ReqestPerBurst, uint16 UpperSrcAddress, uint16 UpperDestAddress) 
{

    /* Allocate a DMA channel. */
    rxDMA_DmaHandle = (uint8)rxDMA__DRQ_NUMBER;

    /* Configure the channel. */
    (void)CyDmaChSetConfiguration(rxDMA_DmaHandle,
                                  BurstCount,
                                  ReqestPerBurst,
                                  (uint8)rxDMA__TERMOUT0_SEL,
                                  (uint8)rxDMA__TERMOUT1_SEL,
                                  (uint8)rxDMA__TERMIN_SEL);

    /* Set the extended address for the transfers */
    (void)CyDmaChSetExtendedAddress(rxDMA_DmaHandle, UpperSrcAddress, UpperDestAddress);

    /* Set the priority for this channel */
    (void)CyDmaChPriority(rxDMA_DmaHandle, (uint8)rxDMA__PRIORITY);
    
    return rxDMA_DmaHandle;
}

/*********************************************************************
* Function Name: void rxDMA_DmaRelease
**********************************************************************
* Summary:
*   Frees the channel associated with rxDMA.
*
*
* Parameters:
*   void.
*
*
*
* Return:
*   void.
*
*******************************************************************/
void rxDMA_DmaRelease(void) 
{
    /* Disable the channel */
    (void)CyDmaChDisable(rxDMA_DmaHandle);
}

