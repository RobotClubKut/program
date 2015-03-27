/*******************************************************************************
* File Name: MOTOR_A_PM.c
* Version 3.0
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/
#include "cytypes.h"
#include "MOTOR_A.h"

static MOTOR_A_backupStruct MOTOR_A_backup;


/*******************************************************************************
* Function Name: MOTOR_A_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*  
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  MOTOR_A_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void MOTOR_A_SaveConfig(void) 
{
    
    #if(!MOTOR_A_UsingFixedFunction)
        #if(!MOTOR_A_PWMModeIsCenterAligned)
            MOTOR_A_backup.PWMPeriod = MOTOR_A_ReadPeriod();
        #endif /* (!MOTOR_A_PWMModeIsCenterAligned) */
        MOTOR_A_backup.PWMUdb = MOTOR_A_ReadCounter();
        #if (MOTOR_A_UseStatus)
            MOTOR_A_backup.InterruptMaskValue = MOTOR_A_STATUS_MASK;
        #endif /* (MOTOR_A_UseStatus) */
        
        #if(MOTOR_A_DeadBandMode == MOTOR_A__B_PWM__DBM_256_CLOCKS || \
            MOTOR_A_DeadBandMode == MOTOR_A__B_PWM__DBM_2_4_CLOCKS)
            MOTOR_A_backup.PWMdeadBandValue = MOTOR_A_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */
        
        #if(MOTOR_A_KillModeMinTime)
             MOTOR_A_backup.PWMKillCounterPeriod = MOTOR_A_ReadKillTime();
        #endif /* (MOTOR_A_KillModeMinTime) */
        
        #if(MOTOR_A_UseControl)
            MOTOR_A_backup.PWMControlRegister = MOTOR_A_ReadControlRegister();
        #endif /* (MOTOR_A_UseControl) */
    #endif  /* (!MOTOR_A_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: MOTOR_A_RestoreConfig
********************************************************************************
* 
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  MOTOR_A_backup:  Variables of this global structure are used to  
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void MOTOR_A_RestoreConfig(void) 
{
        #if(!MOTOR_A_UsingFixedFunction)
            #if(!MOTOR_A_PWMModeIsCenterAligned)
                MOTOR_A_WritePeriod(MOTOR_A_backup.PWMPeriod);
            #endif /* (!MOTOR_A_PWMModeIsCenterAligned) */
            MOTOR_A_WriteCounter(MOTOR_A_backup.PWMUdb);
            #if (MOTOR_A_UseStatus)
                MOTOR_A_STATUS_MASK = MOTOR_A_backup.InterruptMaskValue;
            #endif /* (MOTOR_A_UseStatus) */
            
            #if(MOTOR_A_DeadBandMode == MOTOR_A__B_PWM__DBM_256_CLOCKS || \
                MOTOR_A_DeadBandMode == MOTOR_A__B_PWM__DBM_2_4_CLOCKS)
                MOTOR_A_WriteDeadTime(MOTOR_A_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */
            
            #if(MOTOR_A_KillModeMinTime)
                MOTOR_A_WriteKillTime(MOTOR_A_backup.PWMKillCounterPeriod);
            #endif /* (MOTOR_A_KillModeMinTime) */
            
            #if(MOTOR_A_UseControl)
                MOTOR_A_WriteControlRegister(MOTOR_A_backup.PWMControlRegister); 
            #endif /* (MOTOR_A_UseControl) */
        #endif  /* (!MOTOR_A_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: MOTOR_A_Sleep
********************************************************************************
* 
* Summary:
*  Disables block's operation and saves the user configuration. Should be called 
*  just prior to entering sleep.
*  
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  MOTOR_A_backup.PWMEnableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void MOTOR_A_Sleep(void) 
{
    #if(MOTOR_A_UseControl)
        if(MOTOR_A_CTRL_ENABLE == (MOTOR_A_CONTROL & MOTOR_A_CTRL_ENABLE))
        {
            /*Component is enabled */
            MOTOR_A_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            MOTOR_A_backup.PWMEnableState = 0u;
        }
    #endif /* (MOTOR_A_UseControl) */

    /* Stop component */
    MOTOR_A_Stop();
    
    /* Save registers configuration */
    MOTOR_A_SaveConfig();
}


/*******************************************************************************
* Function Name: MOTOR_A_Wakeup
********************************************************************************
* 
* Summary:
*  Restores and enables the user configuration. Should be called just after 
*  awaking from sleep.
*  
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  MOTOR_A_backup.pwmEnable:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void MOTOR_A_Wakeup(void) 
{
     /* Restore registers values */
    MOTOR_A_RestoreConfig();
    
    if(MOTOR_A_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        MOTOR_A_Enable();
    } /* Do nothing if component's block was disabled before */
    
}


/* [] END OF FILE */
