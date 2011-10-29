/*******************************************************************************
* FILENAME: UART_1.c
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


#include "UART_1.h"

#if(UART_1_PSOC32bit)	
/*for 32-bit PSoC5*/
	#if(UART_1_TX_Enabled && (UART_1_TXBUFFERSIZE > 4))
	uint8 UART_1_TXBUFFER[UART_1_TXBUFFERSIZE];
	uint16 UART_1_TXBUFFERREAD = 0;
	uint16 UART_1_TXBUFFERWRITE = 0;
	#endif
	#if(UART_1_RX_Enabled && (UART_1_RXBUFFERSIZE > 4))
	uint8 UART_1_RXBUFFER[UART_1_RXBUFFERSIZE];
	uint16 UART_1_RXBUFFERREAD = 0;
	uint16 UART_1_RXBUFFERWRITE = 0;
	uint8 UART_1_RXBUFFERLOOPDETECT = 0;
    uint8  UART_1_RXBUFFER_OVERFLOW = 0;
	#endif
#else
/*for 8 bit PSoc3*/	
	#if(UART_1_TX_Enabled && (UART_1_TXBUFFERSIZE > 4))
	uint8 UART_1_TXBUFFER[UART_1_TXBUFFERSIZE];
	uint8 UART_1_TXBUFFERREAD = 0;
	uint8 UART_1_TXBUFFERWRITE = 0;
	#endif
	#if(UART_1_RX_Enabled && (UART_1_RXBUFFERSIZE > 4))
	uint8 UART_1_RXBUFFER[UART_1_RXBUFFERSIZE];
	uint8 UART_1_RXBUFFERREAD = 0;
	uint8 UART_1_RXBUFFERWRITE = 0;
	uint8 UART_1_RXBUFFERLOOPDETECT = 0;
    uint8  UART_1_RXBUFFER_OVERFLOW = 0;
	#endif
#endif


uint8 UART_1_initvar = 0;
/*******************************************************************************
* FUNCTION NAME: void UART_1_Start(void)
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
void UART_1_Start(void)
{
    if(UART_1_initvar == 0)
	{
		UART_1_initvar = 1;
        
        #if(UART_1_RX_Enabled)
        
            #if(UART_1_RX_IntInterruptEnabled && (UART_1_RXBUFFERSIZE > 4))
                /* Set the RX Interrupt. */
                CyIntSetVector(UART_1_RX_VECT_NUM,   UART_1_RXISR);
                CyIntSetPriority(UART_1_RX_VECT_NUM, UART_1_RX_PRIOR_NUM);
                CyIntEnable(UART_1_RX_VECT_NUM);
            #endif
           
            #if (UART_1_RXHW_Address_Enabled)
                UART_1_SetRxAddressMode(UART_1_RXAddressMode); 
                UART_1_SetRxAddress1(UART_1_RXHWADDRESS1);
                UART_1_SetRxAddress2(UART_1_RXHWADDRESS2);
            #endif 
            
            /* Configure the Initial RX interrupt mask */
            UART_1_RXSTATUS_MASK  = UART_1_INIT_RX_INTERRUPTS_MASK;
            UART_1_RXSTATUS_ACTL  |= UART_1_INT_ENABLE;
        #endif
        #if(UART_1_TX_Enabled)
            #if(UART_1_TX_IntInterruptEnabled && (UART_1_TXBUFFERSIZE > 4))
                /* Set the TX Interrupt. */
                CyIntSetVector(UART_1_TX_VECT_NUM,   UART_1_TXISR);
                CyIntSetPriority(UART_1_TX_VECT_NUM, UART_1_TX_PRIOR_NUM);
                CyIntEnable(UART_1_TX_VECT_NUM);
            #endif
            
			  //Write Counter Value for TX Bit Clk Generator 
			 #if(UART_1_TXCLKGEN_DP)
				UART_1_TXBITCLKGEN_CTR = UART_1_BIT_CENTER;
				UART_1_TXBITCLKTX_COMPLETE = (UART_1_NUMBER_OF_DATA_BITS +
														UART_1_NUMBER_OF_START_BIT) *
														UART_1_OverSampleCount;
			#endif	
            
            /* Configure the Initial TX interrupt mask */
            #if(UART_1_TX_IntInterruptEnabled && (UART_1_TXBUFFERSIZE > 4))
                UART_1_TXSTATUS_MASK = UART_1_TX_STS_FIFO_EMPTY;
            #else
                UART_1_TXSTATUS_MASK = UART_1_INIT_TX_INTERRUPTS_MASK;
            #endif
            UART_1_TXSTATUS_ACTL  |= UART_1_INT_ENABLE;

        #endif
    }

    /*Write Bit Counter Enable */
     #if(UART_1_RX_Enabled)
	    UART_1_RXBITCTR_CONTROL |= UART_1_CNTR_ENABLE;
	 #endif	
	 
     #if(UART_1_TX_Enabled)
		 #if(UART_1_TXCLKGEN_DP)
		 	/* TODO: Start DP*/
		#else
			UART_1_TXBITCTR_CONTROL |= UART_1_CNTR_ENABLE;
		#endif	
	 #endif	
	
    #if(UART_1_InternalClockUsed)
        /* Set the bit to enable the clock. */
        *UART_1_IntClock_CLKEN |= UART_1_IntClock_CLKEN_MASK;
    #else
       
    #endif
}

