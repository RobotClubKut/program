/*******************************************************************************
* File Name: air_6.h  
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

#if !defined(CY_PINS_air_6_H) /* Pins air_6_H */
#define CY_PINS_air_6_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "air_6_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    air_6_Write(uint8 value) ;
void    air_6_SetDriveMode(uint8 mode) ;
uint8   air_6_ReadDataReg(void) ;
uint8   air_6_Read(void) ;
uint8   air_6_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define air_6_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define air_6_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define air_6_DM_RES_UP          PIN_DM_RES_UP
#define air_6_DM_RES_DWN         PIN_DM_RES_DWN
#define air_6_DM_OD_LO           PIN_DM_OD_LO
#define air_6_DM_OD_HI           PIN_DM_OD_HI
#define air_6_DM_STRONG          PIN_DM_STRONG
#define air_6_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define air_6_MASK               air_6__MASK
#define air_6_SHIFT              air_6__SHIFT
#define air_6_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define air_6_PS                     (* (reg8 *) air_6__PS)
/* Data Register */
#define air_6_DR                     (* (reg8 *) air_6__DR)
/* Port Number */
#define air_6_PRT_NUM                (* (reg8 *) air_6__PRT) 
/* Connect to Analog Globals */                                                  
#define air_6_AG                     (* (reg8 *) air_6__AG)                       
/* Analog MUX bux enable */
#define air_6_AMUX                   (* (reg8 *) air_6__AMUX) 
/* Bidirectional Enable */                                                        
#define air_6_BIE                    (* (reg8 *) air_6__BIE)
/* Bit-mask for Aliased Register Access */
#define air_6_BIT_MASK               (* (reg8 *) air_6__BIT_MASK)
/* Bypass Enable */
#define air_6_BYP                    (* (reg8 *) air_6__BYP)
/* Port wide control signals */                                                   
#define air_6_CTL                    (* (reg8 *) air_6__CTL)
/* Drive Modes */
#define air_6_DM0                    (* (reg8 *) air_6__DM0) 
#define air_6_DM1                    (* (reg8 *) air_6__DM1)
#define air_6_DM2                    (* (reg8 *) air_6__DM2) 
/* Input Buffer Disable Override */
#define air_6_INP_DIS                (* (reg8 *) air_6__INP_DIS)
/* LCD Common or Segment Drive */
#define air_6_LCD_COM_SEG            (* (reg8 *) air_6__LCD_COM_SEG)
/* Enable Segment LCD */
#define air_6_LCD_EN                 (* (reg8 *) air_6__LCD_EN)
/* Slew Rate Control */
#define air_6_SLW                    (* (reg8 *) air_6__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define air_6_PRTDSI__CAPS_SEL       (* (reg8 *) air_6__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define air_6_PRTDSI__DBL_SYNC_IN    (* (reg8 *) air_6__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define air_6_PRTDSI__OE_SEL0        (* (reg8 *) air_6__PRTDSI__OE_SEL0) 
#define air_6_PRTDSI__OE_SEL1        (* (reg8 *) air_6__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define air_6_PRTDSI__OUT_SEL0       (* (reg8 *) air_6__PRTDSI__OUT_SEL0) 
#define air_6_PRTDSI__OUT_SEL1       (* (reg8 *) air_6__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define air_6_PRTDSI__SYNC_OUT       (* (reg8 *) air_6__PRTDSI__SYNC_OUT) 


#if defined(air_6__INTSTAT)  /* Interrupt Registers */

    #define air_6_INTSTAT                (* (reg8 *) air_6__INTSTAT)
    #define air_6_SNAP                   (* (reg8 *) air_6__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins air_6_H */


/* [] END OF FILE */
