/*******************************************************************************
* File Name: limit_right.h  
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

#if !defined(CY_PINS_limit_right_H) /* Pins limit_right_H */
#define CY_PINS_limit_right_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "limit_right_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    limit_right_Write(uint8 value) ;
void    limit_right_SetDriveMode(uint8 mode) ;
uint8   limit_right_ReadDataReg(void) ;
uint8   limit_right_Read(void) ;
uint8   limit_right_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define limit_right_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define limit_right_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define limit_right_DM_RES_UP          PIN_DM_RES_UP
#define limit_right_DM_RES_DWN         PIN_DM_RES_DWN
#define limit_right_DM_OD_LO           PIN_DM_OD_LO
#define limit_right_DM_OD_HI           PIN_DM_OD_HI
#define limit_right_DM_STRONG          PIN_DM_STRONG
#define limit_right_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define limit_right_MASK               limit_right__MASK
#define limit_right_SHIFT              limit_right__SHIFT
#define limit_right_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define limit_right_PS                     (* (reg8 *) limit_right__PS)
/* Data Register */
#define limit_right_DR                     (* (reg8 *) limit_right__DR)
/* Port Number */
#define limit_right_PRT_NUM                (* (reg8 *) limit_right__PRT) 
/* Connect to Analog Globals */                                                  
#define limit_right_AG                     (* (reg8 *) limit_right__AG)                       
/* Analog MUX bux enable */
#define limit_right_AMUX                   (* (reg8 *) limit_right__AMUX) 
/* Bidirectional Enable */                                                        
#define limit_right_BIE                    (* (reg8 *) limit_right__BIE)
/* Bit-mask for Aliased Register Access */
#define limit_right_BIT_MASK               (* (reg8 *) limit_right__BIT_MASK)
/* Bypass Enable */
#define limit_right_BYP                    (* (reg8 *) limit_right__BYP)
/* Port wide control signals */                                                   
#define limit_right_CTL                    (* (reg8 *) limit_right__CTL)
/* Drive Modes */
#define limit_right_DM0                    (* (reg8 *) limit_right__DM0) 
#define limit_right_DM1                    (* (reg8 *) limit_right__DM1)
#define limit_right_DM2                    (* (reg8 *) limit_right__DM2) 
/* Input Buffer Disable Override */
#define limit_right_INP_DIS                (* (reg8 *) limit_right__INP_DIS)
/* LCD Common or Segment Drive */
#define limit_right_LCD_COM_SEG            (* (reg8 *) limit_right__LCD_COM_SEG)
/* Enable Segment LCD */
#define limit_right_LCD_EN                 (* (reg8 *) limit_right__LCD_EN)
/* Slew Rate Control */
#define limit_right_SLW                    (* (reg8 *) limit_right__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define limit_right_PRTDSI__CAPS_SEL       (* (reg8 *) limit_right__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define limit_right_PRTDSI__DBL_SYNC_IN    (* (reg8 *) limit_right__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define limit_right_PRTDSI__OE_SEL0        (* (reg8 *) limit_right__PRTDSI__OE_SEL0) 
#define limit_right_PRTDSI__OE_SEL1        (* (reg8 *) limit_right__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define limit_right_PRTDSI__OUT_SEL0       (* (reg8 *) limit_right__PRTDSI__OUT_SEL0) 
#define limit_right_PRTDSI__OUT_SEL1       (* (reg8 *) limit_right__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define limit_right_PRTDSI__SYNC_OUT       (* (reg8 *) limit_right__PRTDSI__SYNC_OUT) 


#if defined(limit_right__INTSTAT)  /* Interrupt Registers */

    #define limit_right_INTSTAT                (* (reg8 *) limit_right__INTSTAT)
    #define limit_right_SNAP                   (* (reg8 *) limit_right__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins limit_right_H */


/* [] END OF FILE */
