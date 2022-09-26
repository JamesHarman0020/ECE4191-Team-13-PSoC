/***************************************************************************
* File Name: rxDMA_Old_dma.c  
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
#include <rxDMA_Old_dma.H>



/****************************************************************************
* 
* The following defines are available in Cyfitter.h
* 
* 
* 
* rxDMA_Old__DRQ_CTL_REG
* 
* 
* rxDMA_Old__DRQ_NUMBER
* 
* Number of TD's used by this channel.
* rxDMA_Old__NUMBEROF_TDS
* 
* Priority of this channel.
* rxDMA_Old__PRIORITY
* 
* True if rxDMA_Old_TERMIN_SEL is used.
* rxDMA_Old__TERMIN_EN
* 
* TERMIN interrupt line to signal terminate.
* rxDMA_Old__TERMIN_SEL
* 
* 
* True if rxDMA_Old_TERMOUT0_SEL is used.
* rxDMA_Old__TERMOUT0_EN
* 
* 
* TERMOUT0 interrupt line to signal completion.
* rxDMA_Old__TERMOUT0_SEL
* 
* 
* True if rxDMA_Old_TERMOUT1_SEL is used.
* rxDMA_Old__TERMOUT1_EN
* 
* 
* TERMOUT1 interrupt line to signal completion.
* rxDMA_Old__TERMOUT1_SEL
* 
****************************************************************************/


/* Zero based index of rxDMA_Old dma channel */
uint8 rxDMA_Old_DmaHandle = DMA_INVALID_CHANNEL;

/*********************************************************************
* Function Name: uint8 rxDMA_Old_DmaInitalize
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
uint8 rxDMA_Old_DmaInitialize(uint8 BurstCount, uint8 ReqestPerBurst, uint16 UpperSrcAddress, uint16 UpperDestAddress) 
{

    /* Allocate a DMA channel. */
    rxDMA_Old_DmaHandle = (uint8)rxDMA_Old__DRQ_NUMBER;

    /* Configure the channel. */
    (void)CyDmaChSetConfiguration(rxDMA_Old_DmaHandle,
                                  BurstCount,
                                  ReqestPerBurst,
                                  (uint8)rxDMA_Old__TERMOUT0_SEL,
                                  (uint8)rxDMA_Old__TERMOUT1_SEL,
                                  (uint8)rxDMA_Old__TERMIN_SEL);

    /* Set the extended address for the transfers */
    (void)CyDmaChSetExtendedAddress(rxDMA_Old_DmaHandle, UpperSrcAddress, UpperDestAddress);

    /* Set the priority for this channel */
    (void)CyDmaChPriority(rxDMA_Old_DmaHandle, (uint8)rxDMA_Old__PRIORITY);
    
    return rxDMA_Old_DmaHandle;
}

/*********************************************************************
* Function Name: void rxDMA_Old_DmaRelease
**********************************************************************
* Summary:
*   Frees the channel associated with rxDMA_Old.
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
void rxDMA_Old_DmaRelease(void) 
{
    /* Disable the channel */
    (void)CyDmaChDisable(rxDMA_Old_DmaHandle);
}

