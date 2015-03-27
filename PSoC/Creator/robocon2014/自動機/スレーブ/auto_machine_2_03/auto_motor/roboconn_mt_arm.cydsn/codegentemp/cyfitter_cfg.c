/*******************************************************************************
* FILENAME: cyfitter_cfg.c
* PSoC Creator 3.0
*
* Description:
* This file is automatically generated by PSoC Creator with device 
* initialization code.  Except for the user defined sections in
* CyClockStartupError(), this file should not be modified.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include <string.h>
#include <cytypes.h>
#include <cydevice_trm.h>
#include <cyfitter.h>
#include <CyLib.h>
#include <cyfitter_cfg.h>

#define CY_NEED_CYCLOCKSTARTUPERROR 1


#if defined(__C51__) || defined(__CX51__)
	#define CYPACKED
	#define CYPACKED_ATTR
	#define CYALIGNED
	
    #define CY_CFG_UNUSED
	#define CY_CFG_MEMORY_BARRIER() do { } while (0)



	#define CYMEMZERO(a,c) cymemzero((a),(c))
	#define CYCONFIGCPY(d,s,c) cyconfigcpy((c),(s),(d))
	#define CYCONFIGCPYCODE(d,s,c) cyconfigcpycode((c),(s),(d))
#else
	#error Unsupported toolchain
#endif



/* Clock startup error codes                                                   */
#define CYCLOCKSTART_NO_ERROR    0u
#define CYCLOCKSTART_XTAL_ERROR  1u
#define CYCLOCKSTART_32KHZ_ERROR 2u
#define CYCLOCKSTART_PLL_ERROR   3u

#ifdef CY_NEED_CYCLOCKSTARTUPERROR
/*******************************************************************************
* Function Name: CyClockStartupError
********************************************************************************
* Summary:
*  If an error is encountered during clock configuration (crystal startup error,
*  PLL lock error, etc.), the system will end up here.  Unless reimplemented by
*  the customer, this function will stop in an infinite loop.
*
* Parameters:
*   void
*
* Return:
*   void
*
*******************************************************************************/
CY_CFG_UNUSED
static void CyClockStartupError(uint8 errorCode);
CY_CFG_UNUSED
static void CyClockStartupError(uint8 errorCode)
{
    /* To remove the compiler warning if errorCode not used.                */
    errorCode = errorCode;

    /* `#START CyClockStartupError` */

    /* If we have a clock startup error (bad MHz crystal, PLL lock, etc.),  */
    /* we will end up here to allow the customer to implement something to  */
    /* deal with the clock condition.                                       */

    /* `#END` */

    /* If nothing else, stop here since the clocks have not started         */
    /* correctly.                                                           */
    while(1) {}
}
#endif

#define cfg_byte_table ((const void CYFAR *)0x080000u)
/* UDB_0_4_0_CONFIG Address: CYDEV_UCFG_B0_P6_U1_BASE Size (bytes): 128 */
#define BS_UDB_0_4_0_CONFIG_VAL ((const uint8 CYFAR *)0x00080D70u)

/* UCFG_BCTL0 Address: CYREG_BCTL0_MDCLK_EN Size (bytes): 16 */
#define BS_UCFG_BCTL0_VAL ((const uint8 CYFAR *)0x00080DF0u)

/* IOPINS0_0 Address: CYREG_PRT0_DM0 Size (bytes): 8 */
#define BS_IOPINS0_0_VAL ((const uint8 CYFAR *)0x00080E00u)

/* IOPINS0_2 Address: CYREG_PRT2_DR Size (bytes): 10 */
#define BS_IOPINS0_2_VAL ((const uint8 CYFAR *)0x00080E08u)

/* IOPINS0_4 Address: CYREG_PRT4_DM0 Size (bytes): 8 */
#define BS_IOPINS0_4_VAL ((const uint8 CYFAR *)0x00080E14u)

/* IOPINS0_5 Address: CYREG_PRT5_DM0 Size (bytes): 8 */
#define BS_IOPINS0_5_VAL ((const uint8 CYFAR *)0x00080E1Cu)

/* IOPINS0_6 Address: CYREG_PRT6_DM0 Size (bytes): 8 */
#define BS_IOPINS0_6_VAL ((const uint8 CYFAR *)0x00080E24u)


