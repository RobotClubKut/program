/*******************************************************************************
* File Name: UP.c  
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
#include "UP.h"


/*******************************************************************************
* Function Name: UP_Write
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
void UP_Write(uint8 value) 
{
    uint8 staticBits = (UP_DR & (uint8)(~UP_MASK));
    UP_DR = staticBits | ((uint8)(value << UP_SHIFT) & UP_MASK);
}


/*******************************************************************************
* Function Name: UP_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  UP_DM_STRONG     Strong Drive 
*  UP_DM_OD_HI      Open Drain, Drives High 
*  UP_DM_OD_LO      Open Drain, Drives Low 
*  UP_DM_RES_UP     Resistive Pull Up 
*  UP_DM_RES_DWN    Resistive Pull Down 
*  UP_DM_RES_UPDWN  Resistive Pull Up/Down 
*  UP_DM_DIG_HIZ    High Impedance Digital 
*  UP_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void UP_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(UP_0, mode);
}


/*******************************************************************************
* Function Name: UP_Read
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
*  Macro UP_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 UP_Read(void) 
{
    return (UP_PS & UP_MASK) >> UP_SHIFT;
}


/*******************************************************************************
* Function Name: UP_ReadDataReg
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
uint8 UP_ReadDataReg(void) 
{
    return (UP_DR & UP_MASK) >> UP_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(UP_INTSTAT) 

    /*******************************************************************************
    * Function Name: UP_ClearInterrupt
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
    uint8 UP_ClearInterrupt(void) 
    {
        return (UP_INTSTAT & UP_MASK) >> UP_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
