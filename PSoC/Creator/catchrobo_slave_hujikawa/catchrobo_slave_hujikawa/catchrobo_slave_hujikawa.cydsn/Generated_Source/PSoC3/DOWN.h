/*******************************************************************************
* File Name: DOWN.h  
* Version 2.0
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_DOWN_H) /* Pins DOWN_H */
#define CY_PINS_DOWN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DOWN_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    DOWN_Write(uint8 value) ;
void    DOWN_SetDriveMode(uint8 mode) ;
uint8   DOWN_ReadDataReg(void) ;
uint8   DOWN_Read(void) ;
uint8   DOWN_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define DOWN_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define DOWN_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define DOWN_DM_RES_UP          PIN_DM_RES_UP
#define DOWN_DM_RES_DWN         PIN_DM_RES_DWN
#define DOWN_DM_OD_LO           PIN_DM_OD_LO
#define DOWN_DM_OD_HI           PIN_DM_OD_HI
#define DOWN_DM_STRONG          PIN_DM_STRONG
#define DOWN_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define DOWN_MASK               DOWN__MASK
#define DOWN_SHIFT              DOWN__SHIFT
#define DOWN_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DOWN_PS                     (* (reg8 *) DOWN__PS)
/* Data Register */
#define DOWN_DR                     (* (reg8 *) DOWN__DR)
/* Port Number */
#define DOWN_PRT_NUM                (* (reg8 *) DOWN__PRT) 
/* Connect to Analog Globals */                                                  
#define DOWN_AG                     (* (reg8 *) DOWN__AG)                       
/* Analog MUX bux enable */
#define DOWN_AMUX                   (* (reg8 *) DOWN__AMUX) 
/* Bidirectional Enable */                                                        
#define DOWN_BIE                    (* (reg8 *) DOWN__BIE)
/* Bit-mask for Aliased Register Access */
#define DOWN_BIT_MASK               (* (reg8 *) DOWN__BIT_MASK)
/* Bypass Enable */
#define DOWN_BYP                    (* (reg8 *) DOWN__BYP)
/* Port wide control signals */                                                   
#define DOWN_CTL                    (* (reg8 *) DOWN__CTL)
/* Drive Modes */
#define DOWN_DM0                    (* (reg8 *) DOWN__DM0) 
#define DOWN_DM1                    (* (reg8 *) DOWN__DM1)
#define DOWN_DM2                    (* (reg8 *) DOWN__DM2) 
/* Input Buffer Disable Override */
#define DOWN_INP_DIS                (* (reg8 *) DOWN__INP_DIS)
/* LCD Common or Segment Drive */
#define DOWN_LCD_COM_SEG            (* (reg8 *) DOWN__LCD_COM_SEG)
/* Enable Segment LCD */
#define DOWN_LCD_EN                 (* (reg8 *) DOWN__LCD_EN)
/* Slew Rate Control */
#define DOWN_SLW                    (* (reg8 *) DOWN__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DOWN_PRTDSI__CAPS_SEL       (* (reg8 *) DOWN__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DOWN_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DOWN__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DOWN_PRTDSI__OE_SEL0        (* (reg8 *) DOWN__PRTDSI__OE_SEL0) 
#define DOWN_PRTDSI__OE_SEL1        (* (reg8 *) DOWN__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DOWN_PRTDSI__OUT_SEL0       (* (reg8 *) DOWN__PRTDSI__OUT_SEL0) 
#define DOWN_PRTDSI__OUT_SEL1       (* (reg8 *) DOWN__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DOWN_PRTDSI__SYNC_OUT       (* (reg8 *) DOWN__PRTDSI__SYNC_OUT) 


#if defined(DOWN__INTSTAT)  /* Interrupt Registers */

    #define DOWN_INTSTAT                (* (reg8 *) DOWN__INTSTAT)
    #define DOWN_SNAP                   (* (reg8 *) DOWN__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins DOWN_H */


/* [] END OF FILE */
