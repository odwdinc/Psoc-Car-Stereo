/*******************************************************************************
* File Name: UART_1.h  
* Version 1.20
*
*  Description:
*     Contains the function prototypes and constants available to the UART
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2009, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"


#if !defined(CY_UART_UART_1_H)
#define CY_UART_UART_1_H


#define UART_1_RX_Enabled                     0
#define UART_1_TX_Enabled                     1
#define UART_1_HD_Enabled                     0
#define UART_1_RX_IntInterruptEnabled         0
#define UART_1_TX_IntInterruptEnabled         0
#define UART_1_InternalClockUsed              1
#define UART_1_RXHW_Address_Enabled           1
#define UART_1_OverSampleCount                8
#define UART_1_ParityType                     0
#define UART_1_PSOC32bit                      1

#if(CYDEV_CHIP_DIE_EXPECT == CYDEV_CHIP_DIE_LEOPARD)     
    #if((CYDEV_CHIP_REV_EXPECT <= CYDEV_CHIP_REV_LEOPARD_ES2) && (UART_1_RX_IntInterruptEnabled || UART_1_TX_IntInterruptEnabled))      
        #include <intrins.h>
        #define UART_1_ISR_PATCH() _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
    #endif
#endif    


/* Use Any Enumerated Types */
#define UART_1__B_UART__AM_SW_BYTE_BYTE 1
#define UART_1__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define UART_1__B_UART__AM_HW_BYTE_BY_BYTE 3
#define UART_1__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define UART_1__B_UART__AM_NONE 0


#define UART_1__B_UART__NONE_REVA 0
#define UART_1__B_UART__EVEN_REVA 1
#define UART_1__B_UART__ODD_REVA 2
#define UART_1__B_UART__MARK_SPACE_REVA 3
#define UART_1__B_UART__SOFTWARE_REVA 4


/***************************************
 *   Function Prototypes
 **************************************/
void UART_1_Start(void);
void UART_1_Stop(void);
uint8 UART_1_ReadControlRegister(void);
void  UART_1_WriteControlRegister(uint8 control);

/* Only if RX is enabled */
#if(UART_1_RX_Enabled)

#if(UART_1_RX_IntInterruptEnabled)
    void  UART_1_EnableRxInt(void);
    void  UART_1_DisableRxInt(void);
    CY_ISR_PROTO(UART_1_RXISR);
    #define UART_1_RX_VECT_NUM                UART_1_RXInternalInterrupt__INTC_NUMBER
    #define UART_1_RX_PRIOR_NUM               UART_1_RXInternalInterrupt__INTC_PRIOR_NUM
#endif /* UART_1_RX_IntInterruptEnabled */

    void  UART_1_SetRxInterruptMode(uint8 intSrc);
    uint8 UART_1_ReadRxData(void);
    uint8 UART_1_ReadRxStatus(void);
    uint8 UART_1_GetRxInterruptSource(void);
    uint8 UART_1_GetChar(void);
    uint16 UART_1_GetByte(void);
	
#if(UART_1_PSOC32bit)
    /* for 32-bit PSoC3 */
    uint16 UART_1_GetRxBufferSize(void);
#else
    /* for 8-bit PSoC3 */
    uint8 UART_1_GetRxBufferSize(void);
#endif	

	void UART_1_ClearRxBuffer(void);
    
#if (UART_1_RXHW_Address_Enabled)
        void UART_1_SetRxAddressMode(uint8 addressMode);
        void UART_1_SetRxAddress1(uint8 address);
        void UART_1_SetRxAddress2(uint8 address);
#endif
#endif

/* Only if TX is enabled */
#if(UART_1_TX_Enabled || UART_1_HD_Enabled)

#if(UART_1_TX_IntInterruptEnabled)
    void UART_1_EnableTxInt(void);
    void UART_1_DisableTxInt(void);
    CY_ISR_PROTO(UART_1_TXISR);
    #define UART_1_TX_VECT_NUM                UART_1_TXInternalInterrupt__INTC_NUMBER
    #define UART_1_TX_PRIOR_NUM               UART_1_TXInternalInterrupt__INTC_PRIOR_NUM
#endif /* UART_1_TX_IntInterruptEnabled */
    void UART_1_SetTxInterruptMode(uint8 intSrc);
    void UART_1_WriteTxData(uint8 txDataByte);
    uint8 UART_1_ReadTxStatus(void);
    uint8 UART_1_GetTxInterruptSource(void);

    /* PutChar for 8-bit & 32-bit PSoC3 */
    void UART_1_PutChar(uint8 txDataByte);
    void UART_1_PutString(uint8* string);
    void UART_1_PutArray(uint8* string, uint8 byteCount);
    /* Released functions, defines for backward compatible */
    #define UART_1_PutStringConst		UART_1_PutString
    #define UART_1_PutArrayConst		UART_1_PutArray
    void UART_1_PutCRLF(uint8 txDataByte);
    void UART_1_ClearTxBuffer(void);
    void UART_1_SendBreak(void);
    void UART_1_SetTxAddressMode(uint8 addressMode);
    void UART_1_HardwareAddressEnable(uint8 addressEnable);

	/* 32-bit Version */