/*******************************************************************************
* FUNCTION NAME: void UART_1_Stop(void)
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
void UART_1_Stop(void)
{
    /*Write Bit Counter Disable */
   #if(UART_1_RX_Enabled)
	    UART_1_RXBITCTR_CONTROL &= ~UART_1_CNTR_ENABLE;
   #endif	
	 
   #if(UART_1_TX_Enabled)
     #if(UART_1_TX_Enabled)
		#if(UART_1_TXCLKGEN_DP)
		 	// stop DP 
		#else
			UART_1_TXBITCTR_CONTROL &= ~UART_1_CNTR_ENABLE;
		#endif	
	 #endif	
   #endif	
	

   #if(UART_1_InternalClockUsed)
        /* Clear the bit to enable the clock. */
        *UART_1_IntClock_CLKEN &= ~UART_1_IntClock_CLKEN_MASK;
   #else
       
   #endif
   
   
   /*Disable internal interrupt component*/
   #if(UART_1_RX_Enabled)
       #if(UART_1_RX_IntInterruptEnabled && (UART_1_RXBUFFERSIZE > 4))
            UART_1_DisableRxInt();
       #endif
   #endif
   #if(UART_1_TX_Enabled)
       #if(UART_1_TX_IntInterruptEnabled && (UART_1_TXBUFFERSIZE > 4))
            UART_1_DisableTxInt();
       #endif
   #endif
	
}

/*******************************************************************************
* FUNCTION NAME: uint8 UART_1_ReadControlRegister(void)
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
uint8 UART_1_ReadControlRegister(void)
{
  #if( UART_1_CONTROL_REMOVED )
    return 0;	
  #else 
    return UART_1_CONTROL;
  #endif
}

/*******************************************************************************
* FUNCTION NAME: uint8 UART_1_WriteControlRegister(void)
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
void  UART_1_WriteControlRegister(uint8 control)
{
  #if( UART_1_CONTROL_REMOVED )
  	   control = control;
  #else
       UART_1_CONTROL = control;
  #endif
}


#if(UART_1_RX_Enabled)
#if(UART_1_RX_IntInterruptEnabled)
/*******************************************************************************
* FUNCTION NAME: void UART_1_EnableRxInt(void)
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
void UART_1_EnableRxInt(void)
{
    CyIntEnable(UART_1_RX_VECT_NUM);
}

/*******************************************************************************
* FUNCTION NAME: void UART_1_DisableRxInt(void)
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
void UART_1_DisableRxInt(void)
{
	CyIntDisable(UART_1_RX_VECT_NUM);
}
#endif /* UART_1_RX_IntInterruptEnabled */

