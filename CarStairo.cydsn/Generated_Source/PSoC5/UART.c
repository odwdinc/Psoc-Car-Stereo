/*******************************************************************************
* FILENAME: UART.c
* Version 1.20
* 
*
* DESCRIPTION:
* This file provides all API functionality of the UART component
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


#include "UART.h"

#if(UART_PSOC32bit)	
/*for 32-bit PSoC5*/
	#if(UART_TX_Enabled && (UART_TXBUFFERSIZE > 4))
	uint8 UART_TXBUFFER[UART_TXBUFFERSIZE];
	uint16 UART_TXBUFFERREAD = 0;
	uint16 UART_TXBUFFERWRITE = 0;
	#endif
	#if(UART_RX_Enabled && (UART_RXBUFFERSIZE > 4))
	uint8 UART_RXBUFFER[UART_RXBUFFERSIZE];
	uint16 UART_RXBUFFERREAD = 0;
	uint16 UART_RXBUFFERWRITE = 0;
	uint8 UART_RXBUFFERLOOPDETECT = 0;
    uint8  UART_RXBUFFER_OVERFLOW = 0;
	#endif
#else
/*for 8 bit PSoc3*/	
	#if(UART_TX_Enabled && (UART_TXBUFFERSIZE > 4))
	uint8 UART_TXBUFFER[UART_TXBUFFERSIZE];
	uint8 UART_TXBUFFERREAD = 0;
	uint8 UART_TXBUFFERWRITE = 0;
	#endif
	#if(UART_RX_Enabled && (UART_RXBUFFERSIZE > 4))
	uint8 UART_RXBUFFER[UART_RXBUFFERSIZE];
	uint8 UART_RXBUFFERREAD = 0;
	uint8 UART_RXBUFFERWRITE = 0;
	uint8 UART_RXBUFFERLOOPDETECT = 0;
    uint8  UART_RXBUFFER_OVERFLOW = 0;
	#endif
#endif


uint8 UART_initvar = 0;
/*******************************************************************************
* FUNCTION NAME: void UART_Start(void)
*
* Summary:
* Initialize and Enable the UART component
*
* Parameters:
* -None-
*
* Return:
* -None-
*
* Theory:
* Enable the clock input to enable operation
*
* Side Effects:
* -None-
*******************************************************************************/
void UART_Start(void)
{
    if(UART_initvar == 0)
	{
		UART_initvar = 1;
        
        #if(UART_RX_Enabled)
        
            #if(UART_RX_IntInterruptEnabled && (UART_RXBUFFERSIZE > 4))
                /* Set the RX Interrupt. */
                CyIntSetVector(UART_RX_VECT_NUM,   UART_RXISR);
                CyIntSetPriority(UART_RX_VECT_NUM, UART_RX_PRIOR_NUM);
                CyIntEnable(UART_RX_VECT_NUM);
            #endif
           
            #if (UART_RXHW_Address_Enabled)
                UART_SetRxAddressMode(UART_RXAddressMode); 
                UART_SetRxAddress1(UART_RXHWADDRESS1);
                UART_SetRxAddress2(UART_RXHWADDRESS2);
            #endif 
            
            /* Configure the Initial RX interrupt mask */
            UART_RXSTATUS_MASK  = UART_INIT_RX_INTERRUPTS_MASK;
            UART_RXSTATUS_ACTL  |= UART_INT_ENABLE;
        #endif
        #if(UART_TX_Enabled)
            #if(UART_TX_IntInterruptEnabled && (UART_TXBUFFERSIZE > 4))
                /* Set the TX Interrupt. */
                CyIntSetVector(UART_TX_VECT_NUM,   UART_TXISR);
                CyIntSetPriority(UART_TX_VECT_NUM, UART_TX_PRIOR_NUM);
                CyIntEnable(UART_TX_VECT_NUM);
            #endif
            
			  //Write Counter Value for TX Bit Clk Generator 
			 #if(UART_TXCLKGEN_DP)
				UART_TXBITCLKGEN_CTR = UART_BIT_CENTER;
				UART_TXBITCLKTX_COMPLETE = (UART_NUMBER_OF_DATA_BITS +
														UART_NUMBER_OF_START_BIT) *
														UART_OverSampleCount;
			#endif	
            
            /* Configure the Initial TX interrupt mask */
            #if(UART_TX_IntInterruptEnabled && (UART_TXBUFFERSIZE > 4))
                UART_TXSTATUS_MASK = UART_TX_STS_FIFO_EMPTY;
            #else
                UART_TXSTATUS_MASK = UART_INIT_TX_INTERRUPTS_MASK;
            #endif
            UART_TXSTATUS_ACTL  |= UART_INT_ENABLE;

        #endif
    }

    /*Write Bit Counter Enable */
     #if(UART_RX_Enabled)
	    UART_RXBITCTR_CONTROL |= UART_CNTR_ENABLE;
	 #endif	
	 
     #if(UART_TX_Enabled)
		 #if(UART_TXCLKGEN_DP)
		 	/* TODO: Start DP*/
		#else
			UART_TXBITCTR_CONTROL |= UART_CNTR_ENABLE;
		#endif	
	 #endif	
	
    #if(UART_InternalClockUsed)
        /* Set the bit to enable the clock. */
        *UART_IntClock_CLKEN |= UART_IntClock_CLKEN_MASK;
    #else
       
    #endif
}

