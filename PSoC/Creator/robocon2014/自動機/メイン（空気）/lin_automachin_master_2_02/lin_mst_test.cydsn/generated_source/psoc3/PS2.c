/*******************************************************************************
* File Name: PS2.c
* Version 2.30
*
* Description:
*  This file provides all API functionality of the UART component
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PS2.h"
#include "CyLib.h"
#if(PS2_INTERNAL_CLOCK_USED)
    #include "PS2_IntClock.h"
#endif /* End PS2_INTERNAL_CLOCK_USED */


/***************************************
* Global data allocation
***************************************/

uint8 PS2_initVar = 0u;
#if( PS2_TX_ENABLED && (PS2_TXBUFFERSIZE > PS2_FIFO_LENGTH))
    volatile uint8 PS2_txBuffer[PS2_TXBUFFERSIZE];
    volatile uint8 PS2_txBufferRead = 0u;
    uint8 PS2_txBufferWrite = 0u;
#endif /* End PS2_TX_ENABLED */
#if( ( PS2_RX_ENABLED || PS2_HD_ENABLED ) && \
     (PS2_RXBUFFERSIZE > PS2_FIFO_LENGTH) )
    volatile uint8 PS2_rxBuffer[PS2_RXBUFFERSIZE];
    volatile uint8 PS2_rxBufferRead = 0u;
    volatile uint8 PS2_rxBufferWrite = 0u;
    volatile uint8 PS2_rxBufferLoopDetect = 0u;
    volatile uint8 PS2_rxBufferOverflow = 0u;
    #if (PS2_RXHW_ADDRESS_ENABLED)
        volatile uint8 PS2_rxAddressMode = PS2_RXADDRESSMODE;
        volatile uint8 PS2_rxAddressDetected = 0u;
    #endif /* End EnableHWAddress */
#endif /* End PS2_RX_ENABLED */


/*******************************************************************************
* Function Name: PS2_Start
********************************************************************************
*
* Summary:
*  Initialize and Enable the UART component.
*  Enable the clock input to enable operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The PS2_intiVar variable is used to indicate initial
*  configuration of this component. The variable is initialized to zero (0u)
*  and set to one (1u) the first time UART_Start() is called. This allows for
*  component initialization without re-initialization in all subsequent calls
*  to the PS2_Start() routine.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void PS2_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(PS2_initVar == 0u)
    {
        PS2_Init();
        PS2_initVar = 1u;
    }
    PS2_Enable();
}


/*******************************************************************************
* Function Name: PS2_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  PS2_Start().
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void PS2_Init(void) 
{
    #if(PS2_RX_ENABLED || PS2_HD_ENABLED)

        #if(PS2_RX_INTERRUPT_ENABLED && (PS2_RXBUFFERSIZE > PS2_FIFO_LENGTH))
            /* Set the RX Interrupt. */
            (void)CyIntSetVector(PS2_RX_VECT_NUM, &PS2_RXISR);
            CyIntSetPriority(PS2_RX_VECT_NUM, PS2_RX_PRIOR_NUM);
        #endif /* End PS2_RX_INTERRUPT_ENABLED */

        #if (PS2_RXHW_ADDRESS_ENABLED)
            PS2_SetRxAddressMode(PS2_RXAddressMode);
            PS2_SetRxAddress1(PS2_RXHWADDRESS1);
            PS2_SetRxAddress2(PS2_RXHWADDRESS2);
        #endif /* End PS2_RXHW_ADDRESS_ENABLED */

        /* Init Count7 period */
        PS2_RXBITCTR_PERIOD_REG = PS2_RXBITCTR_INIT;
        /* Configure the Initial RX interrupt mask */
        PS2_RXSTATUS_MASK_REG  = PS2_INIT_RX_INTERRUPTS_MASK;
    #endif /* End PS2_RX_ENABLED || PS2_HD_ENABLED*/

    #if(PS2_TX_ENABLED)
        #if(PS2_TX_INTERRUPT_ENABLED && (PS2_TXBUFFERSIZE > PS2_FIFO_LENGTH))
            /* Set the TX Interrupt. */
            (void)CyIntSetVector(PS2_TX_VECT_NUM, &PS2_TXISR);
            CyIntSetPriority(PS2_TX_VECT_NUM, PS2_TX_PRIOR_NUM);
        #endif /* End PS2_TX_INTERRUPT_ENABLED */

        /* Write Counter Value for TX Bit Clk Generator*/
        #if(PS2_TXCLKGEN_DP)
            PS2_TXBITCLKGEN_CTR_REG = PS2_BIT_CENTER;
            PS2_TXBITCLKTX_COMPLETE_REG = (PS2_NUMBER_OF_DATA_BITS +
                        PS2_NUMBER_OF_START_BIT) * PS2_OVER_SAMPLE_COUNT;
        #else
            PS2_TXBITCTR_PERIOD_REG = ((PS2_NUMBER_OF_DATA_BITS +
                        PS2_NUMBER_OF_START_BIT) * PS2_OVER_SAMPLE_8) - 1u;
        #endif /* End PS2_TXCLKGEN_DP */

        /* Configure the Initial TX interrupt mask */
        #if(PS2_TX_INTERRUPT_ENABLED && (PS2_TXBUFFERSIZE > PS2_FIFO_LENGTH))
            PS2_TXSTATUS_MASK_REG = PS2_TX_STS_FIFO_EMPTY;
        #else
            PS2_TXSTATUS_MASK_REG = PS2_INIT_TX_INTERRUPTS_MASK;
        #endif /*End PS2_TX_INTERRUPT_ENABLED*/

    #endif /* End PS2_TX_ENABLED */

    #if(PS2_PARITY_TYPE_SW)  /* Write Parity to Control Register */
        PS2_WriteControlRegister( \
            (PS2_ReadControlRegister() & (uint8)~PS2_CTRL_PARITY_TYPE_MASK) | \
            (uint8)(PS2_PARITY_TYPE << PS2_CTRL_PARITY_TYPE0_SHIFT) );
    #endif /* End PS2_PARITY_TYPE_SW */
}


