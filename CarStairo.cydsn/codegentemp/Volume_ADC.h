/*******************************************************************************
* File Name: Volume_ADC.h
* Version 1.10
*
* Description:
*  This file contains the function prototypes and constants used in
*  the Successive approximation ADC Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2009, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/



#if !defined(CY_ADC_SAR_Volume_ADC_H) /* CY_ADC_SAR_Volume_ADC_H */
#define CY_ADC_SAR_Volume_ADC_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*        Function Prototypes
***************************************/

void Volume_ADC_Start(void);
void Volume_ADC_Stop(void);
void Volume_ADC_IRQ_Enable(void);
void Volume_ADC_IRQ_Disable(void);
void Volume_ADC_SetPower(uint8 power);
void Volume_ADC_SetResolution(uint8 resolution);
void Volume_ADC_StartConvert(void);
void Volume_ADC_StopConvert(void);
uint8 Volume_ADC_IsEndConversion(uint8 retMode);
int8 Volume_ADC_GetResult8(void);
int16 Volume_ADC_GetResult16(void);

void Volume_ADC_SetOffset(int16 offset);
void Volume_ADC_SetGain(int16 adcGain);
int16 Volume_ADC_CountsTo_mVolts(int16 adcCounts);
CY_ISR_PROTO( Volume_ADC_ISR );

/**************************************
*           API Constants
**************************************/

/* Resolution setting constants  */
#define Volume_ADC__BITS_12 12
#define Volume_ADC__BITS_10 10
#define Volume_ADC__BITS_8 8


/*   Constants for IsEndConversion() "retMode" parameter  */
#define Volume_ADC_RETURN_STATUS              0x01u
#define Volume_ADC_WAIT_FOR_RESULT            0x00u

/* Constants for SetPower(power), "power" paramter */
#define Volume_ADC__HIGHPOWER 0
#define Volume_ADC__MEDPOWER 1
#define Volume_ADC__LOWPOWER 2
#define Volume_ADC__MINPOWER 3

#define Volume_ADC_SAR_API_POWER_MASK        0x03u


/**************************************
*    Enumerated Types and Parameters
**************************************/

/*  Reference constants */
#define Volume_ADC__INT_REF_NOT_BYPASSED 0
#define Volume_ADC__INT_REF_BYPASS 1
#define Volume_ADC__EXT_REF 2

/*  Reference setting constants */
#define Volume_ADC__VSS_TO_VREF 0
#define Volume_ADC__VSSA_TO_VDDA 1
#define Volume_ADC__VSSA_TO_VDAC 2
#define Volume_ADC__VNEG_VREF_DIFF 3
#define Volume_ADC__VNEG_VDDA_DIFF 4
#define Volume_ADC__VNEG_VDDA_2_DIFF 5
#define Volume_ADC__VNEG_VDAC_DIFF 6



/**************************************
*    Initial Parameter Constants
**************************************/

/* Default config values from user parameters */
#define Volume_ADC_DEFAULT_POWER          0        /* Default power setting */
#define Volume_ADC_DEFAULT_RESOLUTION     8   /* ADC resolution selected with parameters.*/
#define Volume_ADC_DEFAULT_CONV_MODE      0   /* Default conversion method */
#define Volume_ADC_DEFAULT_INTERNAL_CLK   1        /* Default clock selection */
#define Volume_ADC_DEFAULT_REFERENCE      0    /* Default reference */
#define Volume_ADC_DEFAULT_RANGE          1  /* ADC Input Range selection. */
#define Volume_ADC_DEFAULT_REF_VOLTAGE    3.7      /* ADC reference voltage. */
#define Volume_ADC_DEFAULT_REF_VOLTAGE_MV 3700   /* ADC reference voltage in mV */


/***************************************
*              Registers
***************************************/

