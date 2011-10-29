/*******************************************************************************
* File Name: Volume_ADC.c
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
#include "Volume_ADC.h"

#if(Volume_ADC_DEFAULT_INTERNAL_CLK)
    #include "Volume_ADC_theACLK.h"
#endif /* End Volume_ADC_DEFAULT_INTERNAL_CLK */

uint8 Volume_ADC_initVar = 0;
int16 Volume_ADC_Offset = 0;
int16 Volume_ADC_CountsPerVolt;   // Gain compensation

void Volume_ADC_SetRef(int8 refMode);
void Volume_ADC_CalcGain(uint8 resolution);


/*******************************************************************************
* Function Name: Volume_ADC_Start
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
void Volume_ADC_Start(void)
{
    uint8 tmpReg;

    /* If not Initialized then initialize all required hardware and software */
    if(Volume_ADC_initVar == 0)
    {
        Volume_ADC_initVar = 1;
        /* This is only valid if there is an internal clock */
        #if(Volume_ADC_DEFAULT_INTERNAL_CLK)
            Volume_ADC_theACLK_SetMode(CYCLK_DUTY);
        #endif /* End Volume_ADC_DEFAULT_INTERNAL_CLK */

        /* Start and set interrupt vector */
        CyIntSetPriority(Volume_ADC_INTC_NUMBER, Volume_ADC_INTC_PRIOR_NUMBER);
        CyIntSetVector(Volume_ADC_INTC_NUMBER, Volume_ADC_ISR );

        /* default CSR0=0 */
        tmpReg = Volume_ADC_SAR_CSR0;

        /* Set Power parameter  */
        tmpReg |= (Volume_ADC_DEFAULT_POWER << Volume_ADC_SAR_POWER_SHIFT);

        /* Clear DAC value at beginning of sampling */
        tmpReg |= Volume_ADC_SAR_HIZ_CLEAR;

        /*Set Convertion mode */
        if(Volume_ADC_DEFAULT_CONV_MODE)                /* If triggered mode */
        {
            tmpReg |= Volume_ADC_SAR_MX_SOF_UDB;            /* source: UDB */
            tmpReg |= Volume_ADC_SAR_SOF_MODE_EDGE;        /* Set edge-sensitive sof source */
         }
        Volume_ADC_SAR_CSR0 = tmpReg;

        /* Enable IRQ mode*/
        Volume_ADC_SAR_CSR1 |= Volume_ADC_SAR_IRQ_MASK_EN | Volume_ADC_SAR_IRQ_MODE_EDGE;
        
        /*Set SAR ADC resolution ADC */
        Volume_ADC_SetResolution(Volume_ADC_DEFAULT_RESOLUTION);

        /*Sets input range of the ADC*/
        switch (Volume_ADC_DEFAULT_RANGE)
        {
            case Volume_ADC__VSS_TO_VREF:
                Volume_ADC_SetRef(Volume_ADC_DEFAULT_RANGE);
                break;

            case Volume_ADC__VSSA_TO_VDDA:
                /* Set bit for VDD/2 mode */
                Volume_ADC_SAR_CSR3 |= Volume_ADC_SAR_EN_RESVDA_EN;
                Volume_ADC_SetRef(Volume_ADC__VSSA_TO_VDDA);
                break;
            case Volume_ADC__VSSA_TO_VDAC:
                Volume_ADC_SetRef(Volume_ADC__VSSA_TO_VDDA);
                break;

            case Volume_ADC__VNEG_VREF_DIFF:
                Volume_ADC_SAR_CSR3 |= Volume_ADC_SAR_EN_CP_EN;         /* Enable charge pump*/
                Volume_ADC_SAR_CSR3 |= Volume_ADC_SAR_EN_BUF_VCM_EN;    /* Enable VCM reference buffer*/
                Volume_ADC_SetRef(Volume_ADC_DEFAULT_RANGE);
                break;

            case Volume_ADC__VNEG_VDDA_DIFF:
                Volume_ADC_SAR_CSR3 |= Volume_ADC_SAR_EN_CP_EN;         /* Enable charge pump*/
                Volume_ADC_SAR_CSR3 |= Volume_ADC_SAR_EN_BUF_VCM_EN;    /* Enable VCM reference buffer*/
                Volume_ADC_SetRef(Volume_ADC__VSSA_TO_VDDA);
                break;

            case Volume_ADC__VNEG_VDDA_2_DIFF:
                 /* Set bit for VDD/2 mode*/
                Volume_ADC_SAR_CSR3 |= Volume_ADC_SAR_EN_RESVDA_EN;
                Volume_ADC_SAR_CSR3 |= Volume_ADC_SAR_EN_CP_EN;         /* Enable charge pump*/
                Volume_ADC_SAR_CSR3 |= Volume_ADC_SAR_EN_BUF_VCM_EN;    /* Enable VCM reference buffer*/
                Volume_ADC_SetRef(Volume_ADC__VSSA_TO_VDDA);
                break;
            case Volume_ADC__VNEG_VDAC_DIFF:
                Volume_ADC_SetRef(Volume_ADC__VSSA_TO_VDDA);
                break;

            default:
                /* if default case is hit, invalid argument was passed.*/
                break;
         }

    } /* End Volume_ADC_initVar */

    /*Volume_ADC_SAR_TR0 = Volume_ADC_SAR_CAP_TRIM_4;*/ /*Set attenuation capacitor*/

    /* This is only valid if there is an internal clock */
    #if(Volume_ADC_DEFAULT_INTERNAL_CLK)
        Volume_ADC_PWRMGR_CLK |= Volume_ADC_ACT_PWR_CLK_EN;
        Volume_ADC_theACLK_Enable();
    #endif /* End Volume_ADC_DEFAULT_INTERNAL_CLK */

    /* Enable clock for SAR ADC*/
    Volume_ADC_SAR_CLK |= Volume_ADC_SAR_MX_CLK_EN;

     /* Enable power for ADC */
    Volume_ADC_PWRMGR_SAR |= Volume_ADC_ACT_PWR_SAR_EN;
    
    /* Clear a pending interrupt */
    CyIntClearPending(Volume_ADC_INTC_NUMBER);
}