/*******************************************************************************
* FUNCTION NAME: void UART_Stop(void)
*
* Summary:
* Disable the UART component
*
* Parameters:
* -None-
*
* Return:
* -None-
*
* Theory:
* Disable the clock input to enable operation
*
* Side Effects:
* -None-
*******************************************************************************/
void UART_Stop(void)
{
    /*Write Bit Counter Disable */
   #if(UART_RX_Enabled)
	    UART_RXBITCTR_CONTROL &= ~UART_CNTR_ENABLE;
   #endif	
	 
   #if(UART_TX_Enabled)
     #if(UART_TX_Enabled)
		#if(UART_TXCLKGEN_DP)
		 	// stop DP 
		#else
			UART_TXBITCTR_CONTROL &= ~UART_CNTR_ENABLE;
		#endif	
	 #endif	
   #endif	
	

   #if(UART_InternalClockUsed)
        /* Clear the bit to enable the clock. */
        *UART_IntClock_CLKEN &= ~UART_IntClock_CLKEN_MASK;
   #else
       
   #endif
   
   
   /*Disable internal interrupt component*/
   #if(UART_RX_Enabled)
       #if(UART_RX_IntInterruptEnabled && (UART_RXBUFFERSIZE > 4))
            UART_DisableRxInt();
       #endif
   #endif
   #if(UART_TX_Enabled)
       #if(UART_TX_IntInterruptEnabled && (UART_TXBUFFERSIZE > 4))
            UART_DisableTxInt();
       #endif
   #endif
	
}

/*******************************************************************************
* FUNCTION NAME: uint8 UART_ReadControlRegister(void)
*
* Summary:
* Read the current state of the control register
*
* Parameters:
* -None-
*
* Return:
* uint8: Current state of the control register.
*
* Theory:
*
* Side Effects:
*  -None-
*******************************************************************************/
uint8 UART_ReadControlRegister(void)
{
  #if( UART_CONTROL_REMOVED )
    return 0;	
  #else 
    return UART_CONTROL;
  #endif
}

/*******************************************************************************
* FUNCTION NAME: uint8 UART_WriteControlRegister(void)
*
* Summary:
* Read the current state of the control register
*
* Parameters:
* -None-
*
* Return:
* uint8: Current state of the control register.
*
* Theory:
*
* Side Effects:
*  -None-
*******************************************************************************/
void  UART_WriteControlRegister(uint8 control)
{
  #if( UART_CONTROL_REMOVED )
  	   control = control;
  #else
       UART_CONTROL = control;
  #endif
}


#if(UART_RX_Enabled)
#if(UART_RX_IntInterruptEnabled)
/*******************************************************************************
* FUNCTION NAME: void UART_EnableRxInt(void)
*
* Summary:
* Enable RX interrupt generation
*
* Parameters:
* -None-
*
* Return:
* -None-
*
* Theory:
* Enable the interrupt output -or- the interrupt component itself
*
* Side Effects:
* -None-
*******************************************************************************/
void UART_EnableRxInt(void)
{
    CyIntEnable(UART_RX_VECT_NUM);
}

/*******************************************************************************
* FUNCTION NAME: void UART_DisableRxInt(void)
*
* Summary:
* Disable RX interrupt generation
*
* Parameters:
* -None-
*
* Return:
* -None-
*
* Theory:
* Disable the interrupt output -or- the interrupt component itself
*
* Side Effects:
* -None-
*******************************************************************************/
void UART_DisableRxInt(void)
{
	CyIntDisable(UART_RX_VECT_NUM);
}
#endif /* UART_RX_IntInterruptEnabled */

/*******************************************************************************
* FUNCTION NAME: void UART_SetRxInterruptMode(uint8 intSrc)
*
* Summary:
* Configure which status bits trigger an interrupt event
*
* Parameters:
* IntSource: An or'd combination of the desired status bit masks (defined in
*                the header file)
*
* Return:
* -None-
*
* Theory:
* Enables the output of specific status bits to the interrupt controller
*
* Side Effects:
* -None-
*******************************************************************************/
void UART_SetRxInterruptMode(uint8 intSrc)
{
    UART_RXSTATUS_MASK  = intSrc;
}

