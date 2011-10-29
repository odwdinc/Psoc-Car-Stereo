/******************************************************************************
* File Name: timer_clock.h
* Version 1.0
*
*  Description:
*   Provides the function definitions for a clock component.
*
*
********************************************************************************
* Copyright 2008-2009, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


#if !defined(CY_CLOCK_timer_clock_H)
#define CY_CLOCK_timer_clock_H

#include <CYTYPES.H>
#include <CYFITTER.H>


/***************************************
*        Function Prototypes            
***************************************/

void timer_clock_Start(void);
void timer_clock_Stop(void);
void timer_clock_StandbyPower(uint8 state);
void timer_clock_SetDivider(uint16 clkDivider);
void timer_clock_SetMode(uint8 clkMode);
void timer_clock_SetSource(uint8 clkSource);

#if defined(timer_clock__CFG3)
void timer_clock_SetPhase(uint8 clkPhase);
#endif


/* Backward compatibility macros for designs created with PSoC Creator 1.0 Beta 1 */
#define timer_clock_Enable timer_clock_Start
#define timer_clock_Disable timer_clock_Stop


/***************************************
*           API Constants        
***************************************/

/* Bit fields for seting the operating mode of the clock. */
#define CYCLK_PIPE    			(1 << 7) /* DSI input pipeline configuration. 0 Bypass pipeline stages, 1 Use pipeline stages. */
#define CYCLK_SSS     			(1 << 6) /* Sync source same as output frequency. Used to bypass synchronization with delay matched path. 0 Sync source not same frequency, 1 Sync source is same frequency */
#define CYCLK_EARLY   			(1 << 5) /* Used to set the early phase mode, with rising edge near the half-count of the divider. 0 DISABLE Disable early phase mode, 1 ENABLE Enable early phase mode. */
#define CYCLK_DUTY    			(1 << 4) /* Force duty cycle to 50%. 0 Disable 50% duty cycle, 1 Enable 50% duty cycle clock output. */ 
#define CYCLK_SYNC    			(1 << 3) /* Select output synchronization to master clock. 0 Disable synchronization, 1 Enable synchronization. */

/* Values for setting the clock source. */
#define CYCLK_SRC_SEL_SYNC_DIG  0 /* Phase delayed clk_sync output is selected. */
#define CYCLK_SRC_SEL_IMO       1 /* Internal Main Oscillator output is selected. */
#define CYCLK_SRC_SEL_XTALM     2 /* 4 to 33 MHz External Crystal Oscillator output is selected. */
#define CYCLK_SRC_SEL_ILO       3 /* Internal Low Speed Oscillator output is selected. */
#define CYCLK_SRC_SEL_PLL       4 /* Phase Locked Loop output is selected. */
#define CYCLK_SRC_SEL_XTALK     5 /* 32.768 kHz External Crystal Oscillator output is selected. */
#define CYCLK_SRC_SEL_DSI_G     6 /* dsi_global output is selected. */
#define CYCLK_SRC_SEL_DSI_D     7 /* dsi_d output is selected. */

/* Time values to delay the phase of an analog clock. */
#define CYCLK_2_5NS     		0x01 /* 2.5 ns delay. */
#define CYCLK_3_5NS     		0x02 /* 3.5 ns delay. */
#define CYCLK_4_5NS   			0x03 /* 4.5 ns delay. */ 
#define CYCLK_5_5NS   			0x04 /* 5.5 ns delay. */ 
#define CYCLK_6_5NS   			0x05 /* 6.5 ns delay. */ 
#define CYCLK_7_5NS   			0x06 /* 7.5 ns delay. */ 
#define CYCLK_8_5NS   			0x07 /* 8.5 ns delay. */ 
#define CYCLK_9_5NS   			0x08 /* 9.5 ns delay. */ 
#define CYCLK_10_5NS   			0x09 /* 10.5 ns delay. */
#define CYCLK_11_5NS   			0x0A /* 11.5 ns delay. */
#define CYCLK_12_5NS    		0x0B /* 12.5 ns delay. */
 

/***************************************
*             Registers        
***************************************/

/* Register to enable or disable the digital clocks */
#define timer_clock_CLKEN              ((reg8 *) timer_clock__PM_ACT_CFG)

/* Clock mask for this clock. */
#define timer_clock_CLKEN_MASK         timer_clock__PM_ACT_MSK

/* Register to enable or disable the digital clocks */
#define timer_clock_CLKSTBY            ((reg8 *) timer_clock__PM_STBY_CFG)

/* Clock mask for this clock. */
#define timer_clock_CLKSTBY_MASK       timer_clock__PM_STBY_MSK

/* Clock LSB divider configuration register. */
#define timer_clock_DIV_LSB            ((reg8 *) timer_clock__CFG0)

/* Clock MSB divider configuration register. */
#define timer_clock_DIV_MSB            ((reg8 *) timer_clock__CFG1)

/* Mode and source configuration register */
#define timer_clock_MOD_SRC            ((reg8 *) timer_clock__CFG2)

#if defined(timer_clock__CFG3)
/* Analog clock phase configuration register */
#define timer_clock_PHASE              ((reg8 *) timer_clock__CFG3)
#endif


/* CY_CLOCK_timer_clock_H */
#endif