/*******************************************************************************
* Function Name: Volume_ADC_SetRef
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
void Volume_ADC_SetRef(int8 refMode)
{
    uint8 tmpReg;
    if(refMode == Volume_ADC__VSSA_TO_VDDA)
    {
        /* Use internal reference*/
        tmpReg = Volume_ADC_SAR_REF_S3_LSB_EN | Volume_ADC_SAR_REF_S4_LSB_EN;
        /*tmpReg = Volume_ADC_SAR_REF_S4_LSB_EN | Volume_ADC_SAR_REF_S7_LSB_EN;*/   /*IROS need update*/
        Volume_ADC_SAR_CSR3 |= Volume_ADC_SAR_EN_BUF_VREF_EN;    /* Enable Int Ref Amp*/
    }
    else
    {
        switch (Volume_ADC_DEFAULT_REFERENCE)
        {
            case Volume_ADC__INT_REF_NOT_BYPASSED:
                tmpReg = Volume_ADC_SAR_REF_S3_LSB_EN | Volume_ADC_SAR_REF_S4_LSB_EN;
                Volume_ADC_SAR_CSR3 |= Volume_ADC_SAR_EN_BUF_VREF_EN; /* Enable Int Ref Amp*/
                break;
            case Volume_ADC__INT_REF_BYPASS:
                tmpReg = Volume_ADC_SAR_REF_S2_LSB_EN | 
                         Volume_ADC_SAR_REF_S3_LSB_EN | 
                         Volume_ADC_SAR_REF_S4_LSB_EN;
                Volume_ADC_SAR_CSR3 |= Volume_ADC_SAR_EN_BUF_VREF_EN; /* Enable Int Ref Amp*/
                //Volume_ADC_SAR_CSR3 |= Volume_ADC_SAR_EN_BUF_VCM_EN;  /* Enable VCM Ref Amp*/
                break;
            case Volume_ADC__EXT_REF:
                tmpReg = Volume_ADC_SAR_REF_S2_LSB_EN;
                Volume_ADC_SAR_CSR3 &= ~Volume_ADC_SAR_EN_BUF_VREF_EN; /* Disable Int Ref Amp*/
                break;
            default:
                /* if default case is hit, invalid argument was passed.*/
                break;
         }
     }
    Volume_ADC_SAR_CSR6 = tmpReg;
    Volume_ADC_SAR_CSR7 = Volume_ADC_SAR_REF_S_MSB_DIS;

 }


