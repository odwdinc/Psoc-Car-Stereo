/*******************************************************************************
* File Name: ADC_SAR_1.h
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



#if !defined(CY_ADC_SAR_ADC_SAR_1_H) /* CY_ADC_SAR_ADC_SAR_1_H */
#define CY_ADC_SAR_ADC_SAR_1_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*        Function Prototypes
***************************************/

void ADC_SAR_1_Start(void);
void ADC_SAR_1_Stop(void);
void ADC_SAR_1_IRQ_Enable(void);
void ADC_SAR_1_IRQ_Disable(void);
void ADC_SAR_1_SetPower(uint8 power);
void ADC_SAR_1_SetResolution(uint8 resolution);
void ADC_SAR_1_StartConvert(void);
void ADC_SAR_1_StopConvert(void);
uint8 ADC_SAR_1_IsEndConversion(uint8 retMode);
int8 ADC_SAR_1_GetResult8(void);
int16 ADC_SAR_1_GetResult16(void);

void ADC_SAR_1_SetOffset(int16 offset);
void ADC_SAR_1_SetGain(int16 adcGain);
int16 ADC_SAR_1_CountsTo_mVolts(int16 adcCounts);
CY_ISR_PROTO( ADC_SAR_1_ISR );

/**************************************
*           API Constants
**************************************/

/* Resolution setting constants  */
#define ADC_SAR_1__BITS_12 12
#define ADC_SAR_1__BITS_10 10
#define ADC_SAR_1__BITS_8 8


/*   Constants for IsEndConversion() "retMode" parameter  */
#define ADC_SAR_1_RETURN_STATUS              0x01u
#define ADC_SAR_1_WAIT_FOR_RESULT            0x00u

/* Constants for SetPower(power), "power" paramter */
#define ADC_SAR_1__HIGHPOWER 0
#define ADC_SAR_1__MEDPOWER 1
#define ADC_SAR_1__LOWPOWER 2
#define ADC_SAR_1__MINPOWER 3

#define ADC_SAR_1_SAR_API_POWER_MASK        0x03u


/**************************************
*    Enumerated Types and Parameters
**************************************/

/*  Reference constants */
#define ADC_SAR_1__INT_REF_NOT_BYPASSED 0
#define ADC_SAR_1__INT_REF_BYPASS 1
#define ADC_SAR_1__EXT_REF 2

/*  Reference setting constants */
#define ADC_SAR_1__VSS_TO_VREF 0
#define ADC_SAR_1__VSSA_TO_VDDA 1
#define ADC_SAR_1__VSSA_TO_VDAC 2
#define ADC_SAR_1__VNEG_VREF_DIFF 3
#define ADC_SAR_1__VNEG_VDDA_DIFF 4
#define ADC_SAR_1__VNEG_VDDA_2_DIFF 5
#define ADC_SAR_1__VNEG_VDAC_DIFF 6



/**************************************
*    Initial Parameter Constants
**************************************/

/* Default config values from user parameters */
#define ADC_SAR_1_DEFAULT_POWER          0        /* Default power setting */
#define ADC_SAR_1_DEFAULT_RESOLUTION     12   /* ADC resolution selected with parameters.*/
#define ADC_SAR_1_DEFAULT_CONV_MODE      0   /* Default conversion method */
#define ADC_SAR_1_DEFAULT_INTERNAL_CLK   1        /* Default clock selection */
#define ADC_SAR_1_DEFAULT_REFERENCE      0    /* Default reference */
#define ADC_SAR_1_DEFAULT_RANGE          0  /* ADC Input Range selection. */
#define ADC_SAR_1_DEFAULT_REF_VOLTAGE    1.024      /* ADC reference voltage. */
#define ADC_SAR_1_DEFAULT_REF_VOLTAGE_MV 1024   /* ADC reference voltage in mV */


/***************************************
*              Registers
***************************************/

