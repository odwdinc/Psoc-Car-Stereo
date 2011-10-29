/*******************************************************************************
* File Name: dPins_MSB.c  
* Version 1.20
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
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
#include "dPins_MSB.h"


/*******************************************************************************
* Function Name: dPins_MSB_Write
********************************************************************************
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  void 
*  
*******************************************************************************/
void dPins_MSB_Write(uint8 value)
{
    uint8 staticBits = dPins_MSB_DR & ~dPins_MSB_MASK;
    dPins_MSB_DR = staticBits | ((value << dPins_MSB_SHIFT) & dPins_MSB_MASK);
}


/*******************************************************************************
* Function Name: dPins_MSB_SetDriveMode
********************************************************************************
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  void
*
*******************************************************************************/
void dPins_MSB_SetDriveMode(uint8 mode)
{
	CyPins_SetPinDriveMode(dPins_MSB_0, mode);
	CyPins_SetPinDriveMode(dPins_MSB_1, mode);
	CyPins_SetPinDriveMode(dPins_MSB_2, mode);
	CyPins_SetPinDriveMode(dPins_MSB_3, mode);
}


/*******************************************************************************
* Function Name: dPins_MSB_Read
********************************************************************************
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  void 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro dPins_MSB_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 dPins_MSB_Read(void)
{
    return (dPins_MSB_PS & dPins_MSB_MASK) >> dPins_MSB_SHIFT;
}


/*******************************************************************************
* Function Name: dPins_MSB_ReadDataReg
********************************************************************************
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  void 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 dPins_MSB_ReadDataReg(void)
{
    return (dPins_MSB_DR & dPins_MSB_MASK) >> dPins_MSB_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(dPins_MSB_INTSTAT) 

    /*******************************************************************************
    * Function Name: dPins_MSB_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  void 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 dPins_MSB_ClearInterrupt(void)
    {
        return (dPins_MSB_INTSTAT & dPins_MSB_MASK) >> dPins_MSB_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */ 
