/*******************************************************************************
* File Name: Counter_1.c  
* Version 1.20
*
*  Description:
*     The Counter User Module consists of a 8, 16, 24 or 32-bit counter with
*     a selectable period between 2 and 2^Width - 1.  
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2009, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


#include "cytypes.h"
#include "Counter_1.h"

uint8 Counter_1_initvar = 0;

/*******************************************************************************
* Function Name: Counter_1_Start
********************************************************************************
* Summary:
*  Enables the counter for operation 
*
* Parameters:  
*  void:  
*
* Return: 
*  (void)
*
* Theory: 
*
* Side Effects: If the Enable mode is set to Hardware only then this function
*               has no effect on the operation of the counter.
*
*******************************************************************************/
void Counter_1_Start(void) 
{
    if(Counter_1_initvar == 0)
    {
        #if (!Counter_1_UsingFixedFunction && !Counter_1_ControlRegRemoved)
            uint8 ctrl;
        #endif
        
        Counter_1_initvar = 1; /* Clear this bit for Initialization */
        
        #if (Counter_1_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            Counter_1_CONTROL &= Counter_1_CTRL_ENABLE;
            
            /* Clear the mode bits to be 000 for continuous mode */
            Counter_1_CONTROL2 &= ~Counter_1_CTRL_CMPMODE_MASK; 
            /* Compare Mode is not available with Fixed Function block so don't set the compare mode */
            
            /* Set the IRQ to use the status register interrupts */
            Counter_1_CONTROL2 |= Counter_1_CTRL2_IRQ_SEL;
        #else
            #if(!Counter_1_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = Counter_1_CONTROL & ~Counter_1_CTRL_CMPMODE_MASK;
            Counter_1_CONTROL = ctrl | Counter_1_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = Counter_1_CONTROL & ~Counter_1_CTRL_CAPMODE_MASK;
            Counter_1_CONTROL = ctrl | Counter_1_DEFAULT_CAPTURE_MODE;
            #endif
        #endif 
        
        /* Clear all data in the FIFO's */
        #if (!Counter_1_UsingFixedFunction)
            Counter_1_ClearFIFO();
        #endif
        
         /* Set Initial values from Configuration */
        Counter_1_WritePeriod(Counter_1_INIT_PERIOD_VALUE);
        Counter_1_WriteCounter(Counter_1_INIT_COUNTER_VALUE);
        Counter_1_SetInterruptMode(Counter_1_INIT_INTERRUPTS_MASK);
        
        #if (Counter_1_UsingFixedFunction)
            /* Globally Enable the Fixed Function Block chosen */
            Counter_1_GLOBAL_ENABLE |= Counter_1_BLOCK_EN_MASK;
            /* Set the Interrupt source to come from the status register */
            Counter_1_CONTROL2 |= Counter_1_CTRL2_IRQ_SEL;
        #else
            /* Set the compare value (only available to non-fixed function implementation */
            Counter_1_WriteCompare(Counter_1_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            Counter_1_STATUS_AUX_CTRL |= Counter_1_STATUS_ACTL_INT_EN_MASK;
        #endif

    }
    
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!Counter_1_ControlRegRemoved || Counter_1_UsingFixedFunction)
   Counter_1_CONTROL |= Counter_1_CTRL_ENABLE;
   #endif
}

/*******************************************************************************
* Function Name: Counter_1_Stop
********************************************************************************
* Summary:
* Halts the counter, but does not change any modes or disable
* interrupts.
*
* Parameters:  
*  void:  
*
* Return: 
*  (void)
*
* Theory: 
*
* Side Effects: If the Enable mode is set to Hardware only then this function
*               has no effect on the operation of the counter.
*
*******************************************************************************/
void Counter_1_Stop(void)
{
    #if(!Counter_1_ControlRegRemoved || Counter_1_UsingFixedFunction)
        Counter_1_CONTROL &= ~Counter_1_CTRL_ENABLE;
    #endif
}