/*******************************************************************************
* FUNCTION NAME: void UART_1_SetRxInterruptMode(uint8 intSrc)
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
void UART_1_SetRxInterruptMode(uint8 intSrc)
{
    UART_1_RXSTATUS_MASK  = intSrc;
}

/*******************************************************************************
* FUNCTION NAME: uint8 UART_1_ReadRxData(void)
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
uint8 UART_1_ReadRxData(void)
{
    uint8 rxData;

#if(UART_1_RXBUFFERSIZE > 4)

    /* Disable Rx interrupt. */
    /* Protect variables that could change on interrupt. */
    #if(UART_1_RX_IntInterruptEnabled)
        UART_1_DisableRxInt();
    #endif

    if( (UART_1_RXBUFFERREAD != UART_1_RXBUFFERWRITE) ||
		(UART_1_RXBUFFERLOOPDETECT > 0) )
    {
        if(UART_1_RXBUFFERLOOPDETECT > 0 ) UART_1_RXBUFFERLOOPDETECT = 0;
		
        if(UART_1_RXBUFFERREAD >= UART_1_RXBUFFERSIZE)
        {
            UART_1_RXBUFFERREAD = 0;
        }

		rxData = UART_1_RXBUFFER[UART_1_RXBUFFERREAD];

		UART_1_RXBUFFERREAD++;
    
    }
    else
    {   /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit*/
        rxData = UART_1_RXDATA;
    }

    /* Enable Rx interrupt. */
    #if(UART_1_RX_IntInterruptEnabled)
        UART_1_EnableRxInt();
    #endif

#else /* UART_1_RXBUFFERSIZE > 4 */

    /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit*/
    rxData = UART_1_RXDATA;

#endif /* UART_1_RXBUFFERSIZE > 4 */

	return rxData;
}

/*******************************************************************************
* FUNCTION NAME: uint8 UART_1_ReadRxStatus(void)
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
uint8 UART_1_ReadRxStatus(void)
{
 uint8 status;
    
    status = UART_1_RXSTATUS;
    status &= UART_1_RX_HW_MASK;
    
	#if(UART_1_RXBUFFERSIZE > 4)
       if( UART_1_RXBUFFER_OVERFLOW )
       {
           status |= UART_1_RX_STS_SOFT_BUFF_OVER;
           UART_1_RXBUFFER_OVERFLOW = 0;
       }
	#endif
    
	return status;
}


/*******************************************************************************
* FUNCTION NAME: uint8 UART_1_GetRxInterruptSource(void)
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
uint8 UART_1_GetRxInterruptSource()
{
    return UART_1_RXSTATUS;
}

/*******************************************************************************
* FUNCTION NAME: uint8 UART_1_GetChar(void)
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
uint8 UART_1_GetChar(void)
{
    uint8 rxData=0;
	uint8 rxStatus; 


#if(UART_1_RXBUFFERSIZE > 4)

    /* Disable Rx interrupt. */
    /* Protect variables that could change on interrupt. */
    #if(UART_1_RX_IntInterruptEnabled)
        UART_1_DisableRxInt();
    #endif

    if( (UART_1_RXBUFFERREAD != UART_1_RXBUFFERWRITE) ||
		(UART_1_RXBUFFERLOOPDETECT > 0) )
    {
        if(UART_1_RXBUFFERLOOPDETECT > 0 ) UART_1_RXBUFFERLOOPDETECT = 0;
       
        if(UART_1_RXBUFFERREAD >= UART_1_RXBUFFERSIZE)
        {
            UART_1_RXBUFFERREAD = 0;
        }

		rxData = UART_1_RXBUFFER[UART_1_RXBUFFERREAD];

		UART_1_RXBUFFERREAD++;
    
		
    }
    else
    {   rxStatus =UART_1_RXSTATUS;
		if(rxStatus & UART_1_RX_STS_FIFO_NOTEMPTY)
		{/* Read received data from FIFO*/
		 rxData = UART_1_RXDATA;
		 /*Check status on error*/
         if(rxStatus & (UART_1_RX_STS_BREAK | UART_1_RX_STS_PAR_ERROR | 
		 			    UART_1_RX_STS_STOP_ERROR | UART_1_RX_STS_OVERRUN))
		   rxData = 0;
		 }
    }

    /* Enable Rx interrupt. */
    #if(UART_1_RX_IntInterruptEnabled)
        UART_1_EnableRxInt();
    #endif

