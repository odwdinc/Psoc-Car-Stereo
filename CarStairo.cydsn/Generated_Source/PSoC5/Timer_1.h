/*******************************************************************************
* File Name: Timer_1.h  
* Version 1.20
*
*  Description:
*     Contains the function prototypes and constants available to the timer
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

#if !defined(CY_TIMER_v1_20_Timer_1_H)
#define CY_TIMER_v1_20_Timer_1_H
#define Timer_1_Resolution 8

/***************************************
*   Conditional Compilation Parameters
***************************************/

#define Timer_1_UsingFixedFunction         1
#define Timer_1_UsingHWCaptureCounter      0
#define Timer_1_SoftwareCaptureMode        0
#define Timer_1_SoftwareTriggerMode        0
#define Timer_1_UsingHWEnable              0
#define Timer_1_EnableTriggerMode          0 
#define Timer_1_InterruptOnCaptureCount    0
#define Timer_1_RunModeUsed                0

/*************************************** 
*       Function Prototypes 
***************************************/

void    Timer_1_Start(void);
void    Timer_1_Stop(void);

void    Timer_1_SetInterruptMode(uint8 interruptsource);
uint8   Timer_1_GetInterruptSource(void);

uint8   Timer_1_ReadStatusRegister(void);
uint8   Timer_1_ReadControlRegister(void);
void    Timer_1_WriteControlRegister(uint8 control);

uint8  Timer_1_ReadPeriod(void);
void    Timer_1_WritePeriod(uint8 period);
uint8  Timer_1_ReadCounter(void);
void    Timer_1_WriteCounter(uint8 counter);
uint8  Timer_1_ReadCapture(void);
void    Timer_1_SoftwareCapture(void);


#if(!Timer_1_UsingFixedFunction) /* UDB Prototypes */
    #if (Timer_1_SoftwareCaptureMode)
        void    Timer_1_SetCaptureMode(uint8 capturemode);
    #endif

    #if (Timer_1_SoftwareTriggerMode)
        void    Timer_1_SetTriggerMode(uint8 triggermode);
    #endif
    #if (Timer_1_EnableTriggerMode)
        void    Timer_1_EnableTrigger(void);
        void    Timer_1_DisableTrigger(void);
    #endif

    #if(Timer_1_InterruptOnCaptureCount)
    void    Timer_1_SetInterruptCount(uint8 interruptcount);
    #endif

    #if (Timer_1_UsingHWCaptureCounter)
    void    Timer_1_SetCaptureCount(uint8 capturecount);
    uint8   Timer_1_ReadCaptureCount();
    #endif

    void Timer_1_ClearFIFO(void);
#endif /* UDB Prototypes */


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define Timer_1__B_TIMER__CM_NONE 0
#define Timer_1__B_TIMER__CM_RISINGEDGE 1
#define Timer_1__B_TIMER__CM_FALLINGEDGE 2
#define Timer_1__B_TIMER__CM_EITHEREDGE 3
#define Timer_1__B_TIMER__CM_SOFTWARE 4


/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define Timer_1__B_TIMER__TM_NONE 0x00
#define Timer_1__B_TIMER__TM_RISINGEDGE 0x04
#define Timer_1__B_TIMER__TM_FALLINGEDGE 0x08
#define Timer_1__B_TIMER__TM_EITHEREDGE 0x0C
#define Timer_1__B_TIMER__TM_SOFTWARE 0x10


/***************************************
*    Initialial Parameter Constants
***************************************/

#define Timer_1_INIT_PERIOD               255
#define Timer_1_INIT_CAPTURE_MODE         (1 << Timer_1_CTRL_CAP_MODE_SHIFT)
#define Timer_1_INIT_TRIGGER_MODE         (0 << Timer_1_CTRL_TRIG_MODE_SHIFT)
#if (Timer_1_UsingFixedFunction)
#define Timer_1_INIT_INTERRUPT_MODE       ((0 << Timer_1_STATUS_TC_INT_MASK_SHIFT) | (0 << Timer_1_STATUS_CAPTURE_INT_MASK_SHIFT))
#else
#define Timer_1_INIT_INTERRUPT_MODE       ((0 << Timer_1_STATUS_TC_INT_MASK_SHIFT) | (0 << Timer_1_STATUS_CAPTURE_INT_MASK_SHIFT) | (0 << Timer_1_STATUS_FIFOFULL_INT_MASK_SHIFT))
#endif
#define Timer_1_INIT_CAPTURE_COUNT        (2)
#define Timer_1_INIT_INT_CAPTURE_COUNT    ((1 - 1) << Timer_1_CTRL_INTCNT_SHIFT)