#define ADC_SAR_1_SAR_TR0      (* (reg8 *) ADC_SAR_1_ADC_SAR__TR0 )
#define ADC_SAR_1_SAR_CSR0     (* (reg8 *) ADC_SAR_1_ADC_SAR__CSR0 )
#define ADC_SAR_1_SAR_CSR1     (* (reg8 *) ADC_SAR_1_ADC_SAR__CSR1 )
#define ADC_SAR_1_SAR_CSR2     (* (reg8 *) ADC_SAR_1_ADC_SAR__CSR2 )
#define ADC_SAR_1_SAR_CSR3     (* (reg8 *) ADC_SAR_1_ADC_SAR__CSR3 )
#define ADC_SAR_1_SAR_CSR4     (* (reg8 *) ADC_SAR_1_ADC_SAR__CSR4 )
#define ADC_SAR_1_SAR_CSR5     (* (reg8 *) ADC_SAR_1_ADC_SAR__CSR5 )
#define ADC_SAR_1_SAR_CSR6     (* (reg8 *) ADC_SAR_1_ADC_SAR__CSR6 )
#define ADC_SAR_1_SAR_CSR7     (* (reg8 *) ADC_SAR_1_ADC_SAR__CSR7 )
#define ADC_SAR_1_SAR_SW0      (* (reg8 *) ADC_SAR_1_ADC_SAR__SW0 )
#define ADC_SAR_1_SAR_SW2      (* (reg8 *) ADC_SAR_1_ADC_SAR__SW2 )
#define ADC_SAR_1_SAR_SW3      (* (reg8 *) ADC_SAR_1_ADC_SAR__SW3 )
#define ADC_SAR_1_SAR_SW4      (* (reg8 *) ADC_SAR_1_ADC_SAR__SW4 )
#define ADC_SAR_1_SAR_SW6      (* (reg8 *) ADC_SAR_1_ADC_SAR__SW6 )
#define ADC_SAR_1_SAR_CLK      (* (reg8 *) ADC_SAR_1_ADC_SAR__CLK )
#define ADC_SAR_1_SAR_WRK0     (* (reg8 *) ADC_SAR_1_ADC_SAR__WRK0 )
#define ADC_SAR_1_SAR_WRK1     (* (reg8 *) ADC_SAR_1_ADC_SAR__WRK1 )
#define ADC_SAR_1_PWRMGR_SAR   (* (reg8 *) ADC_SAR_1_ADC_SAR__PM_ACT_CFG )     /* SAR Power manager Reg */

/* This is only valid if there is an internal clock */
#if(ADC_SAR_1_DEFAULT_INTERNAL_CLK)
    /* Clock Power manager Reg */
    #define ADC_SAR_1_PWRMGR_CLK (* (reg8 *) ADC_SAR_1_theACLK__PM_ACT_CFG )
#endif /*End ADC_SAR_1_DEFAULT_INTERNAL_CLK */


/**************************************
*       Register Constants
**************************************/
/* PM_ACT_CFG (Active Power Mode CFG Register)     */
#define ADC_SAR_1_ACT_PWR_SAR_EN   ADC_SAR_1_ADC_SAR__PM_ACT_MSK /* Power enable mask */

/* This is only valid if there is an internal clock */
#if(ADC_SAR_1_DEFAULT_INTERNAL_CLK)
    /* Power enable mask */
    #define ADC_SAR_1_ACT_PWR_CLK_EN           ADC_SAR_1_theACLK__PM_ACT_MSK
#endif /*End ADC_SAR_1_DEFAULT_INTERNAL_CLK */

/* Priority of the ADC_SAR_IRQ interrupt. */
#define ADC_SAR_1_INTC_PRIOR_NUMBER          ADC_SAR_1_IRQ__INTC_PRIOR_NUM

/* ADC_SAR_IRQ interrupt number */
#define ADC_SAR_1_INTC_NUMBER                ADC_SAR_1_IRQ__INTC_NUMBER
/******************************************/
/* SAR.TR0 Trim Register 0 definitions    */
/******************************************/

/* Bit Field  SAR_CAP_TRIM_ENUM           */
#define ADC_SAR_1_SAR_CAP_TRIM_MASK          0x07
#define ADC_SAR_1_SAR_CAP_TRIM_0             0x00    /*decrease attenuation capacitor by 0*/
#define ADC_SAR_1_SAR_CAP_TRIM_1             0x01    /*decrease by 0.5 LSB*/
#define ADC_SAR_1_SAR_CAP_TRIM_2             0x02    /*decrease by 2*0.5 LSB = 1 LSB*/
#define ADC_SAR_1_SAR_CAP_TRIM_3             0x03    /*decrease by 3*0.5 LSB = 1.5 LSB*/
#define ADC_SAR_1_SAR_CAP_TRIM_4             0x04    /*decrease by 4*0.5 LSB = 2 LSB*/
#define ADC_SAR_1_SAR_CAP_TRIM_5             0x05    /*decrease by 5*0.5 LSB = 2.5 LSB*/
#define ADC_SAR_1_SAR_CAP_TRIM_6             0x06    /*decrease by 6*0.5 LSB = 3 LSB*/
#define ADC_SAR_1_SAR_CAP_TRIM_7             0x07    /*decrease by 7*0.5 LSB = 3.5 LSB*/

