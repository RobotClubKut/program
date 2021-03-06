/*******************************************************************************
* File Name: rori_B.c  
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
#include "rori_B.h"


/*******************************************************************************
* Function Name: rori_B_Write
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
void rori_B_Write(uint8 value) 
{
    uint8 staticBits = (rori_B_DR & (uint8)(~rori_B_MASK));
    rori_B_DR = staticBits | ((uint8)(value << rori_B_SHIFT) & rori_B_MASK);
}


/*******************************************************************************
* Function Name: rori_B_SetDriveMode
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
void rori_B_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(rori_B_0, mode);
}


/*******************************************************************************
* Function Name: rori_B_Read
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
*  Macro rori_B_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 rori_B_Read(void) 
{
    return (rori_B_PS & rori_B_MASK) >> rori_B_SHIFT;
}


/*******************************************************************************
* Function Name: rori_B_ReadDataReg
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
uint8 rori_B_ReadDataReg(void) 
{
    return (rori_B_DR & rori_B_MASK) >> rori_B_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(rori_B_INTSTAT) 

    /*******************************************************************************
    * Function Name: rori_B_ClearInterrupt
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
    uint8 rori_B_ClearInterrupt(void) 
    {
        return (rori_B_INTSTAT & rori_B_MASK) >> rori_B_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