#define Volume_ADC_SAR_TR0      (* (reg8 *) Volume_ADC_ADC_SAR__TR0 )
#define Volume_ADC_SAR_CSR0     (* (reg8 *) Volume_ADC_ADC_SAR__CSR0 )
#define Volume_ADC_SAR_CSR1     (* (reg8 *) Volume_ADC_ADC_SAR__CSR1 )
#define Volume_ADC_SAR_CSR2     (* (reg8 *) Volume_ADC_ADC_SAR__CSR2 )
#define Volume_ADC_SAR_CSR3     (* (reg8 *) Volume_ADC_ADC_SAR__CSR3 )
#define Volume_ADC_SAR_CSR4     (* (reg8 *) Volume_ADC_ADC_SAR__CSR4 )
#define Volume_ADC_SAR_CSR5     (* (reg8 *) Volume_ADC_ADC_SAR__CSR5 )
#define Volume_ADC_SAR_CSR6     (* (reg8 *) Volume_ADC_ADC_SAR__CSR6 )
#define Volume_ADC_SAR_CSR7     (* (reg8 *) Volume_ADC_ADC_SAR__CSR7 )
#define Volume_ADC_SAR_SW0      (* (reg8 *) Volume_ADC_ADC_SAR__SW0 )
#define Volume_ADC_SAR_SW2      (* (reg8 *) Volume_ADC_ADC_SAR__SW2 )
#define Volume_ADC_SAR_SW3      (* (reg8 *) Volume_ADC_ADC_SAR__SW3 )
#define Volume_ADC_SAR_SW4      (* (reg8 *) Volume_ADC_ADC_SAR__SW4 )
#define Volume_ADC_SAR_SW6      (* (reg8 *) Volume_ADC_ADC_SAR__SW6 )
#define Volume_ADC_SAR_CLK      (* (reg8 *) Volume_ADC_ADC_SAR__CLK )
#define Volume_ADC_SAR_WRK0     (* (reg8 *) Volume_ADC_ADC_SAR__WRK0 )
#define Volume_ADC_SAR_WRK1     (* (reg8 *) Volume_ADC_ADC_SAR__WRK1 )
#define Volume_ADC_PWRMGR_SAR   (* (reg8 *) Volume_ADC_ADC_SAR__PM_ACT_CFG )     /* SAR Power manager Reg */

/* This is only valid if there is an internal clock */
#if(Volume_ADC_DEFAULT_INTERNAL_CLK)
    /* Clock Power manager Reg */
    #define Volume_ADC_PWRMGR_CLK (* (reg8 *) Volume_ADC_theACLK__PM_ACT_CFG )
#endif /*End Volume_ADC_DEFAULT_INTERNAL_CLK */


/**************************************
*       Register Constants
**************************************/
/* PM_ACT_CFG (Active Power Mode CFG Register)     */
#define Volume_ADC_ACT_PWR_SAR_EN   Volume_ADC_ADC_SAR__PM_ACT_MSK /* Power enable mask */

/* This is only valid if there is an internal clock */
#if(Volume_ADC_DEFAULT_INTERNAL_CLK)
    /* Power enable mask */
    #define Volume_ADC_ACT_PWR_CLK_EN           Volume_ADC_theACLK__PM_ACT_MSK
#endif /*End Volume_ADC_DEFAULT_INTERNAL_CLK */

/* Priority of the ADC_SAR_IRQ interrupt. */
#define Volume_ADC_INTC_PRIOR_NUMBER          Volume_ADC_IRQ__INTC_PRIOR_NUM

/* ADC_SAR_IRQ interrupt number */
#define Volume_ADC_INTC_NUMBER                Volume_ADC_IRQ__INTC_NUMBER
/******************************************/
/* SAR.TR0 Trim Register 0 definitions    */
/******************************************/

/* Bit Field  SAR_CAP_TRIM_ENUM           */
#define Volume_ADC_SAR_CAP_TRIM_MASK          0x07
#define Volume_ADC_SAR_CAP_TRIM_0             0x00    /*decrease attenuation capacitor by 0*/
#define Volume_ADC_SAR_CAP_TRIM_1             0x01    /*decrease by 0.5 LSB*/
#define Volume_ADC_SAR_CAP_TRIM_2             0x02    /*decrease by 2*0.5 LSB = 1 LSB*/
#define Volume_ADC_SAR_CAP_TRIM_3             0x03    /*decrease by 3*0.5 LSB = 1.5 LSB*/
#define Volume_ADC_SAR_CAP_TRIM_4             0x04    /*decrease by 4*0.5 LSB = 2 LSB*/
#define Volume_ADC_SAR_CAP_TRIM_5             0x05    /*decrease by 5*0.5 LSB = 2.5 LSB*/
#define Volume_ADC_SAR_CAP_TRIM_6             0x06    /*decrease by 6*0.5 LSB = 3 LSB*/
#define Volume_ADC_SAR_CAP_TRIM_7             0x07    /*decrease by 7*0.5 LSB = 3.5 LSB*/

