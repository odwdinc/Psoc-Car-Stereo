/*******************************************************************************
* File Name: ADC_SAR_1.c
* Version 1.10
*
* Description:
*  This file provides the source code to the API for the Successive
*  approximation ADC Component.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2009, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CyLib.h"
#include "ADC_SAR_1.h"

#if(ADC_SAR_1_DEFAULT_INTERNAL_CLK)
    #include "ADC_SAR_1_theACLK.h"
#endif /* End ADC_SAR_1_DEFAULT_INTERNAL_CLK */

uint8 ADC_SAR_1_initVar = 0;
int16 ADC_SAR_1_Offset = 0;
int16 ADC_SAR_1_CountsPerVolt;   // Gain compensation

void ADC_SAR_1_SetRef(int8 refMode);
void ADC_SAR_1_CalcGain(uint8 resolution);


/*******************************************************************************
* Function Name: ADC_SAR_1_Start
********************************************************************************
*
* Summary:
*  Performs all required initialization for this component and enables the
*  power.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void ADC_SAR_1_Start(void)
{
    uint8 tmpReg;

    /* If not Initialized then initialize all required hardware and software */
    if(ADC_SAR_1_initVar == 0)
    {
        ADC_SAR_1_initVar = 1;
        /* This is only valid if there is an internal clock */
        #if(ADC_SAR_1_DEFAULT_INTERNAL_CLK)
            ADC_SAR_1_theACLK_SetMode(CYCLK_DUTY);
        #endif /* End ADC_SAR_1_DEFAULT_INTERNAL_CLK */

        /* Start and set interrupt vector */
        CyIntSetPriority(ADC_SAR_1_INTC_NUMBER, ADC_SAR_1_INTC_PRIOR_NUMBER);
        CyIntSetVector(ADC_SAR_1_INTC_NUMBER, ADC_SAR_1_ISR );

        /* default CSR0=0 */
        tmpReg = ADC_SAR_1_SAR_CSR0;

        /* Set Power parameter  */
        tmpReg |= (ADC_SAR_1_DEFAULT_POWER << ADC_SAR_1_SAR_POWER_SHIFT);

        /* Clear DAC value at beginning of sampling */
        tmpReg |= ADC_SAR_1_SAR_HIZ_CLEAR;

        /*Set Convertion mode */
        if(ADC_SAR_1_DEFAULT_CONV_MODE)                /* If triggered mode */
        {
            tmpReg |= ADC_SAR_1_SAR_MX_SOF_UDB;            /* source: UDB */
            tmpReg |= ADC_SAR_1_SAR_SOF_MODE_EDGE;        /* Set edge-sensitive sof source */
         }
        ADC_SAR_1_SAR_CSR0 = tmpReg;

        /* Enable IRQ mode*/
        ADC_SAR_1_SAR_CSR1 |= ADC_SAR_1_SAR_IRQ_MASK_EN | ADC_SAR_1_SAR_IRQ_MODE_EDGE;
        
        /*Set SAR ADC resolution ADC */
        ADC_SAR_1_SetResolution(ADC_SAR_1_DEFAULT_RESOLUTION);

        /*Sets input range of the ADC*/
        switch (ADC_SAR_1_DEFAULT_RANGE)
        {
            case ADC_SAR_1__VSS_TO_VREF:
                ADC_SAR_1_SetRef(ADC_SAR_1_DEFAULT_RANGE);
                break;

            case ADC_SAR_1__VSSA_TO_VDDA:
                /* Set bit for VDD/2 mode */
                ADC_SAR_1_SAR_CSR3 |= ADC_SAR_1_SAR_EN_RESVDA_EN;
                ADC_SAR_1_SetRef(ADC_SAR_1__VSSA_TO_VDDA);
                break;
            case ADC_SAR_1__VSSA_TO_VDAC:
                ADC_SAR_1_SetRef(ADC_SAR_1__VSSA_TO_VDDA);
                break;

            case ADC_SAR_1__VNEG_VREF_DIFF:
                ADC_SAR_1_SAR_CSR3 |= ADC_SAR_1_SAR_EN_CP_EN;         /* Enable charge pump*/
                ADC_SAR_1_SAR_CSR3 |= ADC_SAR_1_SAR_EN_BUF_VCM_EN;    /* Enable VCM reference buffer*/
                ADC_SAR_1_SetRef(ADC_SAR_1_DEFAULT_RANGE);
                break;

            case ADC_SAR_1__VNEG_VDDA_DIFF:
                ADC_SAR_1_SAR_CSR3 |= ADC_SAR_1_SAR_EN_CP_EN;         /* Enable charge pump*/
                ADC_SAR_1_SAR_CSR3 |= ADC_SAR_1_SAR_EN_BUF_VCM_EN;    /* Enable VCM reference buffer*/
                ADC_SAR_1_SetRef(ADC_SAR_1__VSSA_TO_VDDA);
                break;

            case ADC_SAR_1__VNEG_VDDA_2_DIFF:
                 /* Set bit for VDD/2 mode*/
                ADC_SAR_1_SAR_CSR3 |= ADC_SAR_1_SAR_EN_RESVDA_EN;
                ADC_SAR_1_SAR_CSR3 |= ADC_SAR_1_SAR_EN_CP_EN;         /* Enable charge pump*/
                ADC_SAR_1_SAR_CSR3 |= ADC_SAR_1_SAR_EN_BUF_VCM_EN;    /* Enable VCM reference buffer*/
                ADC_SAR_1_SetRef(ADC_SAR_1__VSSA_TO_VDDA);
                break;
            case ADC_SAR_1__VNEG_VDAC_DIFF:
                ADC_SAR_1_SetRef(ADC_SAR_1__VSSA_TO_VDDA);
                break;

            default:
                /* if default case is hit, invalid argument was passed.*/
                break;
         }

    } /* End ADC_SAR_1_initVar */

    /*ADC_SAR_1_SAR_TR0 = ADC_SAR_1_SAR_CAP_TRIM_4;*/ /*Set attenuation capacitor*/

    /* This is only valid if there is an internal clock */
    #if(ADC_SAR_1_DEFAULT_INTERNAL_CLK)
        ADC_SAR_1_PWRMGR_CLK |= ADC_SAR_1_ACT_PWR_CLK_EN;
        ADC_SAR_1_theACLK_Enable();
    #endif /* End ADC_SAR_1_DEFAULT_INTERNAL_CLK */

    /* Enable clock for SAR ADC*/
    ADC_SAR_1_SAR_CLK |= ADC_SAR_1_SAR_MX_CLK_EN;

     /* Enable power for ADC */
    ADC_SAR_1_PWRMGR_SAR |= ADC_SAR_1_ACT_PWR_SAR_EN;
    
    /* Clear a pending interrupt */
    CyIntClearPending(ADC_SAR_1_INTC_NUMBER);
}