/*******************************************************************************
* FUNCTION NAME: uint8 UART_ReadRxData(void)
*
* Summary:
*  Returns data in RX Data register without checking status register to determine 
*  if data is valid
*
* Parameters:
*  void
*
* Return:
*  uint8: Received data from RX register
*
*******************************************************************************/
uint8 UART_ReadRxData(void)
{
    uint8 rxData;

#if(UART_RXBUFFERSIZE > 4)

    /* Disable Rx interrupt. */
    /* Protect variables that could change on interrupt. */
    #if(UART_RX_IntInterruptEnabled)
        UART_DisableRxInt();
    #endif

    if( (UART_RXBUFFERREAD != UART_RXBUFFERWRITE) ||
		(UART_RXBUFFERLOOPDETECT > 0) )
    {
        if(UART_RXBUFFERLOOPDETECT > 0 ) UART_RXBUFFERLOOPDETECT = 0;
		
        if(UART_RXBUFFERREAD >= UART_RXBUFFERSIZE)
        {
            UART_RXBUFFERREAD = 0;
        }

		rxData = UART_RXBUFFER[UART_RXBUFFERREAD];

		UART_RXBUFFERREAD++;
    
    }
    else
    {   /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit*/
        rxData = UART_RXDATA;
    }

    /* Enable Rx interrupt. */
    #if(UART_RX_IntInterruptEnabled)
        UART_EnableRxInt();
    #endif

#else /* UART_RXBUFFERSIZE > 4 */

    /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit*/
    rxData = UART_RXDATA;

#endif /* UART_RXBUFFERSIZE > 4 */

	return rxData;
}

/*******************************************************************************
* FUNCTION NAME: uint8 UART_ReadRxStatus(void)
*
* Summary:
*  Read the current state of the status register
*  And detect software buffer overflow.
*
* Parameters:
*  void
*
* Return:
* uint8: Current state of the status register.
*
*******************************************************************************/
uint8 UART_ReadRxStatus(void)
{
 uint8 status;
    
    status = UART_RXSTATUS;
    status &= UART_RX_HW_MASK;
    
	#if(UART_RXBUFFERSIZE > 4)
       if( UART_RXBUFFER_OVERFLOW )
       {
           status |= UART_RX_STS_SOFT_BUFF_OVER;
           UART_RXBUFFER_OVERFLOW = 0;
       }
	#endif
    
	return status;
}


/*******************************************************************************
* FUNCTION NAME: uint8 UART_GetRxInterruptSource(void)
*
* Summary:
* Read the current state of the status register for interrupt sources
*
* Parameters:
* -None-
*
* Return:
* uint8: Current state of the status register.
*
*******************************************************************************/
uint8 UART_GetRxInterruptSource()
{
    return UART_RXSTATUS;
}

/*******************************************************************************
* FUNCTION NAME: uint8 UART_GetChar(void)
*
* Summary:
*  Reads UART RX buffer immediately, if data is not available or an error condition 
*  exists, zero is returned; otherwise, character is read and returned.
*
* Parameters:
* -None-
*
* Return:
* uint8: Character read from UART RX buffer. ASCII characters from 1 to 255 are valid. 
* A returned zero signifies an error condition or no data available.
*
* Theory:
*
* Side Effects:
* -None-
*******************************************************************************/
uint8 UART_GetChar(void)
{
    uint8 rxData=0;
	uint8 rxStatus; 


#if(UART_RXBUFFERSIZE > 4)

    /* Disable Rx interrupt. */
    /* Protect variables that could change on interrupt. */
    #if(UART_RX_IntInterruptEnabled)
        UART_DisableRxInt();
    #endif

    if( (UART_RXBUFFERREAD != UART_RXBUFFERWRITE) ||
		(UART_RXBUFFERLOOPDETECT > 0) )
    {
        if(UART_RXBUFFERLOOPDETECT > 0 ) UART_RXBUFFERLOOPDETECT = 0;
       
        if(UART_RXBUFFERREAD >= UART_RXBUFFERSIZE)
        {
            UART_RXBUFFERREAD = 0;
        }

		rxData = UART_RXBUFFER[UART_RXBUFFERREAD];

		UART_RXBUFFERREAD++;
    
		
    }
    else
    {   rxStatus =UART_RXSTATUS;
		if(rxStatus & UART_RX_STS_FIFO_NOTEMPTY)
		{/* Read received data from FIFO*/
		 rxData = UART_RXDATA;
		 /*Check status on error*/
         if(rxStatus & (UART_RX_STS_BREAK | UART_RX_STS_PAR_ERROR | 
		 			    UART_RX_STS_STOP_ERROR | UART_RX_STS_OVERRUN))
		   rxData = 0;
		 }
    }

    /* Enable Rx interrupt. */
    #if(UART_RX_IntInterruptEnabled)
        UART_EnableRxInt();
    #endif

#else /* UART_RXBUFFERSIZE > 4 */

        rxStatus =UART_RXSTATUS;
		if(rxStatus & UART_RX_STS_FIFO_NOTEMPTY)
		{/* Read received data from FIFO*/
		 rxData = UART_RXDATA;
		 /*Check status on error*/
         if(rxStatus & (UART_RX_STS_BREAK | UART_RX_STS_PAR_ERROR | 
		 			    UART_RX_STS_STOP_ERROR | UART_RX_STS_OVERRUN))
		   rxData = 0;
		 }

#endif /* UART_RXBUFFERSIZE > 4 */

	return rxData;

}