#else /* UART_1_RXBUFFERSIZE > 4 */

        rxStatus =UART_1_RXSTATUS;
		if(rxStatus & UART_1_RX_STS_FIFO_NOTEMPTY)
		{/* Read received data from FIFO*/
		 rxData = UART_1_RXDATA;
		 /*Check status on error*/
         if(rxStatus & (UART_1_RX_STS_BREAK | UART_1_RX_STS_PAR_ERROR | 
		 			    UART_1_RX_STS_STOP_ERROR | UART_1_RX_STS_OVERRUN))
		   rxData = 0;
		 }

#endif /* UART_1_RXBUFFERSIZE > 4 */

	return rxData;

}

/*******************************************************************************
* FUNCTION NAME: uint16 UART_1_GetByte(void)
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

uint16 UART_1_GetByte(void)
{

#if(UART_1_RXBUFFERSIZE > 4)
    /* TODO: change status if local buffer used*/
	return ( (UART_1_RXSTATUS << 8) | UART_1_ReadRxData());
#else
	return ( (UART_1_RXSTATUS << 8) | UART_1_ReadRxData() );
#endif
}

/*for 32-bit PSoC5*/
#if(UART_1_PSOC32bit)	
/*******************************************************************************
* FUNCTION NAME: uint16 UART_1_GetRxBufferSize(void)
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

uint16 UART_1_GetRxBufferSize(void)
{
    uint16 size;

  #if(UART_1_RXBUFFERSIZE > 4)

    /* Disable Rx interrupt. */
    /* Protect variables that could change on interrupt. */
    #if(UART_1_RX_IntInterruptEnabled)
        UART_1_DisableRxInt();
    #endif

    if(UART_1_RXBUFFERREAD == UART_1_RXBUFFERWRITE)
    {
        if(UART_1_RXBUFFERLOOPDETECT > 0 ) 
		{
		  size = UART_1_RXBUFFERSIZE;
		}
		else
		{
          size = 0;
		}
    }
    else if(UART_1_RXBUFFERREAD < UART_1_RXBUFFERWRITE)
    {
        size = (UART_1_RXBUFFERWRITE - UART_1_RXBUFFERREAD);
    }
    else
    {
        size = (UART_1_RXBUFFERSIZE - UART_1_RXBUFFERREAD) + UART_1_RXBUFFERWRITE;
    }

    /* Enable Rx interrupt. */
    #if(UART_1_RX_IntInterruptEnabled)
        UART_1_EnableRxInt();
    #endif

 #else /* UART_1_RXBUFFERSIZE > 4 */

    /* We can only know if there is data in the fifo. */
    size = (UART_1_RXSTATUS & UART_1_RX_STS_FIFO_NOTEMPTY) ? 1:0;

  #endif /* UART_1_RXBUFFERSIZE > 4 */

  return size;
}
#else 
/*******************************************************************************
* FUNCTION NAME: uint8 UART_1_GetRxBufferSize(void)
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
uint8 UART_1_GetRxBufferSize(void)
{
    uint8 size;


  #if(UART_1_RXBUFFERSIZE > 4)

    /* Disable Rx interrupt. */
    /* Protect variables that could change on interrupt. */
    #if(UART_1_RX_IntInterruptEnabled)
        UART_1_DisableRxInt();
    #endif

    if(UART_1_RXBUFFERREAD == UART_1_RXBUFFERWRITE)
    {
        if(UART_1_RXBUFFERLOOPDETECT > 0 ) 
		{
		  size = UART_1_RXBUFFERSIZE;
		}
		else
		{
          size = 0;
		}
    }
    else if(UART_1_RXBUFFERREAD < UART_1_RXBUFFERWRITE)
    {
        size = (UART_1_RXBUFFERWRITE - UART_1_RXBUFFERREAD);
    }
    else
    {
        size = (UART_1_RXBUFFERSIZE - UART_1_RXBUFFERREAD) + UART_1_RXBUFFERWRITE;
    }

    /* Enable Rx interrupt. */
    #if(UART_1_RX_IntInterruptEnabled)
        UART_1_EnableRxInt();
    #endif

  #else /* UART_1_RXBUFFERSIZE > 4 */

    /* We can only know if there is data in the fifo. */
    size = (UART_1_RXSTATUS & UART_1_RX_STS_FIFO_NOTEMPTY) ? 1:0;

  #endif /* UART_1_RXBUFFERSIZE > 4 */


    return size;
}

