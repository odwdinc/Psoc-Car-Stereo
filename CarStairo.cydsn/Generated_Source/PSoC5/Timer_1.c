/*******************************************************************************
* File Name: Timer_1.c  
* Version 1.20
*
* Description:
*  The Timer User Module consists of a 8, 16, 24 or 32-bit timer with
*  a selectable period between 2 and 2^Width - 1.  The timer may free run
*  or be used as a capture timer as well.  The capture can be initiated
*  by a positive or negative edge signal as well as via software.
*  A trigger input can be programmed to enable the timer on rising edge
*  falling edge, either edge or continous run.
*  Interrupts may be generated due to a terminal count condition
*  or a capture event.
*
* Note:
*
********************************************************************************
* Copyright 2008-2009, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/



#include "cytypes.h"
#include "Timer_1.h"

uint8 Timer_1_initvar = 0;


/*******************************************************************************
* Function Name: Timer_1_Start
********************************************************************************
* Summary:
*  The start function initializes the timer with the default values, the 
*  enables the timerto begin counting.  It does not enable interrupts,
*  the EnableInt command should be called if interrupt generation is required.
*
* Parameters:  
*  void:  
*
* Return: 
*  void
*
*******************************************************************************/
void Timer_1_Start(void) 
{
    if(Timer_1_initvar == 0)
    {
        Timer_1_initvar = 1;   /* Clear this bit for Initialization */
        
        #if (Timer_1_UsingFixedFunction)
            #if !defined(Timer_1_TimerUDB_ctrlreg__REMOVED)  /* Remove assignment if control register is removed */
                /* Clear all bits but the enable bit (if it's already set) for Timer operation */
                Timer_1_CONTROL &= Timer_1_CTRL_ENABLE;
            #endif 
            /* Clear the mode bits to be 000 for continuous mode */
            Timer_1_CONTROL2 &= ~Timer_1_CTRL_MODE_MASK; 
            
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (Timer_1_RunModeUsed != 0)
                /* Set 3rd bit of Control register to enable one shot mode */
                Timer_1_CONTROL |= 0x04u;
            #endif
            #if (Timer_1_RunModeUsed == 2)
                /* Set last 2 bits of control2 register if one shot(halt on 
                interrupt) is enabled*/
                Timer_1_CONTROL2 |= 0x03u;
            #endif
            
            /* If the Enable HW controllable, then set bit one of CONTROL2 */
            #if (Timer_1_UsingHWEnable != 0)
                Timer_1_CONTROL2 |= Timer_1_CTRL_MODE_PULSEWIDTH; 
            #endif
            
            /* Set the IRQ to use the status register interrupts */
            Timer_1_CONTROL2 |= Timer_1_CTRL2_IRQ_SEL;
        #endif 
        
        /* Set Initial values from Configuration */
        Timer_1_WritePeriod(Timer_1_INIT_PERIOD);
        Timer_1_WriteCounter(Timer_1_INIT_PERIOD);
        
        #if (Timer_1_UsingHWCaptureCounter)/* Capture counter is enabled */
            Timer_1_CAPTURE_COUNT_CTRL |= Timer_1_CNTR_ENABLE;
            Timer_1_SetCaptureCount(Timer_1_INIT_CAPTURE_COUNT);
        #endif
            
        #if (!Timer_1_UsingFixedFunction)
            /* Initialize the Configuration bits of the Control Register */
            #if (Timer_1_SoftwareCaptureMode)
                Timer_1_SetCaptureMode(Timer_1_INIT_CAPTURE_MODE);
            #endif
            
            #if (Timer_1_SoftwareTriggerMode)
                if (!(Timer_1_CONTROL & Timer_1__B_TIMER__TM_SOFTWARE))
                {
                    Timer_1_SetTriggerMode(Timer_1_INIT_TRIGGER_MODE);
                }
            #endif
            
                /* Use the interrupt output of the status register for IRQ output */
            Timer_1_STATUS_AUX_CTRL |= Timer_1_STATUS_ACTL_INT_EN_MASK;

            #if (Timer_1_EnableTriggerMode)
                Timer_1_EnableTrigger();
            #endif

            #if (Timer_1_InterruptOnCaptureCount)
                Timer_1_SetInterruptCount(Timer_1_INIT_INT_CAPTURE_COUNT);
            #endif
            
            Timer_1_ClearFIFO();        

        #else /* (Timer_1_UsingFixedFunction) */
            /* Globally Enable the Fixed Function Block chosen */
            Timer_1_GLOBAL_ENABLE |= Timer_1_BLOCK_EN_MASK;
            /* Set the Interrupt source to come from the status register */
            Timer_1_CONTROL2 |= Timer_1_CTRL2_IRQ_SEL;
        #endif

        Timer_1_SetInterruptMode(Timer_1_INIT_INTERRUPT_MODE);
    }
    #if !defined(Timer_1_TimerUDB_ctrlreg__REMOVED) /* Remove assignment if control register is removed */
        Timer_1_CONTROL |= Timer_1_CTRL_ENABLE;
    #endif
}