/*******************************************************************************
* FUNCTION NAME: uint16 UART_GetByte(void)
*
* Summary:
* Grab the next available byte of data from the recieve FIFO
*
* Parameters:
* -None-
*
* Return:
* uint16: MSB contains Status Register and LSB contains UART RX data
*
* Theory:
*
* Side Effects:
* -None-
*******************************************************************************/

uint16 UART_GetByte(void)
{

#if(UART_RXBUFFERSIZE > 4)
    /* TODO: change status if local buffer used*/
	return ( (UART_RXSTATUS << 8) | UART_ReadRxData());
#else
	return ( (UART_RXSTATUS << 8) | UART_ReadRxData() );
#endif
}

/*for 32-bit PSoC5*/
#if(UART_PSOC32bit)	
/*******************************************************************************
* FUNCTION NAME: uint16 UART_GetRxBufferSize(void)
*
* Summary:
* Determine the amount of space left in the RX buffer and return the count in
*   bytes
*
* Parameters:
* -None-
*
* Return:
* uint16: Integer count of the number of bytes left in the RX buffer
*
* Theory:
* Allows the user to find out how full the RX Buffer is.
*
* Side Effects:
* -None-
*******************************************************************************/

uint16 UART_GetRxBufferSize(void)
{
    uint16 size;

  #if(UART_RXBUFFERSIZE > 4)

    /* Disable Rx interrupt. */
    /* Protect variables that could change on interrupt. */
    #if(UART_RX_IntInterruptEnabled)
        UART_DisableRxInt();
    #endif

    if(UART_RXBUFFERREAD == UART_RXBUFFERWRITE)
    {
        if(UART_RXBUFFERLOOPDETECT > 0 ) 
		{
		  size = UART_RXBUFFERSIZE;
		}
		else
		{
          size = 0;
		}
    }
    else if(UART_RXBUFFERREAD < UART_RXBUFFERWRITE)
    {
        size = (UART_RXBUFFERWRITE - UART_RXBUFFERREAD);
    }
    else
    {
        size = (UART_RXBUFFERSIZE - UART_RXBUFFERREAD) + UART_RXBUFFERWRITE;
    }

    /* Enable Rx interrupt. */
    #if(UART_RX_IntInterruptEnabled)
        UART_EnableRxInt();
    #endif

 #else /* UART_RXBUFFERSIZE > 4 */

    /* We can only know if there is data in the fifo. */
    size = (UART_RXSTATUS & UART_RX_STS_FIFO_NOTEMPTY) ? 1:0;

  #endif /* UART_RXBUFFERSIZE > 4 */

  return size;
}
#else 
/*******************************************************************************
* FUNCTION NAME: uint8 UART_GetRxBufferSize(void)
*
* Summary:
* Determine the amount of space left in the RX buffer and return the count in
*   bytes
*
* Parameters:
* -None-
*
* Return:
* uint8: Integer count of the number of bytes left in the RX buffer
*
* Theory:
* Allows the user to find out how full the RX Buffer is.
*
* Side Effects:
* -None-
*******************************************************************************/
uint8 UART_GetRxBufferSize(void)
{
    uint8 size;


  #if(UART_RXBUFFERSIZE > 4)

    /* Disable Rx interrupt. */
    /* Protect variables that could change on interrupt. */
    #if(UART_RX_IntInterruptEnabled)
        UART_DisableRxInt();
    #endif

    if(UART_RXBUFFERREAD == UART_RXBUFFERWRITE)
    {
        if(UART_RXBUFFERLOOPDETECT > 0 ) 
		{
		  size = UART_RXBUFFERSIZE;
		}
		else
		{
          size = 0;
		}
    }
    else if(UART_RXBUFFERREAD < UART_RXBUFFERWRITE)
    {
        size = (UART_RXBUFFERWRITE - UART_RXBUFFERREAD);
    }
    else
    {
        size = (UART_RXBUFFERSIZE - UART_RXBUFFERREAD) + UART_RXBUFFERWRITE;
    }

    /* Enable Rx interrupt. */
    #if(UART_RX_IntInterruptEnabled)
        UART_EnableRxInt();
    #endif

  #else /* UART_RXBUFFERSIZE > 4 */

    /* We can only know if there is data in the fifo. */
    size = (UART_RXSTATUS & UART_RX_STS_FIFO_NOTEMPTY) ? 1:0;

  #endif /* UART_RXBUFFERSIZE > 4 */


    return size;
}

#endif

/*******************************************************************************
* FUNCTION NAME: void UART_ClearRxBuffer(void)
*
* Summary:
* Clear the RX RAM buffer by setting the read and write pointers both to zero.
*
* Parameters:
* -None-
*
* Return:
* -None-
*
* Theory:
* Setting the pointers to zero makes the system believe there is no data to read
*        and writing will resume at address 0 overwriting any data that may have
*        remained in the RAM.
*
* Side Effects:
* Any received data not read from the RAM buffer will be lost when overwritten.
*******************************************************************************/
void UART_ClearRxBuffer(void)
{
#if(UART_RXBUFFERSIZE > 4)
    /* Disable Rx interrupt. */
    /* Protect variables that could change on interrupt. */
    #if(UART_RX_IntInterruptEnabled)
        UART_DisableRxInt();
    #endif

    UART_RXBUFFERREAD = 0;
    UART_RXBUFFERWRITE = 0;
    UART_RXBUFFERLOOPDETECT = 0; 
    UART_RXBUFFER_OVERFLOW = 0;


    /* Enable Rx interrupt. */
    #if(UART_RX_IntInterruptEnabled)
        UART_EnableRxInt();
    #endif
#endif /* UART_RXBUFFERSIZE > 4 */
}

