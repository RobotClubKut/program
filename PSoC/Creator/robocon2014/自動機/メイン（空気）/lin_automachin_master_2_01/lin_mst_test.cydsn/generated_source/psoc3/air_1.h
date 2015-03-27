/*******************************************************************************
* File Name: air_1.h  
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

#if !defined(CY_PINS_air_1_H) /* Pins air_1_H */
#define CY_PINS_air_1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "air_1_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    air_1_Write(uint8 value) ;
void    air_1_SetDriveMode(uint8 mode) ;
uint8   air_1_ReadDataReg(void) ;
uint8   air_1_Read(void) ;
uint8   air_1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define air_1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define air_1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define air_1_DM_RES_UP          PIN_DM_RES_UP
#define air_1_DM_RES_DWN         PIN_DM_RES_DWN
#define air_1_DM_OD_LO           PIN_DM_OD_LO
#define air_1_DM_OD_HI           PIN_DM_OD_HI
#define air_1_DM_STRONG          PIN_DM_STRONG
#define air_1_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define air_1_MASK               air_1__MASK
#define air_1_SHIFT              air_1__SHIFT
#define air_1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define air_1_PS                     (* (reg8 *) air_1__PS)
/* Data Register */
#define air_1_DR                     (* (reg8 *) air_1__DR)
/* Port Number */
#define air_1_PRT_NUM                (* (reg8 *) air_1__PRT) 
/* Connect to Analog Globals */                                                  
#define air_1_AG                     (* (reg8 *) air_1__AG)                       
/* Analog MUX bux enable */
#define air_1_AMUX                   (* (reg8 *) air_1__AMUX) 
/* Bidirectional Enable */                                                        
#define air_1_BIE                    (* (reg8 *) air_1__BIE)
/* Bit-mask for Aliased Register Access */
#define air_1_BIT_MASK               (* (reg8 *) air_1__BIT_MASK)
/* Bypass Enable */
#define air_1_BYP                    (* (reg8 *) air_1__BYP)
/* Port wide control signals */                                                   
#define air_1_CTL                    (* (reg8 *) air_1__CTL)
/* Drive Modes */
#define air_1_DM0                    (* (reg8 *) air_1__DM0) 
#define air_1_DM1                    (* (reg8 *) air_1__DM1)
#define air_1_DM2                    (* (reg8 *) air_1__DM2) 
/* Input Buffer Disable Override */
#define air_1_INP_DIS                (* (reg8 *) air_1__INP_DIS)
/* LCD Common or Segment Drive */
#define air_1_LCD_COM_SEG            (* (reg8 *) air_1__LCD_COM_SEG)
/* Enable Segment LCD */
#define air_1_LCD_EN                 (* (reg8 *) air_1__LCD_EN)
/* Slew Rate Control */
#define air_1_SLW                    (* (reg8 *) air_1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define air_1_PRTDSI__CAPS_SEL       (* (reg8 *) air_1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define air_1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) air_1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define air_1_PRTDSI__OE_SEL0        (* (reg8 *) air_1__PRTDSI__OE_SEL0) 
#define air_1_PRTDSI__OE_SEL1        (* (reg8 *) air_1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define air_1_PRTDSI__OUT_SEL0       (* (reg8 *) air_1__PRTDSI__OUT_SEL0) 
#define air_1_PRTDSI__OUT_SEL1       (* (reg8 *) air_1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define air_1_PRTDSI__SYNC_OUT       (* (reg8 *) air_1__PRTDSI__SYNC_OUT) 


#if defined(air_1__INTSTAT)  /* Interrupt Registers */

    #define air_1_INTSTAT                (* (reg8 *) air_1__INTSTAT)
    #define air_1_SNAP                   (* (reg8 *) air_1__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins air_1_H */


/* [] END OF FILE */