/*******************************************************************************
* Function Name: Volume_ADC_Stop
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
void Volume_ADC_Stop(void)
{
    /* Stop all conversions */
    Volume_ADC_SAR_CSR0 &= ~Volume_ADC_SAR_SOF_START_CONV;

         /* Disable power for ADC */
    Volume_ADC_PWRMGR_SAR &= ~Volume_ADC_ACT_PWR_SAR_EN;

    /* This is only valid if there is an internal clock */
    #if(Volume_ADC_DEFAULT_INTERNAL_CLK)
        Volume_ADC_PWRMGR_CLK &= ~Volume_ADC_ACT_PWR_CLK_EN;
        Volume_ADC_theACLK_Disable();
    #endif /* End Volume_ADC_DEFAULT_INTERNAL_CLK */

}


/*******************************************************************************
* Function Name: Volume_ADC_IRQ_Enable
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
void Volume_ADC_IRQ_Enable(void)
{
    /* Enable the general interrupt. */
    CyIntEnable(Volume_ADC_INTC_NUMBER);
}


/*******************************************************************************
* Function Name: Volume_ADC_IRQ_Disable
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
void Volume_ADC_IRQ_Disable(void)
{
    /* Disable the general interrupt. */
    CyIntDisable(Volume_ADC_INTC_NUMBER);
}


/*******************************************************************************
* Function Name: Volume_ADC_SetPower
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
void Volume_ADC_SetPower(uint8 power)
{
    uint8 tmpReg;

    /* mask off invalid power settings */
    power &= ~Volume_ADC_SAR_API_POWER_MASK;

    /* Set Power parameter  */
    tmpReg = Volume_ADC_SAR_CSR0 & ~Volume_ADC_SAR_POWER_MASK;
    tmpReg |= (power << Volume_ADC_SAR_POWER_SHIFT);
    Volume_ADC_SAR_CSR0 = tmpReg;
}


/*******************************************************************************
* Function Name: Volume_ADC_SetResolution
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
void Volume_ADC_SetResolution(uint8 resolution)
{
    uint8 tmpReg;

    /*Set SAR ADC resolution ADC */
    switch (resolution)
    {
        case Volume_ADC__BITS_12:
            tmpReg = Volume_ADC_SAR_RESOLUTION_12BIT;
            break;
        case Volume_ADC__BITS_10:
            tmpReg = Volume_ADC_SAR_RESOLUTION_10BIT;
            break;
        case Volume_ADC__BITS_8:
            tmpReg = Volume_ADC_SAR_RESOLUTION_8BIT;
            break;
        default:
            /* if default case is hit, invalid argument was passed.*/
            break;
    }
    
     tmpReg |= Volume_ADC_SAR_SAMPLE_WIDTH;   /* 17 conversion cycles @ 12bits + 1 gap*/
    Volume_ADC_SAR_CSR2 = tmpReg;
    
     /* Calculate gain for convert counts to volts */
    Volume_ADC_CalcGain(resolution);

}


/*******************************************************************************
* Function Name: Volume_ADC_StartConvert
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
void Volume_ADC_StartConvert(void)
{
    if(Volume_ADC_DEFAULT_CONV_MODE)                /* If triggered mode */
    {
        Volume_ADC_SAR_CSR0 &= ~Volume_ADC_SAR_MX_SOF_UDB;   /* source: SOF bit */
    }
    
    /* Start the conversion */
    Volume_ADC_SAR_CSR0 |= Volume_ADC_SAR_SOF_START_CONV;

}


/*******************************************************************************
* Function Name: Volume_ADC_StopConvert
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
void Volume_ADC_StopConvert(void)
{
    /* Stop all conversions */
    Volume_ADC_SAR_CSR0 &= ~Volume_ADC_SAR_SOF_START_CONV;

    if(Volume_ADC_DEFAULT_CONV_MODE)                /* If triggered mode */
    {
        /* Return source to UDB for hardware SOF signal */
        Volume_ADC_SAR_CSR0 |= Volume_ADC_SAR_MX_SOF_UDB;    /* source: UDB */
    }
    
}