#if(UART_1_PSOC32bit)
    uint16 UART_1_GetTxBufferSize(void);
#else   
    uint8 UART_1_GetTxBufferSize(void);
#endif  //end UART_1_PSOC32bit


#endif

#if(UART_1_HD_Enabled)
    void UART_1_LoadRxConfig(void);
    void UART_1_LoadTxConfig(void);
#endif
	

/***********************************
*     Constants
***********************************/                           
/* Status Register definitions */
//TODO: This should be changed to an enumerate type?
#if( (UART_1_TX_Enabled) || (UART_1_HD_Enabled) )
    #define UART_1_TX_STS_COMPLETE_SHIFT      0x00u
    #define UART_1_TX_STS_COMPLETE           (0x01u << UART_1_TX_STS_COMPLETE_SHIFT)
    #define UART_1_TX_STS_FIFO_EMPTY_SHIFT    0x01u
    #define UART_1_TX_STS_FIFO_EMPTY         (0x01u << UART_1_TX_STS_FIFO_EMPTY_SHIFT)
    #define UART_1_TX_STS_FIFO_FULL_SHIFT     0x02u
    #define UART_1_TX_STS_FIFO_FULL          (0x01u << UART_1_TX_STS_FIFO_FULL_SHIFT)
    #define UART_1_TX_STS_FIFO_NOT_FULL_SHIFT 0x02u
    #define UART_1_TX_STS_FIFO_NOT_FULL      (0x01u << UART_1_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif
#if(UART_1_RX_Enabled)
    #define UART_1_RX_STS_MRKSPC_SHIFT            0x00u
    #define UART_1_RX_STS_BREAK_SHIFT             0x01u
    #define UART_1_RX_STS_PAR_ERROR_SHIFT         0x02u
    #define UART_1_RX_STS_STOP_ERROR_SHIFT        0x03u
    #define UART_1_RX_STS_OVERRUN_SHIFT           0x04u
    #define UART_1_RX_STS_FIFO_NOTEMPTY_SHIFT     0x05u
    #define UART_1_RX_STS_ADDR_MATCH_SHIFT        0x06u
    #define UART_1_RX_STS_SOFT_BUFF_OVER_SHIFT    0x07u
    
    #define UART_1_RX_STS_MRKSPC              (0x01u << UART_1_RX_STS_MRKSPC_SHIFT)   
    #define UART_1_RX_STS_BREAK               (0x01u << UART_1_RX_STS_BREAK_SHIFT)   
    #define UART_1_RX_STS_PAR_ERROR           (0x01u << UART_1_RX_STS_PAR_ERROR_SHIFT) 
    #define UART_1_RX_STS_STOP_ERROR          (0x01u << UART_1_RX_STS_STOP_ERROR_SHIFT)
    #define UART_1_RX_STS_OVERRUN             (0x01u << UART_1_RX_STS_OVERRUN_SHIFT)
    #define UART_1_RX_STS_FIFO_NOTEMPTY       (0x01u << UART_1_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define UART_1_RX_STS_ADDR_MATCH          (0x01u << UART_1_RX_STS_ADDR_MATCH_SHIFT )
    #define UART_1_RX_STS_SOFT_BUFF_OVER      (0x01u << UART_1_RX_STS_SOFT_BUFF_OVER_SHIFT )
    #define UART_1_RX_HW_MASK                  0x7Fu
#endif                                                        

/* Control Register definitions */
//TODO: This should be changed to an enumerate type?
#define UART_1_CTRL_HD_SEND_SHIFT				0x00u /* 1 enable TX part in Half Duplex mode */
#define UART_1_CTRL_HD_SEND_BREAK_SHIFT		0x01u /* 1 send BREAK signal in Half Duplez mode */
#define UART_1_CTRL_MARK_SHIFT                0x02u /* 1 sets mark, 0 sets space */
#define UART_1_CTRL_PARITYTYPE0_SHIFT         0x03u /* Defines the type of parity implemented */
#define UART_1_CTRL_PARITYTYPE1_SHIFT         0x04u /* Defines the type of parity implemented */
#define UART_1_CTRL_RXADDR_MODE0_SHIFT        0x05u
#define UART_1_CTRL_RXADDR_MODE1_SHIFT        0x06u
#define UART_1_CTRL_RXADDR_MODE2_SHIFT        0x07u

