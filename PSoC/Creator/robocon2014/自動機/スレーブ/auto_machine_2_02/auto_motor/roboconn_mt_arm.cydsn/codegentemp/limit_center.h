/*******************************************************************************
* File Name: limit_center.h  
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

#if !defined(CY_PINS_limit_center_H) /* Pins limit_center_H */
#define CY_PINS_limit_center_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "limit_center_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    limit_center_Write(uint8 value) ;
void    limit_center_SetDriveMode(uint8 mode) ;
uint8   limit_center_ReadDataReg(void) ;
uint8   limit_center_Read(void) ;
uint8   limit_center_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define limit_center_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define limit_center_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define limit_center_DM_RES_UP          PIN_DM_RES_UP
#define limit_center_DM_RES_DWN         PIN_DM_RES_DWN
#define limit_center_DM_OD_LO           PIN_DM_OD_LO
#define limit_center_DM_OD_HI           PIN_DM_OD_HI
#define limit_center_DM_STRONG          PIN_DM_STRONG
#define limit_center_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define limit_center_MASK               limit_center__MASK
#define limit_center_SHIFT              limit_center__SHIFT
#define limit_center_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define limit_center_PS                     (* (reg8 *) limit_center__PS)
/* Data Register */
#define limit_center_DR                     (* (reg8 *) limit_center__DR)
/* Port Number */
#define limit_center_PRT_NUM                (* (reg8 *) limit_center__PRT) 
/* Connect to Analog Globals */                                                  
#define limit_center_AG                     (* (reg8 *) limit_center__AG)                       
/* Analog MUX bux enable */
#define limit_center_AMUX                   (* (reg8 *) limit_center__AMUX) 
/* Bidirectional Enable */                                                        
#define limit_center_BIE                    (* (reg8 *) limit_center__BIE)
/* Bit-mask for Aliased Register Access */
#define limit_center_BIT_MASK               (* (reg8 *) limit_center__BIT_MASK)
/* Bypass Enable */
#define limit_center_BYP                    (* (reg8 *) limit_center__BYP)
/* Port wide control signals */                                                   
#define limit_center_CTL                    (* (reg8 *) limit_center__CTL)
/* Drive Modes */
#define limit_center_DM0                    (* (reg8 *) limit_center__DM0) 
#define limit_center_DM1                    (* (reg8 *) limit_center__DM1)
#define limit_center_DM2                    (* (reg8 *) limit_center__DM2) 
/* Input Buffer Disable Override */
#define limit_center_INP_DIS                (* (reg8 *) limit_center__INP_DIS)
/* LCD Common or Segment Drive */
#define limit_center_LCD_COM_SEG            (* (reg8 *) limit_center__LCD_COM_SEG)
/* Enable Segment LCD */
#define limit_center_LCD_EN                 (* (reg8 *) limit_center__LCD_EN)
/* Slew Rate Control */
#define limit_center_SLW                    (* (reg8 *) limit_center__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define limit_center_PRTDSI__CAPS_SEL       (* (reg8 *) limit_center__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define limit_center_PRTDSI__DBL_SYNC_IN    (* (reg8 *) limit_center__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define limit_center_PRTDSI__OE_SEL0        (* (reg8 *) limit_center__PRTDSI__OE_SEL0) 
#define limit_center_PRTDSI__OE_SEL1        (* (reg8 *) limit_center__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define limit_center_PRTDSI__OUT_SEL0       (* (reg8 *) limit_center__PRTDSI__OUT_SEL0) 
#define limit_center_PRTDSI__OUT_SEL1       (* (reg8 *) limit_center__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define limit_center_PRTDSI__SYNC_OUT       (* (reg8 *) limit_center__PRTDSI__SYNC_OUT) 


#if defined(limit_center__INTSTAT)  /* Interrupt Registers */

    #define limit_center_INTSTAT                (* (reg8 *) limit_center__INTSTAT)
    #define limit_center_SNAP                   (* (reg8 *) limit_center__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins limit_center_H */


/* [] END OF FILE */