#define Volume_ADC_SAR_TRIMUNIT               0x08    /*Increase by 6fF*/

/*******************************************************/
/* SAR.CSR0 Satatus and Control Register 0 definitions */
/*******************************************************/

/* Bit Field  SAR_ICONT_LV_ENUM           */
#define Volume_ADC_SAR_POWER_MASK             0xC0u
#define Volume_ADC_SAR_POWER_SHIFT            0x06u
#define Volume_ADC_ICONT_LV_0                 0x00u
#define Volume_ADC_ICONT_LV_1                 0x40u
#define Volume_ADC_ICONT_LV_2                 0x80u
#define Volume_ADC_ICONT_LV_3                 0xC0u

/* Bit Field SAR_RESET_SOFT_ENUM         */
#define Volume_ADC_SAR_RESET_SOFT_NOTACTIVE   0x00u
#define Volume_ADC_SAR_RESET_SOFT_ACTIVE      0x20u

/* Bit Field  SAR_COHERENCY_EN_ENUM                   */
#define Volume_ADC_SAR_COHERENCY_EN_NOLOCK    0x00u
#define Volume_ADC_SAR_COHERENCY_EN_LOCK      0x10u

/* Bit Field  SAR_HIZ_ENUM              */
#define Volume_ADC_SAR_HIZ_RETAIN             0x00u
#define Volume_ADC_SAR_HIZ_CLEAR              0x08u

/* Bit Field SAR_MX_SOF_ENUM            */
#define Volume_ADC_SAR_MX_SOF_BIT             0x00u
#define Volume_ADC_SAR_MX_SOF_UDB             0x04u

/* Bit Field SAR_SOF_MODE_ENUM             */
#define Volume_ADC_SAR_SOF_MODE_LEVEL         0x00u
#define Volume_ADC_SAR_SOF_MODE_EDGE          0x02u

/* Bit Field SAR_SOF_BIT_ENUM              */
#define Volume_ADC_SAR_SOF_START_CONV         0x01u            /* Enable conversion */


/*******************************************************/
/* SAR.CSR1 Satatus and Control Register 1 definitions */
/*******************************************************/

/* Bit Field  SAR_MUXREF_ENUM           */
#define Volume_ADC_SAR_MUXREF_MASK            0xE0u
#define Volume_ADC_SAR_MUXREF_NONE            0x00u
#define Volume_ADC_SAR_MUXREF_VDDA_2          0x40u
#define Volume_ADC_SAR_MUXREF_DAC             0x60u
#define Volume_ADC_SAR_MUXREF_1_024V          0x80u
#define Volume_ADC_SAR_MUXREF_1_20V           0xA0u

/* Bit Field  SAR_SWVP_SRC_ENUM           */
#define Volume_ADC_SAR_SWVP_SRC_REG           0x00u
#define Volume_ADC_SAR_SWVP_SRC_UDB           0x10u

/* Bit Field  SAR_SWVP_SRC_ENUM           */
#define Volume_ADC_SAR_SWVN_SRC_REG           0x00u
#define Volume_ADC_SAR_SWVN_SRC_UDB           0x08u

/* Bit Field  SAR_IRQ_MODE_ENUM           */
#define Volume_ADC_SAR_IRQ_MODE_LEVEL         0x00u
#define Volume_ADC_SAR_IRQ_MODE_EDGE          0x04u

/* Bit Field  SAR_IRQ_MASK_ENUM          */
#define Volume_ADC_SAR_IRQ_MASK_DIS           0x00u
#define Volume_ADC_SAR_IRQ_MASK_EN            0x02u

/* Bit Field  SAR_EOF_ENUM                  */
#define Volume_ADC_SAR_EOF_0                  0x00u
#define Volume_ADC_SAR_EOF_1                  0x01u

/*******************************************************/
/* SAR.CSR2 Satatus and Control Register 2 definitions */
/*******************************************************/