/*******************************************************************************
* Function Name: Timer_1_Stop
********************************************************************************
* Summary:
*  The stop function halts the timer, but does not change any modes or disable
*  interrupts.
*
* Parameters:  
*  void:  
*
* Return: 
*  void
*
*******************************************************************************/
void Timer_1_Stop(void)
{
    #if !defined(Timer_1_TimerUDB_ctrlreg__REMOVED)   /* Remove assignment if control register is removed */
        Timer_1_CONTROL &= ~Timer_1_CTRL_ENABLE;
    #endif  
}


/*******************************************************************************
* Function Name: Timer_1_SetInterruptMode
********************************************************************************
* Summary:
*  This function selects which of the interrupt inputs may cause an interrupt.  
*  The twosources are caputure and terminal.  One, both or neither may 
*  be selected.
*
* Parameters:  
*  interruptsource: This parameter is used to enable interrups on either/or 
*                   terminal count or capture.  
*
* Return: 
*  void
*
*******************************************************************************/
void Timer_1_SetInterruptMode( uint8 interruptMode )
{
    Timer_1_STATUS_MASK = interruptMode;
}


/*******************************************************************************
* Function Name: Timer_1_GetInterruptSource
********************************************************************************
* Summary:
*  Returns the status register with the information on the interrupt source
*
* Parameters:  
*  void:  
*
* Return: 
*  Status register bit-field containing the interrupt source
*
* Side Effects: 
*  Status register is clear on Read, therefore all interrupt sources must be 
*  handled.
*
*******************************************************************************/
uint8 Timer_1_GetInterruptSource()
{
    return Timer_1_STATUS;
}


/*******************************************************************************
* Function Name: Timer_1_SoftwareCapture
********************************************************************************
* Summary:
*  This function forces a capture independent of the capture signal.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Side Effects:
*  An existing hardware capture could be overwritten.
*
*******************************************************************************/
void Timer_1_SoftwareCapture(void)
{
    /* Generate a software capture by reading the counter register */
    CY_GET_REG8(Timer_1_COUNTER_LSB_PTR);
    /* Capture Data is now in the FIFO */
}


/*******************************************************************************
* Function Name: Timer_1_ReadStatusRegister
********************************************************************************
* Summary:
*  Reads the status register and returns it's state. This function should use
*  defined types for the bit-field information as the bits in this register may
*  be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  The contents of the status register
*
* Side Effects:
*  Status register bits may be clear on read. 
*
*******************************************************************************/
uint8   Timer_1_ReadStatusRegister(void)
{
    return Timer_1_STATUS;
}


#if !defined(Timer_1_TimerUDB_ctrlreg__REMOVED)   /* Remove API if control register is removed */
/*******************************************************************************
* Function Name: Timer_1_ReadControlRegister
********************************************************************************
* Summary:
*  Reads the control register and returns it's value. 
*
* Parameters:  
*  void
*
* Return: 
*  The contents of the control register
*
*
*******************************************************************************/
uint8   Timer_1_ReadControlRegister(void)
{
        return Timer_1_CONTROL;
}


/*******************************************************************************
* Function Name: Timer_1_WriteControlRegister
********************************************************************************
* Summary:
*  Sets the bit-field of the control register.  
*
* Parameters:  
*  void
*
* Return: 
*  The contents of the control register
*
*******************************************************************************/
void    Timer_1_WriteControlRegister(uint8 control)
{
    Timer_1_CONTROL = control;
}
#endif /* Remove API if control register is removed */


/*******************************************************************************
* Function Name: Timer_1_ReadPeriod
********************************************************************************
* Summary:
*  This function returns the current value of the Period.
*
* Parameters:  
*  void:
*
* Return: 
*  The present value of the counter.
*
*******************************************************************************/
uint8 Timer_1_ReadPeriod(void)
{
   return ( CY_GET_REG8(Timer_1_PERIOD_LSB_PTR) );  
}


