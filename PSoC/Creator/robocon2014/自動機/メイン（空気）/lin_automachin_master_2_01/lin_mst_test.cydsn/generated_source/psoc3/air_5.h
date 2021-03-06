/*******************************************************************************
* File Name: air_5.h  
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

#if !defined(CY_PINS_air_5_H) /* Pins air_5_H */
#define CY_PINS_air_5_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "air_5_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    air_5_Write(uint8 value) ;
void    air_5_SetDriveMode(uint8 mode) ;
uint8   air_5_ReadDataReg(void) ;
uint8   air_5_Read(void) ;
uint8   air_5_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define air_5_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define air_5_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define air_5_DM_RES_UP          PIN_DM_RES_UP
#define air_5_DM_RES_DWN         PIN_DM_RES_DWN
#define air_5_DM_OD_LO           PIN_DM_OD_LO
#define air_5_DM_OD_HI           PIN_DM_OD_HI
#define air_5_DM_STRONG          PIN_DM_STRONG
#define air_5_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define air_5_MASK               air_5__MASK
#define air_5_SHIFT              air_5__SHIFT
#define air_5_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define air_5_PS                     (* (reg8 *) air_5__PS)
/* Data Register */
#define air_5_DR                     (* (reg8 *) air_5__DR)
/* Port Number */
#define air_5_PRT_NUM                (* (reg8 *) air_5__PRT) 
/* Connect to Analog Globals */                                                  
#define air_5_AG                     (* (reg8 *) air_5__AG)                       
/* Analog MUX bux enable */
#define air_5_AMUX                   (* (reg8 *) air_5__AMUX) 
/* Bidirectional Enable */                                                        
#define air_5_BIE                    (* (reg8 *) air_5__BIE)
/* Bit-mask for Aliased Register Access */
#define air_5_BIT_MASK               (* (reg8 *) air_5__BIT_MASK)
/* Bypass Enable */
#define air_5_BYP                    (* (reg8 *) air_5__BYP)
/* Port wide control signals */                                                   
#define air_5_CTL                    (* (reg8 *) air_5__CTL)
/* Drive Modes */
#define air_5_DM0                    (* (reg8 *) air_5__DM0) 
#define air_5_DM1                    (* (reg8 *) air_5__DM1)
#define air_5_DM2                    (* (reg8 *) air_5__DM2) 
/* Input Buffer Disable Override */
#define air_5_INP_DIS                (* (reg8 *) air_5__INP_DIS)
/* LCD Common or Segment Drive */
#define air_5_LCD_COM_SEG            (* (reg8 *) air_5__LCD_COM_SEG)
/* Enable Segment LCD */
#define air_5_LCD_EN                 (* (reg8 *) air_5__LCD_EN)
/* Slew Rate Control */
#define air_5_SLW                    (* (reg8 *) air_5__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define air_5_PRTDSI__CAPS_SEL       (* (reg8 *) air_5__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define air_5_PRTDSI__DBL_SYNC_IN    (* (reg8 *) air_5__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define air_5_PRTDSI__OE_SEL0        (* (reg8 *) air_5__PRTDSI__OE_SEL0) 
#define air_5_PRTDSI__OE_SEL1        (* (reg8 *) air_5__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define air_5_PRTDSI__OUT_SEL0       (* (reg8 *) air_5__PRTDSI__OUT_SEL0) 
#define air_5_PRTDSI__OUT_SEL1       (* (reg8 *) air_5__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define air_5_PRTDSI__SYNC_OUT       (* (reg8 *) air_5__PRTDSI__SYNC_OUT) 


#if defined(air_5__INTSTAT)  /* Interrupt Registers */

    #define air_5_INTSTAT                (* (reg8 *) air_5__INTSTAT)
    #define air_5_SNAP                   (* (reg8 *) air_5__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins air_5_H */


/* [] END OF FILE */
