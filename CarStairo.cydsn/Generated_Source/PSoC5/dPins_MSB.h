/*******************************************************************************
* File Name: dPins_MSB.h  
* Version 1.20
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

#if !defined(CY_PINS_dPins_MSB_H) /* Pins dPins_MSB_H */
#define CY_PINS_dPins_MSB_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "dPins_MSB_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    dPins_MSB_Write(uint8 value);
void    dPins_MSB_SetDriveMode(uint8 mode);
uint8   dPins_MSB_ReadDataReg(void);
uint8   dPins_MSB_Read(void);
uint8   dPins_MSB_ClearInterrupt(void);

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define dPins_MSB_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define dPins_MSB_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define dPins_MSB_DM_RES_UP          PIN_DM_RES_UP
#define dPins_MSB_DM_RES_DWN         PIN_DM_RES_DWN
#define dPins_MSB_DM_OD_LO           PIN_DM_OD_LO
#define dPins_MSB_DM_OD_HI           PIN_DM_OD_HI
#define dPins_MSB_DM_STRONG          PIN_DM_STRONG
#define dPins_MSB_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define dPins_MSB_MASK               dPins_MSB__MASK
#define dPins_MSB_SHIFT              dPins_MSB__SHIFT
#define dPins_MSB_WIDTH              4u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define dPins_MSB_PS                     (* (reg8 *) dPins_MSB__PS)
/* Data Register */
#define dPins_MSB_DR                     (* (reg8 *) dPins_MSB__DR)
/* Port Number */
#define dPins_MSB_PRT_NUM                (* (reg8 *) dPins_MSB__PRT) 
/* Connect to Analog Globals */                                                  
#define dPins_MSB_AG                     (* (reg8 *) dPins_MSB__AG)                       
/* Analog MUX bux enable */
#define dPins_MSB_AMUX                   (* (reg8 *) dPins_MSB__AMUX) 
/* Bidirectional Enable */                                                        
#define dPins_MSB_BIE                    (* (reg8 *) dPins_MSB__BIE)
/* Bit-mask for Aliased Register Access */
#define dPins_MSB_BIT_MASK               (* (reg8 *) dPins_MSB__BIT_MASK)
/* Bypass Enable */
#define dPins_MSB_BYP                    (* (reg8 *) dPins_MSB__BYP)
/* Port wide control signals */                                                   
#define dPins_MSB_CTL                    (* (reg8 *) dPins_MSB__CTL)
/* Drive Modes */
#define dPins_MSB_DM0                    (* (reg8 *) dPins_MSB__DM0) 
#define dPins_MSB_DM1                    (* (reg8 *) dPins_MSB__DM1)
#define dPins_MSB_DM2                    (* (reg8 *) dPins_MSB__DM2) 
/* Input Buffer Disable Override */
#define dPins_MSB_INP_DIS                (* (reg8 *) dPins_MSB__INP_DIS)
/* LCD Common or Segment Drive */
#define dPins_MSB_LCD_COM_SEG            (* (reg8 *) dPins_MSB__LCD_COM_SEG)
/* Enable Segment LCD */
#define dPins_MSB_LCD_EN                 (* (reg8 *) dPins_MSB__LCD_EN)
/* Slew Rate Control */
#define dPins_MSB_SLW                    (* (reg8 *) dPins_MSB__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define dPins_MSB_PRTDSI__CAPS_SEL       (* (reg8 *) dPins_MSB__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define dPins_MSB_PRTDSI__DBL_SYNC_IN    (* (reg8 *) dPins_MSB__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define dPins_MSB_PRTDSI__OE_SEL0        (* (reg8 *) dPins_MSB__PRTDSI__OE_SEL0) 
#define dPins_MSB_PRTDSI__OE_SEL1        (* (reg8 *) dPins_MSB__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define dPins_MSB_PRTDSI__OUT_SEL0       (* (reg8 *) dPins_MSB__PRTDSI__OUT_SEL0) 
#define dPins_MSB_PRTDSI__OUT_SEL1       (* (reg8 *) dPins_MSB__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define dPins_MSB_PRTDSI__SYNC_OUT       (* (reg8 *) dPins_MSB__PRTDSI__SYNC_OUT) 


#if defined(dPins_MSB__INTSTAT)  /* Interrupt Registers */

    #define dPins_MSB_INTSTAT                (* (reg8 *) dPins_MSB__INTSTAT)
    #define dPins_MSB_SNAP                   (* (reg8 *) dPins_MSB__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins dPins_MSB_H */


/* [] END OF FILE */