/*******************************************************************************
* Function Name: Timer_1_WritePeriod
********************************************************************************
* Summary:
*  This function is used to change the period of the counter.  The new period 
*  will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period: This value may be between 1 and (2^Resolution)-1.  A value of 0 will result in
*          the counter remaining at zero.
*
* Return: 
*  void
*
*******************************************************************************/
void Timer_1_WritePeriod(uint8 period)
{
    #if(Timer_1_UsingFixedFunction)
        uint16 period_temp = (uint16)period;
        CY_SET_REG16(Timer_1_PERIOD_LSB_PTR, period_temp);
    #else
        CY_SET_REG8(Timer_1_PERIOD_LSB_PTR, period);
    #endif
}


/*******************************************************************************
* Function Name: Timer_1_ReadCapture
********************************************************************************
* Summary:
*  This function returns the last value captured.
*
* Parameters:  
*  void: 
*
* Return: 
*  Present Capture value.
*
*******************************************************************************/
uint8 Timer_1_ReadCapture( void )
{
   return ( CY_GET_REG8(Timer_1_CAPTURE_LSB_PTR) );  
}


/*******************************************************************************
* Function Name: Timer_1_WriteCounter
********************************************************************************
* Summary:
*  This funtion is used to set the counter to a specific value
*
* Parameters:  
*  counter:  New counter value. 
*
* Return: 
*  void 
*
*******************************************************************************/
void Timer_1_WriteCounter(uint8 counter )
{
    #if(Timer_1_UsingFixedFunction)
        counter = counter;
        /* This functionality is removed until a FixedFunction HW update to 
         * allow this register to be written 
         */
        /* uint16 counter_temp = (uint16)counter;
         * CY_SET_REG16(Timer_1_COUNTER_LSB_PTR, counter_temp);
         */
    #else
        CY_SET_REG8(Timer_1_COUNTER_LSB_PTR, counter);
    #endif
}


/*******************************************************************************
* Function Name: Timer_1_ReadCounter
********************************************************************************
* Summary:
*  This function returns the current counter value.
*
* Parameters:  
*  void:
*
* Return: 
*  Present compare value. 
*
*******************************************************************************/
uint8 Timer_1_ReadCounter( void )
{
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    CY_GET_REG8(Timer_1_COUNTER_LSB_PTR);
    return (CY_GET_REG8(Timer_1_CAPTURE_LSB_PTR));
}


#if(!Timer_1_UsingFixedFunction) /* UDB Specific Functions */

/*******************************************************************************
 * The functions below this point are only available using the UDB 
 * implementation.  If a feature is selected, then the API is enabled.
 ******************************************************************************/


#if (Timer_1_SoftwareCaptureMode)
/*******************************************************************************
* Function Name: Timer_1_SetCaptureMode
********************************************************************************
* Summary:
*  This function sets the capture mode to either rising or falling edge.
*
* Parameters:  
*  capturemode:  This parameter sets the capture polarity. If 0, capture will 
*                be on rising edge of caputure input, if non-zero, capture 
*                will occure on falling edge. Use any of these 
*                Enumerated Types Except Software mode:
*                #define Timer_1__B_TIMER__CM_NONE 0
#define Timer_1__B_TIMER__CM_RISINGEDGE 1
#define Timer_1__B_TIMER__CM_FALLINGEDGE 2
#define Timer_1__B_TIMER__CM_EITHEREDGE 3
#define Timer_1__B_TIMER__CM_SOFTWARE 4

*
* Return: 
*  void
*
*******************************************************************************/
void Timer_1_SetCaptureMode( uint8 capturemode )
{
    /* This must only set to two bits of the control register associated */
    capturemode &= Timer_1_CTRL_CAP_MODE_MASK;
    
    #if !defined(Timer_1_TimerUDB_ctrlreg__REMOVED)   /* Remove assignment if control register is removed */
        /* Clear the Current Setting */
        Timer_1_CONTROL &= ~Timer_1_CTRL_CAP_MODE_MASK;
    
        /* Write The New Setting */   
        Timer_1_CONTROL |= capturemode; 
    #endif
}
#endif

#if (Timer_1_SoftwareTriggerMode)
/*******************************************************************************
* Function Name: Timer_1_SetTriggerMode
********************************************************************************
* Summary:
*  This function sets the trigger input mode
*
* Parameters:  
*  triggermode: Pass one of the pre-defined Trigger Modes (except Software)
    #define Timer_1__B_TIMER__TM_NONE 0x00
    #define Timer_1__B_TIMER__TM_RISINGEDGE 0x04
    #define Timer_1__B_TIMER__TM_FALLINGEDGE 0x08
    #define Timer_1__B_TIMER__TM_EITHEREDGE 0x0C
    #define Timer_1__B_TIMER__TM_SOFTWARE 0x10
*
* Return: 
*  void
*
*******************************************************************************/
void Timer_1_SetTriggerMode( uint8 triggermode )
{
    /* This must only set to two bits of the control register associated */
    triggermode &= Timer_1_CTRL_TRIG_MODE_MASK;
    
    #if !defined(Timer_1_TimerUDB_ctrlreg__REMOVED)   /* Remove assignment if control register is removed */
       /* Clear the Current Setting */
       Timer_1_CONTROL &= ~Timer_1_CTRL_TRIG_MODE_MASK;
       /* Write The New Setting */   
       Timer_1_CONTROL |= (triggermode | Timer_1__B_TIMER__TM_SOFTWARE);
    #endif 
}
#endif