/***************************************
*           Registers
***************************************/

#if (Timer_1_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */

    
    /***************************************
    *    Fixed Function Registers 
    ***************************************/
    
    #define Timer_1_STATUS         (*(reg8 *) Timer_1_TimerHW__SR0 )
    #define Timer_1_STATUS_MASK    (*(reg8 *) Timer_1_TimerHW__SR0 ) /* In Fixed Function Block Status and Mask are the same register */
    #define Timer_1_CONTROL        (*(reg8 *) Timer_1_TimerHW__CFG0)
    #define Timer_1_CONTROL2       (*(reg8 *) Timer_1_TimerHW__CFG1)
    #define Timer_1_GLOBAL_ENABLE  (*(reg8 *) Timer_1_TimerHW__PM_ACT_CFG)
    
    #define Timer_1_CAPTURE_LSB         (* (reg16 *) Timer_1_TimerHW__CAP0 )
    #define Timer_1_CAPTURE_LSB_PTR       ((reg16 *) Timer_1_TimerHW__CAP0 )
    #define Timer_1_PERIOD_LSB          (* (reg16 *) Timer_1_TimerHW__PER0 )
    #define Timer_1_PERIOD_LSB_PTR        ((reg16 *) Timer_1_TimerHW__PER0 )
    #define Timer_1_COUNTER_LSB         (* (reg16 *) Timer_1_TimerHW__CNT_CMP0 )
    #define Timer_1_COUNTER_LSB_PTR       ((reg16 *) Timer_1_TimerHW__CNT_CMP0 )
    
    /***************************************
    *    Register Constants
    ***************************************/
    
    /* Fixed Function Block Chosen */
    #define Timer_1_BLOCK_EN_MASK                      Timer_1_TimerHW__PM_ACT_MSK
    
    /* Control Register Bit Locations */
    #define Timer_1_CTRL_INTCNT_SHIFT                  0x00u       /* Interrupt Count - Not valid for Fixed Function Block */
    #define Timer_1_CTRL_TRIG_MODE_SHIFT               0x00u       /* Trigger Polarity - Not valid for Fixed Function Block */
    #define Timer_1_CTRL_TRIG_EN_SHIFT                 0x00u       /* Trigger Enable - Not valid for Fixed Function Block */
    #define Timer_1_CTRL_CAP_MODE_SHIFT                0x00u       /* Capture Polarity - Not valid for Fixed Function Block */ 
    #define Timer_1_CTRL_ENABLE_SHIFT                  0x00u       /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
   
    /* Control Register Bit Masks */
    /* Timer_1_CTRL_INTCNT_MASK                        Not valid for Fixed Function Block */ 
    /* Timer_1_CTRL_TRIG_MODE_MASK                     Not valid for Fixed Function Block */ 
    /* Timer_1_CTRL_TRIG_EN                            Not valid for Fixed Function Block */ 
    /* Timer_1_CTRL_CAP_MODE_MASK                      Not valid for Fixed Function Block */    
    #define Timer_1_CTRL_ENABLE                        (0x01u << Timer_1_CTRL_ENABLE_SHIFT)
    
    /* Control2 Register Bit Masks */
    #define Timer_1_CTRL2_IRQ_SEL_SHIFT                 0x00u       /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define Timer_1_CTRL2_IRQ_SEL                      (0x01u << Timer_1_CTRL2_IRQ_SEL_SHIFT) 
    
    #define Timer_1_CTRL_MODE_SHIFT                     0x01u       /* As defined by Verilog Implementation */ 
    #define Timer_1_CTRL_MODE_MASK                     (0x07u << Timer_1_CTRL_MODE_SHIFT) 
    #define Timer_1_CTRL_MODE_PULSEWIDTH               (0x01u << Timer_1_CTRL_MODE_SHIFT) 
    #define Timer_1_CTRL_MODE_PERIOD                   (0x02u << Timer_1_CTRL_MODE_SHIFT) 
    #define Timer_1_CTRL_MODE_CONTINUOUS               (0x00u << Timer_1_CTRL_MODE_SHIFT) 
    
    /* Status Register Bit Locations */
    #define Timer_1_STATUS_TC_SHIFT                    0x07u  /* As defined in Register Map, part of TMRX_SR0 register */ 
    #define Timer_1_STATUS_CAPTURE_SHIFT               0x06u  /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define Timer_1_STATUS_TC_INT_MASK_SHIFT           (Timer_1_STATUS_TC_SHIFT - 4)      /* As defined in Register Map, part of TMRX_SR0 register */ 
    #define Timer_1_STATUS_CAPTURE_INT_MASK_SHIFT      (Timer_1_STATUS_CAPTURE_SHIFT - 4) /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */ 
    /* Timer_1_STATUS_FIFOFULL_SHIFT                   Not valid for Fixed Function Block */ 
    /* Timer_1_STATUS_FIFONEMP_SHIFT                   Not valid for Fixed Function Block */ 
    /* Timer_1_STATUS_FIFOFULL_INT_MASK_SHIFT          Not valid for Fixed Function Block */
    
    /* Status Register Bit Masks */
    #define Timer_1_STATUS_TC                          (0x01u << Timer_1_STATUS_TC_SHIFT)
    #define Timer_1_STATUS_CAPTURE                     (0x01u << Timer_1_STATUS_CAPTURE_SHIFT)
    #define Timer_1_STATUS_TC_INT_MASK                 (0x01u << Timer_1_STATUS_TC_INT_MASK_SHIFT)      /* Interrupt Enable Bit-Mask */ 
    #define Timer_1_STATUS_CAPTURE_INT_MASK            (0x01u << Timer_1_STATUS_CAPTURE_INT_MASK_SHIFT) /* Interrupt Enable Bit-Mask */ 
    /* Timer_1_STATUS_FIFOFULL                         Not valid for Fixed Function Block */ 
    /* Timer_1_STATUS_FIFONEMP                         Not valid for Fixed Function Block */
    /* Timer_1_STATUS_FIFOFULL_INT_MASK                Not valid for Fixed Function Block */
    
     /* Datapath Auxillary Control Register definitions */
    /* Timer_1_AUX_CTRL_FIFO0_CLR                      Not valid for Fixed Function Block */ 
    /* Timer_1_AUX_CTRL_FIFO1_CLR                      Not valid for Fixed Function Block */ 
    /* Timer_1_AUX_CTRL_FIFO0_LVL                      Not valid for Fixed Function Block */ 
    /* Timer_1_AUX_CTRL_FIFO1_LVL                      Not valid for Fixed Function Block */ 
    /* Timer_1_STATUS_ACTL_INT_EN_MASK                 Not valid for Fixed Function Block */  