/*******************************************************************************
* Function Name: Counter_1_SetInterruptMode
********************************************************************************
* Summary:
* Configures which interrupt sources are enabled to generate the final interrupt
*
* Parameters:  
*  InterruptsMask: This parameter is an or'd collection of the status bits
*                   which will be allowed to generate the counters interrupt.   
*
* Return: 
*  (void)
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void Counter_1_SetInterruptMode(uint8 interruptsMask)
{
    Counter_1_STATUS_MASK = interruptsMask;
}

/*******************************************************************************
* Function Name: Counter_1_GetInterruptSource
********************************************************************************
* Summary:
* Returns the status register with data about the interrupt source.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint8): Status Register Bit-Field of interrupt source(s)
*
* Theory: 
*
* Side Effects:  The Status register may be clear on read and all interrupt sources
*                    must be handled.
*
*******************************************************************************/
uint8 Counter_1_GetInterruptSource(void)
{
    return Counter_1_STATUS;
}

/*******************************************************************************
* Function Name: Counter_1_ReadStatusRegister
********************************************************************************
* Summary:
*   Reads the status register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the status register
*
* Theory: 
*
* Side Effects:
*   Status register bits may be clear on read. 
*******************************************************************************/
uint8   Counter_1_ReadStatusRegister(void)
{
    return Counter_1_STATUS;
}

#if(!Counter_1_ControlRegRemoved)
/*******************************************************************************
* Function Name: Counter_1_ReadControlRegister
********************************************************************************
* Summary:
*   Reads the control register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
* Theory: 
*
* Side Effects:
*   
*******************************************************************************/
uint8   Counter_1_ReadControlRegister(void)
{
    return Counter_1_CONTROL;
}

/*******************************************************************************
* Function Name: Counter_1_WriteControlRegister
********************************************************************************
* Summary:
*   Sets the bit-field of the control register.  This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
* Theory: 
*
* Side Effects:
*   
*******************************************************************************/
void    Counter_1_WriteControlRegister(uint8 control)
{
    Counter_1_CONTROL = control;
}
#endif

/*******************************************************************************
* Function Name: Counter_1_WriteCounter
********************************************************************************
* Summary:
*   This funtion is used to set the counter to a specific value
*
* Parameters:  
*  counter:  New counter value. 
*
* Return: 
*  (void) 
*
* Theory: 
*
* Side Effects:
*   
*******************************************************************************/
void Counter_1_WriteCounter(uint8 counter )
{
    #if(Counter_1_UsingFixedFunction)
        uint16 counter_temp = (uint16)counter;
        CY_SET_REG16(Counter_1_COUNTER_LSB_PTR, counter_temp);
    #else
        CY_SET_REG8(Counter_1_COUNTER_LSB_PTR, counter);
    #endif
}

/*******************************************************************************
* Function Name: Counter_1_ReadCounter
********************************************************************************
* Summary:
* Returns the current value of the counter.  It doesn't matter
* if the counter is enabled or running.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint8) The present value of the counter.
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
uint8 Counter_1_ReadCounter(void)
{
    
    CY_GET_REG8(Counter_1_COUNTER_LSB_PTR);
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    return (CY_GET_REG8(Counter_1_STATICCOUNT_LSB_PTR));
}

/*******************************************************************************
* Function Name: Counter_1_ReadCapture
********************************************************************************
* Summary:
*   This function returns the last value captured.
*
* Parameters:  
*  void: 
*
* Return: 
*  (uint8) Present Capture value.
*
* Theory: 
*
* Side Effects:
*  
*******************************************************************************/
uint8 Counter_1_ReadCapture( void )
{
   return ( CY_GET_REG8(Counter_1_STATICCOUNT_LSB_PTR) );  
}

