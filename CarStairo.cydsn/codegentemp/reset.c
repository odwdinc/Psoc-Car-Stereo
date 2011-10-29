/*******************************************************************************
* File Name: reset.c  
* Version 1.0
*
* Description:
*  This file contains API to enable firmware control of a control register.
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
#include "reset.h"

#if !defined(reset_ctrl_reg__REMOVED) /* Check for removal by optimization */


/*******************************************************************************
* Function Name: reset_Write
********************************************************************************
* Summary:
*  Write a byte to a control register.
*
* Parameters:  
*  control:  The value to be assigned to the control register. 
*
* Return: 
*  void 
*  
*******************************************************************************/
void reset_Write(uint8 control)
{
	reset_Control = control;
}


/*******************************************************************************
* Function Name: reset_Read
********************************************************************************
* Summary:
*  Read the current value assigned to a control register.
*
* Parameters:  
*  void 
*
* Return: 
*  Returns the current value assigned to the control register
*  
*******************************************************************************/
uint8 reset_Read(void)
{
	return reset_Control;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */ 
