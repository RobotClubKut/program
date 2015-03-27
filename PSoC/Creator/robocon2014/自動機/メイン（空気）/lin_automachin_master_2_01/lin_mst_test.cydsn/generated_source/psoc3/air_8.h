/*******************************************************************************
* File Name: air_8.h  
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

#if !defined(CY_PINS_air_8_H) /* Pins air_8_H */
#define CY_PINS_air_8_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "air_8_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    air_8_Write(uint8 value) ;
void    air_8_SetDriveMode(uint8 mode) ;
uint8   air_8_ReadDataReg(void) ;
uint8   air_8_Read(void) ;
uint8   air_8_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define air_8_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define air_8_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define air_8_DM_RES_UP          PIN_DM_RES_UP
#define air_8_DM_RES_DWN         PIN_DM_RES_DWN
#define air_8_DM_OD_LO           PIN_DM_OD_LO
#define air_8_DM_OD_HI           PIN_DM_OD_HI
#define air_8_DM_STRONG          PIN_DM_STRONG
#define air_8_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define air_8_MASK               air_8__MASK
#define air_8_SHIFT              air_8__SHIFT
#define air_8_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define air_8_PS                     (* (reg8 *) air_8__PS)
/* Data Register */
#define air_8_DR                     (* (reg8 *) air_8__DR)
/* Port Number */
#define air_8_PRT_NUM                (* (reg8 *) air_8__PRT) 
/* Connect to Analog Globals */                                                  
#define air_8_AG                     (* (reg8 *) air_8__AG)                       
/* Analog MUX bux enable */
#define air_8_AMUX                   (* (reg8 *) air_8__AMUX) 
/* Bidirectional Enable */                                                        
#define air_8_BIE                    (* (reg8 *) air_8__BIE)
/* Bit-mask for Aliased Register Access */
#define air_8_BIT_MASK               (* (reg8 *) air_8__BIT_MASK)
/* Bypass Enable */
#define air_8_BYP                    (* (reg8 *) air_8__BYP)
/* Port wide control signals */                                                   
#define air_8_CTL                    (* (reg8 *) air_8__CTL)
/* Drive Modes */
#define air_8_DM0                    (* (reg8 *) air_8__DM0) 
#define air_8_DM1                    (* (reg8 *) air_8__DM1)
#define air_8_DM2                    (* (reg8 *) air_8__DM2) 
/* Input Buffer Disable Override */
#define air_8_INP_DIS                (* (reg8 *) air_8__INP_DIS)
/* LCD Common or Segment Drive */
#define air_8_LCD_COM_SEG            (* (reg8 *) air_8__LCD_COM_SEG)
/* Enable Segment LCD */
#define air_8_LCD_EN                 (* (reg8 *) air_8__LCD_EN)
/* Slew Rate Control */
#define air_8_SLW                    (* (reg8 *) air_8__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define air_8_PRTDSI__CAPS_SEL       (* (reg8 *) air_8__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define air_8_PRTDSI__DBL_SYNC_IN    (* (reg8 *) air_8__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define air_8_PRTDSI__OE_SEL0        (* (reg8 *) air_8__PRTDSI__OE_SEL0) 
#define air_8_PRTDSI__OE_SEL1        (* (reg8 *) air_8__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define air_8_PRTDSI__OUT_SEL0       (* (reg8 *) air_8__PRTDSI__OUT_SEL0) 
#define air_8_PRTDSI__OUT_SEL1       (* (reg8 *) air_8__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define air_8_PRTDSI__SYNC_OUT       (* (reg8 *) air_8__PRTDSI__SYNC_OUT) 


#if defined(air_8__INTSTAT)  /* Interrupt Registers */

    #define air_8_INTSTAT                (* (reg8 *) air_8__INTSTAT)
    #define air_8_SNAP                   (* (reg8 *) air_8__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins air_8_H */


/* [] END OF FILE */
