/*******************************************************************************
* File Name: air_2.h  
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

#if !defined(CY_PINS_air_2_H) /* Pins air_2_H */
#define CY_PINS_air_2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "air_2_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    air_2_Write(uint8 value) ;
void    air_2_SetDriveMode(uint8 mode) ;
uint8   air_2_ReadDataReg(void) ;
uint8   air_2_Read(void) ;
uint8   air_2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define air_2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define air_2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define air_2_DM_RES_UP          PIN_DM_RES_UP
#define air_2_DM_RES_DWN         PIN_DM_RES_DWN
#define air_2_DM_OD_LO           PIN_DM_OD_LO
#define air_2_DM_OD_HI           PIN_DM_OD_HI
#define air_2_DM_STRONG          PIN_DM_STRONG
#define air_2_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define air_2_MASK               air_2__MASK
#define air_2_SHIFT              air_2__SHIFT
#define air_2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define air_2_PS                     (* (reg8 *) air_2__PS)
/* Data Register */
#define air_2_DR                     (* (reg8 *) air_2__DR)
/* Port Number */
#define air_2_PRT_NUM                (* (reg8 *) air_2__PRT) 
/* Connect to Analog Globals */                                                  
#define air_2_AG                     (* (reg8 *) air_2__AG)                       
/* Analog MUX bux enable */
#define air_2_AMUX                   (* (reg8 *) air_2__AMUX) 
/* Bidirectional Enable */                                                        
#define air_2_BIE                    (* (reg8 *) air_2__BIE)
/* Bit-mask for Aliased Register Access */
#define air_2_BIT_MASK               (* (reg8 *) air_2__BIT_MASK)
/* Bypass Enable */
#define air_2_BYP                    (* (reg8 *) air_2__BYP)
/* Port wide control signals */                                                   
#define air_2_CTL                    (* (reg8 *) air_2__CTL)
/* Drive Modes */
#define air_2_DM0                    (* (reg8 *) air_2__DM0) 
#define air_2_DM1                    (* (reg8 *) air_2__DM1)
#define air_2_DM2                    (* (reg8 *) air_2__DM2) 
/* Input Buffer Disable Override */
#define air_2_INP_DIS                (* (reg8 *) air_2__INP_DIS)
/* LCD Common or Segment Drive */
#define air_2_LCD_COM_SEG            (* (reg8 *) air_2__LCD_COM_SEG)
/* Enable Segment LCD */
#define air_2_LCD_EN                 (* (reg8 *) air_2__LCD_EN)
/* Slew Rate Control */
#define air_2_SLW                    (* (reg8 *) air_2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define air_2_PRTDSI__CAPS_SEL       (* (reg8 *) air_2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define air_2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) air_2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define air_2_PRTDSI__OE_SEL0        (* (reg8 *) air_2__PRTDSI__OE_SEL0) 
#define air_2_PRTDSI__OE_SEL1        (* (reg8 *) air_2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define air_2_PRTDSI__OUT_SEL0       (* (reg8 *) air_2__PRTDSI__OUT_SEL0) 
#define air_2_PRTDSI__OUT_SEL1       (* (reg8 *) air_2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define air_2_PRTDSI__SYNC_OUT       (* (reg8 *) air_2__PRTDSI__SYNC_OUT) 


#if defined(air_2__INTSTAT)  /* Interrupt Registers */

    #define air_2_INTSTAT                (* (reg8 *) air_2__INTSTAT)
    #define air_2_SNAP                   (* (reg8 *) air_2__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins air_2_H */


/* [] END OF FILE */