/*******************************************************************************
* Function Name: ADC_SAR_1_SetRef
********************************************************************************
*
* Summary:
*   Sets reference for ADC
*
* Parameters:
*  refMode: Reference configuration.
*
* Return:
*  void
*
*******************************************************************************/
void ADC_SAR_1_SetRef(int8 refMode)
{
    uint8 tmpReg;
    if(refMode == ADC_SAR_1__VSSA_TO_VDDA)
    {
        /* Use internal reference*/
        tmpReg = ADC_SAR_1_SAR_REF_S3_LSB_EN | ADC_SAR_1_SAR_REF_S4_LSB_EN;
        /*tmpReg = ADC_SAR_1_SAR_REF_S4_LSB_EN | ADC_SAR_1_SAR_REF_S7_LSB_EN;*/   /*IROS need update*/
        ADC_SAR_1_SAR_CSR3 |= ADC_SAR_1_SAR_EN_BUF_VREF_EN;    /* Enable Int Ref Amp*/
    }
    else
    {
        switch (ADC_SAR_1_DEFAULT_REFERENCE)
        {
            case ADC_SAR_1__INT_REF_NOT_BYPASSED:
                tmpReg = ADC_SAR_1_SAR_REF_S3_LSB_EN | ADC_SAR_1_SAR_REF_S4_LSB_EN;
                ADC_SAR_1_SAR_CSR3 |= ADC_SAR_1_SAR_EN_BUF_VREF_EN; /* Enable Int Ref Amp*/
                break;
            case ADC_SAR_1__INT_REF_BYPASS:
                tmpReg = ADC_SAR_1_SAR_REF_S2_LSB_EN | 
                         ADC_SAR_1_SAR_REF_S3_LSB_EN | 
                         ADC_SAR_1_SAR_REF_S4_LSB_EN;
                ADC_SAR_1_SAR_CSR3 |= ADC_SAR_1_SAR_EN_BUF_VREF_EN; /* Enable Int Ref Amp*/
                //ADC_SAR_1_SAR_CSR3 |= ADC_SAR_1_SAR_EN_BUF_VCM_EN;  /* Enable VCM Ref Amp*/
                break;
            case ADC_SAR_1__EXT_REF:
                tmpReg = ADC_SAR_1_SAR_REF_S2_LSB_EN;
                ADC_SAR_1_SAR_CSR3 &= ~ADC_SAR_1_SAR_EN_BUF_VREF_EN; /* Disable Int Ref Amp*/
                break;
            default:
                /* if default case is hit, invalid argument was passed.*/
                break;
         }
     }
    ADC_SAR_1_SAR_CSR6 = tmpReg;
    ADC_SAR_1_SAR_CSR7 = ADC_SAR_1_SAR_REF_S_MSB_DIS;

 }