/*******************************************************************************
* FUNCTION NAME: void UART_SetRxAddressMode( uint8 addressMode )
*
* Summary:
* Set the receive addressing mode
*
* Parameters:
* addressMode: Use one of the Enumerated Types listed below
        #define UART__B_UART__AM_SW_BYTE_BYTE 1
#define UART__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define UART__B_UART__AM_HW_BYTE_BY_BYTE 3
#define UART__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define UART__B_UART__AM_NONE 0

*
* Return:
* -None-
*
* Theory:
*
* Side Effects:
* -None-
*******************************************************************************/
void UART_SetRxAddressMode(uint8 addressMode)
{
  #if(UART_RXHW_Address_Enabled) 
	#if(UART_CONTROL_REMOVED)
		addressMode = addressMode;
	#else
		uint8 tmpCtrl = 0;
		tmpCtrl = UART_CONTROL & ~UART_CTRL_RXADDR_MODE_MASK;
		tmpCtrl |= ((addressMode << UART_CTRL_RXADDR_MODE0_SHIFT) & UART_CTRL_RXADDR_MODE_MASK);
		UART_CONTROL = tmpCtrl;
	#endif
  #else
    addressMode = addressMode;
  #endif	
	
}


/*******************************************************************************
* FUNCTION NAME: void UART_HardwareAddressEnable( uint8 addressEnable )
*
* Summary:
*  Selects the hardware address compares active 
*
* Parameters:
*  Address Compare Enable
*
* Return:
* -None-
*
*******************************************************************************/
void UART_HardwareAddressEnable(uint8 addressEnable)
{
    /* It is always enabled if SetRxAddressMode sets not None adress mode*/
    addressEnable = addressEnable;
}


/*******************************************************************************
* FUNCTION NAME: void UART_SetRxAddress1(uint8 address)
*
* Summary:
* Set the first hardware address compare value
*
* Parameters:
* address: 
*
* Return:
* -None-
*
* Theory:
*
* Side Effects:
* -None-
*******************************************************************************/
void UART_SetRxAddress1(uint8 address)
{
	UART_RXADDRESS1 = address;
}

/*******************************************************************************
* FUNCTION NAME: void UART_SetRxAddress2(uint8 address)
*
* Summary:
* Set the second hardware address compare value
*
* Parameters:
* address: 
*
* Return:
* -None-
*
* Theory:
*
* Side Effects:
* -None-
*******************************************************************************/
void UART_SetRxAddress2(uint8 address)
{
	UART_RXADDRESS2 = address;
}

#endif  /* UART_RX_Enabled */

#if( (UART_TX_Enabled) || (UART_HD_Enabled) )
#if(UART_TX_IntInterruptEnabled)
/*******************************************************************************
* FUNCTION NAME: void UART_EnableTxInt(void)
*
* Summary:
* Enable TX interrupt generation
*
* Parameters:
* -None-
*
* Return:
* -None-
*
* Theory:
* Enable the interrupt output -or- the interrupt component itself
*
* Side Effects:
* -None-
*******************************************************************************/
void UART_EnableTxInt(void)
{
	CyIntEnable(UART_TX_VECT_NUM);
}

/*******************************************************************************
* FUNCTION NAME: void UART_DisableTxInt(void)
*
* Summary:
* Disable TX interrupt generation
*
* Parameters:
* -None-
*
* Return:
* -None-
*
* Theory:
* Disable the interrupt output -or- the interrupt component itself
*
* Side Effects:
* -None-
*******************************************************************************/
void UART_DisableTxInt(void)
{
	CyIntDisable(UART_TX_VECT_NUM);
}
#endif /* UART_TX_IntInterruptEnabled */

/*******************************************************************************
* FUNCTION NAME: void UART_SetTxInterruptMode(uint8 intSrc)
*
* Summary:
* Configure which status bits trigger an interrupt event
*
* Parameters:
* intSrc: An or'd combination of the desired status bit masks (defined in
*                the header file)
*
* Return:
* -None-
*
* Theory:
* Enables the output of specific status bits to the interrupt controller
*
* Side Effects:
* -None-
*******************************************************************************/
void UART_SetTxInterruptMode(uint8 intSrc)
{
    UART_TXSTATUS_MASK = intSrc;
}