/*******************************************************************************
* Function Name: ClockSetup
********************************************************************************
*
* Summary:
*  Performs the initialization of all of the clocks in the device based on the
*  settings in the Clock tab of the DWR.  This includes enabling the requested
*  clocks and setting the necessary dividers to produce the desired frequency. 
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
static void ClockSetup(void);
static void ClockSetup(void)
{
	uint32 timeout;
	uint8 pllLock;


	/* Configure Digital Clocks based on settings from Clock DWR */
	CY_SET_XTND_REG16((void CYFAR *)(CYREG_CLKDIST_DCFG0_CFG0), 0x0000u);
	CY_SET_REG8((void CYXDATA *)(CYREG_CLKDIST_DCFG0_CFG0 + 0x2u), 0x58u);
	CY_SET_XTND_REG16((void CYFAR *)(CYREG_CLKDIST_DCFG1_CFG0), 0x009Bu);
	CY_SET_REG8((void CYXDATA *)(CYREG_CLKDIST_DCFG1_CFG0 + 0x2u), 0x18u);
	CY_SET_XTND_REG16((void CYFAR *)(CYREG_CLKDIST_DCFG2_CFG0), 0x009Bu);
	CY_SET_REG8((void CYXDATA *)(CYREG_CLKDIST_DCFG2_CFG0 + 0x2u), 0x18u);
	CY_SET_XTND_REG16((void CYFAR *)(CYREG_CLKDIST_DCFG3_CFG0), 0x001Du);
	CY_SET_REG8((void CYXDATA *)(CYREG_CLKDIST_DCFG3_CFG0 + 0x2u), 0x19u);
	CY_SET_XTND_REG16((void CYFAR *)(CYREG_CLKDIST_DCFG4_CFG0), 0x3A97u);
	CY_SET_REG8((void CYXDATA *)(CYREG_CLKDIST_DCFG4_CFG0 + 0x2u), 0x19u);

	/* Configure ILO based on settings from Clock DWR */
	CY_SET_REG8((void CYXDATA *)(CYREG_SLOWCLK_ILO_CR0), 0x02u);
	CY_SET_REG8((void CYXDATA *)(CYREG_CLKDIST_CR), 0x08u);

	/* Configure IMO based on settings from Clock DWR */
	CY_SET_REG8((void CYXDATA *)(CYREG_FASTCLK_IMO_CR), 0x03u);
	CY_SET_REG8((void CYXDATA *)(CYREG_IMO_TR1), (CY_GET_XTND_REG8((void CYFAR *)CYREG_FLSHID_CUST_TABLES_IMO_3MHZ)));

	/* Configure PLL based on settings from Clock DWR */
	CY_SET_XTND_REG16((void CYFAR *)(CYREG_FASTCLK_PLL_P), 0x0010u);
	CY_SET_XTND_REG16((void CYFAR *)(CYREG_FASTCLK_PLL_CFG0), 0x1251u);
	/* Wait up to 250us for the PLL to lock */
	pllLock = 0u;
	for (timeout = 250u / 10u; (timeout > 0u) && (pllLock != 0x03u); timeout--)
	{ 
		pllLock = 0x03u & ((uint8)((uint8)pllLock << 1) | ((CY_GET_REG8((void CYXDATA *)CYREG_FASTCLK_PLL_SR) & 0x01u) >> 0));
		CyDelayCycles(10u * 48u); /* Delay 10us based on 48MHz clock */
	}
	/* If we ran out of time the PLL didn't lock so go to the error function */
	if (timeout == 0u)
	{
		CyClockStartupError(CYCLOCKSTART_PLL_ERROR);
	}

	/* Configure Bus/Master Clock based on settings from Clock DWR */
	CY_SET_XTND_REG16((void CYFAR *)(CYREG_CLKDIST_MSTR0), 0x0100u);
	CY_SET_REG8((void CYXDATA *)(CYREG_CLKDIST_MSTR0), 0x07u);
	CY_SET_REG8((void CYXDATA *)(CYREG_CLKDIST_BCFG0), 0x00u);
	CY_SET_REG8((void CYXDATA *)(CYREG_CLKDIST_BCFG2), 0x48u);
	CY_SET_REG8((void CYXDATA *)(CYREG_CLKDIST_MSTR0), 0x00u);
	CY_SET_REG8((void CYXDATA *)(CYREG_CLKDIST_LD), 0x02u);

	CY_SET_REG8((void CYXDATA *)(CYREG_PM_ACT_CFG2), ((CY_GET_REG8((void CYXDATA *)CYREG_PM_ACT_CFG2) | 0x1Fu)));
}


/* Analog API Functions */