#endif

/*******************************************************************************
* FUNCTION NAME: void UART_1_ClearRxBuffer(void)
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
void UART_1_ClearRxBuffer(void)
{
#if(UART_1_RXBUFFERSIZE > 4)
    /* Disable Rx interrupt. */
    /* Protect variables that could change on interrupt. */
    #if(UART_1_RX_IntInterruptEnabled)
        UART_1_DisableRxInt();
    #endif

    UART_1_RXBUFFERREAD = 0;
    UART_1_RXBUFFERWRITE = 0;
    UART_1_RXBUFFERLOOPDETECT = 0; 
    UART_1_RXBUFFER_OVERFLOW = 0;


    /* Enable Rx interrupt. */
    #if(UART_1_RX_IntInterruptEnabled)
        UART_1_EnableRxInt();
    #endif
#endif /* UART_1_RXBUFFERSIZE > 4 */
}

/*******************************************************************************
* FUNCTION NAME: void UART_1_SetRxAddressMode( uint8 addressMode )
*
* Summary:
* Set the receive addressing mode
*
* Parameters:
* addressMode: Use one of the Enumerated Types listed below
        #define UART_1__B_UART__AM_SW_BYTE_BYTE 1
#define UART_1__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define UART_1__B_UART__AM_HW_BYTE_BY_BYTE 3
#define UART_1__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define UART_1__B_UART__AM_NONE 0

*
* Return:
* -None-
*
* Theory:
*
* Side Effects:
* -None-
*******************************************************************************/
void UART_1_SetRxAddressMode(uint8 addressMode)
{
  #if(UART_1_RXHW_Address_Enabled) 
	#if(UART_1_CONTROL_REMOVED)
		addressMode = addressMode;
	#else
		uint8 tmpCtrl = 0;
		tmpCtrl = UART_1_CONTROL & ~UART_1_CTRL_RXADDR_MODE_MASK;
		tmpCtrl |= ((addressMode << UART_1_CTRL_RXADDR_MODE0_SHIFT) & UART_1_CTRL_RXADDR_MODE_MASK);
		UART_1_CONTROL = tmpCtrl;
	#endif
  #else
    addressMode = addressMode;
  #endif	
	
}


/*******************************************************************************
* FUNCTION NAME: void UART_1_HardwareAddressEnable( uint8 addressEnable )
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
void UART_1_HardwareAddressEnable(uint8 addressEnable)
{
    /* It is always enabled if SetRxAddressMode sets not None adress mode*/
    addressEnable = addressEnable;
}


/*******************************************************************************
* FUNCTION NAME: void UART_1_SetRxAddress1(uint8 address)
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
void UART_1_SetRxAddress1(uint8 address)
{
	UART_1_RXADDRESS1 = address;
}

/*******************************************************************************
* FUNCTION NAME: void UART_1_SetRxAddress2(uint8 address)
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
void UART_1_SetRxAddress2(uint8 address)
{
	UART_1_RXADDRESS2 = address;
}

#endif  /* UART_1_RX_Enabled */

#if( (UART_1_TX_Enabled) || (UART_1_HD_Enabled) )
#if(UART_1_TX_IntInterruptEnabled)
/*******************************************************************************
* FUNCTION NAME: void UART_1_EnableTxInt(void)
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
void UART_1_EnableTxInt(void)
{
	CyIntEnable(UART_1_TX_VECT_NUM);
}

/*******************************************************************************
* FUNCTION NAME: void UART_1_DisableTxInt(void)
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
void UART_1_DisableTxInt(void)
{
	CyIntDisable(UART_1_TX_VECT_NUM);
}
#endif /* UART_1_TX_IntInterruptEnabled */