#else   /* UDB Registers and Register Constants */

    
    /***************************************
    *           UDB Registers 
    ***************************************/
    
    #define Timer_1_STATUS              (* (reg8 *) Timer_1_TimerUDB_stsreg__STATUS_REG )
    #define Timer_1_STATUS_MASK         (* (reg8 *) Timer_1_TimerUDB_stsreg__MASK_REG)
    #define Timer_1_STATUS_AUX_CTRL     (* (reg8 *) Timer_1_TimerUDB_stsreg__STATUS_AUX_CTL_REG)
    #define Timer_1_CONTROL             (* (reg8 *) Timer_1_TimerUDB_ctrlreg__CONTROL_REG )
    
    #define Timer_1_CAPTURE_LSB         (* (reg8 *) Timer_1_TimerUDB_sT8_timerdp_u0__F0_REG )
    #define Timer_1_CAPTURE_LSB_PTR       ((reg8 *) Timer_1_TimerUDB_sT8_timerdp_u0__F0_REG )
    #define Timer_1_PERIOD_LSB          (* (reg8 *) Timer_1_TimerUDB_sT8_timerdp_u0__D0_REG )
    #define Timer_1_PERIOD_LSB_PTR        ((reg8 *) Timer_1_TimerUDB_sT8_timerdp_u0__D0_REG )
    #define Timer_1_COUNTER_LSB         (* (reg8 *) Timer_1_TimerUDB_sT8_timerdp_u0__A0_REG )
    #define Timer_1_COUNTER_LSB_PTR       ((reg8 *) Timer_1_TimerUDB_sT8_timerdp_u0__A0_REG )

    #if (Timer_1_UsingHWCaptureCounter)
        #define Timer_1_CAP_COUNT              (*(reg8 *) Timer_1_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define Timer_1_CAP_COUNT_PTR          ( (reg8 *) Timer_1_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define Timer_1_CAPTURE_COUNT_CTRL     (*(reg8 *) Timer_1_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define Timer_1_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) Timer_1_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif


    /***************************************
    *       Register Constants
    ***************************************/
    
    /* Control Register Bit Locations */
    #define Timer_1_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define Timer_1_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define Timer_1_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define Timer_1_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define Timer_1_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */
    
    /* Control Register Bit Masks */
    #define Timer_1_CTRL_INTCNT_MASK               (0x03u << Timer_1_CTRL_INTCNT_SHIFT)
    #define Timer_1_CTRL_TRIG_MODE_MASK            (0x03u << Timer_1_CTRL_TRIG_MODE_SHIFT)  
    #define Timer_1_CTRL_TRIG_EN                   (0x01u << Timer_1_CTRL_TRIG_EN_SHIFT)
    #define Timer_1_CTRL_CAP_MODE_MASK             (0x03u << Timer_1_CTRL_CAP_MODE_SHIFT)   
    #define Timer_1_CTRL_ENABLE                    (0x01u << Timer_1_CTRL_ENABLE_SHIFT)
    
    /* Bit Counter (7-bit) Control Register Bit Definitions */
    #define Timer_1_CNTR_ENABLE                    0x20u   /* As defined by the Register map for the AUX Control Register */
    
    /* Status Register Bit Locations */
    #define Timer_1_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define Timer_1_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define Timer_1_STATUS_TC_INT_MASK_SHIFT       Timer_1_STATUS_TC_SHIFT                
    #define Timer_1_STATUS_CAPTURE_INT_MASK_SHIFT  Timer_1_STATUS_CAPTURE_SHIFT
    #define Timer_1_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define Timer_1_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define Timer_1_STATUS_FIFOFULL_INT_MASK_SHIFT Timer_1_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    #define Timer_1_STATUS_TC                      (0x01u << Timer_1_STATUS_TC_SHIFT)             /* Sticky TC Event Bit-Mask */ 
    #define Timer_1_STATUS_CAPTURE                 (0x01u << Timer_1_STATUS_CAPTURE_SHIFT)        /* Sticky Capture Event Bit-Mask */ 
    #define Timer_1_STATUS_TC_INT_MASK             (0x01u << Timer_1_STATUS_TC_SHIFT)             /* Interrupt Enable Bit-Mask */            
    #define Timer_1_STATUS_CAPTURE_INT_MASK        (0x01u << Timer_1_STATUS_CAPTURE_SHIFT)        /* Interrupt Enable Bit-Mask */ 
    #define Timer_1_STATUS_FIFOFULL                (0x01u << Timer_1_STATUS_FIFOFULL_SHIFT)       /* NOT-Sticky FIFO Full Bit-Mask */ 
    #define Timer_1_STATUS_FIFONEMP                (0x01u << Timer_1_STATUS_FIFONEMP_SHIFT)       /* NOT-Sticky FIFO Not Empty Bit-Mask */ 
    #define Timer_1_STATUS_FIFOFULL_INT_MASK       (0x01u << Timer_1_STATUS_FIFOFULL_SHIFT)       /* Interrupt Enable Bit-Mask */ 
    
    #define Timer_1_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */
    
    /* Datapath Auxillary Control Register definitions */
    #define Timer_1_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define Timer_1_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define Timer_1_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define Timer_1_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define Timer_1_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */
    
#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_v1_20_Timer_1_H */