/*******************************************************************************
* FUNCTION NAME: void UART_WriteTxData(uint8 txDataByte)
*
* Summary:
* Write a byte of data to the Transmit FIFO
*
* Parameters:
* TXDataByte: byte of data to place in the transmit FIFO
*
* Return:
* -None-
*
* Theory:
* Allows the user and the API to read the status register for error detection
*         and flow control.
*
* Side Effects:
* How does this affect the interrupts if it has not been serviced yet?
*******************************************************************************/
void UART_WriteTxData(uint8 txDataByte)
{
#if(UART_TXBUFFERSIZE > 4)

    /* Block if buffer is full, so we dont overwrite. */
    while(UART_TXBUFFERWRITE == (UART_TXBUFFERREAD - 1) ||
          (uint8)(UART_TXBUFFERWRITE - UART_TXBUFFERREAD) == (uint8)(UART_TXBUFFERSIZE - 1))
    {
        /* Software buffer is full. */
    }

    /* Disable Tx interrupt. */
    /* Protect variables that could change on interrupt. */
    #if(UART_TX_IntInterruptEnabled)
        UART_DisableTxInt();
    #endif

	if((UART_TXBUFFERREAD == UART_TXBUFFERWRITE) && !(UART_TXSTATUS & UART_TX_STS_FIFO_FULL))
	{
        /* Add directly to the FIFO. */
		UART_TXDATA = txDataByte;
	}
    else
    {

        if(UART_TXBUFFERWRITE >= UART_TXBUFFERSIZE)
		{
            UART_TXBUFFERWRITE = 0;
		 }

        UART_TXBUFFER[UART_TXBUFFERWRITE] = txDataByte;

        /* Add to the software buffer. */
        UART_TXBUFFERWRITE++;

	}

    /* Enable Rx interrupt. */
    #if(UART_TX_IntInterruptEnabled)
        UART_EnableTxInt();
    #endif

#else /* UART_TXBUFFERSIZE > 4 */

    /* Block if there isnt room. */
	while(UART_TXSTATUS & UART_TX_STS_FIFO_FULL);

    /* Add directly to the FIFO. */
	UART_TXDATA = txDataByte;

#endif /* UART_TXBUFFERSIZE > 4 */

}

/*******************************************************************************
* FUNCTION NAME: uint8 UART_ReadTxStatus(void)
*
* Summary:
* Read the status register for the component
*
* Parameters:
* -None-
*
* Return:
* uint8: Contents of the status register
*
* Theory:
* Allows the user and the API to read the status register for error detection
*         and flow control.
*
* Side Effects:
* How does this affect the interrupts if it has not been serviced yet?
*******************************************************************************/
uint8 UART_ReadTxStatus(void)
{
	return (UART_TXSTATUS);
}

/*******************************************************************************
* FUNCTION NAME: uint8 UART_GetTxInterruptSource(void)
*
* Summary:
* Read the current state of the status register for interrupt sources
*
* Parameters:
* -None-
*
* Return:
* uint8: Current state of the status register.
*
* Theory:
*
* Side Effects:
* TODO: Should this AND off bits that are enabled as interrupt masks?
*******************************************************************************/
uint8 UART_GetTxInterruptSource()
{
    return UART_TXSTATUS;
}

/*******************************************************************************
* FUNCTION NAME: void UART_PutChar(uint8 txDataByte)
*
* Summary:
*  Wait to send byte until TX register or buffer has room
*
* Parameters:
*  TxDataByte: The 8-bit data value to send across the UART
*
* Return:
*  void
*
* Theory:
*  Allows the user to transmit any byte of data in a single transfer
*
*******************************************************************************/
void UART_PutChar(uint8 txDataByte)
{
#if(UART_TXBUFFERSIZE > 4)
		UART_WriteTxData(txDataByte);
#else /* UART_TXBUFFERSIZE > 4 */

    /* Block if there isnt room. */
	while(UART_TXSTATUS & UART_TX_STS_FIFO_FULL);

    /* Add directly to the FIFO. */
	UART_TXDATA = txDataByte;

#endif /* UART_TXBUFFERSIZE > 4 */

}

/*******************************************************************************
* FUNCTION NAME: void UART_PutString( uint8* string )
*
* Summary:
* Write a Sequence of bytes on the Transmit line. Data comes from RAM.
*
* Parameters:
* string: uint8 pointer to character string of Data to Send
*
* Return:
* -None-
*
* Theory:
*
* Side Effects:
* -None-
*******************************************************************************/
void UART_PutString(uint8* string)
{
	//This is a blocking function, it will not exit until all data is sent
	while(*string != 0)	
	{
		UART_WriteTxData(*string++);
	}
}


/*******************************************************************************
* FUNCTION NAME: void UART_PutArray( uint8* string, uint8 byteCount )
*
* Summary:
* Write a Sequence of bytes on the Transmit line. Data comes from RAM.
*
* Parameters:
* string: uint8 pointer to character string of Data to Send
* byteCount: Number of Bytes to be transmitted
*
* Return:
* -None-
*
* Theory:
*
* Side Effects:
* -None-
*******************************************************************************/
void UART_PutArray(uint8* string, uint8 byteCount)
{
	while(byteCount > 0)
	{
		UART_WriteTxData(*string++);
		byteCount--;
	}	
}

