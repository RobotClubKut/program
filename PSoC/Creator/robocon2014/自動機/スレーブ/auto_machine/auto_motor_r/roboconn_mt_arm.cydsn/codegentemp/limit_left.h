/*******************************************************************************
* File Name: limit_left.h  
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

#if !defined(CY_PINS_limit_left_H) /* Pins limit_left_H */
#define CY_PINS_limit_left_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "limit_left_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    limit_left_Write(uint8 value) ;
void    limit_left_SetDriveMode(uint8 mode) ;
uint8   limit_left_ReadDataReg(void) ;
uint8   limit_left_Read(void) ;
uint8   limit_left_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define limit_left_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define limit_left_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define limit_left_DM_RES_UP          PIN_DM_RES_UP
#define limit_left_DM_RES_DWN         PIN_DM_RES_DWN
#define limit_left_DM_OD_LO           PIN_DM_OD_LO
#define limit_left_DM_OD_HI           PIN_DM_OD_HI
#define limit_left_DM_STRONG          PIN_DM_STRONG
#define limit_left_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define limit_left_MASK               limit_left__MASK
#define limit_left_SHIFT              limit_left__SHIFT
#define limit_left_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define limit_left_PS                     (* (reg8 *) limit_left__PS)
/* Data Register */
#define limit_left_DR                     (* (reg8 *) limit_left__DR)
/* Port Number */
#define limit_left_PRT_NUM                (* (reg8 *) limit_left__PRT) 
/* Connect to Analog Globals */                                                  
#define limit_left_AG                     (* (reg8 *) limit_left__AG)                       
/* Analog MUX bux enable */
#define limit_left_AMUX                   (* (reg8 *) limit_left__AMUX) 
/* Bidirectional Enable */                                                        
#define limit_left_BIE                    (* (reg8 *) limit_left__BIE)
/* Bit-mask for Aliased Register Access */
#define limit_left_BIT_MASK               (* (reg8 *) limit_left__BIT_MASK)
/* Bypass Enable */
#define limit_left_BYP                    (* (reg8 *) limit_left__BYP)
/* Port wide control signals */                                                   
#define limit_left_CTL                    (* (reg8 *) limit_left__CTL)
/* Drive Modes */
#define limit_left_DM0                    (* (reg8 *) limit_left__DM0) 
#define limit_left_DM1                    (* (reg8 *) limit_left__DM1)
#define limit_left_DM2                    (* (reg8 *) limit_left__DM2) 
/* Input Buffer Disable Override */
#define limit_left_INP_DIS                (* (reg8 *) limit_left__INP_DIS)
/* LCD Common or Segment Drive */
#define limit_left_LCD_COM_SEG            (* (reg8 *) limit_left__LCD_COM_SEG)
/* Enable Segment LCD */
#define limit_left_LCD_EN                 (* (reg8 *) limit_left__LCD_EN)
/* Slew Rate Control */
#define limit_left_SLW                    (* (reg8 *) limit_left__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define limit_left_PRTDSI__CAPS_SEL       (* (reg8 *) limit_left__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define limit_left_PRTDSI__DBL_SYNC_IN    (* (reg8 *) limit_left__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define limit_left_PRTDSI__OE_SEL0        (* (reg8 *) limit_left__PRTDSI__OE_SEL0) 
#define limit_left_PRTDSI__OE_SEL1        (* (reg8 *) limit_left__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define limit_left_PRTDSI__OUT_SEL0       (* (reg8 *) limit_left__PRTDSI__OUT_SEL0) 
#define limit_left_PRTDSI__OUT_SEL1       (* (reg8 *) limit_left__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define limit_left_PRTDSI__SYNC_OUT       (* (reg8 *) limit_left__PRTDSI__SYNC_OUT) 


#if defined(limit_left__INTSTAT)  /* Interrupt Registers */

    #define limit_left_INTSTAT                (* (reg8 *) limit_left__INTSTAT)
    #define limit_left_SNAP                   (* (reg8 *) limit_left__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins limit_left_H */


/* [] END OF FILE */
