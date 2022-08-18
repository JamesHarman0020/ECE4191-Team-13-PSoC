/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "stdio.h"
#include "unistd.h"
#include "math.h"
#include "string.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    UART_Start();

    for(;;)
    {
        while(1) // infinite loop which keep receiving data and convert str type to float type data
        {
            UART_ReadRxStatus();           //read rx state, this will return variables listed below
            /*
            UART_RX_STS_FIFO_NOTEMPTY 
            If set, indicates the FIFO has data available.
            
            
            UART_RX_STS_PAR_ERROR 
            If set, indicates a parity error was detected.
            
            
            UART_RX_STS_STOP_ERROR 
            If set, indicates a framing error was detected. The 
            framing error is caused when the UART hardware 
            sees the logic 0 where the stop bit should be (logic 1).
            
            
            UART_RX_STS_BREAK 
            If set, indicates a break was detected.
            
            
            UART_RX_STS_OVERRUN 
            If set, indicates the FIFO buffer was overrun.
            
            
            UART_RX_STS_ADDR_MATCH 
            Indicates that the received byte matches one of the 
            two addresses available for hardware address 
            detection. It is not implemented if Address Mode is 
            set to None. In Half Duplex mode, only Address #1
            is implemented for this detection.
            
            UART_RX_STS_MRKSPC 
            Status of the mark/space parity bit. This bit indicates 
            whether a mark or space was seen in the parity bit 
            location of the transfer. It is not implemented if 
            Address Mode is set to None. 
            
            UART_RX_STS_SOFT_BUFF_OVER
            If set, indicates the RX buffer was overrun.
            */
            
            if(ART_RX_STS_FIFO_NOTEMPTY == 1) // if ART_RX_STS_FIFO_NOTEMPTY == 1, means there is data in the rx buffer to be collected.
            { 
                
                char read_data[] = UART_ReadRxData(); // read and crearte char list which contain the data
                UART_ClearRxBuffer(); // clear the buffer when read process finished
                
                char *pEnd;
                int len = sizeof(read_data); 
                for (int i = 0 ; i<len-1; i++)  // find out the simbol "," and replace by "space"
                {
                    if (read_data[i] == 44) // change "," to "<space>" inside the data recieved base on ascii code "," = 44, "space" = 32
                    {
                        read_data[i] = 32;
                    }
                    
                    float para1 = strtof(a, &pEnd);     // save the 1st data as float type named para1
                    float para2 = strtof(pEnd, &pEnd);  // save the 2nd data as float type named para2
                    float para3 = strtof(pEnd, &pEnd);  // save the 3rd data as float type named para3
                }
            }
        }
    }
}

/* [] END OF FILE */
