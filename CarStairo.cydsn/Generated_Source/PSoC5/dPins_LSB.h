/*******************************************************************************
* File Name: dPins_LSB.h  
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

#if !defined(CY_PINS_dPins_LSB_H) /* Pins dPins_LSB_H */
#define CY_PINS_dPins_LSB_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "dPins_LSB_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    dPins_LSB_Write(uint8 value);
void    dPins_LSB_SetDriveMode(uint8 mode);
uint8   dPins_LSB_ReadDataReg(void);
uint8   dPins_LSB_Read(void);
uint8   dPins_LSB_ClearInterrupt(void);

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define dPins_LSB_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define dPins_LSB_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define dPins_LSB_DM_RES_UP          PIN_DM_RES_UP
#define dPins_LSB_DM_RES_DWN         PIN_DM_RES_DWN
#define dPins_LSB_DM_OD_LO           PIN_DM_OD_LO
#define dPins_LSB_DM_OD_HI           PIN_DM_OD_HI
#define dPins_LSB_DM_STRONG          PIN_DM_STRONG
#define dPins_LSB_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define dPins_LSB_MASK               dPins_LSB__MASK
#define dPins_LSB_SHIFT              dPins_LSB__SHIFT
#define dPins_LSB_WIDTH              4u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define dPins_LSB_PS                     (* (reg8 *) dPins_LSB__PS)
/* Data Register */
#define dPins_LSB_DR                     (* (reg8 *) dPins_LSB__DR)
/* Port Number */
#define dPins_LSB_PRT_NUM                (* (reg8 *) dPins_LSB__PRT) 
/* Connect to Analog Globals */                                                  
#define dPins_LSB_AG                     (* (reg8 *) dPins_LSB__AG)                       
/* Analog MUX bux enable */
#define dPins_LSB_AMUX                   (* (reg8 *) dPins_LSB__AMUX) 
/* Bidirectional Enable */                                                        
#define dPins_LSB_BIE                    (* (reg8 *) dPins_LSB__BIE)
/* Bit-mask for Aliased Register Access */
#define dPins_LSB_BIT_MASK               (* (reg8 *) dPins_LSB__BIT_MASK)
/* Bypass Enable */
#define dPins_LSB_BYP                    (* (reg8 *) dPins_LSB__BYP)
/* Port wide control signals */                                                   
#define dPins_LSB_CTL                    (* (reg8 *) dPins_LSB__CTL)
/* Drive Modes */
#define dPins_LSB_DM0                    (* (reg8 *) dPins_LSB__DM0) 
#define dPins_LSB_DM1                    (* (reg8 *) dPins_LSB__DM1)
#define dPins_LSB_DM2                    (* (reg8 *) dPins_LSB__DM2) 
/* Input Buffer Disable Override */
#define dPins_LSB_INP_DIS                (* (reg8 *) dPins_LSB__INP_DIS)
/* LCD Common or Segment Drive */
#define dPins_LSB_LCD_COM_SEG            (* (reg8 *) dPins_LSB__LCD_COM_SEG)
/* Enable Segment LCD */
#define dPins_LSB_LCD_EN                 (* (reg8 *) dPins_LSB__LCD_EN)
/* Slew Rate Control */
#define dPins_LSB_SLW                    (* (reg8 *) dPins_LSB__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define dPins_LSB_PRTDSI__CAPS_SEL       (* (reg8 *) dPins_LSB__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define dPins_LSB_PRTDSI__DBL_SYNC_IN    (* (reg8 *) dPins_LSB__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define dPins_LSB_PRTDSI__OE_SEL0        (* (reg8 *) dPins_LSB__PRTDSI__OE_SEL0) 
#define dPins_LSB_PRTDSI__OE_SEL1        (* (reg8 *) dPins_LSB__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define dPins_LSB_PRTDSI__OUT_SEL0       (* (reg8 *) dPins_LSB__PRTDSI__OUT_SEL0) 
#define dPins_LSB_PRTDSI__OUT_SEL1       (* (reg8 *) dPins_LSB__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define dPins_LSB_PRTDSI__SYNC_OUT       (* (reg8 *) dPins_LSB__PRTDSI__SYNC_OUT) 


#if defined(dPins_LSB__INTSTAT)  /* Interrupt Registers */

    #define dPins_LSB_INTSTAT                (* (reg8 *) dPins_LSB__INTSTAT)
    #define dPins_LSB_SNAP                   (* (reg8 *) dPins_LSB__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins dPins_LSB_H */


/* [] END OF FILE */