/*******************************************************************************
* Function Name: ADC_SAR_1_Stop
********************************************************************************
*
* Summary:
*  Stops and powers the SAR ADC component off.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void ADC_SAR_1_Stop(void)
{
    /* Stop all conversions */
    ADC_SAR_1_SAR_CSR0 &= ~ADC_SAR_1_SAR_SOF_START_CONV;

         /* Disable power for ADC */
    ADC_SAR_1_PWRMGR_SAR &= ~ADC_SAR_1_ACT_PWR_SAR_EN;

    /* This is only valid if there is an internal clock */
    #if(ADC_SAR_1_DEFAULT_INTERNAL_CLK)
        ADC_SAR_1_PWRMGR_CLK &= ~ADC_SAR_1_ACT_PWR_CLK_EN;
        ADC_SAR_1_theACLK_Disable();
    #endif /* End ADC_SAR_1_DEFAULT_INTERNAL_CLK */

}


/*******************************************************************************
* Function Name: ADC_SAR_1_IRQ_Enable
********************************************************************************
* Summary:
*   Enables the interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void ADC_SAR_1_IRQ_Enable(void)
{
    /* Enable the general interrupt. */
    CyIntEnable(ADC_SAR_1_INTC_NUMBER);
}


/*******************************************************************************
* Function Name: ADC_SAR_1_IRQ_Disable
********************************************************************************
* Summary:
*   Disables the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void ADC_SAR_1_IRQ_Disable(void)
{
    /* Disable the general interrupt. */
    CyIntDisable(ADC_SAR_1_INTC_NUMBER);
}


/*******************************************************************************
* Function Name: ADC_SAR_1_SetPower
********************************************************************************
*
* Summary:
*  Sets the Power mode.
*
* Parameters:
*  power:  Power setting for ADC
*  0 ->    Normal
*  1 ->    Half power
*  2 ->    1/3rd power
*  3 ->    Quarter power.
*
* Return:
*  void
*
*******************************************************************************/
void ADC_SAR_1_SetPower(uint8 power)
{
    uint8 tmpReg;

    /* mask off invalid power settings */
    power &= ~ADC_SAR_1_SAR_API_POWER_MASK;

    /* Set Power parameter  */
    tmpReg = ADC_SAR_1_SAR_CSR0 & ~ADC_SAR_1_SAR_POWER_MASK;
    tmpReg |= (power << ADC_SAR_1_SAR_POWER_SHIFT);
    ADC_SAR_1_SAR_CSR0 = tmpReg;
}


/*******************************************************************************
* Function Name: ADC_SAR_1_SetResolution
********************************************************************************
*
* Summary:
*  Sets the Relution of the SAR.
*
* Parameters:
*  resolution:
*  12 ->    RES12
*  10 ->    RES10
*  8  ->    RES8
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*  This function calls CalcGain procedure to calculate new gain based on 
*  resolution 
*******************************************************************************/
void ADC_SAR_1_SetResolution(uint8 resolution)
{
    uint8 tmpReg;

    /*Set SAR ADC resolution ADC */
    switch (resolution)
    {
        case ADC_SAR_1__BITS_12:
            tmpReg = ADC_SAR_1_SAR_RESOLUTION_12BIT;
            break;
        case ADC_SAR_1__BITS_10:
            tmpReg = ADC_SAR_1_SAR_RESOLUTION_10BIT;
            break;
        case ADC_SAR_1__BITS_8:
            tmpReg = ADC_SAR_1_SAR_RESOLUTION_8BIT;
            break;
        default:
            /* if default case is hit, invalid argument was passed.*/
            break;
    }
    
     tmpReg |= ADC_SAR_1_SAR_SAMPLE_WIDTH;   /* 17 conversion cycles @ 12bits + 1 gap*/
    ADC_SAR_1_SAR_CSR2 = tmpReg;
    
     /* Calculate gain for convert counts to volts */
    ADC_SAR_1_CalcGain(resolution);

}


