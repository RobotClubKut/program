/*******************************************************************************
* File Name: Position_1.h  
* Version 1.90
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Position_1_H) /* Pins Position_1_H */
#define CY_PINS_Position_1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Position_1_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Position_1_Write(uint8 value) ;
void    Position_1_SetDriveMode(uint8 mode) ;
uint8   Position_1_ReadDataReg(void) ;
uint8   Position_1_Read(void) ;
uint8   Position_1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Position_1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Position_1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Position_1_DM_RES_UP          PIN_DM_RES_UP
#define Position_1_DM_RES_DWN         PIN_DM_RES_DWN
#define Position_1_DM_OD_LO           PIN_DM_OD_LO
#define Position_1_DM_OD_HI           PIN_DM_OD_HI
#define Position_1_DM_STRONG          PIN_DM_STRONG
#define Position_1_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Position_1_MASK               Position_1__MASK
#define Position_1_SHIFT              Position_1__SHIFT
#define Position_1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Position_1_PS                     (* (reg8 *) Position_1__PS)
/* Data Register */
#define Position_1_DR                     (* (reg8 *) Position_1__DR)
/* Port Number */
#define Position_1_PRT_NUM                (* (reg8 *) Position_1__PRT) 
/* Connect to Analog Globals */                                                  
#define Position_1_AG                     (* (reg8 *) Position_1__AG)                       
/* Analog MUX bux enable */
#define Position_1_AMUX                   (* (reg8 *) Position_1__AMUX) 
/* Bidirectional Enable */                                                        
#define Position_1_BIE                    (* (reg8 *) Position_1__BIE)
/* Bit-mask for Aliased Register Access */
#define Position_1_BIT_MASK               (* (reg8 *) Position_1__BIT_MASK)
/* Bypass Enable */
#define Position_1_BYP                    (* (reg8 *) Position_1__BYP)
/* Port wide control signals */                                                   
#define Position_1_CTL                    (* (reg8 *) Position_1__CTL)
/* Drive Modes */
#define Position_1_DM0                    (* (reg8 *) Position_1__DM0) 
#define Position_1_DM1                    (* (reg8 *) Position_1__DM1)
#define Position_1_DM2                    (* (reg8 *) Position_1__DM2) 
/* Input Buffer Disable Override */
#define Position_1_INP_DIS                (* (reg8 *) Position_1__INP_DIS)
/* LCD Common or Segment Drive */
#define Position_1_LCD_COM_SEG            (* (reg8 *) Position_1__LCD_COM_SEG)
/* Enable Segment LCD */
#define Position_1_LCD_EN                 (* (reg8 *) Position_1__LCD_EN)
/* Slew Rate Control */
#define Position_1_SLW                    (* (reg8 *) Position_1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Position_1_PRTDSI__CAPS_SEL       (* (reg8 *) Position_1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Position_1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Position_1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Position_1_PRTDSI__OE_SEL0        (* (reg8 *) Position_1__PRTDSI__OE_SEL0) 
#define Position_1_PRTDSI__OE_SEL1        (* (reg8 *) Position_1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Position_1_PRTDSI__OUT_SEL0       (* (reg8 *) Position_1__PRTDSI__OUT_SEL0) 
#define Position_1_PRTDSI__OUT_SEL1       (* (reg8 *) Position_1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Position_1_PRTDSI__SYNC_OUT       (* (reg8 *) Position_1__PRTDSI__SYNC_OUT) 


#if defined(Position_1__INTSTAT)  /* Interrupt Registers */

    #define Position_1_INTSTAT                (* (reg8 *) Position_1__INTSTAT)
    #define Position_1_SNAP                   (* (reg8 *) Position_1__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Position_1_H */


/* [] END OF FILE */