#define ADC_SAR_1_SAR_TRIMUNIT               0x08    /*Increase by 6fF*/

/*******************************************************/
/* SAR.CSR0 Satatus and Control Register 0 definitions */
/*******************************************************/

/* Bit Field  SAR_ICONT_LV_ENUM           */
#define ADC_SAR_1_SAR_POWER_MASK             0xC0u
#define ADC_SAR_1_SAR_POWER_SHIFT            0x06u
#define ADC_SAR_1_ICONT_LV_0                 0x00u
#define ADC_SAR_1_ICONT_LV_1                 0x40u
#define ADC_SAR_1_ICONT_LV_2                 0x80u
#define ADC_SAR_1_ICONT_LV_3                 0xC0u

/* Bit Field SAR_RESET_SOFT_ENUM         */
#define ADC_SAR_1_SAR_RESET_SOFT_NOTACTIVE   0x00u
#define ADC_SAR_1_SAR_RESET_SOFT_ACTIVE      0x20u

/* Bit Field  SAR_COHERENCY_EN_ENUM                   */
#define ADC_SAR_1_SAR_COHERENCY_EN_NOLOCK    0x00u
#define ADC_SAR_1_SAR_COHERENCY_EN_LOCK      0x10u

/* Bit Field  SAR_HIZ_ENUM              */
#define ADC_SAR_1_SAR_HIZ_RETAIN             0x00u
#define ADC_SAR_1_SAR_HIZ_CLEAR              0x08u

/* Bit Field SAR_MX_SOF_ENUM            */
#define ADC_SAR_1_SAR_MX_SOF_BIT             0x00u
#define ADC_SAR_1_SAR_MX_SOF_UDB             0x04u

/* Bit Field SAR_SOF_MODE_ENUM             */
#define ADC_SAR_1_SAR_SOF_MODE_LEVEL         0x00u
#define ADC_SAR_1_SAR_SOF_MODE_EDGE          0x02u

/* Bit Field SAR_SOF_BIT_ENUM              */
#define ADC_SAR_1_SAR_SOF_START_CONV         0x01u            /* Enable conversion */


/*******************************************************/
/* SAR.CSR1 Satatus and Control Register 1 definitions */
/*******************************************************/

/* Bit Field  SAR_MUXREF_ENUM           */
#define ADC_SAR_1_SAR_MUXREF_MASK            0xE0u
#define ADC_SAR_1_SAR_MUXREF_NONE            0x00u
#define ADC_SAR_1_SAR_MUXREF_VDDA_2          0x40u
#define ADC_SAR_1_SAR_MUXREF_DAC             0x60u
#define ADC_SAR_1_SAR_MUXREF_1_024V          0x80u
#define ADC_SAR_1_SAR_MUXREF_1_20V           0xA0u

/* Bit Field  SAR_SWVP_SRC_ENUM           */
#define ADC_SAR_1_SAR_SWVP_SRC_REG           0x00u
#define ADC_SAR_1_SAR_SWVP_SRC_UDB           0x10u

/* Bit Field  SAR_SWVP_SRC_ENUM           */
#define ADC_SAR_1_SAR_SWVN_SRC_REG           0x00u
#define ADC_SAR_1_SAR_SWVN_SRC_UDB           0x08u

/* Bit Field  SAR_IRQ_MODE_ENUM           */
#define ADC_SAR_1_SAR_IRQ_MODE_LEVEL         0x00u
#define ADC_SAR_1_SAR_IRQ_MODE_EDGE          0x04u

/* Bit Field  SAR_IRQ_MASK_ENUM          */
#define ADC_SAR_1_SAR_IRQ_MASK_DIS           0x00u
#define ADC_SAR_1_SAR_IRQ_MASK_EN            0x02u

/* Bit Field  SAR_EOF_ENUM                  */
#define ADC_SAR_1_SAR_EOF_0                  0x00u
#define ADC_SAR_1_SAR_EOF_1                  0x01u

/*******************************************************/
/* SAR.CSR2 Satatus and Control Register 2 definitions */
/*******************************************************/

