/*******************************************************************************
* FILENAME: UART_1_INT.c
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
#include "UART_1.h"



#if(UART_1_RX_Enabled && (UART_1_RXBUFFERSIZE > 4))
extern uint8 UART_1_RXBUFFER[];
#if(UART_1_PSOC32bit)	
/*for 32-bit PSoC5*/
extern uint16 UART_1_RXBUFFERREAD;
extern uint16 UART_1_RXBUFFERWRITE;
#else
/*for 8-bit PSoC3*/
extern uint8 UART_1_RXBUFFERREAD;
extern uint8 UART_1_RXBUFFERWRITE;
#endif
extern uint8 UART_1_RXBUFFERLOOPDETECT;
extern uint8 UART_1_RXBUFFER_OVERFLOW;
/*******************************************************************************
* FUNCTION NAME: void UART_1_RXISR( void )
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
CY_ISR(UART_1_RXISR)
{
	uint8 readData;

   /* User code required at start of ISR */
   /* `#START UART_1_RXISR_START` */

   /* `#END` */

   /* 
    * User Module interrupt service code
    */

    readData = UART_1_RXSTATUS;

    if(readData & (UART_1_RX_STS_BREAK | UART_1_RX_STS_PAR_ERROR | UART_1_RX_STS_STOP_ERROR | UART_1_RX_STS_OVERRUN))
    {
        /* ERROR condition. */
    }


    while(readData & UART_1_RX_STS_FIFO_NOTEMPTY)
    {
		/* Check pointer. */
        if(UART_1_RXBUFFERWRITE >= UART_1_RXBUFFERSIZE)
        {
            UART_1_RXBUFFERWRITE = 0;
            if(UART_1_RXBUFFERWRITE == UART_1_RXBUFFERREAD)
            {/* Set Software Buffer status Overflow */
                UART_1_RXBUFFER_OVERFLOW = 1;
            }
        }

        UART_1_RXBUFFER[UART_1_RXBUFFERWRITE] = UART_1_RXDATA;

		if(UART_1_RXBUFFERLOOPDETECT)
        {/* Set Software Buffer status Overflow */
            UART_1_RXBUFFER_OVERFLOW = 1;
         }
        /* Set next pointer. */
        UART_1_RXBUFFERWRITE++;

		if(UART_1_RXBUFFERWRITE == UART_1_RXBUFFERREAD)
		{
		 UART_1_RXBUFFERLOOPDETECT = 1;
		}
		

        /* Check again if there is data. */        
        readData = UART_1_RXSTATUS;
    }

   /* User code required at end of ISR (Optional) */
   /* `#START UART_1_RXISR_END` */

   /* `#END` */

   /* PSoC3 ES1, ES2 RTC ISR PATCH  */ 
    #if(CYDEV_CHIP_DIE_EXPECT == CYDEV_CHIP_DIE_LEOPARD)
        #if((CYDEV_CHIP_REV_EXPECT <= CYDEV_CHIP_REV_LEOPARD_ES2) && (UART_1_RXInternalInterrupt__ES2_PATCH ))      
            UART_1_ISR_PATCH();
        #endif
    #endif

}

#endif


#if(UART_1_TX_Enabled && (UART_1_TXBUFFERSIZE > 4))
extern uint8 UART_1_TXBUFFER[];
#if(UART_1_PSOC32bit)	
/*for 32-bit PSoC5*/
extern uint16 UART_1_TXBUFFERREAD;
extern uint16 UART_1_TXBUFFERWRITE;
#else
/*for 8-bit PSoC3*/
extern uint8 UART_1_TXBUFFERREAD;
extern uint8 UART_1_TXBUFFERWRITE;
#endif

/*******************************************************************************
* FUNCTION NAME: void UART_1_TXISR( void )
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
CY_ISR(UART_1_TXISR)
{
 

   /* User code required at start of ISR */
   /* `#START UART_1_TXISR_START` */

   /* `#END` */

   /* 
    * User Module interrupt service code
    */

    while((UART_1_TXBUFFERREAD != UART_1_TXBUFFERWRITE) && !(UART_1_TXSTATUS & UART_1_TX_STS_FIFO_FULL))
    {
		/* Check pointer. */
        if(UART_1_TXBUFFERREAD >= UART_1_TXBUFFERSIZE)
        {
            UART_1_TXBUFFERREAD = 0;
        }

		UART_1_TXDATA = UART_1_TXBUFFER[UART_1_TXBUFFERREAD];

		/* Set next pointer. */
		UART_1_TXBUFFERREAD++;

    }

   /* User code required at end of ISR (Optional) */
   /* `#START UART_1_TXISR_END` */

   /* `#END` */
   /* PSoC3 ES1, ES2 RTC ISR PATCH  */ 
    #if(CYDEV_CHIP_DIE_EXPECT == CYDEV_CHIP_DIE_LEOPARD)
        #if((CYDEV_CHIP_REV_EXPECT <= CYDEV_CHIP_REV_LEOPARD_ES2) && (UART_1_TXInternalInterrupt__ES2_PATCH))      
            UART_1_ISR_PATCH();
        #endif
    #endif
   
}

#endif


