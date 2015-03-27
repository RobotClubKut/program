/*******************************************************************************
* File Name: air_4.h  
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

#if !defined(CY_PINS_air_4_H) /* Pins air_4_H */
#define CY_PINS_air_4_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "air_4_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    air_4_Write(uint8 value) ;
void    air_4_SetDriveMode(uint8 mode) ;
uint8   air_4_ReadDataReg(void) ;
uint8   air_4_Read(void) ;
uint8   air_4_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define air_4_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define air_4_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define air_4_DM_RES_UP          PIN_DM_RES_UP
#define air_4_DM_RES_DWN         PIN_DM_RES_DWN
#define air_4_DM_OD_LO           PIN_DM_OD_LO
#define air_4_DM_OD_HI           PIN_DM_OD_HI
#define air_4_DM_STRONG          PIN_DM_STRONG
#define air_4_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define air_4_MASK               air_4__MASK
#define air_4_SHIFT              air_4__SHIFT
#define air_4_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define air_4_PS                     (* (reg8 *) air_4__PS)
/* Data Register */
#define air_4_DR                     (* (reg8 *) air_4__DR)
/* Port Number */
#define air_4_PRT_NUM                (* (reg8 *) air_4__PRT) 
/* Connect to Analog Globals */                                                  
#define air_4_AG                     (* (reg8 *) air_4__AG)                       
/* Analog MUX bux enable */
#define air_4_AMUX                   (* (reg8 *) air_4__AMUX) 
/* Bidirectional Enable */                                                        
#define air_4_BIE                    (* (reg8 *) air_4__BIE)
/* Bit-mask for Aliased Register Access */
#define air_4_BIT_MASK               (* (reg8 *) air_4__BIT_MASK)
/* Bypass Enable */
#define air_4_BYP                    (* (reg8 *) air_4__BYP)
/* Port wide control signals */                                                   
#define air_4_CTL                    (* (reg8 *) air_4__CTL)
/* Drive Modes */
#define air_4_DM0                    (* (reg8 *) air_4__DM0) 
#define air_4_DM1                    (* (reg8 *) air_4__DM1)
#define air_4_DM2                    (* (reg8 *) air_4__DM2) 
/* Input Buffer Disable Override */
#define air_4_INP_DIS                (* (reg8 *) air_4__INP_DIS)
/* LCD Common or Segment Drive */
#define air_4_LCD_COM_SEG            (* (reg8 *) air_4__LCD_COM_SEG)
/* Enable Segment LCD */
#define air_4_LCD_EN                 (* (reg8 *) air_4__LCD_EN)
/* Slew Rate Control */
#define air_4_SLW                    (* (reg8 *) air_4__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define air_4_PRTDSI__CAPS_SEL       (* (reg8 *) air_4__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define air_4_PRTDSI__DBL_SYNC_IN    (* (reg8 *) air_4__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define air_4_PRTDSI__OE_SEL0        (* (reg8 *) air_4__PRTDSI__OE_SEL0) 
#define air_4_PRTDSI__OE_SEL1        (* (reg8 *) air_4__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define air_4_PRTDSI__OUT_SEL0       (* (reg8 *) air_4__PRTDSI__OUT_SEL0) 
#define air_4_PRTDSI__OUT_SEL1       (* (reg8 *) air_4__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define air_4_PRTDSI__SYNC_OUT       (* (reg8 *) air_4__PRTDSI__SYNC_OUT) 


#if defined(air_4__INTSTAT)  /* Interrupt Registers */

    #define air_4_INTSTAT                (* (reg8 *) air_4__INTSTAT)
    #define air_4_SNAP                   (* (reg8 *) air_4__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins air_4_H */


/* [] END OF FILE */