#define UART_1_CTRL_HD_SEND                   (0x01u << UART_1_CTRL_HD_SEND_SHIFT)
#define UART_1_CTRL_HD_SEND_BREAK             (0x01u << UART_1_CTRL_HD_SEND_BREAK_SHIFT)
#define UART_1_CTRL_MARK                      (0x01u << UART_1_CTRL_MARK_SHIFT)
#define UART_1_CTRL_PARITYTYPE_MASK           (0x03u << UART_1_CTRL_PARITYTYPE0_SHIFT)
#define UART_1_CTRL_RXADDR_MODE_MASK          (0x07u << UART_1_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits */
#define UART_1_INT_ENABLE                     0x10u   /* As defined by the Register map for the AUX Control Register */

/* Bit Counter (7-bit) Control Register Bit Definitions */
#define UART_1_CNTR_ENABLE                    0x20u   /* As defined by the Register map for the AUX Control Register */


/***************************************
 *    Initialization Values
 **************************************/
 //TODO: Finish this initialization value
#define UART_1_INIT_RX_INTERRUPTS_MASK        (0 << UART_1_RX_STS_FIFO_NOTEMPTY_SHIFT ) | (0 << UART_1_RX_STS_MRKSPC_SHIFT) | (0 << UART_1_RX_STS_ADDR_MATCH_SHIFT ) | (0 << UART_1_RX_STS_PAR_ERROR_SHIFT ) | (0 << UART_1_RX_STS_STOP_ERROR_SHIFT ) | (0 << UART_1_RX_STS_BREAK_SHIFT ) | (0 << UART_1_RX_STS_OVERRUN_SHIFT) 
#define UART_1_INIT_TX_INTERRUPTS_MASK        (0 << UART_1_TX_STS_COMPLETE_SHIFT) | (0 << UART_1_TX_STS_FIFO_EMPTY ) | (0 << UART_1_TX_STS_FIFO_FULL_SHIFT ) | (0 << UART_1_TX_STS_FIFO_NOT_FULL_SHIFT )

/****************************************************
******      Parameter values                    *****
****************************************************/
#define UART_1_TXBUFFERSIZE                   1
#define UART_1_RXBUFFERSIZE                   1

#define UART_1_NUMBER_OF_START_BIT            1
#define UART_1_NUMBER_OF_DATA_BITS            8
#define UART_1_NUMBER_OF_STOP_BITS            1
#define UART_1_TXBITCTR_13BITS                (13+1)*UART_1_OverSampleCount-1
#define UART_1_TXCLKGEN_DP                    1

#define UART_1_HD_TXBITCTR_INIT               UART_1_TXBITCTR_13BITS
#define UART_1_HD_RXBITCTR_INIT               UART_1_TXBITCTR_13BITS+(UART_1_OverSampleCount/2)


#if (UART_1_RXHW_Address_Enabled)
	#define UART_1_RXAddressMode              1
    #define UART_1_RXHWADDRESS1               0
    #define UART_1_RXHWADDRESS2               0
#endif

/****************************************************
******     Registers                            *****
****************************************************/
 #ifdef UART_1_BUART_sCR_ctrl__CONTROL_REG
    #define UART_1_CONTROL                    (* (reg8 *) UART_1_BUART_sCR_ctrl__CONTROL_REG )
	#define UART_1_CONTROL_REMOVED 			0
 #else	
	#define UART_1_CONTROL_REMOVED 			1
 #endif

#if(UART_1_TX_Enabled)
    #define UART_1_TXDATA                     (* (reg8 *) UART_1_BUART_sTX_dpTXShifter_u0__F0_REG )
    #define UART_1_TXDATA_PTR                 ((reg8 *) UART_1_BUART_sTX_dpTXShifter_u0__F0_REG )
    
    #define UART_1_TXSTATUS                   (* (reg8 *) UART_1_BUART_sTX_tx_sts__STATUS_REG )
    #define UART_1_TXSTATUS_MASK              (* (reg8 *) UART_1_BUART_sTX_tx_sts__MASK_REG )
    #define UART_1_TXSTATUS_ACTL              (* (reg8 *) UART_1_BUART_sTX_tx_sts__STATUS_AUX_CTL_REG )
	
			/*DP clock */	
  #if(UART_1_TXCLKGEN_DP)
	#define UART_1_BIT_CENTER                 (UART_1_OverSampleCount-1)
    #define UART_1_TXBITCLKGEN_CTR			(* (reg8 *) UART_1_BUART_sTX_sCLOCK_dpTXBitClkGen_u0__D0_REG )
    #define UART_1_TXBITCLKTX_COMPLETE		(* (reg8 *) UART_1_BUART_sTX_sCLOCK_dpTXBitClkGen_u0__D1_REG )
  #else 	/* Count7 clock*/
    #define UART_1_TXBITCTR_PERIOD            (* (reg8 *) UART_1_BUART_sTX_sCLOCK_TXBitCounter__PERIOD_REG )
    #define UART_1_TXBITCTR_PERIOD_PTR        ((reg8 *) UART_1_BUART_sTX_sCLOCK_TXBitCounter__PERIOD_REG )    
    #define UART_1_TXBITCTR_CONTROL           (* (reg8 *) UART_1_BUART_sTX_sCLOCK_TXBitCounter__CONTROL_AUX_CTL_REG )
    #define UART_1_TXBITCTR_CONTROL_PTR       ((reg8 *) UART_1_BUART_sTX_sCLOCK_TXBitCounter__CONTROL_AUX_CTL_REG )
    #define UART_1_TXBITCTR_COUNTER           (* (reg8 *) UART_1_BUART_sTX_sCLOCK_TXBitCounter__COUNT_REG )
    #define UART_1_TXBITCTR_COUNTER_PTR       ((reg8 *) UART_1_BUART_sTX_sCLOCK_TXBitCounter__COUNT_REG )
  #endif

