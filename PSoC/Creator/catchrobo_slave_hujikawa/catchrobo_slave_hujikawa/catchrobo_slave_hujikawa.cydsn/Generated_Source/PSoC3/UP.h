/*******************************************************************************
* File Name: UP.h  
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

#if !defined(CY_PINS_UP_H) /* Pins UP_H */
#define CY_PINS_UP_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "UP_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    UP_Write(uint8 value) ;
void    UP_SetDriveMode(uint8 mode) ;
uint8   UP_ReadDataReg(void) ;
uint8   UP_Read(void) ;
uint8   UP_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define UP_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define UP_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define UP_DM_RES_UP          PIN_DM_RES_UP
#define UP_DM_RES_DWN         PIN_DM_RES_DWN
#define UP_DM_OD_LO           PIN_DM_OD_LO
#define UP_DM_OD_HI           PIN_DM_OD_HI
#define UP_DM_STRONG          PIN_DM_STRONG
#define UP_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define UP_MASK               UP__MASK
#define UP_SHIFT              UP__SHIFT
#define UP_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define UP_PS                     (* (reg8 *) UP__PS)
/* Data Register */
#define UP_DR                     (* (reg8 *) UP__DR)
/* Port Number */
#define UP_PRT_NUM                (* (reg8 *) UP__PRT) 
/* Connect to Analog Globals */                                                  
#define UP_AG                     (* (reg8 *) UP__AG)                       
/* Analog MUX bux enable */
#define UP_AMUX                   (* (reg8 *) UP__AMUX) 
/* Bidirectional Enable */                                                        
#define UP_BIE                    (* (reg8 *) UP__BIE)
/* Bit-mask for Aliased Register Access */
#define UP_BIT_MASK               (* (reg8 *) UP__BIT_MASK)
/* Bypass Enable */
#define UP_BYP                    (* (reg8 *) UP__BYP)
/* Port wide control signals */                                                   
#define UP_CTL                    (* (reg8 *) UP__CTL)
/* Drive Modes */
#define UP_DM0                    (* (reg8 *) UP__DM0) 
#define UP_DM1                    (* (reg8 *) UP__DM1)
#define UP_DM2                    (* (reg8 *) UP__DM2) 
/* Input Buffer Disable Override */
#define UP_INP_DIS                (* (reg8 *) UP__INP_DIS)
/* LCD Common or Segment Drive */
#define UP_LCD_COM_SEG            (* (reg8 *) UP__LCD_COM_SEG)
/* Enable Segment LCD */
#define UP_LCD_EN                 (* (reg8 *) UP__LCD_EN)
/* Slew Rate Control */
#define UP_SLW                    (* (reg8 *) UP__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define UP_PRTDSI__CAPS_SEL       (* (reg8 *) UP__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define UP_PRTDSI__DBL_SYNC_IN    (* (reg8 *) UP__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define UP_PRTDSI__OE_SEL0        (* (reg8 *) UP__PRTDSI__OE_SEL0) 
#define UP_PRTDSI__OE_SEL1        (* (reg8 *) UP__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define UP_PRTDSI__OUT_SEL0       (* (reg8 *) UP__PRTDSI__OUT_SEL0) 
#define UP_PRTDSI__OUT_SEL1       (* (reg8 *) UP__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define UP_PRTDSI__SYNC_OUT       (* (reg8 *) UP__PRTDSI__SYNC_OUT) 


#if defined(UP__INTSTAT)  /* Interrupt Registers */

    #define UP_INTSTAT                (* (reg8 *) UP__INTSTAT)
    #define UP_SNAP                   (* (reg8 *) UP__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins UP_H */


/* [] END OF FILE */