/*******************************************************************************
* Function Name: AnalogSetDefault
********************************************************************************
*
* Summary:
*  Sets up the analog portions of the chip to default values based on chip
*  configuration options from the project.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
static void AnalogSetDefault(void);
static void AnalogSetDefault(void)
{
	uint8 bg_xover_inl_trim = CY_GET_XTND_REG8((void CYFAR *)(CYREG_FLSHID_MFG_CFG_BG_XOVER_INL_TRIM + 1u));
	CY_SET_REG8((void CYXDATA *)(CYREG_BG_DFT0), (bg_xover_inl_trim & 0x07u));
	CY_SET_REG8((void CYXDATA *)(CYREG_BG_DFT1), ((bg_xover_inl_trim >> 4) & 0x0Fu));
	CY_SET_REG8((void CYXDATA *)CYREG_PUMP_CR0, 0x44u);
}


/*******************************************************************************
* Function Name: SetAnalogRoutingPumps
********************************************************************************
*
* Summary:
* Enables or disables the analog pumps feeding analog routing switches.
* Intended to be called at startup, based on the Vdda system configuration;
* may be called during operation when the user informs us that the Vdda voltage
* crossed the pump threshold.
*
* Parameters:
*  enabled - 1 to enable the pumps, 0 to disable the pumps
*
* Return:
*  void
*
*******************************************************************************/
void SetAnalogRoutingPumps(uint8 enabled)
{
	uint8 regValue = CY_GET_REG8((void CYXDATA *)CYREG_PUMP_CR0);
	if (enabled != 0u)
	{
		regValue |= 0x00u;
	}
	else
	{
		regValue &= (uint8)~0x00u;
	}
	CY_SET_REG8((void CYXDATA *)CYREG_PUMP_CR0, regValue);
}

#define CY_AMUX_UNUSED CYREG_BOOST_SR


/*******************************************************************************
* Function Name: cyfitter_cfg
********************************************************************************
* Summary:
*  This function is called by the start-up code for the selected device. It
*  performs all of the necessary device configuration based on the design
*  settings.  This includes settings from the Design Wide Resources (DWR) such
*  as Clocks and Pins as well as any component configuration that is necessary.
*
* Parameters:  
*   void
*
* Return:
*   void
*
*******************************************************************************/

