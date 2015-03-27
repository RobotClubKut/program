/*******************************************************************************
* File Name: rori_R_i.h  
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

#if !defined(CY_PINS_rori_R_i_H) /* Pins rori_R_i_H */
#define CY_PINS_rori_R_i_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "rori_R_i_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    rori_R_i_Write(uint8 value) ;
void    rori_R_i_SetDriveMode(uint8 mode) ;
uint8   rori_R_i_ReadDataReg(void) ;
uint8   rori_R_i_Read(void) ;
uint8   rori_R_i_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define rori_R_i_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define rori_R_i_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define rori_R_i_DM_RES_UP          PIN_DM_RES_UP
#define rori_R_i_DM_RES_DWN         PIN_DM_RES_DWN
#define rori_R_i_DM_OD_LO           PIN_DM_OD_LO
#define rori_R_i_DM_OD_HI           PIN_DM_OD_HI
#define rori_R_i_DM_STRONG          PIN_DM_STRONG
#define rori_R_i_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define rori_R_i_MASK               rori_R_i__MASK
#define rori_R_i_SHIFT              rori_R_i__SHIFT
#define rori_R_i_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define rori_R_i_PS                     (* (reg8 *) rori_R_i__PS)
/* Data Register */
#define rori_R_i_DR                     (* (reg8 *) rori_R_i__DR)
/* Port Number */
#define rori_R_i_PRT_NUM                (* (reg8 *) rori_R_i__PRT) 
/* Connect to Analog Globals */                                                  
#define rori_R_i_AG                     (* (reg8 *) rori_R_i__AG)                       
/* Analog MUX bux enable */
#define rori_R_i_AMUX                   (* (reg8 *) rori_R_i__AMUX) 
/* Bidirectional Enable */                                                        
#define rori_R_i_BIE                    (* (reg8 *) rori_R_i__BIE)
/* Bit-mask for Aliased Register Access */
#define rori_R_i_BIT_MASK               (* (reg8 *) rori_R_i__BIT_MASK)
/* Bypass Enable */
#define rori_R_i_BYP                    (* (reg8 *) rori_R_i__BYP)
/* Port wide control signals */                                                   
#define rori_R_i_CTL                    (* (reg8 *) rori_R_i__CTL)
/* Drive Modes */
#define rori_R_i_DM0                    (* (reg8 *) rori_R_i__DM0) 
#define rori_R_i_DM1                    (* (reg8 *) rori_R_i__DM1)
#define rori_R_i_DM2                    (* (reg8 *) rori_R_i__DM2) 
/* Input Buffer Disable Override */
#define rori_R_i_INP_DIS                (* (reg8 *) rori_R_i__INP_DIS)
/* LCD Common or Segment Drive */
#define rori_R_i_LCD_COM_SEG            (* (reg8 *) rori_R_i__LCD_COM_SEG)
/* Enable Segment LCD */
#define rori_R_i_LCD_EN                 (* (reg8 *) rori_R_i__LCD_EN)
/* Slew Rate Control */
#define rori_R_i_SLW                    (* (reg8 *) rori_R_i__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define rori_R_i_PRTDSI__CAPS_SEL       (* (reg8 *) rori_R_i__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define rori_R_i_PRTDSI__DBL_SYNC_IN    (* (reg8 *) rori_R_i__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define rori_R_i_PRTDSI__OE_SEL0        (* (reg8 *) rori_R_i__PRTDSI__OE_SEL0) 
#define rori_R_i_PRTDSI__OE_SEL1        (* (reg8 *) rori_R_i__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define rori_R_i_PRTDSI__OUT_SEL0       (* (reg8 *) rori_R_i__PRTDSI__OUT_SEL0) 
#define rori_R_i_PRTDSI__OUT_SEL1       (* (reg8 *) rori_R_i__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define rori_R_i_PRTDSI__SYNC_OUT       (* (reg8 *) rori_R_i__PRTDSI__SYNC_OUT) 


#if defined(rori_R_i__INTSTAT)  /* Interrupt Registers */

    #define rori_R_i_INTSTAT                (* (reg8 *) rori_R_i__INTSTAT)
    #define rori_R_i_SNAP                   (* (reg8 *) rori_R_i__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins rori_R_i_H */


/* [] END OF FILE */