/* Bit Field  SAR_RESOLUTION_ENUM          */
#define Volume_ADC_SAR_RESOLUTION_MASK        0xC0u
#define Volume_ADC_SAR_RESOLUTION_SHIFT       0x06u
#define Volume_ADC_SAR_RESOLUTION_12BIT       0xC0u
#define Volume_ADC_SAR_RESOLUTION_10BIT       0x80u
#define Volume_ADC_SAR_RESOLUTION_8BIT        0x40u

/* Bit Field SAR_SAMPLE_WIDTH_ENUM        */
#define Volume_ADC_SAR_SAMPLE_WIDTH_MASK      0x3Fu
#define Volume_ADC_SAR_SAMPLE_WIDTH_MIN       0x00u   /* minimum sample time: +1 clock cycle */
#define Volume_ADC_SAR_SAMPLE_WIDTH           0x04u   /* sample time width + resolution +1 clock cycle */
#define Volume_ADC_SAR_SAMPLE_WIDTH_MAX       0x07u   /* maximum sample time: +8 clock cycles */

/*******************************************************/
/* SAR.CSR3 Satatus and Control Register 3 definitions */
/*******************************************************/

/* Bit Field  SAR_EN_CP_ENUM              */
#define Volume_ADC_SAR_EN_CP_DIS              0x00u
#define Volume_ADC_SAR_EN_CP_EN               0x80u

/* Bit Field  SAR_EN_RESVDA_ENUM        */
#define Volume_ADC_SAR_EN_RESVDA_DIS          0x00u
#define Volume_ADC_SAR_EN_RESVDA_EN           0x40u

/* Bit Field  SAR_PWR_CTRL_VCM_ENUM    */
#define Volume_ADC_SAR_PWR_CTRL_VCM_MASK      0x30u
#define Volume_ADC_SAR_PWR_CTRL_VCM_0         0x00u

/* Bit Field  SAR_PWR_CTRL_VREF_ENUM    */
#define Volume_ADC_SAR_PWR_CTRL_VREF_MASK     0x0Cu
#define Volume_ADC_SAR_PWR_CTRL_VREF_0        0x00u

/* Bit Field  SAR_EN_BUF_VCM_ENUM          */
#define Volume_ADC_SAR_EN_BUF_VCM_DIS         0x00u
#define Volume_ADC_SAR_EN_BUF_VCM_EN          0x02u

/* Bit Field  SAR_EN_BUF_VREF_ENUM      */
#define Volume_ADC_SAR_EN_BUF_VREF_DIS        0x00u
#define Volume_ADC_SAR_EN_BUF_VREF_EN         0x01u

/*******************************************************/
/* SAR.CSR4 Satatus and Control Register 4 definitions */
/*******************************************************/

/* Bit Field  SAR_DFT_INC_ENUM          */
#define Volume_ADC_SAR_DFT_INC_MASK           0x0Fu
#define Volume_ADC_SAR_DFT_INC_DIS            0x00u
#define Volume_ADC_SAR_DFT_INC_EN             0x0Fu

/* Bit Field  SAR_DFT_INC_ENUM          */
#define Volume_ADC_SAR_DFT_OUTC_MASK          0x70u
#define Volume_ADC_SAR_DFT_OUTC_DIS           0x00u
#define Volume_ADC_SAR_DFT_OUTC_EN            0x70u

/*******************************************************/
/* SAR.CSR5 Satatus and Control Register 5 definitions */
/*******************************************************/

/* Bit Field  SAR_DCEN_ENUM                */
#define Volume_ADC_SAR_DCEN_0                 0x00u
#define Volume_ADC_SAR_DCEN_1                 0x40u

/* Bit Field  SAR_EN_CSEL_DFT_ENUM        */
#define Volume_ADC_SAR_EN_CSEL_DFT_DISABLED   0x00u
#define Volume_ADC_SAR_EN_CSEL_DFT_ENABLED    0x10u

/* Bit Field  SAR_SEL_CSEL_DFT_ENUM        */
#define Volume_ADC_SAR_SEL_CSEL_DFT_MASK      0x0Fu
#define Volume_ADC_SAR_SEL_CSEL_DFT_MIN       0x00u
#define Volume_ADC_SAR_SEL_CSEL_DFT_MAX       0x0Fu