/*******************************************************************************
* FUNCTION NAME: void UART_1_SetTxInterruptMode(uint8 intSrc)
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
void UART_1_SetTxInterruptMode(uint8 intSrc)
{
    UART_1_TXSTATUS_MASK = intSrc;
}

/*******************************************************************************
* FUNCTION NAME: void UART_1_WriteTxData(uint8 txDataByte)
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
void UART_1_WriteTxData(uint8 txDataByte)
{
#if(UART_1_TXBUFFERSIZE > 4)

    /* Block if buffer is full, so we dont overwrite. */
    while(UART_1_TXBUFFERWRITE == (UART_1_TXBUFFERREAD - 1) ||
          (uint8)(UART_1_TXBUFFERWRITE - UART_1_TXBUFFERREAD) == (uint8)(UART_1_TXBUFFERSIZE - 1))
    {
        /* Software buffer is full. */
    }

    /* Disable Tx interrupt. */
    /* Protect variables that could change on interrupt. */
    #if(UART_1_TX_IntInterruptEnabled)
        UART_1_DisableTxInt();
    #endif

	if((UART_1_TXBUFFERREAD == UART_1_TXBUFFERWRITE) && !(UART_1_TXSTATUS & UART_1_TX_STS_FIFO_FULL))
	{
        /* Add directly to the FIFO. */
		UART_1_TXDATA = txDataByte;
	}
    else
    {

        if(UART_1_TXBUFFERWRITE >= UART_1_TXBUFFERSIZE)
		{
            UART_1_TXBUFFERWRITE = 0;
		 }

        UART_1_TXBUFFER[UART_1_TXBUFFERWRITE] = txDataByte;

        /* Add to the software buffer. */
        UART_1_TXBUFFERWRITE++;

	}

    /* Enable Rx interrupt. */
    #if(UART_1_TX_IntInterruptEnabled)
        UART_1_EnableTxInt();
    #endif

#else /* UART_1_TXBUFFERSIZE > 4 */

    /* Block if there isnt room. */
	while(UART_1_TXSTATUS & UART_1_TX_STS_FIFO_FULL);

    /* Add directly to the FIFO. */
	UART_1_TXDATA = txDataByte;

#endif /* UART_1_TXBUFFERSIZE > 4 */

}

/*******************************************************************************
* FUNCTION NAME: uint8 UART_1_ReadTxStatus(void)
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
uint8 UART_1_ReadTxStatus(void)
{
	return (UART_1_TXSTATUS);
}

/*******************************************************************************
* FUNCTION NAME: uint8 UART_1_GetTxInterruptSource(void)
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
uint8 UART_1_GetTxInterruptSource()
{
    return UART_1_TXSTATUS;
}

/*******************************************************************************
* FUNCTION NAME: void UART_1_PutChar(uint8 txDataByte)
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
void UART_1_PutChar(uint8 txDataByte)
{
#if(UART_1_TXBUFFERSIZE > 4)
		UART_1_WriteTxData(txDataByte);
#else /* UART_1_TXBUFFERSIZE > 4 */

    /* Block if there isnt room. */
	while(UART_1_TXSTATUS & UART_1_TX_STS_FIFO_FULL);

    /* Add directly to the FIFO. */
	UART_1_TXDATA = txDataByte;

#endif /* UART_1_TXBUFFERSIZE > 4 */

}