/*******************************************************************************
* Function Name: Volume_ADC_IsEndConversion
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
uint8 Volume_ADC_IsEndConversion(uint8 retMode)
{
    uint8 status;

    do
    {
        status = Volume_ADC_SAR_CSR1 & Volume_ADC_SAR_EOF_1;
    } while ((status != Volume_ADC_SAR_EOF_1) && (retMode == Volume_ADC_WAIT_FOR_RESULT));

    return(status);
}


/*******************************************************************************
* Function Name: Volume_ADC_GetResult8
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
int8 Volume_ADC_GetResult8( void )
{
    return( Volume_ADC_SAR_WRK0 );
}


/*******************************************************************************
* Function Name: Volume_ADC_GetResult16
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
int16 Volume_ADC_GetResult16( void )
{
    return( (Volume_ADC_SAR_WRK1 << 8 ) | Volume_ADC_SAR_WRK0 );
}


/*******************************************************************************
* Function Name: Volume_ADC_SetOffset
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
void Volume_ADC_SetOffset(int16 offset)
{

    Volume_ADC_Offset = offset;
}


/*******************************************************************************
* Function Name: Volume_ADC_CalcGain
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
void Volume_ADC_CalcGain( uint8 resolution )
{
    uint32 counts = 0xFFF; /*default 12 bits*/
    uint16 diff_zero = 0x800;
    
    if(resolution == Volume_ADC__BITS_10)
    {
        counts >>= 2;
        diff_zero >>= 2;
    }
    if(resolution == Volume_ADC__BITS_8)
    {
        counts >>= 4;
        diff_zero >>= 4;
    }
    counts *= 1000; /* To avoid float point arithmetic*/

        switch (Volume_ADC_DEFAULT_RANGE)
        {   /*TODO: use float point when it will be available*/
            case Volume_ADC__VSS_TO_VREF:
                Volume_ADC_CountsPerVolt = counts / Volume_ADC_DEFAULT_REF_VOLTAGE_MV / 2;
                Volume_ADC_Offset = 0;
                break;

            case Volume_ADC__VSSA_TO_VDDA:
                Volume_ADC_CountsPerVolt = counts / Volume_ADC_DEFAULT_REF_VOLTAGE_MV;
                Volume_ADC_Offset = 0;
                break;

            case Volume_ADC__VSSA_TO_VDAC:
                Volume_ADC_CountsPerVolt = counts / Volume_ADC_DEFAULT_REF_VOLTAGE_MV / 2;
                Volume_ADC_Offset = 0;
                break;

            case Volume_ADC__VNEG_VREF_DIFF:
                Volume_ADC_CountsPerVolt = counts / Volume_ADC_DEFAULT_REF_VOLTAGE_MV / 2;
                Volume_ADC_Offset = diff_zero;
                break;
                
            case Volume_ADC__VNEG_VDDA_DIFF:
                Volume_ADC_CountsPerVolt = counts / Volume_ADC_DEFAULT_REF_VOLTAGE_MV / 2;
                Volume_ADC_Offset = diff_zero;
                break;

            case Volume_ADC__VNEG_VDDA_2_DIFF:
                Volume_ADC_CountsPerVolt = counts / Volume_ADC_DEFAULT_REF_VOLTAGE_MV;
                Volume_ADC_Offset = diff_zero;
                break;

            case Volume_ADC__VNEG_VDAC_DIFF:
                Volume_ADC_CountsPerVolt = counts / Volume_ADC_DEFAULT_REF_VOLTAGE_MV / 2;
                Volume_ADC_Offset = diff_zero;
                break;

            default:
                /* if default case is hit, invalid argument was passed.*/
                break;
         }
}


/*******************************************************************************
* Function Name: Volume_ADC_SetGain
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
void Volume_ADC_SetGain(int16 adcGain)
{

    Volume_ADC_CountsPerVolt = adcGain;
}


/*******************************************************************************
* Function Name: Volume_ADC_CountsTo_mVolts
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
int16 Volume_ADC_CountsTo_mVolts( int16 adcCounts)
{

    int16 mVolts = 0;

    /* Subtract ADC offset */
    adcCounts -= Volume_ADC_Offset;

    mVolts = ( (int32)adcCounts * 1000 ) / Volume_ADC_CountsPerVolt ;

    return( mVolts );
}


/* [] END OF FILE */