/*******************************************************/
/* SAR.CSR6 Satatus and Control Register 6 definitions */
/*******************************************************/

/* Bit Field  SAR_REF_S_LSB_ENUM            */
#define Volume_ADC_SAR_REF_S_LSB_MASK         0xFFu
#define Volume_ADC_SAR_REF_S_LSB_DIS          0x00u
#define Volume_ADC_SAR_REF_S0_LSB_EN          0x01u
#define Volume_ADC_SAR_REF_S1_LSB_EN          0x02u
#define Volume_ADC_SAR_REF_S2_LSB_EN          0x04u
#define Volume_ADC_SAR_REF_S3_LSB_EN          0x08u
#define Volume_ADC_SAR_REF_S4_LSB_EN          0x10u
#define Volume_ADC_SAR_REF_S5_LSB_EN          0x20u
#define Volume_ADC_SAR_REF_S6_LSB_EN          0x40u
#define Volume_ADC_SAR_REF_S7_LSB_EN          0x80u

/*******************************************************/
/* SAR.CSR7 Satatus and Control Register 7 definitions */
/*******************************************************/

/* Bit Field  SAR_REF_S_ENUM            */
#define Volume_ADC_SAR_REF_S_MSB_MASK         0x3Fu
#define Volume_ADC_SAR_REF_S_MSB_DIS          0x00u
#define Volume_ADC_SAR_REF_S8_MSB_DIS         0x01u
#define Volume_ADC_SAR_REF_S9_MSB_EN          0x02u
#define Volume_ADC_SAR_REF_S10_MSB_EN         0x04u
#define Volume_ADC_SAR_REF_S11_MSB_EN         0x08u
#define Volume_ADC_SAR_REF_S12_MSB_EN         0x10u
#define Volume_ADC_SAR_REF_S13_MSB_EN         0x20u

/*******************************************************/
/* SAR.CLK SAR Clock Selection Register definitions    */
/*******************************************************/

/* Bit Field  MX_PUMPCLK_ENUM            */
#define Volume_ADC_SAR_MX_PUMPCLK_MASK        0xE0u
#define Volume_ADC_SAR_MX_PUMPCLK_0           0x00u
#define Volume_ADC_SAR_MX_PUMPCLK_1           0x20u
#define Volume_ADC_SAR_MX_PUMPCLK_2           0x40u
#define Volume_ADC_SAR_MX_PUMPCLK_3           0x60u
#define Volume_ADC_SAR_MX_PUMPCLK_4           0x80u

/* Bit Field  BYPASS_SYNC_ENUM            */
#define Volume_ADC_SAR_BYPASS_SYNC_0          0x00u
#define Volume_ADC_SAR_BYPASS_SYNC_1          0x10u

/* Bit Field  MX_CLK_EN_ENUM            */
#define Volume_ADC_SAR_MX_CLK_EN              0x08u

/* Bit Field  MX_CLK_ENUM                */
#define Volume_ADC_SAR_MX_CLK_MASK            0x07u
#define Volume_ADC_SAR_MX_CLK_0               0x00u
#define Volume_ADC_SAR_MX_CLK_1               0x01u
#define Volume_ADC_SAR_MX_CLK_2               0x02u
#define Volume_ADC_SAR_MX_CLK_3               0x03u
#define Volume_ADC_SAR_MX_CLK_4               0x04u

/*********************************************************/
/* ANAIF.WRK.SARS.SOF SAR Global Start-of-frame register */
/*********************************************************/

/* Bit Field  SAR_SOF_BIT_ENUM            */
#define Volume_ADC_SAR_SOFR_BIT_MASK          0x03u
#define Volume_ADC_SAR_SOFR_BIT_0             0x00u
#define Volume_ADC_SAR_SOFR_BIT_1             0x01u

/***********************************************/
/* SAR.SW3 SAR Analog Routing Register 3       */
/***********************************************/
#define Volume_ADC_SAR_VP_VSSA                0x04u
#define Volume_ADC_SAR_VN_AMX                 0x10u
#define Volume_ADC_SAR_VN_VREF                0x20u
#define Volume_ADC_SAR_VN_VSSA                0x40u
#define Volume_ADC_SAR_VN_MASK                0x60u

#endif /* End CY_ADC_SAR_Volume_ADC_H */


/* [] END OF FILE */