#endif

#if(UART_1_HD_Enabled)

    #define UART_1_TXDATA                     (* (reg8 *) UART_1_BUART_sRX_dpRXShifter_u0__F1_REG )
    #define UART_1_TXDATA_PTR                 ((reg8 *) UART_1_BUART_sRX_dpRXShifter_u0__F1_REG )
    
    #define UART_1_TXSTATUS                   (* (reg8 *) UART_1_BUART_sRX_rx_sts__STATUS_REG )
    #define UART_1_TXSTATUS_MASK              (* (reg8 *) UART_1_BUART_sRX_rx_sts__MASK_REG )
    #define UART_1_TXSTATUS_ACTL              (* (reg8 *) UART_1_BUART_sRX_rx_sts__STATUS_AUX_CTL_REG )
#endif

#if(UART_1_RX_Enabled)
    #define UART_1_RXDATA                     (* (reg8 *) UART_1_BUART_sRX_dpRXShifter_u0__F0_REG )
    #define UART_1_RXDATA_PTR                 ((reg8 *) UART_1_BUART_sRX_dpRXShifter_u0__F0_REG )    
    #define UART_1_RXADDRESS1                 (* (reg8 *) UART_1_BUART_sRX_dpRXShifter_u0__D0_REG )
    #define UART_1_RXADDRESS1_PTR             ((reg8 *) UART_1_BUART_sRX_dpRXShifter_u0__D0_REG )
    #define UART_1_RXADDRESS2                 (* (reg8 *) UART_1_BUART_sRX_dpRXShifter_u0__D1_REG )
    #define UART_1_RXADDRESS2_PTR             ((reg8 *) UART_1_BUART_sRX_dpRXShifter_u0__D1_REG )    
    
    #define UART_1_RXBITCTR_PERIOD            (* (reg8 *) UART_1_BUART_sRX_RXBitCounter__PERIOD_REG )
    #define UART_1_RXBITCTR_PERIOD_PTR        ((reg8 *) UART_1_BUART_sRX_RXBitCounter__PERIOD_REG )    
    #define UART_1_RXBITCTR_CONTROL           (* (reg8 *) UART_1_BUART_sRX_RXBitCounter__CONTROL_AUX_CTL_REG )
    #define UART_1_RXBITCTR_CONTROL_PTR       ((reg8 *) UART_1_BUART_sRX_RXBitCounter__CONTROL_AUX_CTL_REG )
    #define UART_1_RXBITCTR_COUNTER           (* (reg8 *) UART_1_BUART_sRX_RXBitCounter__COUNT_REG )
    #define UART_1_RXBITCTR_COUNTER_PTR       ((reg8 *) UART_1_BUART_sRX_RXBitCounter__COUNT_REG )    
    
    #define UART_1_RXSTATUS                   (* (reg8 *) UART_1_BUART_sRX_rx_sts__STATUS_REG )
    #define UART_1_RXSTATUS_MASK              (* (reg8 *) UART_1_BUART_sRX_rx_sts__MASK_REG )
    #define UART_1_RXSTATUS_ACTL              (* (reg8 *) UART_1_BUART_sRX_rx_sts__STATUS_AUX_CTL_REG )
#endif

#if(UART_1_InternalClockUsed)
    /* Register to enable or disable the digital clocks */
    #define UART_1_IntClock_CLKEN              ((reg8 *) UART_1_IntClock__PM_ACT_CFG)
    
    /* Clock mask for this clock. */
    #define UART_1_IntClock_CLKEN_MASK         UART_1_IntClock__PM_ACT_MSK
#endif

#endif  /* CY_UART_UART_1_H */