/*******************************************************************************
* FUNCTION NAME: void UART_1_PutString( uint8* string )
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
void UART_1_PutString(uint8* string)
{
	//This is a blocking function, it will not exit until all data is sent
	while(*string != 0)	
	{
		UART_1_WriteTxData(*string++);
	}
}


/*******************************************************************************
* FUNCTION NAME: void UART_1_PutArray( uint8* string, uint8 byteCount )
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
void UART_1_PutArray(uint8* string, uint8 byteCount)
{
	while(byteCount > 0)
	{
		UART_1_WriteTxData(*string++);
		byteCount--;
	}	
}

/*******************************************************************************
* FUNCTION NAME: void UART_1_PutCRLF( uint8 txDataByte )
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
void UART_1_PutCRLF(uint8 txDataByte)
{
    UART_1_WriteTxData(txDataByte);
    UART_1_WriteTxData(0x0D);
    UART_1_WriteTxData(0x0A);
}
/*for 32-bit PSoC5*/
#if(UART_1_PSOC32bit)	
/*******************************************************************************
* FUNCTION NAME: uint16 UART_1_GetTxBufferSize(void)
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
uint16 UART_1_GetTxBufferSize(void)
{
    uint16 size;


#if(UART_1_TXBUFFERSIZE > 4)

    /* Disable Tx interrupt. */
    /* Protect variables that could change on interrupt. */
    #if(UART_1_TX_IntInterruptEnabled)
        UART_1_DisableTxInt();
    #endif

    if(UART_1_TXBUFFERREAD == UART_1_TXBUFFERWRITE)
    {
        size = 0;
    }
    else if(UART_1_TXBUFFERREAD < UART_1_TXBUFFERWRITE)
    {
        size = (UART_1_TXBUFFERWRITE - UART_1_TXBUFFERREAD);
    }
    else
    {
        size = (UART_1_TXBUFFERSIZE - UART_1_TXBUFFERREAD) + UART_1_TXBUFFERWRITE;
    }

    /* Enable Tx interrupt. */
    #if(UART_1_TX_IntInterruptEnabled)
        UART_1_EnableTxInt();
    #endif

#else /* UART_1_TXBUFFERSIZE > 4 */

    size = UART_1_TXSTATUS;

    /* Is the fifo is full. */
    if(size & UART_1_TX_STS_FIFO_FULL)
    {
        size = 4;
    }
    else if(size & UART_1_TX_STS_FIFO_EMPTY)
    {
        size = 0;
    }
    else
    {
        /* We only know there is data in the fifo. */
        size = 1;
    }

#endif /* UART_1_TXBUFFERSIZE > 4 */

    return size;
}

#else
/* 8-bit version */
/*******************************************************************************
* FUNCTION NAME: uint8 UART_1_GetTxBufferSize(void)
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
uint8 UART_1_GetTxBufferSize(void)
{
    uint8 size;


#if(UART_1_TXBUFFERSIZE > 4)

    /* Disable Tx interrupt. */
    /* Protect variables that could change on interrupt. */
    #if(UART_1_TX_IntInterruptEnabled)
        UART_1_DisableTxInt();
    #endif

    if(UART_1_TXBUFFERREAD == UART_1_TXBUFFERWRITE)
    {
        size = 0;
    }
    else if(UART_1_TXBUFFERREAD < UART_1_TXBUFFERWRITE)
    {
        size = (UART_1_TXBUFFERWRITE - UART_1_TXBUFFERREAD);
    }
    else
    {
        size = (UART_1_TXBUFFERSIZE - UART_1_TXBUFFERREAD) + UART_1_TXBUFFERWRITE;
    }

    /* Enable Tx interrupt. */
    #if(UART_1_TX_IntInterruptEnabled)
        UART_1_EnableTxInt();
    #endif

#else /* UART_1_TXBUFFERSIZE > 4 */

    size = UART_1_TXSTATUS;

    /* Is the fifo is full. */
    if(size & UART_1_TX_STS_FIFO_FULL)
    {
        size = 4;
    }
    else if(size & UART_1_TX_STS_FIFO_EMPTY)
    {
        size = 0;
    }
    else
    {
        /* We only know there is data in the fifo. */
        size = 1;
    }

#endif /* UART_1_TXBUFFERSIZE > 4 */

    return size;
}
#endif // End UART_1_PSOC32bit

/*******************************************************************************
* FUNCTION NAME: void UART_1_ClearTxBuffer(void)
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
void UART_1_ClearTxBuffer(void)
{
#if(UART_1_TXBUFFERSIZE > 4)

    /* Disable Tx interrupt. */
    /* Protect variables that could change on interrupt. */
    #if(UART_1_TX_IntInterruptEnabled)
        UART_1_DisableTxInt();
    #endif

    UART_1_TXBUFFERREAD = 0;
    UART_1_TXBUFFERWRITE = 0;

    /* Enable Tx interrupt. */
    #if(UART_1_TX_IntInterruptEnabled)
        UART_1_EnableTxInt();
    #endif

