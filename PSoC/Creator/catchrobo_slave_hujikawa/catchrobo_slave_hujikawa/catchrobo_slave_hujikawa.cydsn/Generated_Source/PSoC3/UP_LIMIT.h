/*******************************************************************************
* File Name: UP_LIMIT.h  
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

#if !defined(CY_PINS_UP_LIMIT_H) /* Pins UP_LIMIT_H */
#define CY_PINS_UP_LIMIT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "UP_LIMIT_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    UP_LIMIT_Write(uint8 value) ;
void    UP_LIMIT_SetDriveMode(uint8 mode) ;
uint8   UP_LIMIT_ReadDataReg(void) ;
uint8   UP_LIMIT_Read(void) ;
uint8   UP_LIMIT_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define UP_LIMIT_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define UP_LIMIT_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define UP_LIMIT_DM_RES_UP          PIN_DM_RES_UP
#define UP_LIMIT_DM_RES_DWN         PIN_DM_RES_DWN
#define UP_LIMIT_DM_OD_LO           PIN_DM_OD_LO
#define UP_LIMIT_DM_OD_HI           PIN_DM_OD_HI
#define UP_LIMIT_DM_STRONG          PIN_DM_STRONG
#define UP_LIMIT_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define UP_LIMIT_MASK               UP_LIMIT__MASK
#define UP_LIMIT_SHIFT              UP_LIMIT__SHIFT
#define UP_LIMIT_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define UP_LIMIT_PS                     (* (reg8 *) UP_LIMIT__PS)
/* Data Register */
#define UP_LIMIT_DR                     (* (reg8 *) UP_LIMIT__DR)
/* Port Number */
#define UP_LIMIT_PRT_NUM                (* (reg8 *) UP_LIMIT__PRT) 
/* Connect to Analog Globals */                                                  
#define UP_LIMIT_AG                     (* (reg8 *) UP_LIMIT__AG)                       
/* Analog MUX bux enable */
#define UP_LIMIT_AMUX                   (* (reg8 *) UP_LIMIT__AMUX) 
/* Bidirectional Enable */                                                        
#define UP_LIMIT_BIE                    (* (reg8 *) UP_LIMIT__BIE)
/* Bit-mask for Aliased Register Access */
#define UP_LIMIT_BIT_MASK               (* (reg8 *) UP_LIMIT__BIT_MASK)
/* Bypass Enable */
#define UP_LIMIT_BYP                    (* (reg8 *) UP_LIMIT__BYP)
/* Port wide control signals */                                                   
#define UP_LIMIT_CTL                    (* (reg8 *) UP_LIMIT__CTL)
/* Drive Modes */
#define UP_LIMIT_DM0                    (* (reg8 *) UP_LIMIT__DM0) 
#define UP_LIMIT_DM1                    (* (reg8 *) UP_LIMIT__DM1)
#define UP_LIMIT_DM2                    (* (reg8 *) UP_LIMIT__DM2) 
/* Input Buffer Disable Override */
#define UP_LIMIT_INP_DIS                (* (reg8 *) UP_LIMIT__INP_DIS)
/* LCD Common or Segment Drive */
#define UP_LIMIT_LCD_COM_SEG            (* (reg8 *) UP_LIMIT__LCD_COM_SEG)
/* Enable Segment LCD */
#define UP_LIMIT_LCD_EN                 (* (reg8 *) UP_LIMIT__LCD_EN)
/* Slew Rate Control */
#define UP_LIMIT_SLW                    (* (reg8 *) UP_LIMIT__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define UP_LIMIT_PRTDSI__CAPS_SEL       (* (reg8 *) UP_LIMIT__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define UP_LIMIT_PRTDSI__DBL_SYNC_IN    (* (reg8 *) UP_LIMIT__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define UP_LIMIT_PRTDSI__OE_SEL0        (* (reg8 *) UP_LIMIT__PRTDSI__OE_SEL0) 
#define UP_LIMIT_PRTDSI__OE_SEL1        (* (reg8 *) UP_LIMIT__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define UP_LIMIT_PRTDSI__OUT_SEL0       (* (reg8 *) UP_LIMIT__PRTDSI__OUT_SEL0) 
#define UP_LIMIT_PRTDSI__OUT_SEL1       (* (reg8 *) UP_LIMIT__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define UP_LIMIT_PRTDSI__SYNC_OUT       (* (reg8 *) UP_LIMIT__PRTDSI__SYNC_OUT) 


#if defined(UP_LIMIT__INTSTAT)  /* Interrupt Registers */

    #define UP_LIMIT_INTSTAT                (* (reg8 *) UP_LIMIT__INTSTAT)
    #define UP_LIMIT_SNAP                   (* (reg8 *) UP_LIMIT__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins UP_LIMIT_H */


/* [] END OF FILE */