/*******************************************************************************
* Function Name: ADC_SAR_1_StartConvert
********************************************************************************
*
* Summary:
*  Starts ADC conversion using the given mode.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Theory:
*  Forces the ADC to initiate a conversion. In Free Running mode, the ADC will 
*  run continuously. In a triggered mode the function also acts as a software
*  version of the SOC. Here every conversion has to be triggered by the routine. 
*  This writes into the SOC bit in SAR_CTRL reg.
*
* Side Effects:
*  
*******************************************************************************/
void ADC_SAR_1_StartConvert(void)
{
    if(ADC_SAR_1_DEFAULT_CONV_MODE)                /* If triggered mode */
    {
        ADC_SAR_1_SAR_CSR0 &= ~ADC_SAR_1_SAR_MX_SOF_UDB;   /* source: SOF bit */
    }
    
    /* Start the conversion */
    ADC_SAR_1_SAR_CSR0 |= ADC_SAR_1_SAR_SOF_START_CONV;

}


/*******************************************************************************
* Function Name: ADC_SAR_1_StopConvert
********************************************************************************
*
* Summary:
*  Stops ADC conversion using the given mode.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Theory:
*  Stops ADC conversion in Free Running mode. 
*  In a triggered mode the function set a software version of the SOC to low level
*  and return SOF source to hardware SOF signal.
*  This writes into the SOC bit in SAR_CTRL reg.
*
* Side Effects:
*  
*******************************************************************************/
void ADC_SAR_1_StopConvert(void)
{
    /* Stop all conversions */
    ADC_SAR_1_SAR_CSR0 &= ~ADC_SAR_1_SAR_SOF_START_CONV;

    if(ADC_SAR_1_DEFAULT_CONV_MODE)                /* If triggered mode */
    {
        /* Return source to UDB for hardware SOF signal */
        ADC_SAR_1_SAR_CSR0 |= ADC_SAR_1_SAR_MX_SOF_UDB;    /* source: UDB */
    }
    
}


/*******************************************************************************
* Function Name: ADC_SAR_1_IsEndConversion
********************************************************************************
*
* Summary:
*  Queries the ADC to see if conversion is complete
*
* Parameters:
*  retMode:  Wait mode,
*   0 if return with answer imediately.
*   1 if wait until conversion is complete, then return.
*
* Return:
*  (uint8)  0 =>  Conversion not complete.
*           1 =>  Conversion complete.
*
*******************************************************************************/
uint8 ADC_SAR_1_IsEndConversion(uint8 retMode)
{
    uint8 status;

    do
    {
        status = ADC_SAR_1_SAR_CSR1 & ADC_SAR_1_SAR_EOF_1;
    } while ((status != ADC_SAR_1_SAR_EOF_1) && (retMode == ADC_SAR_1_WAIT_FOR_RESULT));

    return(status);
}


/*******************************************************************************
* Function Name: ADC_SAR_1_GetResult8
********************************************************************************
*
* Summary:
*  Returns an 8-bit result or the LSB of the last conversion.
*
* Parameters:
*  void
*
* Return:
*  ADC result.
*
*******************************************************************************/
int8 ADC_SAR_1_GetResult8( void )
{
    return( ADC_SAR_1_SAR_WRK0 );
}


/*******************************************************************************
* Function Name: ADC_SAR_1_GetResult16
********************************************************************************
*
* Summary:
*  Gets the data available in the SAR DATA registers.
*
* Parameters:
*  void
*
* Return:
*  ADC result. WORD value which has the converted 12bits.
*
*******************************************************************************/
int16 ADC_SAR_1_GetResult16( void )
{
    return( (ADC_SAR_1_SAR_WRK1 << 8 ) | ADC_SAR_1_SAR_WRK0 );
}