/*******************************************************************************
* Function Name: Counter_1_WritePeriod
********************************************************************************
* Summary:
* Changes the period of the counter.  The new period 
* will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period: (uint8) A value of 0 will result in
*         the counter remaining at zero.  
*
* Return: 
*  (void)
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void Counter_1_WritePeriod(uint8 period)
{
    #if(Counter_1_UsingFixedFunction)
        uint16 period_temp = (uint16)period;
        CY_SET_REG16(Counter_1_PERIOD_LSB_PTR,period_temp);
    #else
        CY_SET_REG8(Counter_1_PERIOD_LSB_PTR,period);
    #endif
}

/*******************************************************************************
* Function Name: Counter_1_ReadPeriod
********************************************************************************
* Summary:
* Reads the current period value without affecting counter operation.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint8) Present period value.
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
uint8 Counter_1_ReadPeriod(void)
{
   return ( CY_GET_REG8(Counter_1_PERIOD_LSB_PTR));
}

#if (!Counter_1_UsingFixedFunction)
/*******************************************************************************
* Function Name: Counter_1_WriteCompare
********************************************************************************
* Summary:
* Changes the compare value.  The compare output will 
* reflect the new value on the next UDB clock.  The compare output will be 
* driven high when the present counter value compares true based on the 
* configured compare mode setting. 
*
* Parameters:  
*  Compare:  New compare value. 
*
* Return: 
*  void
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void Counter_1_WriteCompare(uint8 compare)
{
    #if(Counter_1_UsingFixedFunction)
        uint16 compare_temp = (uint16)compare;
        CY_SET_REG16(Counter_1_COMPARE_LSB_PTR,compare_temp);
    #else
        CY_SET_REG8(Counter_1_COMPARE_LSB_PTR,compare);
    #endif
}

/*******************************************************************************
* Function Name: Counter_1_ReadCompare
********************************************************************************
* Summary:
* Returns the compare value.
*
* Parameters:  
*  void:
*
* Return: 
*  (uint8) Present compare value.
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
uint8 Counter_1_ReadCompare(void)
{
   return ( CY_GET_REG8(Counter_1_COMPARE_LSB_PTR));
}


#if (Counter_1_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: Counter_1_SetCompareMode
********************************************************************************
*
* Summary:
*  Sets the software controlled Compare Mode.
*
* Parameters:
*  compareMode:  Compare Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void Counter_1_SetCompareMode(uint8 compareMode)
{
    /* Clear the compare mode bits in the control register */
    Counter_1_CONTROL &= ~Counter_1_CTRL_CMPMODE_MASK;
    
    /* Write the new setting */
    Counter_1_CONTROL |= (compareMode << Counter_1_CTRL_CMPMODE0_SHIFT);
}
#endif


#if (Counter_1_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: Counter_1_SetCaptureMode
********************************************************************************
*
* Summary:
*  Sets the software controlled Capture Mode.
*
* Parameters:
*  captureMode:  Capture Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void Counter_1_SetCaptureMode(uint8 captureMode)
{
    /* Clear the capture mode bits in the control register */
    Counter_1_CONTROL &= ~Counter_1_CTRL_CAPMODE_MASK;
    
    /* Write the new setting */
    Counter_1_CONTROL |= (captureMode << Counter_1_CTRL_CAPMODE0_SHIFT);
}
#endif


/*******************************************************************************
* Function Name: Counter_1_ClearFIFO
********************************************************************************
* Summary:
*   This function clears all capture data from the capture FIFO
*
* Parameters:  
*  void:
*
* Return: 
*  None
*
* Theory: 
*
* Side Effects:
*   
*******************************************************************************/
void Counter_1_ClearFIFO(void)
{

   /* It will be easier to cler FIFO in using auxilary control register */
      Counter_1_AUX_CONTROLDP0 |=  Counter_1_AUX_CTRL_FIFO0_CLR;
      Counter_1_AUX_CONTROLDP0 &= ~Counter_1_AUX_CTRL_FIFO0_CLR;
     
#if (Counter_1_Resolution == 16 || Counter_1_Resolution == 24 || Counter_1_Resolution == 32)
      Counter_1_AUX_CONTROLDP1 |=  Counter_1_AUX_CTRL_FIFO0_CLR;
      Counter_1_AUX_CONTROLDP1 &= ~Counter_1_AUX_CTRL_FIFO0_CLR;
#endif

#if (Counter_1_Resolution == 24 || Counter_1_Resolution == 32)
      Counter_1_AUX_CONTROLDP2 |=  Counter_1_AUX_CTRL_FIFO0_CLR;   
      Counter_1_AUX_CONTROLDP2 &= ~Counter_1_AUX_CTRL_FIFO0_CLR;
#endif

#if (Counter_1_Resolution == 32)
      Counter_1_AUX_CONTROLDP3 |=  Counter_1_AUX_CTRL_FIFO0_CLR;   
      Counter_1_AUX_CONTROLDP3 &= ~Counter_1_AUX_CTRL_FIFO0_CLR;
#endif
      
//    while(Counter_1_ReadStatusRegister() & Counter_1_STATUS_FIFONEMP)
//        Counter_1_ReadCapture();

}
#endif

/* [] END OF FILE */