/*******************************************************************************
* FUNCTION NAME: void UART_PutCRLF( uint8 txDataByte )
*
* Summary:
* Write a character and then carriage return and line feed.
*
* Parameters:
* txDataByte: uint8 Character to send
*
* Return:
* -None-
*
* Theory:
*
* Side Effects:
* -None-
*******************************************************************************/
void UART_PutCRLF(uint8 txDataByte)
{
    UART_WriteTxData(txDataByte);
    UART_WriteTxData(0x0D);
    UART_WriteTxData(0x0A);
}
/*for 32-bit PSoC5*/
#if(UART_PSOC32bit)	
/*******************************************************************************
* FUNCTION NAME: uint16 UART_GetTxBufferSize(void)
*
* Summary:
* Determine the amount of space left in the TX buffer and return the count in
*   bytes
*
* Parameters:
* -None-
*
* Return:
* uint16: Integer count of the number of bytes left in the TX buffer
*
* Theory:
* Allows the user to find out how full the TX Buffer is.
*
* Side Effects:
* -None-
*******************************************************************************/
uint16 UART_GetTxBufferSize(void)
{
    uint16 size;


#if(UART_TXBUFFERSIZE > 4)

    /* Disable Tx interrupt. */
    /* Protect variables that could change on interrupt. */
    #if(UART_TX_IntInterruptEnabled)
        UART_DisableTxInt();
    #endif

    if(UART_TXBUFFERREAD == UART_TXBUFFERWRITE)
    {
        size = 0;
    }
    else if(UART_TXBUFFERREAD < UART_TXBUFFERWRITE)
    {
        size = (UART_TXBUFFERWRITE - UART_TXBUFFERREAD);
    }
    else
    {
        size = (UART_TXBUFFERSIZE - UART_TXBUFFERREAD) + UART_TXBUFFERWRITE;
    }

    /* Enable Tx interrupt. */
    #if(UART_TX_IntInterruptEnabled)
        UART_EnableTxInt();
    #endif

#else /* UART_TXBUFFERSIZE > 4 */

    size = UART_TXSTATUS;

    /* Is the fifo is full. */
    if(size & UART_TX_STS_FIFO_FULL)
    {
        size = 4;
    }
    else if(size & UART_TX_STS_FIFO_EMPTY)
    {
        size = 0;
    }
    else
    {
        /* We only know there is data in the fifo. */
        size = 1;
    }

#endif /* UART_TXBUFFERSIZE > 4 */

    return size;
}

#else
/* 8-bit version */
/*******************************************************************************
* FUNCTION NAME: uint8 UART_GetTxBufferSize(void)
*
* Summary:
* Determine the amount of space left in the TX buffer and return the count in
*   bytes
*
* Parameters:
* -None-
*
* Return:
* uint8: Integer count of the number of bytes left in the TX buffer
*
* Theory:
* Allows the user to find out how full the TX Buffer is.
*
* Side Effects:
* -None-
*******************************************************************************/
uint8 UART_GetTxBufferSize(void)
{
    uint8 size;


#if(UART_TXBUFFERSIZE > 4)

    /* Disable Tx interrupt. */
    /* Protect variables that could change on interrupt. */
    #if(UART_TX_IntInterruptEnabled)
        UART_DisableTxInt();
    #endif

    if(UART_TXBUFFERREAD == UART_TXBUFFERWRITE)
    {
        size = 0;
    }
    else if(UART_TXBUFFERREAD < UART_TXBUFFERWRITE)
    {
        size = (UART_TXBUFFERWRITE - UART_TXBUFFERREAD);
    }
    else
    {
        size = (UART_TXBUFFERSIZE - UART_TXBUFFERREAD) + UART_TXBUFFERWRITE;
    }

    /* Enable Tx interrupt. */
    #if(UART_TX_IntInterruptEnabled)
        UART_EnableTxInt();
    #endif

#else /* UART_TXBUFFERSIZE > 4 */

    size = UART_TXSTATUS;

    /* Is the fifo is full. */
    if(size & UART_TX_STS_FIFO_FULL)
    {
        size = 4;
    }
    else if(size & UART_TX_STS_FIFO_EMPTY)
    {
        size = 0;
    }
    else
    {
        /* We only know there is data in the fifo. */
        size = 1;
    }

#endif /* UART_TXBUFFERSIZE > 4 */

    return size;
}
#endif // End UART_PSOC32bit

/*******************************************************************************
* FUNCTION NAME: void UART_ClearTxBuffer(void)
*
* Summary:
* Clear the TX RAM buffer by setting the read and write pointers both to zero.
*
* Parameters:
* -None-
*
* Return:
* -None-
*
* Theory:
* Setting the pointers to zero makes the system believe there is no data to read
*        and writing will resume at address 0 overwriting any data that may have
*        remained in the RAM.
*
* Side Effects:
* Any received data not read from the RAM buffer will be lost when overwritten.
*******************************************************************************/
void UART_ClearTxBuffer(void)
{
#if(UART_TXBUFFERSIZE > 4)

    /* Disable Tx interrupt. */
    /* Protect variables that could change on interrupt. */
    #if(UART_TX_IntInterruptEnabled)
        UART_DisableTxInt();
    #endif

    UART_TXBUFFERREAD = 0;
    UART_TXBUFFERWRITE = 0;

    /* Enable Tx interrupt. */
    #if(UART_TX_IntInterruptEnabled)
        UART_EnableTxInt();
    #endif

#endif /* UART_TXBUFFERSIZE > 4 */
}

