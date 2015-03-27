/*******************************************************************************
* File Name: air_3.h  
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

#if !defined(CY_PINS_air_3_H) /* Pins air_3_H */
#define CY_PINS_air_3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "air_3_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    air_3_Write(uint8 value) ;
void    air_3_SetDriveMode(uint8 mode) ;
uint8   air_3_ReadDataReg(void) ;
uint8   air_3_Read(void) ;
uint8   air_3_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define air_3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define air_3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define air_3_DM_RES_UP          PIN_DM_RES_UP
#define air_3_DM_RES_DWN         PIN_DM_RES_DWN
#define air_3_DM_OD_LO           PIN_DM_OD_LO
#define air_3_DM_OD_HI           PIN_DM_OD_HI
#define air_3_DM_STRONG          PIN_DM_STRONG
#define air_3_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define air_3_MASK               air_3__MASK
#define air_3_SHIFT              air_3__SHIFT
#define air_3_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define air_3_PS                     (* (reg8 *) air_3__PS)
/* Data Register */
#define air_3_DR                     (* (reg8 *) air_3__DR)
/* Port Number */
#define air_3_PRT_NUM                (* (reg8 *) air_3__PRT) 
/* Connect to Analog Globals */                                                  
#define air_3_AG                     (* (reg8 *) air_3__AG)                       
/* Analog MUX bux enable */
#define air_3_AMUX                   (* (reg8 *) air_3__AMUX) 
/* Bidirectional Enable */                                                        
#define air_3_BIE                    (* (reg8 *) air_3__BIE)
/* Bit-mask for Aliased Register Access */
#define air_3_BIT_MASK               (* (reg8 *) air_3__BIT_MASK)
/* Bypass Enable */
#define air_3_BYP                    (* (reg8 *) air_3__BYP)
/* Port wide control signals */                                                   
#define air_3_CTL                    (* (reg8 *) air_3__CTL)
/* Drive Modes */
#define air_3_DM0                    (* (reg8 *) air_3__DM0) 
#define air_3_DM1                    (* (reg8 *) air_3__DM1)
#define air_3_DM2                    (* (reg8 *) air_3__DM2) 
/* Input Buffer Disable Override */
#define air_3_INP_DIS                (* (reg8 *) air_3__INP_DIS)
/* LCD Common or Segment Drive */
#define air_3_LCD_COM_SEG            (* (reg8 *) air_3__LCD_COM_SEG)
/* Enable Segment LCD */
#define air_3_LCD_EN                 (* (reg8 *) air_3__LCD_EN)
/* Slew Rate Control */
#define air_3_SLW                    (* (reg8 *) air_3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define air_3_PRTDSI__CAPS_SEL       (* (reg8 *) air_3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define air_3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) air_3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define air_3_PRTDSI__OE_SEL0        (* (reg8 *) air_3__PRTDSI__OE_SEL0) 
#define air_3_PRTDSI__OE_SEL1        (* (reg8 *) air_3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define air_3_PRTDSI__OUT_SEL0       (* (reg8 *) air_3__PRTDSI__OUT_SEL0) 
#define air_3_PRTDSI__OUT_SEL1       (* (reg8 *) air_3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define air_3_PRTDSI__SYNC_OUT       (* (reg8 *) air_3__PRTDSI__SYNC_OUT) 


#if defined(air_3__INTSTAT)  /* Interrupt Registers */

    #define air_3_INTSTAT                (* (reg8 *) air_3__INTSTAT)
    #define air_3_SNAP                   (* (reg8 *) air_3__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins air_3_H */


/* [] END OF FILE */