void cyfitter_cfg(void)
{
	/* Enable/Disable Debug functionality based on settings from System DWR */
	CY_SET_XTND_REG8((void CYFAR *)CYREG_MLOGIC_DEBUG, (CY_GET_XTND_REG8((void CYFAR *)CYREG_MLOGIC_DEBUG) | 0x05u));

	{

		CYPACKED typedef struct {
			void CYFAR *address;
			uint16 size;
		} CYPACKED_ATTR cfg_memset_t;


		CYPACKED typedef struct {
			void CYFAR *dest;
			const void CYFAR *src;
			uint16 size;
		} CYPACKED_ATTR cfg_memcpy_t;

		static const cfg_memset_t CYCODE cfg_memset_list [] = {
			/* address, size */
			{(void CYFAR *)(CYREG_PRT1_DR), 16u},
			{(void CYFAR *)(CYREG_PRT3_DR), 16u},
			{(void CYFAR *)(CYREG_PRT12_DR), 16u},
			{(void CYFAR *)(CYREG_PRT15_DR), 16u},
			{(void CYFAR *)(CYDEV_UCFG_B0_P0_U0_BASE), 3200u},
			{(void CYFAR *)(CYDEV_UCFG_B0_P6_ROUTE_BASE), 768u},
			{(void CYFAR *)(CYDEV_UCFG_B1_P2_U0_BASE), 2048u},
			{(void CYFAR *)(CYDEV_UCFG_DSI0_BASE), 2560u},
			{(void CYFAR *)(CYDEV_UCFG_DSI12_BASE), 512u},
			{(void CYFAR *)(CYREG_BCTL1_MDCLK_EN), 16u},
		};

		static const cfg_memcpy_t CYCODE cfg_memcpy_list [] = {
			/* dest, src, size */
			{(void CYFAR *)(CYDEV_UCFG_B0_P6_U1_BASE), BS_UDB_0_4_0_CONFIG_VAL, 128u},
			{(void CYFAR *)(CYREG_BCTL0_MDCLK_EN), BS_UCFG_BCTL0_VAL, 16u},
		};

		uint8 CYDATA i;

		/* Zero out critical memory blocks before beginning configuration */
		for (i = 0u; i < (sizeof(cfg_memset_list)/sizeof(cfg_memset_list[0])); i++)
		{
			const cfg_memset_t CYCODE * CYDATA ms = &cfg_memset_list[i];
			CYMEMZERO(ms->address, ms->size);
		}

		/* Copy device configuration data into registers */
		for (i = 0u; i < (sizeof(cfg_memcpy_list)/sizeof(cfg_memcpy_list[0])); i++)
		{
			const cfg_memcpy_t CYCODE * CYDATA mc = &cfg_memcpy_list[i];
			void * CYDATA destPtr = mc->dest;
			const void * CYDATA srcPtr = mc->src;
			uint16 CYDATA numBytes = mc->size;
			CYCONFIGCPY(destPtr, srcPtr, numBytes);
		}

		cfg_write_bytes(cfg_byte_table);

		/* Enable digital routing */
		CY_SET_XTND_REG8((void CYFAR *)CYREG_BCTL0_BANK_CTL, CY_GET_XTND_REG8((void CYFAR *)CYREG_BCTL0_BANK_CTL) | 0x02u);
		CY_SET_XTND_REG8((void CYFAR *)CYREG_BCTL1_BANK_CTL, CY_GET_XTND_REG8((void CYFAR *)CYREG_BCTL1_BANK_CTL) | 0x02u);

		/* Enable UDB array */
		CY_SET_REG8((void CYXDATA *)CYREG_PM_ACT_CFG0, CY_GET_REG8((void CYXDATA *)CYREG_PM_ACT_CFG0) | 0x40u);
		CY_SET_REG8((void CYXDATA *)CYREG_PM_AVAIL_CR2, CY_GET_REG8((void CYXDATA *)CYREG_PM_AVAIL_CR2) | 0x10u);
	}

	/* Perform second pass device configuration. These items must be configured in specific order after the regular configuration is done. */
	CYCONFIGCPY((void CYFAR *)(CYREG_PRT0_DM0), (const void CYFAR *)(BS_IOPINS0_0_VAL), 8u);
	CYCONFIGCPY((void CYFAR *)(CYREG_PRT2_DR), (const void CYFAR *)(BS_IOPINS0_2_VAL), 10u);
	CYCONFIGCPY((void CYFAR *)(CYREG_PRT4_DM0), (const void CYFAR *)(BS_IOPINS0_4_VAL), 8u);
	CYCONFIGCPY((void CYFAR *)(CYREG_PRT5_DM0), (const void CYFAR *)(BS_IOPINS0_5_VAL), 8u);
	CYCONFIGCPY((void CYFAR *)(CYREG_PRT6_DM0), (const void CYFAR *)(BS_IOPINS0_6_VAL), 8u);
	CY_SET_XTND_REG8((void CYFAR *)(CYREG_B0_P0_U1_CFG27), 0x84u);
	CY_SET_XTND_REG8((void CYFAR *)(CYREG_B1_P3_U0_CFG27), 0xC4u);
	CY_SET_REG8((void CYXDATA *)(CYREG_INTC_CSR_EN), 0x01u);

	/* Switch Boost to the precision bandgap reference from its internal reference */
	CY_SET_REG8((void CYXDATA *)CYREG_BOOST_CR2, (CY_GET_REG8((void CYXDATA *)CYREG_BOOST_CR2) | 0x08u));
	if (CYDEV_CHIP_REV_ACTUAL < 5u)
	{
		CY_SET_REG8((void CYXDATA *)CYREG_PWRSYS_WAKE_TR2, 0x3Au);
	}


	/* Set Flash Cycles based on max possible frequency in case a glitch occurs during ClockSetup(). */
	CY_SET_REG8((void CYXDATA *)(CYREG_CACHE_CR), (((CYDEV_INSTRUCT_CACHE_ENABLED) != 0) ? 0xF1u : 0xC0u));
	/* Setup clocks based on selections from Clock DWR */
	ClockSetup();

	/* Perform basic analog initialization to defaults */
	AnalogSetDefault();

	/* Configure alternate active mode */
	CYCONFIGCPY((void CYFAR *)CYDEV_PM_STBY_BASE, (const void CYFAR *)CYDEV_PM_ACT_BASE, 14u);
	CY_SET_REG8((void CYXDATA *)CYREG_PM_STBY_CFG0, CY_GET_REG8((void CYXDATA *)CYREG_PM_STBY_CFG0) & (uint8)~0x02u);	/* Disable CPU */
}
