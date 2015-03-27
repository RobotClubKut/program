/*******************************************************************************
* File Name: air_5.c  
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
#include "air_5.h"


/*******************************************************************************
* Function Name: air_5_Write
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
void air_5_Write(uint8 value) 
{
    uint8 staticBits = (air_5_DR & (uint8)(~air_5_MASK));
    air_5_DR = staticBits | ((uint8)(value << air_5_SHIFT) & air_5_MASK);
}


/*******************************************************************************
* Function Name: air_5_SetDriveMode
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
void air_5_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(air_5_0, mode);
}


/*******************************************************************************
* Function Name: air_5_Read
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
*  Macro air_5_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 air_5_Read(void) 
{
    return (air_5_PS & air_5_MASK) >> air_5_SHIFT;
}


/*******************************************************************************
* Function Name: air_5_ReadDataReg
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
uint8 air_5_ReadDataReg(void) 
{
    return (air_5_DR & air_5_MASK) >> air_5_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(air_5_INTSTAT) 

    /*******************************************************************************
    * Function Name: air_5_ClearInterrupt
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
    uint8 air_5_ClearInterrupt(void) 
    {
        return (air_5_INTSTAT & air_5_MASK) >> air_5_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
