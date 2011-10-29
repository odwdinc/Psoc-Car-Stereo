/*******************************************************************************
* File Name: reset.h  
* Version 1.0
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2009, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_CONTROL_REG_reset_H) /* CY_CONTROL_REG_reset_H */
#define CY_CONTROL_REG_reset_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*        Function Prototypes 		    
***************************************/    

void    reset_Write(uint8 control);
uint8   reset_Read(void);


/***************************************
*             Registers        
***************************************/

/* Control Register */
#define reset_Control		(* (reg8 *) reset_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_reset_H */


/* [] END OF FILE */