#if (Timer_1_EnableTriggerMode)
/*******************************************************************************
* Function Name: Timer_1_EnableTrigger
********************************************************************************
* Summary:
*  Sets the control bit enabling Hardware Trigger mode
*
* Parameters:  
*  void:
*
* Return: 
*  void
*
*******************************************************************************/
void    Timer_1_EnableTrigger(void)
{
    #if !defined(Timer_1_TimerUDB_ctrlreg__REMOVED)   /* Remove assignment if control register is removed */
        Timer_1_CONTROL |= Timer_1_CTRL_TRIG_EN;
    #endif
}

/*******************************************************************************
* Function Name: Timer_1_DisableTrigger
********************************************************************************
* Summary:
*  Clears the control bit enabling Hardware Trigger mode
*
* Parameters:  
*  void:
*
* Return: 
*  void
*
*******************************************************************************/
void    Timer_1_DisableTrigger(void)
{
    #if !defined(Timer_1_TimerUDB_ctrlreg__REMOVED)   /* Remove assignment if control register is removed */
        Timer_1_CONTROL &= ~Timer_1_CTRL_TRIG_EN;
    #endif
}
#endif


#if(Timer_1_InterruptOnCaptureCount)
/*******************************************************************************
* Function Name: Timer_1_SetInterruptCount
********************************************************************************
* Summary:
*  This function sets the capture count before an interrupt is triggered.
*
* Parameters:  
*  interruptcount:  A value between 0 and 3 is valid.  If the value is 0, then 
*                   an interrupt will occur each time a capture occurs.  
*                   A value of 1 to 3 will cause the interrupt  
*                   to delay by the same number of captures.
*
* Return: 
*  void
*
*******************************************************************************/
void Timer_1_SetInterruptCount( uint8 interruptcount )
{
    /* This must only set to two bits of the control register associated */
    interruptcount &= Timer_1_CTRL_INTCNT_MASK;
    
    #if !defined(Timer_1_TimerUDB_ctrlreg__REMOVED)   /* Remove assignment if control register is removed */
        /* Clear the Current Setting */
        Timer_1_CONTROL &= ~Timer_1_CTRL_INTCNT_MASK;
        /* Write The New Setting */   
        Timer_1_CONTROL |= interruptcount; 
    #endif
}
#endif


#if (Timer_1_UsingHWCaptureCounter)
/*******************************************************************************
* Function Name: Timer_1_SetCaptureCount
********************************************************************************
* Summary:
*  This function sets the capture count
*
* Parameters:  
*  capturecount: A value between 0 and 3 is valid.  If the value is 0, then an 
*                interrupt will occur each time a capture occurs.  A value of 1 
*                to 3 will cause the interrupt to delay by the same number of 
*                captures.
*
* Return: 
*  void
*
*******************************************************************************/
void    Timer_1_SetCaptureCount(uint8 capturecount)
{
    Timer_1_CAP_COUNT = capturecount;
}


/*******************************************************************************
* Function Name: Timer_1_ReadCaptureCount
********************************************************************************
* Summary:
*  This function reads the capture count setting
*
* Parameters:  
*  void
*
* Return: 
*  Returns the Capture Count Setting
*
*******************************************************************************/
uint8   Timer_1_ReadCaptureCount()
{
    return Timer_1_CAP_COUNT ;
}
#endif /* Timer_1_UsingHWCaptureCounter */


/*******************************************************************************
* Function Name: Timer_1_ClearFIFO
********************************************************************************
* Summary:
*  This function clears all capture data from the capture FIFO
*
* Parameters:  
*  void:
*
* Return: 
*  void
*
*******************************************************************************/
void Timer_1_ClearFIFO(void)
{
    while(Timer_1_ReadStatusRegister() & Timer_1_STATUS_FIFONEMP)
    {
        Timer_1_ReadCapture();
    }
}

#endif /* UDB Specific Functions */

/* [] END OF FILE */