/*******************************************************************************
* FUNCTION NAME: void UART_SendBreak( void )
*
* Summary:
* Write a Break command to the UART
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
void UART_SendBreak(void)
{
    /*Set the Counter to 13-bits and transmit a 00 byte*/
    /*When that is done then reset the counter value back*/
	uint8 tmpStat;

#if(UART_HD_Enabled)

	 uint8 tmpControl;
	 
     tmpControl = UART_ReadControlRegister();
	 UART_WriteControlRegister(tmpControl | UART_CTRL_HD_SEND_BREAK);

	/* Send zeros*/
	UART_TXDATA = 0;

	/*wait till transmit start*/
	do{tmpStat = UART_TXSTATUS;
	   }while(tmpStat&UART_TX_STS_COMPLETE);

	/*wait till transmit complete*/
	do{tmpStat = UART_TXSTATUS;
	   }while(~tmpStat&UART_TX_STS_COMPLETE);

	 UART_WriteControlRegister(tmpControl);
	 
#else

	uint8 lastPeriod;

	 #if(UART_TXCLKGEN_DP)
	    lastPeriod=UART_TXBITCLKTX_COMPLETE;
		UART_TXBITCLKTX_COMPLETE = UART_TXBITCTR_13BITS;
	#else
		lastPeriod=UART_TXBITCTR_PERIOD;
		UART_TXBITCTR_PERIOD = UART_TXBITCTR_13BITS;
	#endif	

	/* Send zeros*/
	UART_TXDATA = 0;

	/*wait till transmit start*/
	do{tmpStat = UART_TXSTATUS;
	   }while(tmpStat&UART_TX_STS_COMPLETE);

	/*wait till transmit complete*/
	do{tmpStat = UART_TXSTATUS;
	   }while(~tmpStat&UART_TX_STS_COMPLETE);

	 #if(UART_TXCLKGEN_DP)
		UART_TXBITCLKTX_COMPLETE = lastPeriod;
	#else
		UART_TXBITCTR_PERIOD=lastPeriod;
	#endif	

#endif	

}

/*******************************************************************************
* FUNCTION NAME: void UART_SetTxAddressMode( uint8 addressMode )
*
* Summary:
* Set the transmit addressing mode
*
* Parameters:
* addressMode: 0 -> Space
*              1 -> Mark
*
* Return:
* -None-
*
* Theory:
*
* Side Effects:
* -None-
*******************************************************************************/
void UART_SetTxAddressMode(uint8 addressMode)
{
   uint8 control;
    
	if(UART_ParityType == UART__B_UART__MARK_SPACE_REVA)
    {
        control = UART_ReadControlRegister();
	    /* Mark/Space sending enable*/
        if(addressMode != 0)
        {
	        UART_WriteControlRegister(control | UART_CTRL_MARK);
        }
        else
        {
	        UART_WriteControlRegister(control & ~UART_CTRL_MARK);
        }
	 }    
     else
     {
        addressMode = addressMode;
     }
}

#endif  //UART_TX_Enabled

#if(UART_HD_Enabled) 

/*******************************************************************************
* FUNCTION NAME: void UART_LoadTxConfig(void)
*
* Summary:
* Unloads the Tx configuration if required and loads the
* Rx configuration. It is the user?s responsibility to ensure that any
* transmission is complete and it is safe to unload the Tx
* configuration.
*
* Parameters:
* -None-
*
* Return:
* -None-
*
* Theory: Valid only for half duplex UART
*
* Side Effects:
* -None-
*******************************************************************************/
void UART_LoadTxConfig(void)
{
uint8 control_tmp;   
	control_tmp = UART_ReadControlRegister();
	UART_WriteControlRegister( control_tmp | UART_CTRL_HD_SEND);
   
   UART_RXBITCTR_PERIOD=UART_HD_TXBITCTR_INIT;

}

/*******************************************************************************
* FUNCTION NAME: void UART_LoadRxConfig( void )
*
* Summary:
* Unloads the Rx configuration if required and loads the
* Tx configuration. It is the user?s responsibility to ensure that any
* transmission is complete and it is safe to unload the Rx
* configuration.
*
* Parameters:
* -None-
*
* Return:
* -None-
*
* Theory: Valid only for half duplex UART
*
* Side Effects:
* -None-
*******************************************************************************/
void UART_LoadRxConfig(void)
{
uint8 control_tmp;   
	control_tmp = UART_ReadControlRegister();
	UART_WriteControlRegister( control_tmp & ~UART_CTRL_HD_SEND);
   
   UART_RXBITCTR_PERIOD=UART_HD_RXBITCTR_INIT;
}
#endif  /* UART_HD_Enabled */

