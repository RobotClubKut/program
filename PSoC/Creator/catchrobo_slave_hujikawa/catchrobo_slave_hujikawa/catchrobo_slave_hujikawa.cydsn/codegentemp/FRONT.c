/*******************************************************************************
* File Name: FRONT.c  
* Version 2.0
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "FRONT.h"


/*******************************************************************************
* Function Name: FRONT_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void FRONT_Write(uint8 value) 
{
    uint8 staticBits = (FRONT_DR & (uint8)(~FRONT_MASK));
    FRONT_DR = staticBits | ((uint8)(value << FRONT_SHIFT) & FRONT_MASK);
}


/*******************************************************************************
* Function Name: FRONT_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  FRONT_DM_STRONG     Strong Drive 
*  FRONT_DM_OD_HI      Open Drain, Drives High 
*  FRONT_DM_OD_LO      Open Drain, Drives Low 
*  FRONT_DM_RES_UP     Resistive Pull Up 
*  FRONT_DM_RES_DWN    Resistive Pull Down 
*  FRONT_DM_RES_UPDWN  Resistive Pull Up/Down 
*  FRONT_DM_DIG_HIZ    High Impedance Digital 
*  FRONT_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void FRONT_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(FRONT_0, mode);
}


/*******************************************************************************
* Function Name: FRONT_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro FRONT_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 FRONT_Read(void) 
{
    return (FRONT_PS & FRONT_MASK) >> FRONT_SHIFT;
}


/*******************************************************************************
* Function Name: FRONT_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 FRONT_ReadDataReg(void) 
{
    return (FRONT_DR & FRONT_MASK) >> FRONT_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(FRONT_INTSTAT) 

    /*******************************************************************************
    * Function Name: FRONT_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 FRONT_ClearInterrupt(void) 
    {
        return (FRONT_INTSTAT & FRONT_MASK) >> FRONT_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