/* Bit Field  SAR_RESOLUTION_ENUM          */
#define ADC_SAR_1_SAR_RESOLUTION_MASK        0xC0u
#define ADC_SAR_1_SAR_RESOLUTION_SHIFT       0x06u
#define ADC_SAR_1_SAR_RESOLUTION_12BIT       0xC0u
#define ADC_SAR_1_SAR_RESOLUTION_10BIT       0x80u
#define ADC_SAR_1_SAR_RESOLUTION_8BIT        0x40u

/* Bit Field SAR_SAMPLE_WIDTH_ENUM        */
#define ADC_SAR_1_SAR_SAMPLE_WIDTH_MASK      0x3Fu
#define ADC_SAR_1_SAR_SAMPLE_WIDTH_MIN       0x00u   /* minimum sample time: +1 clock cycle */
#define ADC_SAR_1_SAR_SAMPLE_WIDTH           0x04u   /* sample time width + resolution +1 clock cycle */
#define ADC_SAR_1_SAR_SAMPLE_WIDTH_MAX       0x07u   /* maximum sample time: +8 clock cycles */

/*******************************************************/
/* SAR.CSR3 Satatus and Control Register 3 definitions */
/*******************************************************/

/* Bit Field  SAR_EN_CP_ENUM              */
#define ADC_SAR_1_SAR_EN_CP_DIS              0x00u
#define ADC_SAR_1_SAR_EN_CP_EN               0x80u

/* Bit Field  SAR_EN_RESVDA_ENUM        */
#define ADC_SAR_1_SAR_EN_RESVDA_DIS          0x00u
#define ADC_SAR_1_SAR_EN_RESVDA_EN           0x40u

/* Bit Field  SAR_PWR_CTRL_VCM_ENUM    */
#define ADC_SAR_1_SAR_PWR_CTRL_VCM_MASK      0x30u
#define ADC_SAR_1_SAR_PWR_CTRL_VCM_0         0x00u

/* Bit Field  SAR_PWR_CTRL_VREF_ENUM    */
#define ADC_SAR_1_SAR_PWR_CTRL_VREF_MASK     0x0Cu
#define ADC_SAR_1_SAR_PWR_CTRL_VREF_0        0x00u

/* Bit Field  SAR_EN_BUF_VCM_ENUM          */
#define ADC_SAR_1_SAR_EN_BUF_VCM_DIS         0x00u
#define ADC_SAR_1_SAR_EN_BUF_VCM_EN          0x02u

/* Bit Field  SAR_EN_BUF_VREF_ENUM      */
#define ADC_SAR_1_SAR_EN_BUF_VREF_DIS        0x00u
#define ADC_SAR_1_SAR_EN_BUF_VREF_EN         0x01u

/*******************************************************/
/* SAR.CSR4 Satatus and Control Register 4 definitions */
/*******************************************************/

/* Bit Field  SAR_DFT_INC_ENUM          */
#define ADC_SAR_1_SAR_DFT_INC_MASK           0x0Fu
#define ADC_SAR_1_SAR_DFT_INC_DIS            0x00u
#define ADC_SAR_1_SAR_DFT_INC_EN             0x0Fu

/* Bit Field  SAR_DFT_INC_ENUM          */
#define ADC_SAR_1_SAR_DFT_OUTC_MASK          0x70u
#define ADC_SAR_1_SAR_DFT_OUTC_DIS           0x00u
#define ADC_SAR_1_SAR_DFT_OUTC_EN            0x70u

/*******************************************************/
/* SAR.CSR5 Satatus and Control Register 5 definitions */
/*******************************************************/

/* Bit Field  SAR_DCEN_ENUM                */
#define ADC_SAR_1_SAR_DCEN_0                 0x00u
#define ADC_SAR_1_SAR_DCEN_1                 0x40u

/* Bit Field  SAR_EN_CSEL_DFT_ENUM        */
#define ADC_SAR_1_SAR_EN_CSEL_DFT_DISABLED   0x00u
#define ADC_SAR_1_SAR_EN_CSEL_DFT_ENABLED    0x10u

/* Bit Field  SAR_SEL_CSEL_DFT_ENUM        */
#define ADC_SAR_1_SAR_SEL_CSEL_DFT_MASK      0x0Fu
#define ADC_SAR_1_SAR_SEL_CSEL_DFT_MIN       0x00u
#define ADC_SAR_1_SAR_SEL_CSEL_DFT_MAX       0x0Fu

/*******************************************************/
/* SAR.CSR6 Satatus and Control Register 6 definitions */
/*******************************************************/

