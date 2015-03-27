//*****************************************************************************
//
// rgb_commands.c - Command line functionality implementation
//
// Copyright (c) 2012 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 9453 of the EK-LM4F120XL Firmware Package.
//
//*****************************************************************************

#include "qs-rgb.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "drivers/rgb.h"
#include "driverlib/gpio.h"
#include "utils/ustdlib.h"
#include "utils/uartstdio.h"
#include "utils/cmdline.h"
#include "rgb_commands.h"

//*****************************************************************************
//
// Table of valid command strings, callback functions and help messages.
//
//*****************************************************************************
tCmdLineEntry g_sCmdTable[] =
{
    {"help",     CMD_help,      " : Display list of commands" },
    {"hib",      CMD_hib,       " : Place system into hibernate mode"},
    {"rand",     CMD_rand,      " : Start automatic color sequencing"},
    {"intensity",CMD_intensity, " : Adjust brightness 0 to 100 percent"},
    {"rgb",      CMD_rgb,       " : Adjust color 000000-FFFFFF HTML notation"},
    {"oppai",    CMD_oppai,     " : Oppai & Lolita"},
    {"nadeko",    CMD_nadeko,     " : nadeko is cute"},
    { 0, 0, 0 }
};

const int NUM_CMD = sizeof(g_sCmdTable)/sizeof(tCmdLineEntry);

//*****************************************************************************
//
// Command: help
//
// Print the help strings for all commands.
//
//*****************************************************************************
int
CMD_help (int argc, char **argv)
{
    int index;
    
    (void)argc;
    (void)argv;
    
    UARTprintf("\n");
    for (index = 0; index < NUM_CMD; index++)
    {
      UARTprintf("%17s %s\n\n",
        g_sCmdTable[index].pcCmd,
        g_sCmdTable[index].pcHelp);
    }
    UARTprintf("\n"); 
    
    return (0);
}

//*****************************************************************************
//
// Command: hib
//
// Force the device into hibernate mode now.
//
//*****************************************************************************
int
CMD_hib (int argc, char **argv)
{
    (void) argc;
    (void) argv;
    AppHibernateEnter();

    return (0);
}

//*****************************************************************************
//
// Command: rand
//
// Starts the automatic light sequence immediately.
//
//*****************************************************************************
int
CMD_rand (int argc, char **argv)
{
    (void) argc;
    (void) argv;
    g_sAppState.ulMode = APP_MODE_AUTO;

    return (0);
}

//*****************************************************************************
//
// Command: intensity
//
// Takes a single argument that is between zero and one hundred. The argument 
// must be an integer.  This is interpreted as the percentage of maximum
// brightness with which to display the current color.  
//
//*****************************************************************************
int
CMD_intensity (int argc, char **argv)
{
    unsigned long ulIntensity;


    if(argc == 2)
    {
        ulIntensity = ustrtoul(argv[1], 0, 10);
        g_sAppState.fIntensity = ((float) ulIntensity) / 100.0f;
        RGBIntensitySet(g_sAppState.fIntensity);
    }

    return 0;
}

//*****************************************************************************
//
// Command: rgb
//
// Takes a single argument that is a string between 000000 and FFFFFF.
// This is the HTML color code that should be used to set the RGB LED color.
// 
// http://www.w3schools.com/html/html_colors.asp
//
//*****************************************************************************
int
CMD_rgb (int argc, char **argv)
{
    unsigned long ulHTMLColor;
    
    if(argc == 2)
    {
        ulHTMLColor = ustrtoul(argv[1], 0, 16);
        g_sAppState.ulColors[RED] = (ulHTMLColor & 0xFF0000) >> 8;
        g_sAppState.ulColors[GREEN] = (ulHTMLColor & 0x00FF00);
        g_sAppState.ulColors[BLUE] = (ulHTMLColor & 0x0000FF) << 8;
        g_sAppState.ulMode = APP_MODE_REMOTE;
        g_sAppState.ulModeTimer = 0;
        RGBColorSet(g_sAppState.ulColors);
    }
    
    return (0);

}

//*****************************************************************************
//
// Command: oppai
//
//
//*****************************************************************************

#define rori_x 0x80
#define rori_y 0x40
#define rori_z 0x20
#define rori_mask (rori_x | rori_y | rori_z)

// 0 -> 1 -> 3 -> 2
//#define rori_check(t) (((t & rori_x) != 0) | (((t & rori_y) != 0) << 1))

// 0 -> 1 -> 2 -> 3
#define rori_check(t) (((t & rori_x) != 0) ^ (((t & rori_y) != 0) * 0x03))

int CMD_oppai (int argc, char **argv)
{
	//const unsigned long cycle[4] = {0, rori_x, rori_x | rori_y, rori_y};
	//unsigned long count = 0;
	//unsigned int i = 0;
	//unsigned int t = 0;
	unsigned int read = 0;
	unsigned int ulpta = 0;
	unsigned int ulpta_old = 0;
	(void) argc;
	(void) argv;
	UARTprintf("ÉçÉäÅ[É^ñúçŒÅ_(^o^)Å^ \n");
	while (!(g_sAppState.ulButtons & GPIO_PIN_0))	// RIGHT BOTTON
	{
		read = (GPIOPinRead(GPIO_PORTA_BASE,GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7) & rori_mask);
		ulpta = rori_check(read);
		if (ulpta != ulpta_old)
		{
			UARTprintf("%d, %d\n", ulpta, ((read & rori_z) != 0));
		}

		ulpta_old = ulpta;

#if 0
		if ((ulpta & 0xc0) != (ulpta_old & 0xc0))
		{
			if (t < 10)
			{
				t++;
			}
			else
			{
				t = 0;
				UARTprintf(
						"%d %d %d %d\n",
						0x01 & (ulpta >> 5),
						0x01 & (ulpta >> 6),
						0x01 & (ulpta >> 7),
						count);
			}
			ulpta     &= 0xc0;
			ulpta_old &= 0xc0;
			for (i = 0; i < 4; i++)
			{
				if (temp[i] == ulpta_old)
				{
					if (((i != 3) && (ulpta == temp[i + 1])) ||
							((ulpta == temp[0]) && (ulpta_old == temp[3])))
					{
						count++;
					}
					else if (((i != 0) && (ulpta == temp[i-1])) ||
							((ulpta == temp[3]) && (ulpta_old == temp[0])))
					{
						count--;
					}
					else if (((i < 2) && (ulpta == temp[i+2])) ||
							((ulpta == temp[0]) && (ulpta_old == temp[2])) ||
							((ulpta == temp[1]) && (ulpta_old == temp[3])))
					{
						count += 2;
					}
					else if((ulpta == temp[i-2]) ||
							((ulpta == temp[2]) && (ulpta_old == temp[0]))||
							((ulpta == temp[3]) && (ulpta_old == temp[1]))
							)
					{
						count -= 2;
					}
					else
					{
						UARTprintf("error\n");
					}
					break;
				}
			}
		}
		ulpta_old = ulpta;
#endif
	}
	return 0;
}

int
CMD_nadeko (int argc, char **argv)
{

	unsigned long ulb0;
	(void) argc;
	UARTprintf("êÁêŒìdè§\n");
	ulb0= ustrtoul(argv[1], 0, 10);
	UARTprintf("RB0 = %d\n",ulb0);
	GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0,ulb0);
	return 0;
}