/*******************************************************************************
* Function Name: ADC_SAR_1_SetOffset
********************************************************************************
*
* Summary:
*  This function sets the offset for voltage readings.
*
* Parameters:
*  int16  offset  Offset in counts
*
* Return:
*  void
*
*******************************************************************************/
void ADC_SAR_1_SetOffset(int16 offset)
{

    ADC_SAR_1_Offset = offset;
}


/*******************************************************************************
* Function Name: ADC_SAR_1_CalcGain
********************************************************************************
*
* Summary:
*  This function calculates the ADC gain in counts per volt.
*
* Parameters:
*  uint8: resolution
*
* Return:
*  void
*
*******************************************************************************/
void ADC_SAR_1_CalcGain( uint8 resolution )
{
    uint32 counts = 0xFFF; /*default 12 bits*/
    uint16 diff_zero = 0x800;
    
    if(resolution == ADC_SAR_1__BITS_10)
    {
        counts >>= 2;
        diff_zero >>= 2;
    }
    if(resolution == ADC_SAR_1__BITS_8)
    {
        counts >>= 4;
        diff_zero >>= 4;
    }
    counts *= 1000; /* To avoid float point arithmetic*/

        switch (ADC_SAR_1_DEFAULT_RANGE)
        {   /*TODO: use float point when it will be available*/
            case ADC_SAR_1__VSS_TO_VREF:
                ADC_SAR_1_CountsPerVolt = counts / ADC_SAR_1_DEFAULT_REF_VOLTAGE_MV / 2;
                ADC_SAR_1_Offset = 0;
                break;

            case ADC_SAR_1__VSSA_TO_VDDA:
                ADC_SAR_1_CountsPerVolt = counts / ADC_SAR_1_DEFAULT_REF_VOLTAGE_MV;
                ADC_SAR_1_Offset = 0;
                break;

            case ADC_SAR_1__VSSA_TO_VDAC:
                ADC_SAR_1_CountsPerVolt = counts / ADC_SAR_1_DEFAULT_REF_VOLTAGE_MV / 2;
                ADC_SAR_1_Offset = 0;
                break;

            case ADC_SAR_1__VNEG_VREF_DIFF:
                ADC_SAR_1_CountsPerVolt = counts / ADC_SAR_1_DEFAULT_REF_VOLTAGE_MV / 2;
                ADC_SAR_1_Offset = diff_zero;
                break;
                
            case ADC_SAR_1__VNEG_VDDA_DIFF:
                ADC_SAR_1_CountsPerVolt = counts / ADC_SAR_1_DEFAULT_REF_VOLTAGE_MV / 2;
                ADC_SAR_1_Offset = diff_zero;
                break;

            case ADC_SAR_1__VNEG_VDDA_2_DIFF:
                ADC_SAR_1_CountsPerVolt = counts / ADC_SAR_1_DEFAULT_REF_VOLTAGE_MV;
                ADC_SAR_1_Offset = diff_zero;
                break;

            case ADC_SAR_1__VNEG_VDAC_DIFF:
                ADC_SAR_1_CountsPerVolt = counts / ADC_SAR_1_DEFAULT_REF_VOLTAGE_MV / 2;
                ADC_SAR_1_Offset = diff_zero;
                break;

            default:
                /* if default case is hit, invalid argument was passed.*/
                break;
         }
}


/*******************************************************************************
* Function Name: ADC_SAR_1_SetGain
********************************************************************************
*
* Summary:
*  This function sets the ADC gain in counts per volt.
*
* Parameters:
*  int16  adcGain  counts per volt
*
* Return:
*  void
*
*******************************************************************************/
void ADC_SAR_1_SetGain(int16 adcGain)
{

    ADC_SAR_1_CountsPerVolt = adcGain;
}


/*******************************************************************************
* Function Name: ADC_SAR_1_CountsTo_mVolts
********************************************************************************
*
* Summary:
*  This function converts ADC counts to mVolts
*
* Parameters:
*  int16  adcCounts   Reading from ADC.
*
* Return:
*  int16  Result in mVolts
*
*******************************************************************************/
int16 ADC_SAR_1_CountsTo_mVolts( int16 adcCounts)
{

    int16 mVolts = 0;

    /* Subtract ADC offset */
    adcCounts -= ADC_SAR_1_Offset;

    mVolts = ( (int32)adcCounts * 1000 ) / ADC_SAR_1_CountsPerVolt ;

    return( mVolts );
}


/* [] END OF FILE */