/* Bit Field  SAR_REF_S_LSB_ENUM            */
#define ADC_SAR_1_SAR_REF_S_LSB_MASK         0xFFu
#define ADC_SAR_1_SAR_REF_S_LSB_DIS          0x00u
#define ADC_SAR_1_SAR_REF_S0_LSB_EN          0x01u
#define ADC_SAR_1_SAR_REF_S1_LSB_EN          0x02u
#define ADC_SAR_1_SAR_REF_S2_LSB_EN          0x04u
#define ADC_SAR_1_SAR_REF_S3_LSB_EN          0x08u
#define ADC_SAR_1_SAR_REF_S4_LSB_EN          0x10u
#define ADC_SAR_1_SAR_REF_S5_LSB_EN          0x20u
#define ADC_SAR_1_SAR_REF_S6_LSB_EN          0x40u
#define ADC_SAR_1_SAR_REF_S7_LSB_EN          0x80u

/*******************************************************/
/* SAR.CSR7 Satatus and Control Register 7 definitions */
/*******************************************************/

/* Bit Field  SAR_REF_S_ENUM            */
#define ADC_SAR_1_SAR_REF_S_MSB_MASK         0x3Fu
#define ADC_SAR_1_SAR_REF_S_MSB_DIS          0x00u
#define ADC_SAR_1_SAR_REF_S8_MSB_DIS         0x01u
#define ADC_SAR_1_SAR_REF_S9_MSB_EN          0x02u
#define ADC_SAR_1_SAR_REF_S10_MSB_EN         0x04u
#define ADC_SAR_1_SAR_REF_S11_MSB_EN         0x08u
#define ADC_SAR_1_SAR_REF_S12_MSB_EN         0x10u
#define ADC_SAR_1_SAR_REF_S13_MSB_EN         0x20u

/*******************************************************/
/* SAR.CLK SAR Clock Selection Register definitions    */
/*******************************************************/

/* Bit Field  MX_PUMPCLK_ENUM            */
#define ADC_SAR_1_SAR_MX_PUMPCLK_MASK        0xE0u
#define ADC_SAR_1_SAR_MX_PUMPCLK_0           0x00u
#define ADC_SAR_1_SAR_MX_PUMPCLK_1           0x20u
#define ADC_SAR_1_SAR_MX_PUMPCLK_2           0x40u
#define ADC_SAR_1_SAR_MX_PUMPCLK_3           0x60u
#define ADC_SAR_1_SAR_MX_PUMPCLK_4           0x80u

/* Bit Field  BYPASS_SYNC_ENUM            */
#define ADC_SAR_1_SAR_BYPASS_SYNC_0          0x00u
#define ADC_SAR_1_SAR_BYPASS_SYNC_1          0x10u

/* Bit Field  MX_CLK_EN_ENUM            */
#define ADC_SAR_1_SAR_MX_CLK_EN              0x08u

/* Bit Field  MX_CLK_ENUM                */
#define ADC_SAR_1_SAR_MX_CLK_MASK            0x07u
#define ADC_SAR_1_SAR_MX_CLK_0               0x00u
#define ADC_SAR_1_SAR_MX_CLK_1               0x01u
#define ADC_SAR_1_SAR_MX_CLK_2               0x02u
#define ADC_SAR_1_SAR_MX_CLK_3               0x03u
#define ADC_SAR_1_SAR_MX_CLK_4               0x04u

/*********************************************************/
/* ANAIF.WRK.SARS.SOF SAR Global Start-of-frame register */
/*********************************************************/

/* Bit Field  SAR_SOF_BIT_ENUM            */
#define ADC_SAR_1_SAR_SOFR_BIT_MASK          0x03u
#define ADC_SAR_1_SAR_SOFR_BIT_0             0x00u
#define ADC_SAR_1_SAR_SOFR_BIT_1             0x01u

/***********************************************/
/* SAR.SW3 SAR Analog Routing Register 3       */
/***********************************************/
#define ADC_SAR_1_SAR_VP_VSSA                0x04u
#define ADC_SAR_1_SAR_VN_AMX                 0x10u
#define ADC_SAR_1_SAR_VN_VREF                0x20u
#define ADC_SAR_1_SAR_VN_VSSA                0x40u
#define ADC_SAR_1_SAR_VN_MASK                0x60u

#endif /* End CY_ADC_SAR_ADC_SAR_1_H */


/* [] END OF FILE */
