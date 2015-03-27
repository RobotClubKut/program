/*******************************************************************************
* File Name: QuadDec_R_PM.c
* Version 2.30
*
* Description:
*  This file contains the setup, control and status commands to support 
*  component operations in low power mode.  
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "QuadDec_R.h"

static QuadDec_R_BACKUP_STRUCT QuadDec_R_backup = {0u};


/*******************************************************************************
* Function Name: QuadDec_R_SaveConfig
********************************************************************************
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void QuadDec_R_SaveConfig(void) 
{
    #if (QuadDec_R_COUNTER_SIZE == QuadDec_R_COUNTER_SIZE_8_BIT)
        QuadDec_R_Cnt8_SaveConfig();
    #else 
        /* (QuadDec_R_COUNTER_SIZE == QuadDec_R_COUNTER_SIZE_16_BIT) || 
         * (QuadDec_R_COUNTER_SIZE == QuadDec_R_COUNTER_SIZE_32_BIT)
         */
        QuadDec_R_Cnt16_SaveConfig();
    #endif /* (QuadDec_R_COUNTER_SIZE == QuadDec_R_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: QuadDec_R_RestoreConfig
********************************************************************************
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void QuadDec_R_RestoreConfig(void) 
{
    #if (QuadDec_R_COUNTER_SIZE == QuadDec_R_COUNTER_SIZE_8_BIT)
        QuadDec_R_Cnt8_RestoreConfig();
    #else 
        /* (QuadDec_R_COUNTER_SIZE == QuadDec_R_COUNTER_SIZE_16_BIT) || 
         * (QuadDec_R_COUNTER_SIZE == QuadDec_R_COUNTER_SIZE_32_BIT) 
         */
        QuadDec_R_Cnt16_RestoreConfig();
    #endif /* (QuadDec_R_COUNTER_SIZE == QuadDec_R_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: QuadDec_R_Sleep
********************************************************************************
* 
* Summary:
*  Prepare Quadrature Decoder Component goes to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  QuadDec_R_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void QuadDec_R_Sleep(void) 
{
    if (0u != (QuadDec_R_SR_AUX_CONTROL & QuadDec_R_INTERRUPTS_ENABLE))
    {
        QuadDec_R_backup.enableState = 1u;
    }
    else /* The Quadrature Decoder Component is disabled */
    {
        QuadDec_R_backup.enableState = 0u;
    }

    QuadDec_R_Stop();
    QuadDec_R_SaveConfig();
}


/*******************************************************************************
* Function Name: QuadDec_R_Wakeup
********************************************************************************
*
* Summary:
*  Prepare Quadrature Decoder Component to wake up.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  QuadDec_R_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void QuadDec_R_Wakeup(void) 
{
    QuadDec_R_RestoreConfig();

    if (QuadDec_R_backup.enableState != 0u)
    {
        #if (QuadDec_R_COUNTER_SIZE == QuadDec_R_COUNTER_SIZE_8_BIT)
            QuadDec_R_Cnt8_Enable();
        #else 
            /* (QuadDec_R_COUNTER_SIZE == QuadDec_R_COUNTER_SIZE_16_BIT) || 
            *  (QuadDec_R_COUNTER_SIZE == QuadDec_R_COUNTER_SIZE_32_BIT) 
            */
            QuadDec_R_Cnt16_Enable();
        #endif /* (QuadDec_R_COUNTER_SIZE == QuadDec_R_COUNTER_SIZE_8_BIT) */

        /* Enable component's operation */
        QuadDec_R_Enable();
    } /* Do nothing if component's block was disabled before */
}


/* [] END OF FILE */