/*******************************************************************************
* Function Name: PS2_Enable
********************************************************************************
*
* Summary:
*  Enables the UART block operation
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  PS2_rxAddressDetected - set to initial state (0).
*
*******************************************************************************/
void PS2_Enable(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    #if(PS2_RX_ENABLED || PS2_HD_ENABLED)
        /*RX Counter (Count7) Enable */
        PS2_RXBITCTR_CONTROL_REG |= PS2_CNTR_ENABLE;
        /* Enable the RX Interrupt. */
        PS2_RXSTATUS_ACTL_REG  |= PS2_INT_ENABLE;
        #if(PS2_RX_INTERRUPT_ENABLED && (PS2_RXBUFFERSIZE > PS2_FIFO_LENGTH))
            CyIntEnable(PS2_RX_VECT_NUM);
            #if (PS2_RXHW_ADDRESS_ENABLED)
                PS2_rxAddressDetected = 0u;
            #endif /* End PS2_RXHW_ADDRESS_ENABLED */
        #endif /* End PS2_RX_INTERRUPT_ENABLED */
    #endif /* End PS2_RX_ENABLED || PS2_HD_ENABLED*/

    #if(PS2_TX_ENABLED)
        /*TX Counter (DP/Count7) Enable */
        #if(!PS2_TXCLKGEN_DP)
            PS2_TXBITCTR_CONTROL_REG |= PS2_CNTR_ENABLE;
        #endif /* End PS2_TXCLKGEN_DP */
        /* Enable the TX Interrupt. */
        PS2_TXSTATUS_ACTL_REG |= PS2_INT_ENABLE;
        #if(PS2_TX_INTERRUPT_ENABLED && (PS2_TXBUFFERSIZE > PS2_FIFO_LENGTH))
            CyIntEnable(PS2_TX_VECT_NUM);
        #endif /* End PS2_TX_INTERRUPT_ENABLED*/
     #endif /* End PS2_TX_ENABLED */

    #if(PS2_INTERNAL_CLOCK_USED)
        /* Enable the clock. */
        PS2_IntClock_Start();
    #endif /* End PS2_INTERNAL_CLOCK_USED */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PS2_Stop
********************************************************************************
*
* Summary:
*  Disable the UART component
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void PS2_Stop(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Write Bit Counter Disable */
    #if(PS2_RX_ENABLED || PS2_HD_ENABLED)
        PS2_RXBITCTR_CONTROL_REG &= (uint8)~PS2_CNTR_ENABLE;
    #endif /* End PS2_RX_ENABLED */

    #if(PS2_TX_ENABLED)
        #if(!PS2_TXCLKGEN_DP)
            PS2_TXBITCTR_CONTROL_REG &= (uint8)~PS2_CNTR_ENABLE;
        #endif /* End PS2_TXCLKGEN_DP */
    #endif /* PS2_TX_ENABLED */

    #if(PS2_INTERNAL_CLOCK_USED)
        /* Disable the clock. */
        PS2_IntClock_Stop();
    #endif /* End PS2_INTERNAL_CLOCK_USED */

    /* Disable internal interrupt component */
    #if(PS2_RX_ENABLED || PS2_HD_ENABLED)
        PS2_RXSTATUS_ACTL_REG  &= (uint8)~PS2_INT_ENABLE;
        #if(PS2_RX_INTERRUPT_ENABLED && (PS2_RXBUFFERSIZE > PS2_FIFO_LENGTH))
            PS2_DisableRxInt();
        #endif /* End PS2_RX_INTERRUPT_ENABLED */
    #endif /* End PS2_RX_ENABLED */

    #if(PS2_TX_ENABLED)
        PS2_TXSTATUS_ACTL_REG &= (uint8)~PS2_INT_ENABLE;
        #if(PS2_TX_INTERRUPT_ENABLED && (PS2_TXBUFFERSIZE > PS2_FIFO_LENGTH))
            PS2_DisableTxInt();
        #endif /* End PS2_TX_INTERRUPT_ENABLED */
    #endif /* End PS2_TX_ENABLED */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PS2_ReadControlRegister
********************************************************************************
*
* Summary:
*  Read the current state of the control register
*
* Parameters:
*  None.
*
* Return:
*  Current state of the control register.
*
*******************************************************************************/
uint8 PS2_ReadControlRegister(void) 
{
    #if( PS2_CONTROL_REG_REMOVED )
        return(0u);
    #else
        return(PS2_CONTROL_REG);
    #endif /* End PS2_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: PS2_WriteControlRegister
********************************************************************************
*
* Summary:
*  Writes an 8-bit value into the control register
*
* Parameters:
*  control:  control register value
*
* Return:
*  None.
*
*******************************************************************************/
void  PS2_WriteControlRegister(uint8 control) 
{
    #if( PS2_CONTROL_REG_REMOVED )
        if(control != 0u) { }      /* release compiler warning */
    #else
       PS2_CONTROL_REG = control;
    #endif /* End PS2_CONTROL_REG_REMOVED */
}


#if(PS2_RX_ENABLED || PS2_HD_ENABLED)

    #if(PS2_RX_INTERRUPT_ENABLED)

        /*******************************************************************************
        * Function Name: PS2_EnableRxInt
        ********************************************************************************
        *
        * Summary:
        *  Enable RX interrupt generation
        *
        * Parameters:
        *  None.
        *
        * Return:
        *  None.
        *
        * Theory:
        *  Enable the interrupt output -or- the interrupt component itself
        *
        *******************************************************************************/
        void PS2_EnableRxInt(void) 
        {
            CyIntEnable(PS2_RX_VECT_NUM);
        }


        /*******************************************************************************
        * Function Name: PS2_DisableRxInt
        ********************************************************************************
        *
        * Summary:
        *  Disable RX interrupt generation
        *
        * Parameters:
        *  None.
        *
        * Return:
        *  None.
        *
        * Theory:
        *  Disable the interrupt output -or- the interrupt component itself
        *
        *******************************************************************************/
        void PS2_DisableRxInt(void) 
        {
            CyIntDisable(PS2_RX_VECT_NUM);
        }

    #endif /* PS2_RX_INTERRUPT_ENABLED */


    /*******************************************************************************
    * Function Name: PS2_SetRxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configure which status bits trigger an interrupt event
    *
    * Parameters:
    *  IntSrc:  An or'd combination of the desired status bit masks (defined in
    *           the header file)
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void PS2_SetRxInterruptMode(uint8 intSrc) 
    {
        PS2_RXSTATUS_MASK_REG  = intSrc;
    }


    /*******************************************************************************
    * Function Name: PS2_ReadRxData
    ********************************************************************************
    *
    * Summary:
    *  Returns data in RX Data register without checking status register to
    *  determine if data is valid
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Received data from RX register
    *
    * Global Variables:
    *  PS2_rxBuffer - RAM buffer pointer for save received data.
    *  PS2_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  PS2_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  PS2_rxBufferLoopDetect - creared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 PS2_ReadRxData(void) 
    {
        uint8 rxData;

        #if(PS2_RXBUFFERSIZE > PS2_FIFO_LENGTH)
            uint8 loc_rxBufferRead;
            uint8 loc_rxBufferWrite;
            /* Protect variables that could change on interrupt. */
            /* Disable Rx interrupt. */
            #if(PS2_RX_INTERRUPT_ENABLED)
                PS2_DisableRxInt();
            #endif /* PS2_RX_INTERRUPT_ENABLED */
            loc_rxBufferRead = PS2_rxBufferRead;
            loc_rxBufferWrite = PS2_rxBufferWrite;

            if( (PS2_rxBufferLoopDetect != 0u) || (loc_rxBufferRead != loc_rxBufferWrite) )
            {
                rxData = PS2_rxBuffer[loc_rxBufferRead];
                loc_rxBufferRead++;

                if(loc_rxBufferRead >= PS2_RXBUFFERSIZE)
                {
                    loc_rxBufferRead = 0u;
                }
                /* Update the real pointer */
                PS2_rxBufferRead = loc_rxBufferRead;

                if(PS2_rxBufferLoopDetect != 0u )
                {
                    PS2_rxBufferLoopDetect = 0u;
                    #if( (PS2_RX_INTERRUPT_ENABLED) && (PS2_FLOW_CONTROL != 0u) && \
                         (PS2_RXBUFFERSIZE > PS2_FIFO_LENGTH) )
                        /* When Hardware Flow Control selected - return RX mask */
                        #if( PS2_HD_ENABLED )
                            if((PS2_CONTROL_REG & PS2_CTRL_HD_SEND) == 0u)
                            {   /* In Half duplex mode return RX mask only in RX
                                *  configuration set, otherwise
                                *  mask will be returned in LoadRxConfig() API.
                                */
                                PS2_RXSTATUS_MASK_REG  |= PS2_RX_STS_FIFO_NOTEMPTY;
                            }
                        #else
                            PS2_RXSTATUS_MASK_REG  |= PS2_RX_STS_FIFO_NOTEMPTY;
                        #endif /* end PS2_HD_ENABLED */
                    #endif /* PS2_RX_INTERRUPT_ENABLED and Hardware flow control*/
                }
            }
            else
            {   /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit*/
                rxData = PS2_RXDATA_REG;
            }

            /* Enable Rx interrupt. */
            #if(PS2_RX_INTERRUPT_ENABLED)
                PS2_EnableRxInt();
            #endif /* End PS2_RX_INTERRUPT_ENABLED */

        #else /* PS2_RXBUFFERSIZE > PS2_FIFO_LENGTH */

            /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit*/
            rxData = PS2_RXDATA_REG;

        #endif /* PS2_RXBUFFERSIZE > PS2_FIFO_LENGTH */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: PS2_ReadRxStatus
    ********************************************************************************
    *
    * Summary:
    *  Read the current state of the status register
    *  And detect software buffer overflow.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Current state of the status register.
    *
    * Global Variables:
    *  PS2_rxBufferOverflow - used to indicate overload condition.
    *   It set to one in RX interrupt when there isn?t free space in
    *   PS2_rxBufferRead to write new data. This condition returned
    *   and cleared to zero by this API as an
    *   PS2_RX_STS_SOFT_BUFF_OVER bit along with RX Status register
    *   bits.
    *
    *******************************************************************************/
    uint8 PS2_ReadRxStatus(void) 
    {
        uint8 status;

        status = PS2_RXSTATUS_REG & PS2_RX_HW_MASK;

        #if(PS2_RXBUFFERSIZE > PS2_FIFO_LENGTH)
            if( PS2_rxBufferOverflow != 0u )
            {
                status |= PS2_RX_STS_SOFT_BUFF_OVER;
                PS2_rxBufferOverflow = 0u;
            }
        #endif /* PS2_RXBUFFERSIZE */

        return(status);
    }


    /*******************************************************************************
    * Function Name: PS2_GetChar
    ********************************************************************************
    *
    * Summary:
    *  Reads UART RX buffer immediately, if data is not available or an error
    *  condition exists, zero is returned; otherwise, character is read and
    *  returned.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Character read from UART RX buffer. ASCII characters from 1 to 255 are valid.
    *  A returned zero signifies an error condition or no data available.
    *
    * Global Variables:
    *  PS2_rxBuffer - RAM buffer pointer for save received data.
    *  PS2_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  PS2_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  PS2_rxBufferLoopDetect - creared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 PS2_GetChar(void) 
    {
        uint8 rxData = 0u;
        uint8 rxStatus;

        #if(PS2_RXBUFFERSIZE > PS2_FIFO_LENGTH)
            uint8 loc_rxBufferRead;
            uint8 loc_rxBufferWrite;
            /* Protect variables that could change on interrupt. */
            /* Disable Rx interrupt. */
            #if(PS2_RX_INTERRUPT_ENABLED)
                PS2_DisableRxInt();
            #endif /* PS2_RX_INTERRUPT_ENABLED */
            loc_rxBufferRead = PS2_rxBufferRead;
            loc_rxBufferWrite = PS2_rxBufferWrite;

            if( (PS2_rxBufferLoopDetect != 0u) || (loc_rxBufferRead != loc_rxBufferWrite) )
            {
                rxData = PS2_rxBuffer[loc_rxBufferRead];
                loc_rxBufferRead++;
                if(loc_rxBufferRead >= PS2_RXBUFFERSIZE)
                {
                    loc_rxBufferRead = 0u;
                }
                /* Update the real pointer */
                PS2_rxBufferRead = loc_rxBufferRead;

                if(PS2_rxBufferLoopDetect > 0u )
                {
                    PS2_rxBufferLoopDetect = 0u;
                    #if( (PS2_RX_INTERRUPT_ENABLED) && (PS2_FLOW_CONTROL != 0u) )
                        /* When Hardware Flow Control selected - return RX mask */
                        #if( PS2_HD_ENABLED )
                            if((PS2_CONTROL_REG & PS2_CTRL_HD_SEND) == 0u)
                            {   /* In Half duplex mode return RX mask only if
                                *  RX configuration set, otherwise
                                *  mask will be returned in LoadRxConfig() API.
                                */
                                PS2_RXSTATUS_MASK_REG  |= PS2_RX_STS_FIFO_NOTEMPTY;
                            }
                        #else
                            PS2_RXSTATUS_MASK_REG  |= PS2_RX_STS_FIFO_NOTEMPTY;
                        #endif /* end PS2_HD_ENABLED */
                    #endif /* PS2_RX_INTERRUPT_ENABLED and Hardware flow control*/
                }

            }
            else
            {   rxStatus = PS2_RXSTATUS_REG;
                if((rxStatus & PS2_RX_STS_FIFO_NOTEMPTY) != 0u)
                {   /* Read received data from FIFO*/
                    rxData = PS2_RXDATA_REG;
                    /*Check status on error*/
                    if((rxStatus & (PS2_RX_STS_BREAK | PS2_RX_STS_PAR_ERROR |
                                   PS2_RX_STS_STOP_ERROR | PS2_RX_STS_OVERRUN)) != 0u)
                    {
                        rxData = 0u;
                    }
                }
            }

            /* Enable Rx interrupt. */
            #if(PS2_RX_INTERRUPT_ENABLED)
                PS2_EnableRxInt();
            #endif /* PS2_RX_INTERRUPT_ENABLED */

        #else /* PS2_RXBUFFERSIZE > PS2_FIFO_LENGTH */

            rxStatus =PS2_RXSTATUS_REG;
            if((rxStatus & PS2_RX_STS_FIFO_NOTEMPTY) != 0u)
            {   /* Read received data from FIFO*/
                rxData = PS2_RXDATA_REG;
                /*Check status on error*/
                if((rxStatus & (PS2_RX_STS_BREAK | PS2_RX_STS_PAR_ERROR |
                               PS2_RX_STS_STOP_ERROR | PS2_RX_STS_OVERRUN)) != 0u)
                {
                    rxData = 0u;
                }
            }
        #endif /* PS2_RXBUFFERSIZE > PS2_FIFO_LENGTH */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: PS2_GetByte
    ********************************************************************************
    *
    * Summary:
    *  Grab the next available byte of data from the recieve FIFO
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  MSB contains Status Register and LSB contains UART RX data
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint16 PS2_GetByte(void) 
    {
        return ( ((uint16)PS2_ReadRxStatus() << 8u) | PS2_ReadRxData() );
    }


    /*******************************************************************************
    * Function Name: PS2_GetRxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Determine the amount of bytes left in the RX buffer and return the count in
    *  bytes
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  uint8: Integer count of the number of bytes left
    *  in the RX buffer
    *
    * Global Variables:
    *  PS2_rxBufferWrite - used to calculate left bytes.
    *  PS2_rxBufferRead - used to calculate left bytes.
    *  PS2_rxBufferLoopDetect - checked to decide left bytes amount.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the RX Buffer is.
    *
    *******************************************************************************/
    uint8 PS2_GetRxBufferSize(void)
                                                            
    {
        uint8 size;

        #if(PS2_RXBUFFERSIZE > PS2_FIFO_LENGTH)

            /* Disable Rx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(PS2_RX_INTERRUPT_ENABLED)
                PS2_DisableRxInt();
            #endif /* PS2_RX_INTERRUPT_ENABLED */

            if(PS2_rxBufferRead == PS2_rxBufferWrite)
            {
                if(PS2_rxBufferLoopDetect > 0u)
                {
                    size = PS2_RXBUFFERSIZE;
                }
                else
                {
                    size = 0u;
                }
            }
            else if(PS2_rxBufferRead < PS2_rxBufferWrite)
            {
                size = (PS2_rxBufferWrite - PS2_rxBufferRead);
            }
            else
            {
                size = (PS2_RXBUFFERSIZE - PS2_rxBufferRead) + PS2_rxBufferWrite;
            }

            /* Enable Rx interrupt. */
            #if(PS2_RX_INTERRUPT_ENABLED)
                PS2_EnableRxInt();
            #endif /* End PS2_RX_INTERRUPT_ENABLED */

        #else /* PS2_RXBUFFERSIZE > PS2_FIFO_LENGTH */

            /* We can only know if there is data in the fifo. */
            size = ((PS2_RXSTATUS_REG & PS2_RX_STS_FIFO_NOTEMPTY) != 0u) ? 1u : 0u;

        #endif /* End PS2_RXBUFFERSIZE > PS2_FIFO_LENGTH */

        return(size);
    }


    /*******************************************************************************
    * Function Name: PS2_ClearRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the RX RAM buffer by setting the read and write pointers both to zero.
    *  Clears hardware RX FIFO.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  PS2_rxBufferWrite - cleared to zero.
    *  PS2_rxBufferRead - cleared to zero.
    *  PS2_rxBufferLoopDetect - cleared to zero.
    *  PS2_rxBufferOverflow - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to
    *  read and writing will resume at address 0 overwriting any data that may
    *  have remained in the RAM.
    *
    * Side Effects:
    *  Any received data not read from the RAM or FIFO buffer will be lost.
    *******************************************************************************/
    void PS2_ClearRxBuffer(void) 
    {
        uint8 enableInterrupts;

        /* clear the HW FIFO */
        /* Enter critical section */
        enableInterrupts = CyEnterCriticalSection();
        PS2_RXDATA_AUX_CTL_REG |=  PS2_RX_FIFO_CLR;
        PS2_RXDATA_AUX_CTL_REG &= (uint8)~PS2_RX_FIFO_CLR;
        /* Exit critical section */
        CyExitCriticalSection(enableInterrupts);

        #if(PS2_RXBUFFERSIZE > PS2_FIFO_LENGTH)
            /* Disable Rx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(PS2_RX_INTERRUPT_ENABLED)
                PS2_DisableRxInt();
            #endif /* End PS2_RX_INTERRUPT_ENABLED */

            PS2_rxBufferRead = 0u;
            PS2_rxBufferWrite = 0u;
            PS2_rxBufferLoopDetect = 0u;
            PS2_rxBufferOverflow = 0u;

            /* Enable Rx interrupt. */
            #if(PS2_RX_INTERRUPT_ENABLED)
                PS2_EnableRxInt();
            #endif /* End PS2_RX_INTERRUPT_ENABLED */
        #endif /* End PS2_RXBUFFERSIZE > PS2_FIFO_LENGTH */

    }


    /*******************************************************************************
    * Function Name: PS2_SetRxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Set the receive addressing mode
    *
    * Parameters:
    *  addressMode: Enumerated value indicating the mode of RX addressing
    *  PS2__B_UART__AM_SW_BYTE_BYTE -  Software Byte-by-Byte address
    *                                               detection
    *  PS2__B_UART__AM_SW_DETECT_TO_BUFFER - Software Detect to Buffer
    *                                               address detection
    *  PS2__B_UART__AM_HW_BYTE_BY_BYTE - Hardware Byte-by-Byte address
    *                                               detection
    *  PS2__B_UART__AM_HW_DETECT_TO_BUFFER - Hardware Detect to Buffer
    *                                               address detection
    *  PS2__B_UART__AM_NONE - No address detection
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  PS2_rxAddressMode - the parameter stored in this variable for
    *   the farther usage in RX ISR.
    *  PS2_rxAddressDetected - set to initial state (0).
    *
    *******************************************************************************/
    void PS2_SetRxAddressMode(uint8 addressMode)
                                                        
    {
        #if(PS2_RXHW_ADDRESS_ENABLED)
            #if(PS2_CONTROL_REG_REMOVED)
                if(addressMode != 0u) { }     /* release compiler warning */
            #else /* PS2_CONTROL_REG_REMOVED */
                uint8 tmpCtrl;
                tmpCtrl = PS2_CONTROL_REG & (uint8)~PS2_CTRL_RXADDR_MODE_MASK;
                tmpCtrl |= (uint8)(addressMode << PS2_CTRL_RXADDR_MODE0_SHIFT);
                PS2_CONTROL_REG = tmpCtrl;
                #if(PS2_RX_INTERRUPT_ENABLED && \
                   (PS2_RXBUFFERSIZE > PS2_FIFO_LENGTH) )
                    PS2_rxAddressMode = addressMode;
                    PS2_rxAddressDetected = 0u;
                #endif /* End PS2_RXBUFFERSIZE > PS2_FIFO_LENGTH*/
            #endif /* End PS2_CONTROL_REG_REMOVED */
        #else /* PS2_RXHW_ADDRESS_ENABLED */
            if(addressMode != 0u) { }     /* release compiler warning */
        #endif /* End PS2_RXHW_ADDRESS_ENABLED */
    }


    /*******************************************************************************
    * Function Name: PS2_SetRxAddress1
    ********************************************************************************
    *
    * Summary:
    *  Set the first hardware address compare value
    *
    * Parameters:
    *  address
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void PS2_SetRxAddress1(uint8 address) 

    {
        PS2_RXADDRESS1_REG = address;
    }


    /*******************************************************************************
    * Function Name: PS2_SetRxAddress2
    ********************************************************************************
    *
    * Summary:
    *  Set the second hardware address compare value
    *
    * Parameters:
    *  address
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void PS2_SetRxAddress2(uint8 address) 
    {
        PS2_RXADDRESS2_REG = address;
    }

#endif  /* PS2_RX_ENABLED || PS2_HD_ENABLED*/


#if( (PS2_TX_ENABLED) || (PS2_HD_ENABLED) )

    #if(PS2_TX_INTERRUPT_ENABLED)

        /*******************************************************************************
        * Function Name: PS2_EnableTxInt
        ********************************************************************************
        *
        * Summary:
        *  Enable TX interrupt generation
        *
        * Parameters:
        *  None.
        *
        * Return:
        *  None.
        *
        * Theory:
        *  Enable the interrupt output -or- the interrupt component itself
        *
        *******************************************************************************/
        void PS2_EnableTxInt(void) 
        {
            CyIntEnable(PS2_TX_VECT_NUM);
        }


        /*******************************************************************************
        * Function Name: PS2_DisableTxInt
        ********************************************************************************
        *
        * Summary:
        *  Disable TX interrupt generation
        *
        * Parameters:
        *  None.
        *
        * Return:
        *  None.
        *
        * Theory:
        *  Disable the interrupt output -or- the interrupt component itself
        *
        *******************************************************************************/
        void PS2_DisableTxInt(void) 
        {
            CyIntDisable(PS2_TX_VECT_NUM);
        }

    #endif /* PS2_TX_INTERRUPT_ENABLED */


    /*******************************************************************************
    * Function Name: PS2_SetTxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configure which status bits trigger an interrupt event
    *
    * Parameters:
    *  intSrc: An or'd combination of the desired status bit masks (defined in
    *          the header file)
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void PS2_SetTxInterruptMode(uint8 intSrc) 
    {
        PS2_TXSTATUS_MASK_REG = intSrc;
    }


    /*******************************************************************************
    * Function Name: PS2_WriteTxData
    ********************************************************************************
    *
    * Summary:
    *  Write a byte of data to the Transmit FIFO or TX buffer to be sent when the
    *  bus is available. WriteTxData sends a byte without checking for buffer room
    *  or status. It is up to the user to separately check status.
    *
    * Parameters:
    *  TXDataByte: byte of data to place in the transmit FIFO
    *
    * Return:
    * void
    *
    * Global Variables:
    *  PS2_txBuffer - RAM buffer pointer for save data for transmission
    *  PS2_txBufferWrite - cyclic index for write to txBuffer,
    *    incremented after each byte saved to buffer.
    *  PS2_txBufferRead - cyclic index for read from txBuffer,
    *    checked to identify the condition to write to FIFO directly or to TX buffer
    *  PS2_initVar - checked to identify that the component has been
    *    initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void PS2_WriteTxData(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function*/
        if(PS2_initVar != 0u)
        {
            #if(PS2_TXBUFFERSIZE > PS2_FIFO_LENGTH)

                /* Disable Tx interrupt. */
                /* Protect variables that could change on interrupt. */
                #if(PS2_TX_INTERRUPT_ENABLED)
                    PS2_DisableTxInt();
                #endif /* End PS2_TX_INTERRUPT_ENABLED */

                if( (PS2_txBufferRead == PS2_txBufferWrite) &&
                    ((PS2_TXSTATUS_REG & PS2_TX_STS_FIFO_FULL) == 0u) )
                {
                    /* Add directly to the FIFO. */
                    PS2_TXDATA_REG = txDataByte;
                }
                else
                {
                    if(PS2_txBufferWrite >= PS2_TXBUFFERSIZE)
                    {
                        PS2_txBufferWrite = 0u;
                    }

                    PS2_txBuffer[PS2_txBufferWrite] = txDataByte;

                    /* Add to the software buffer. */
                    PS2_txBufferWrite++;

                }

                /* Enable Tx interrupt. */
                #if(PS2_TX_INTERRUPT_ENABLED)
                    PS2_EnableTxInt();
                #endif /* End PS2_TX_INTERRUPT_ENABLED */

            #else /* PS2_TXBUFFERSIZE > PS2_FIFO_LENGTH */

                /* Add directly to the FIFO. */
                PS2_TXDATA_REG = txDataByte;

            #endif /* End PS2_TXBUFFERSIZE > PS2_FIFO_LENGTH */
        }
    }


    /*******************************************************************************
    * Function Name: PS2_ReadTxStatus
    ********************************************************************************
    *
    * Summary:
    *  Read the status register for the component
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Contents of the status register
    *
    * Theory:
    *  This function reads the status register which is clear on read. It is up to
    *  the user to handle all bits in this return value accordingly, even if the bit
    *  was not enabled as an interrupt source the event happened and must be handled
    *  accordingly.
    *
    *******************************************************************************/
    uint8 PS2_ReadTxStatus(void) 
    {
        return(PS2_TXSTATUS_REG);
    }


    /*******************************************************************************
    * Function Name: PS2_PutChar
    ********************************************************************************
    *
    * Summary:
    *  Wait to send byte until TX register or buffer has room.
    *
    * Parameters:
    *  txDataByte: The 8-bit data value to send across the UART.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  PS2_txBuffer - RAM buffer pointer for save data for transmission
    *  PS2_txBufferWrite - cyclic index for write to txBuffer,
    *     checked to identify free space in txBuffer and incremented after each byte
    *     saved to buffer.
    *  PS2_txBufferRead - cyclic index for read from txBuffer,
    *     checked to identify free space in txBuffer.
    *  PS2_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to transmit any byte of data in a single transfer
    *
    *******************************************************************************/
    void PS2_PutChar(uint8 txDataByte) 
    {
            #if(PS2_TXBUFFERSIZE > PS2_FIFO_LENGTH)
                /* The temporary output pointer is used since it takes two instructions
                *  to increment with a wrap, and we can't risk doing that with the real
                *  pointer and getting an interrupt in between instructions.
                */
                uint8 loc_txBufferWrite;
                uint8 loc_txBufferRead;

                do{
                    /* Block if software buffer is full, so we don't overwrite. */
                    #if ((PS2_TXBUFFERSIZE > PS2_MAX_BYTE_VALUE) && (CY_PSOC3))
                        /* Disable TX interrupt to protect variables that could change on interrupt */
                        CyIntDisable(PS2_TX_VECT_NUM);
                    #endif /* End TXBUFFERSIZE > 255 */
                    loc_txBufferWrite = PS2_txBufferWrite;
                    loc_txBufferRead = PS2_txBufferRead;
                    #if ((PS2_TXBUFFERSIZE > PS2_MAX_BYTE_VALUE) && (CY_PSOC3))
                        /* Enable interrupt to continue transmission */
                        CyIntEnable(PS2_TX_VECT_NUM);
                    #endif /* End TXBUFFERSIZE > 255 */
                }while( (loc_txBufferWrite < loc_txBufferRead) ? (loc_txBufferWrite == (loc_txBufferRead - 1u)) :
                                        ((loc_txBufferWrite - loc_txBufferRead) ==
                                        (uint8)(PS2_TXBUFFERSIZE - 1u)) );

                if( (loc_txBufferRead == loc_txBufferWrite) &&
                    ((PS2_TXSTATUS_REG & PS2_TX_STS_FIFO_FULL) == 0u) )
                {
                    /* Add directly to the FIFO. */
                    PS2_TXDATA_REG = txDataByte;
                }
                else
                {
                    if(loc_txBufferWrite >= PS2_TXBUFFERSIZE)
                    {
                        loc_txBufferWrite = 0u;
                    }
                    /* Add to the software buffer. */
                    PS2_txBuffer[loc_txBufferWrite] = txDataByte;
                    loc_txBufferWrite++;

                    /* Finally, update the real output pointer */
                    #if ((PS2_TXBUFFERSIZE > PS2_MAX_BYTE_VALUE) && (CY_PSOC3))
                        CyIntDisable(PS2_TX_VECT_NUM);
                    #endif /* End TXBUFFERSIZE > 255 */
                    PS2_txBufferWrite = loc_txBufferWrite;
                    #if ((PS2_TXBUFFERSIZE > PS2_MAX_BYTE_VALUE) && (CY_PSOC3))
                        CyIntEnable(PS2_TX_VECT_NUM);
                    #endif /* End TXBUFFERSIZE > 255 */
                }

            #else /* PS2_TXBUFFERSIZE > PS2_FIFO_LENGTH */

                while((PS2_TXSTATUS_REG & PS2_TX_STS_FIFO_FULL) != 0u)
                {
                    ; /* Wait for room in the FIFO. */
                }

                /* Add directly to the FIFO. */
                PS2_TXDATA_REG = txDataByte;

            #endif /* End PS2_TXBUFFERSIZE > PS2_FIFO_LENGTH */
    }


    /*******************************************************************************
    * Function Name: PS2_PutString
    ********************************************************************************
    *
    * Summary:
    *  Write a Sequence of bytes on the Transmit line. Data comes from RAM or ROM.
    *
    * Parameters:
    *  string: char pointer to character string of Data to Send.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  PS2_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  This function will block if there is not enough memory to place the whole
    *  string, it will block until the entire string has been written to the
    *  transmit buffer.
    *
    *******************************************************************************/
    void PS2_PutString(const char8 string[]) 
    {
        uint16 buf_index = 0u;
        /* If not Initialized then skip this function*/
        if(PS2_initVar != 0u)
        {
            /* This is a blocking function, it will not exit until all data is sent*/
            while(string[buf_index] != (char8)0)
            {
                PS2_PutChar((uint8)string[buf_index]);
                buf_index++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: PS2_PutArray
    ********************************************************************************
    *
    * Summary:
    *  Write a Sequence of bytes on the Transmit line. Data comes from RAM or ROM.
    *
    * Parameters:
    *  string: Address of the memory array residing in RAM or ROM.
    *  byteCount: Number of Bytes to be transmitted.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  PS2_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void PS2_PutArray(const uint8 string[], uint8 byteCount)
                                                                    
    {
        uint8 buf_index = 0u;
        /* If not Initialized then skip this function*/
        if(PS2_initVar != 0u)
        {
            do
            {
                PS2_PutChar(string[buf_index]);
                buf_index++;
            }while(buf_index < byteCount);
        }
    }


    /*******************************************************************************
    * Function Name: PS2_PutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Write a character and then carriage return and line feed.
    *
    * Parameters:
    *  txDataByte: uint8 Character to send.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  PS2_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void PS2_PutCRLF(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function*/
        if(PS2_initVar != 0u)
        {
            PS2_PutChar(txDataByte);
            PS2_PutChar(0x0Du);
            PS2_PutChar(0x0Au);
        }
    }


    /*******************************************************************************
    * Function Name: PS2_GetTxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Determine the amount of space left in the TX buffer and return the count in
    *  bytes
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Integer count of the number of bytes left in the TX buffer
    *
    * Global Variables:
    *  PS2_txBufferWrite - used to calculate left space.
    *  PS2_txBufferRead - used to calculate left space.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the TX Buffer is.
    *
    *******************************************************************************/
    uint8 PS2_GetTxBufferSize(void)
                                                            
    {
        uint8 size;

        #if(PS2_TXBUFFERSIZE > PS2_FIFO_LENGTH)

            /* Disable Tx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(PS2_TX_INTERRUPT_ENABLED)
                PS2_DisableTxInt();
            #endif /* End PS2_TX_INTERRUPT_ENABLED */

            if(PS2_txBufferRead == PS2_txBufferWrite)
            {
                size = 0u;
            }
            else if(PS2_txBufferRead < PS2_txBufferWrite)
            {
                size = (PS2_txBufferWrite - PS2_txBufferRead);
            }
            else
            {
                size = (PS2_TXBUFFERSIZE - PS2_txBufferRead) + PS2_txBufferWrite;
            }

            /* Enable Tx interrupt. */
            #if(PS2_TX_INTERRUPT_ENABLED)
                PS2_EnableTxInt();
            #endif /* End PS2_TX_INTERRUPT_ENABLED */

        #else /* PS2_TXBUFFERSIZE > PS2_FIFO_LENGTH */

            size = PS2_TXSTATUS_REG;

            /* Is the fifo is full. */
            if((size & PS2_TX_STS_FIFO_FULL) != 0u)
            {
                size = PS2_FIFO_LENGTH;
            }
            else if((size & PS2_TX_STS_FIFO_EMPTY) != 0u)
            {
                size = 0u;
            }
            else
            {
                /* We only know there is data in the fifo. */
                size = 1u;
            }

        #endif /* End PS2_TXBUFFERSIZE > PS2_FIFO_LENGTH */

        return(size);
    }


    /*******************************************************************************
    * Function Name: PS2_ClearTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the TX RAM buffer by setting the read and write pointers both to zero.
    *  Clears the hardware TX FIFO.  Any data present in the FIFO will not be sent.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  PS2_txBufferWrite - cleared to zero.
    *  PS2_txBufferRead - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to
    *  read and writing will resume at address 0 overwriting any data that may have
    *  remained in the RAM.
    *
    * Side Effects:
    *  Any received data not read from the RAM buffer will be lost when overwritten.
    *
    *******************************************************************************/
    void PS2_ClearTxBuffer(void) 
    {
        uint8 enableInterrupts;

        /* Enter critical section */
        enableInterrupts = CyEnterCriticalSection();
        /* clear the HW FIFO */
        PS2_TXDATA_AUX_CTL_REG |=  PS2_TX_FIFO_CLR;
        PS2_TXDATA_AUX_CTL_REG &= (uint8)~PS2_TX_FIFO_CLR;
        /* Exit critical section */
        CyExitCriticalSection(enableInterrupts);

        #if(PS2_TXBUFFERSIZE > PS2_FIFO_LENGTH)

            /* Disable Tx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(PS2_TX_INTERRUPT_ENABLED)
                PS2_DisableTxInt();
            #endif /* End PS2_TX_INTERRUPT_ENABLED */

            PS2_txBufferRead = 0u;
            PS2_txBufferWrite = 0u;

            /* Enable Tx interrupt. */
            #if(PS2_TX_INTERRUPT_ENABLED)
                PS2_EnableTxInt();
            #endif /* End PS2_TX_INTERRUPT_ENABLED */

        #endif /* End PS2_TXBUFFERSIZE > PS2_FIFO_LENGTH */
    }


    /*******************************************************************************
    * Function Name: PS2_SendBreak
    ********************************************************************************
    *
    * Summary:
    *  Write a Break command to the UART
    *
    * Parameters:
    *  uint8 retMode:  Wait mode,
    *   0 - Initialize registers for Break, sends the Break signal and return
    *       imediately.
    *   1 - Wait until Break sending is complete, reinitialize registers to normal
    *       transmission mode then return.
    *   2 - Reinitialize registers to normal transmission mode then return.
    *   3 - both steps: 0 and 1
    *       init registers for Break, send Break signal
    *       wait until Break sending is complete, reinit registers to normal
    *       transmission mode then return.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  PS2_initVar - checked to identify that the component has been
    *     initialized.
    *  tx_period - static variable, used for keeping TX period configuration.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  SendBreak function initializes registers to send 13-bit break signal. It is
    *  important to return the registers configuration to normal for continue 8-bit
    *  operation.
    *  Trere are 3 variants for this API usage:
    *  1) SendBreak(3) - function will send the Break signal and take care on the
    *     configuration returning. Funcition will block CPU untill transmition
    *     complete.
    *  2) User may want to use bloking time if UART configured to the low speed
    *     operation
    *     Emample for this case:
    *     SendBreak(0);     - init Break signal transmition
    *         Add your code here to use CPU time
    *     SendBreak(1);     - complete Break operation
    *  3) Same to 2) but user may want to init and use the interrupt for complete
    *     break operation.
    *     Example for this case:
    *     Init TX interrupt whith "TX - On TX Complete" parameter
    *     SendBreak(0);     - init Break signal transmition
    *         Add your code here to use CPU time
    *     When interrupt appear with UART_TX_STS_COMPLETE status:
    *     SendBreak(2);     - complete Break operation
    *
    * Side Effects:
    *   Uses static variable to keep registers configuration.
    *
    *******************************************************************************/
    void PS2_SendBreak(uint8 retMode) 
    {

        /* If not Initialized then skip this function*/
        if(PS2_initVar != 0u)
        {
            /*Set the Counter to 13-bits and transmit a 00 byte*/
            /*When that is done then reset the counter value back*/
            uint8 tmpStat;

            #if(PS2_HD_ENABLED) /* Half Duplex mode*/

                if( (retMode == PS2_SEND_BREAK) ||
                    (retMode == PS2_SEND_WAIT_REINIT ) )
                {
                    /* CTRL_HD_SEND_BREAK - sends break bits in HD mode*/
                    PS2_WriteControlRegister(PS2_ReadControlRegister() |
                                                          PS2_CTRL_HD_SEND_BREAK);
                    /* Send zeros*/
                    PS2_TXDATA_REG = 0u;

                    do /*wait until transmit starts*/
                    {
                        tmpStat = PS2_TXSTATUS_REG;
                    }while((tmpStat & PS2_TX_STS_FIFO_EMPTY) != 0u);
                }

                if( (retMode == PS2_WAIT_FOR_COMPLETE_REINIT) ||
                    (retMode == PS2_SEND_WAIT_REINIT) )
                {
                    do /*wait until transmit complete*/
                    {
                        tmpStat = PS2_TXSTATUS_REG;
                    }while(((uint8)~tmpStat & PS2_TX_STS_COMPLETE) != 0u);
                }

                if( (retMode == PS2_WAIT_FOR_COMPLETE_REINIT) ||
                    (retMode == PS2_REINIT) ||
                    (retMode == PS2_SEND_WAIT_REINIT) )
                {
                    PS2_WriteControlRegister(PS2_ReadControlRegister() &
                                                  (uint8)~PS2_CTRL_HD_SEND_BREAK);
                }

            #else /* PS2_HD_ENABLED Full Duplex mode */

                static uint8 tx_period;

                if( (retMode == PS2_SEND_BREAK) ||
                    (retMode == PS2_SEND_WAIT_REINIT) )
                {
                    /* CTRL_HD_SEND_BREAK - skip to send parity bit at Break signal in Full Duplex mode*/
                    #if( (PS2_PARITY_TYPE != PS2__B_UART__NONE_REVB) || \
                                        (PS2_PARITY_TYPE_SW != 0u) )
                        PS2_WriteControlRegister(PS2_ReadControlRegister() |
                                                              PS2_CTRL_HD_SEND_BREAK);
                    #endif /* End PS2_PARITY_TYPE != PS2__B_UART__NONE_REVB  */

                    #if(PS2_TXCLKGEN_DP)
                        tx_period = PS2_TXBITCLKTX_COMPLETE_REG;
                        PS2_TXBITCLKTX_COMPLETE_REG = PS2_TXBITCTR_BREAKBITS;
                    #else
                        tx_period = PS2_TXBITCTR_PERIOD_REG;
                        PS2_TXBITCTR_PERIOD_REG = PS2_TXBITCTR_BREAKBITS8X;
                    #endif /* End PS2_TXCLKGEN_DP */

                    /* Send zeros*/
                    PS2_TXDATA_REG = 0u;

                    do /* wait until transmit starts */
                    {
                        tmpStat = PS2_TXSTATUS_REG;
                    }while((tmpStat & PS2_TX_STS_FIFO_EMPTY) != 0u);
                }

                if( (retMode == PS2_WAIT_FOR_COMPLETE_REINIT) ||
                    (retMode == PS2_SEND_WAIT_REINIT) )
                {
                    do /*wait until transmit complete*/
                    {
                        tmpStat = PS2_TXSTATUS_REG;
                    }while(((uint8)~tmpStat & PS2_TX_STS_COMPLETE) != 0u);
                }

                if( (retMode == PS2_WAIT_FOR_COMPLETE_REINIT) ||
                    (retMode == PS2_REINIT) ||
                    (retMode == PS2_SEND_WAIT_REINIT) )
                {

                    #if(PS2_TXCLKGEN_DP)
                        PS2_TXBITCLKTX_COMPLETE_REG = tx_period;
                    #else
                        PS2_TXBITCTR_PERIOD_REG = tx_period;
                    #endif /* End PS2_TXCLKGEN_DP */

                    #if( (PS2_PARITY_TYPE != PS2__B_UART__NONE_REVB) || \
                         (PS2_PARITY_TYPE_SW != 0u) )
                        PS2_WriteControlRegister(PS2_ReadControlRegister() &
                                                      (uint8)~PS2_CTRL_HD_SEND_BREAK);
                    #endif /* End PS2_PARITY_TYPE != NONE */
                }
            #endif    /* End PS2_HD_ENABLED */
        }
    }


    /*******************************************************************************
    * Function Name: PS2_SetTxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Set the transmit addressing mode
    *
    * Parameters:
    *  addressMode: 0 -> Space
    *               1 -> Mark
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void PS2_SetTxAddressMode(uint8 addressMode) 
    {
        /* Mark/Space sending enable*/
        if(addressMode != 0u)
        {
            #if( PS2_CONTROL_REG_REMOVED == 0u )
                PS2_WriteControlRegister(PS2_ReadControlRegister() |
                                                      PS2_CTRL_MARK);
            #endif /* End PS2_CONTROL_REG_REMOVED == 0u */
        }
        else
        {
            #if( PS2_CONTROL_REG_REMOVED == 0u )
                PS2_WriteControlRegister(PS2_ReadControlRegister() &
                                                    (uint8)~PS2_CTRL_MARK);
            #endif /* End PS2_CONTROL_REG_REMOVED == 0u */
        }
    }

