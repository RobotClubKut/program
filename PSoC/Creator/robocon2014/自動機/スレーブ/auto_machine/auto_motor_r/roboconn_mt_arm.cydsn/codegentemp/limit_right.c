/*******************************************************************************
* File Name: limit_right.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
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
#include "limit_right.h"


/*******************************************************************************
* Function Name: limit_right_Write
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
void limit_right_Write(uint8 value) 
{
    uint8 staticBits = (limit_right_DR & (uint8)(~limit_right_MASK));
    limit_right_DR = staticBits | ((uint8)(value << limit_right_SHIFT) & limit_right_MASK);
}


/*******************************************************************************
* Function Name: limit_right_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  None
*
*******************************************************************************/
void limit_right_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(limit_right_0, mode);
}


/*******************************************************************************
* Function Name: limit_right_Read
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
*  Macro limit_right_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 limit_right_Read(void) 
{
    return (limit_right_PS & limit_right_MASK) >> limit_right_SHIFT;
}


/*******************************************************************************
* Function Name: limit_right_ReadDataReg
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
uint8 limit_right_ReadDataReg(void) 
{
    return (limit_right_DR & limit_right_MASK) >> limit_right_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(limit_right_INTSTAT) 

    /*******************************************************************************
    * Function Name: limit_right_ClearInterrupt
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
    uint8 limit_right_ClearInterrupt(void) 
    {
        return (limit_right_INTSTAT & limit_right_MASK) >> limit_right_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
