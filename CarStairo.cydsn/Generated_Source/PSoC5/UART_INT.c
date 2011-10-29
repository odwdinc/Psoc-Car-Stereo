/*******************************************************************************
* FILENAME: UART_INT.c
* Version 1.20
* 
*
* DESCRIPTION:
* This file provides all Interrupt Service functionality of the UART component
*
* NOTE:
* Any unusual or non-standard behavior should be noted here. Other-
* wise, this section should remain blank.
*
*******************************************************************************
* Copyright 2008-2009, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


#include "cytypes.h"
#include "UART.h"



#if(UART_RX_Enabled && (UART_RXBUFFERSIZE > 4))
extern uint8 UART_RXBUFFER[];
#if(UART_PSOC32bit)	
/*for 32-bit PSoC5*/
extern uint16 UART_RXBUFFERREAD;
extern uint16 UART_RXBUFFERWRITE;
#else
/*for 8-bit PSoC3*/
extern uint8 UART_RXBUFFERREAD;
extern uint8 UART_RXBUFFERWRITE;
#endif
extern uint8 UART_RXBUFFERLOOPDETECT;
extern uint8 UART_RXBUFFER_OVERFLOW;
/*******************************************************************************
* FUNCTION NAME: void UART_RXISR( void )
*
* Summary:
* Interrupt Service Routine for RX portion of the UART
*
* Parameters:
* -None-
*
* Return:
* -None-
*
* Theory:
*
* Side Effects:
* -None-
*******************************************************************************/
CY_ISR(UART_RXISR)
{
	uint8 readData;

   /* User code required at start of ISR */
   /* `#START UART_RXISR_START` */

   /* `#END` */

   /* 
    * User Module interrupt service code
    */

    readData = UART_RXSTATUS;

    if(readData & (UART_RX_STS_BREAK | UART_RX_STS_PAR_ERROR | UART_RX_STS_STOP_ERROR | UART_RX_STS_OVERRUN))
    {
        /* ERROR condition. */
    }


    while(readData & UART_RX_STS_FIFO_NOTEMPTY)
    {
		/* Check pointer. */
        if(UART_RXBUFFERWRITE >= UART_RXBUFFERSIZE)
        {
            UART_RXBUFFERWRITE = 0;
            if(UART_RXBUFFERWRITE == UART_RXBUFFERREAD)
            {/* Set Software Buffer status Overflow */
                UART_RXBUFFER_OVERFLOW = 1;
            }
        }

        UART_RXBUFFER[UART_RXBUFFERWRITE] = UART_RXDATA;

		if(UART_RXBUFFERLOOPDETECT)
        {/* Set Software Buffer status Overflow */
            UART_RXBUFFER_OVERFLOW = 1;
         }
        /* Set next pointer. */
        UART_RXBUFFERWRITE++;

		if(UART_RXBUFFERWRITE == UART_RXBUFFERREAD)
		{
		 UART_RXBUFFERLOOPDETECT = 1;
		}
		

        /* Check again if there is data. */        
        readData = UART_RXSTATUS;
    }

   /* User code required at end of ISR (Optional) */
   /* `#START UART_RXISR_END` */

   /* `#END` */

   /* PSoC3 ES1, ES2 RTC ISR PATCH  */ 
    #if(CYDEV_CHIP_DIE_EXPECT == CYDEV_CHIP_DIE_LEOPARD)
        #if((CYDEV_CHIP_REV_EXPECT <= CYDEV_CHIP_REV_LEOPARD_ES2) && (UART_RXInternalInterrupt__ES2_PATCH ))      
            UART_ISR_PATCH();
        #endif
    #endif

}

#endif


#if(UART_TX_Enabled && (UART_TXBUFFERSIZE > 4))
extern uint8 UART_TXBUFFER[];
#if(UART_PSOC32bit)	
/*for 32-bit PSoC5*/
extern uint16 UART_TXBUFFERREAD;
extern uint16 UART_TXBUFFERWRITE;
#else
/*for 8-bit PSoC3*/
extern uint8 UART_TXBUFFERREAD;
extern uint8 UART_TXBUFFERWRITE;
#endif

/*******************************************************************************
* FUNCTION NAME: void UART_TXISR( void )
*
* Summary:
* Interrupt Service Routine for the TX portion of the UART
*
* Parameters:
* -None-
*
* Return:
* -None-
*
* Theory:
*
* Side Effects:
* -None-
*******************************************************************************/
CY_ISR(UART_TXISR)
{
 

   /* User code required at start of ISR */
   /* `#START UART_TXISR_START` */

   /* `#END` */

   /* 
    * User Module interrupt service code
    */

    while((UART_TXBUFFERREAD != UART_TXBUFFERWRITE) && !(UART_TXSTATUS & UART_TX_STS_FIFO_FULL))
    {
		/* Check pointer. */
        if(UART_TXBUFFERREAD >= UART_TXBUFFERSIZE)
        {
            UART_TXBUFFERREAD = 0;
        }

		UART_TXDATA = UART_TXBUFFER[UART_TXBUFFERREAD];

		/* Set next pointer. */
		UART_TXBUFFERREAD++;

    }

   /* User code required at end of ISR (Optional) */
   /* `#START UART_TXISR_END` */

   /* `#END` */
   /* PSoC3 ES1, ES2 RTC ISR PATCH  */ 
    #if(CYDEV_CHIP_DIE_EXPECT == CYDEV_CHIP_DIE_LEOPARD)
        #if((CYDEV_CHIP_REV_EXPECT <= CYDEV_CHIP_REV_LEOPARD_ES2) && (UART_TXInternalInterrupt__ES2_PATCH))      
            UART_ISR_PATCH();
        #endif
    #endif
   
}

#endif


