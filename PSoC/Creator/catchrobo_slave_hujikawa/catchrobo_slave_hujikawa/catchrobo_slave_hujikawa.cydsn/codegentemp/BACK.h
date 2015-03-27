/*******************************************************************************
* File Name: BACK.h  
* Version 2.0
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_BACK_H) /* Pins BACK_H */
#define CY_PINS_BACK_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "BACK_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    BACK_Write(uint8 value) ;
void    BACK_SetDriveMode(uint8 mode) ;
uint8   BACK_ReadDataReg(void) ;
uint8   BACK_Read(void) ;
uint8   BACK_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define BACK_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define BACK_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define BACK_DM_RES_UP          PIN_DM_RES_UP
#define BACK_DM_RES_DWN         PIN_DM_RES_DWN
#define BACK_DM_OD_LO           PIN_DM_OD_LO
#define BACK_DM_OD_HI           PIN_DM_OD_HI
#define BACK_DM_STRONG          PIN_DM_STRONG
#define BACK_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define BACK_MASK               BACK__MASK
#define BACK_SHIFT              BACK__SHIFT
#define BACK_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define BACK_PS                     (* (reg8 *) BACK__PS)
/* Data Register */
#define BACK_DR                     (* (reg8 *) BACK__DR)
/* Port Number */
#define BACK_PRT_NUM                (* (reg8 *) BACK__PRT) 
/* Connect to Analog Globals */                                                  
#define BACK_AG                     (* (reg8 *) BACK__AG)                       
/* Analog MUX bux enable */
#define BACK_AMUX                   (* (reg8 *) BACK__AMUX) 
/* Bidirectional Enable */                                                        
#define BACK_BIE                    (* (reg8 *) BACK__BIE)
/* Bit-mask for Aliased Register Access */
#define BACK_BIT_MASK               (* (reg8 *) BACK__BIT_MASK)
/* Bypass Enable */
#define BACK_BYP                    (* (reg8 *) BACK__BYP)
/* Port wide control signals */                                                   
#define BACK_CTL                    (* (reg8 *) BACK__CTL)
/* Drive Modes */
#define BACK_DM0                    (* (reg8 *) BACK__DM0) 
#define BACK_DM1                    (* (reg8 *) BACK__DM1)
#define BACK_DM2                    (* (reg8 *) BACK__DM2) 
/* Input Buffer Disable Override */
#define BACK_INP_DIS                (* (reg8 *) BACK__INP_DIS)
/* LCD Common or Segment Drive */
#define BACK_LCD_COM_SEG            (* (reg8 *) BACK__LCD_COM_SEG)
/* Enable Segment LCD */
#define BACK_LCD_EN                 (* (reg8 *) BACK__LCD_EN)
/* Slew Rate Control */
#define BACK_SLW                    (* (reg8 *) BACK__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define BACK_PRTDSI__CAPS_SEL       (* (reg8 *) BACK__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define BACK_PRTDSI__DBL_SYNC_IN    (* (reg8 *) BACK__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define BACK_PRTDSI__OE_SEL0        (* (reg8 *) BACK__PRTDSI__OE_SEL0) 
#define BACK_PRTDSI__OE_SEL1        (* (reg8 *) BACK__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define BACK_PRTDSI__OUT_SEL0       (* (reg8 *) BACK__PRTDSI__OUT_SEL0) 
#define BACK_PRTDSI__OUT_SEL1       (* (reg8 *) BACK__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define BACK_PRTDSI__SYNC_OUT       (* (reg8 *) BACK__PRTDSI__SYNC_OUT) 


#if defined(BACK__INTSTAT)  /* Interrupt Registers */

    #define BACK_INTSTAT                (* (reg8 *) BACK__INTSTAT)
    #define BACK_SNAP                   (* (reg8 *) BACK__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins BACK_H */


/* [] END OF FILE */
