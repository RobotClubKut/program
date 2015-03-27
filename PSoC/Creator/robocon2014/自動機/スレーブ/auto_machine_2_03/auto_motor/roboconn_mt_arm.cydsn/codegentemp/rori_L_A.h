/*******************************************************************************
* File Name: rori_L_A.h  
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

#if !defined(CY_PINS_rori_L_A_H) /* Pins rori_L_A_H */
#define CY_PINS_rori_L_A_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "rori_L_A_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    rori_L_A_Write(uint8 value) ;
void    rori_L_A_SetDriveMode(uint8 mode) ;
uint8   rori_L_A_ReadDataReg(void) ;
uint8   rori_L_A_Read(void) ;
uint8   rori_L_A_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define rori_L_A_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define rori_L_A_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define rori_L_A_DM_RES_UP          PIN_DM_RES_UP
#define rori_L_A_DM_RES_DWN         PIN_DM_RES_DWN
#define rori_L_A_DM_OD_LO           PIN_DM_OD_LO
#define rori_L_A_DM_OD_HI           PIN_DM_OD_HI
#define rori_L_A_DM_STRONG          PIN_DM_STRONG
#define rori_L_A_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define rori_L_A_MASK               rori_L_A__MASK
#define rori_L_A_SHIFT              rori_L_A__SHIFT
#define rori_L_A_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define rori_L_A_PS                     (* (reg8 *) rori_L_A__PS)
/* Data Register */
#define rori_L_A_DR                     (* (reg8 *) rori_L_A__DR)
/* Port Number */
#define rori_L_A_PRT_NUM                (* (reg8 *) rori_L_A__PRT) 
/* Connect to Analog Globals */                                                  
#define rori_L_A_AG                     (* (reg8 *) rori_L_A__AG)                       
/* Analog MUX bux enable */
#define rori_L_A_AMUX                   (* (reg8 *) rori_L_A__AMUX) 
/* Bidirectional Enable */                                                        
#define rori_L_A_BIE                    (* (reg8 *) rori_L_A__BIE)
/* Bit-mask for Aliased Register Access */
#define rori_L_A_BIT_MASK               (* (reg8 *) rori_L_A__BIT_MASK)
/* Bypass Enable */
#define rori_L_A_BYP                    (* (reg8 *) rori_L_A__BYP)
/* Port wide control signals */                                                   
#define rori_L_A_CTL                    (* (reg8 *) rori_L_A__CTL)
/* Drive Modes */
#define rori_L_A_DM0                    (* (reg8 *) rori_L_A__DM0) 
#define rori_L_A_DM1                    (* (reg8 *) rori_L_A__DM1)
#define rori_L_A_DM2                    (* (reg8 *) rori_L_A__DM2) 
/* Input Buffer Disable Override */
#define rori_L_A_INP_DIS                (* (reg8 *) rori_L_A__INP_DIS)
/* LCD Common or Segment Drive */
#define rori_L_A_LCD_COM_SEG            (* (reg8 *) rori_L_A__LCD_COM_SEG)
/* Enable Segment LCD */
#define rori_L_A_LCD_EN                 (* (reg8 *) rori_L_A__LCD_EN)
/* Slew Rate Control */
#define rori_L_A_SLW                    (* (reg8 *) rori_L_A__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define rori_L_A_PRTDSI__CAPS_SEL       (* (reg8 *) rori_L_A__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define rori_L_A_PRTDSI__DBL_SYNC_IN    (* (reg8 *) rori_L_A__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define rori_L_A_PRTDSI__OE_SEL0        (* (reg8 *) rori_L_A__PRTDSI__OE_SEL0) 
#define rori_L_A_PRTDSI__OE_SEL1        (* (reg8 *) rori_L_A__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define rori_L_A_PRTDSI__OUT_SEL0       (* (reg8 *) rori_L_A__PRTDSI__OUT_SEL0) 
#define rori_L_A_PRTDSI__OUT_SEL1       (* (reg8 *) rori_L_A__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define rori_L_A_PRTDSI__SYNC_OUT       (* (reg8 *) rori_L_A__PRTDSI__SYNC_OUT) 


#if defined(rori_L_A__INTSTAT)  /* Interrupt Registers */

    #define rori_L_A_INTSTAT                (* (reg8 *) rori_L_A__INTSTAT)
    #define rori_L_A_SNAP                   (* (reg8 *) rori_L_A__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins rori_L_A_H */


/* [] END OF FILE */