#endif  /* EndPS2_TX_ENABLED */

#if(PS2_HD_ENABLED)


    /*******************************************************************************
    * Function Name: PS2_LoadTxConfig
    ********************************************************************************
    *
    * Summary:
    *  Unloads the Rx configuration if required and loads the
    *  Tx configuration. It is the users responsibility to ensure that any
    *  transaction is complete and it is safe to unload the Tx
    *  configuration.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Valid only for half duplex UART.
    *
    * Side Effects:
    *  Disable RX interrupt mask, when software buffer has been used.
    *
    *******************************************************************************/
    void PS2_LoadTxConfig(void) 
    {
        #if((PS2_RX_INTERRUPT_ENABLED) && (PS2_RXBUFFERSIZE > PS2_FIFO_LENGTH))
            /* Disable RX interrupts before set TX configuration */
            PS2_SetRxInterruptMode(0u);
        #endif /* PS2_RX_INTERRUPT_ENABLED */

        PS2_WriteControlRegister(PS2_ReadControlRegister() | PS2_CTRL_HD_SEND);
        PS2_RXBITCTR_PERIOD_REG = PS2_HD_TXBITCTR_INIT;
        #if(CY_UDB_V0) /* Manually clear status register when mode has been changed */
            /* Clear status register */
            CY_GET_REG8(PS2_RXSTATUS_PTR);
        #endif /* CY_UDB_V0 */
    }


    /*******************************************************************************
    * Function Name: PS2_LoadRxConfig
    ********************************************************************************
    *
    * Summary:
    *  Unloads the Tx configuration if required and loads the
    *  Rx configuration. It is the users responsibility to ensure that any
    *  transaction is complete and it is safe to unload the Rx
    *  configuration.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Valid only for half duplex UART
    *
    * Side Effects:
    *  Set RX interrupt mask based on customizer settings, when software buffer
    *  has been used.
    *
    *******************************************************************************/
    void PS2_LoadRxConfig(void) 
    {
        PS2_WriteControlRegister(PS2_ReadControlRegister() &
                                                (uint8)~PS2_CTRL_HD_SEND);
        PS2_RXBITCTR_PERIOD_REG = PS2_HD_RXBITCTR_INIT;
        #if(CY_UDB_V0) /* Manually clear status register when mode has been changed */
            /* Clear status register */
            CY_GET_REG8(PS2_RXSTATUS_PTR);
        #endif /* CY_UDB_V0 */

        #if((PS2_RX_INTERRUPT_ENABLED) && (PS2_RXBUFFERSIZE > PS2_FIFO_LENGTH))
            /* Enable RX interrupt after set RX configuration */
            PS2_SetRxInterruptMode(PS2_INIT_RX_INTERRUPTS_MASK);
        #endif /* PS2_RX_INTERRUPT_ENABLED */
    }

#endif  /* PS2_HD_ENABLED */


/* [] END OF FILE */