#endif /* UART_1_TXBUFFERSIZE > 4 */
}

/*******************************************************************************
* FUNCTION NAME: void UART_1_SendBreak( void )
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
void UART_1_SendBreak(void)
{
    /*Set the Counter to 13-bits and transmit a 00 byte*/
    /*When that is done then reset the counter value back*/
	uint8 tmpStat;

#if(UART_1_HD_Enabled)

	 uint8 tmpControl;
	 
     tmpControl = UART_1_ReadControlRegister();
	 UART_1_WriteControlRegister(tmpControl | UART_1_CTRL_HD_SEND_BREAK);

	/* Send zeros*/
	UART_1_TXDATA = 0;

	/*wait till transmit start*/
	do{tmpStat = UART_1_TXSTATUS;
	   }while(tmpStat&UART_1_TX_STS_COMPLETE);

	/*wait till transmit complete*/
	do{tmpStat = UART_1_TXSTATUS;
	   }while(~tmpStat&UART_1_TX_STS_COMPLETE);

	 UART_1_WriteControlRegister(tmpControl);
	 
#else

	uint8 lastPeriod;

	 #if(UART_1_TXCLKGEN_DP)
	    lastPeriod=UART_1_TXBITCLKTX_COMPLETE;
		UART_1_TXBITCLKTX_COMPLETE = UART_1_TXBITCTR_13BITS;
	#else
		lastPeriod=UART_1_TXBITCTR_PERIOD;
		UART_1_TXBITCTR_PERIOD = UART_1_TXBITCTR_13BITS;
	#endif	

	/* Send zeros*/
	UART_1_TXDATA = 0;

	/*wait till transmit start*/
	do{tmpStat = UART_1_TXSTATUS;
	   }while(tmpStat&UART_1_TX_STS_COMPLETE);

	/*wait till transmit complete*/
	do{tmpStat = UART_1_TXSTATUS;
	   }while(~tmpStat&UART_1_TX_STS_COMPLETE);

	 #if(UART_1_TXCLKGEN_DP)
		UART_1_TXBITCLKTX_COMPLETE = lastPeriod;
	#else
		UART_1_TXBITCTR_PERIOD=lastPeriod;
	#endif	

#endif	

}

/*******************************************************************************
* FUNCTION NAME: void UART_1_SetTxAddressMode( uint8 addressMode )
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
void UART_1_SetTxAddressMode(uint8 addressMode)
{
   uint8 control;
    
	if(UART_1_ParityType == UART_1__B_UART__MARK_SPACE_REVA)
    {
        control = UART_1_ReadControlRegister();
	    /* Mark/Space sending enable*/
        if(addressMode != 0)
        {
	        UART_1_WriteControlRegister(control | UART_1_CTRL_MARK);
        }
        else
        {
	        UART_1_WriteControlRegister(control & ~UART_1_CTRL_MARK);
        }
	 }    
     else
     {
        addressMode = addressMode;
     }
}

#endif  //UART_1_TX_Enabled

#if(UART_1_HD_Enabled) 

/*******************************************************************************
* FUNCTION NAME: void UART_1_LoadTxConfig(void)
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
void UART_1_LoadTxConfig(void)
{
uint8 control_tmp;   
	control_tmp = UART_1_ReadControlRegister();
	UART_1_WriteControlRegister( control_tmp | UART_1_CTRL_HD_SEND);
   
   UART_1_RXBITCTR_PERIOD=UART_1_HD_TXBITCTR_INIT;

}

/*******************************************************************************
* FUNCTION NAME: void UART_1_LoadRxConfig( void )
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
void UART_1_LoadRxConfig(void)
{
uint8 control_tmp;   
	control_tmp = UART_1_ReadControlRegister();
	UART_1_WriteControlRegister( control_tmp & ~UART_1_CTRL_HD_SEND);
   
   UART_1_RXBITCTR_PERIOD=UART_1_HD_RXBITCTR_INIT;
}
#endif  /* UART_1_HD_Enabled */

