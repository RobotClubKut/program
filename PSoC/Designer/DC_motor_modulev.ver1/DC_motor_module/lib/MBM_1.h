//*****************************************************************************
//*****************************************************************************
//  FILENAME: MBM_1.h
//   Version: 1.1, Updated on 2013/5/19 at 10:43:55
//  Generated by PSoC Designer 5.4.2946
//
//  DESCRIPTION: MBM_1 User Module C Language interface file  
//-----------------------------------------------------------------------------
//  Copyright (c) Cypress Semiconductor 2013. All Rights Reserved.
//*****************************************************************************
//*****************************************************************************

#ifndef MBM_1_include
#define MBM_1_include

#include <m8c.h>

//--------------------------------------------------
// constants for mailboxes
//--------------------------------------------------
#define MBM_1_SERVICE_VARS_ABOVE               0
#define MBM_1_SERVICE_VARS_BELOW               1
// mailbox service variables position
#define MBM_1_SERVICE_VARS_POSITION            MBM_1_SERVICE_VARS_ABOVE // Position of service variables in structure

// offset of service bytes
#define MBM_1_CONFIG_0                         0
#define MBM_1_CONFIG_1                         1

#define MBM_1_BUSY                             0x80   // Busy Flag - set by the slave to tell the host not to read data until cleared
#define MBM_1_DIRTY                            0x40   // Dirty Flag - set by the host to denote that data is in the process of being written and that the slave should not read data from the mailbox until it is cleared

// variables aliases (offset inside of structure)
// access to some structure member:
//(TYPE)* (MBM_1_pMyMailbox+Alias)
#define MAILBOXCONFIG0		 0x00
#define MAILBOXCONFIG1		 0x01
#define OUTBOX_FLAG		 0x02
#define X_TRD		 0x03
#define X_SPEED		 0x04
#define Y_TRD		 0x05
#define Y_SPEED		 0x06
#define Z_TRD		 0x07
#define Z_SPEED		 0x08
#define INBOX_FLAG		 0x09
#define X_CRD		 0x0A
#define X_CSPEED		 0x0B
#define Y_CRD		 0x0C
#define Y_CSPEED		 0x0D
#define Z_CRD		 0x0E
#define Z_CSPEED		 0x0F


//--------------------------------------------------
// typedefs for mailboxes
//--------------------------------------------------

typedef struct
{
	BYTE outbox_flag; 			// reserved variable
	BYTE x_trd; 			// 
	BYTE x_speed; 			// 
	BYTE y_trd; 			// 
	BYTE y_speed; 			// 
	BYTE z_trd; 			// 
	BYTE z_speed; 			// 

} MBM_1_Outbox;

typedef struct
{
	BYTE inbox_flag; 			// reserved variable
	BYTE x_crd; 			// 
	BYTE x_cspeed; 			// 
	BYTE y_crd; 			// 
	BYTE y_cspeed; 			// 
	BYTE z_crd; 			// 
	BYTE z_cspeed; 			// 

} MBM_1_Inbox;

typedef struct
{
    #if (MBM_1_SERVICE_VARS_POSITION == MBM_1_SERVICE_VARS_ABOVE)

	BYTE MailboxConfig0; 			// Reserved for Mailbox UM usage
	BYTE MailboxConfig1; 			// Reserved for Mailbox UM usage

    #endif

    MBM_1_Outbox Outbox;
    MBM_1_Inbox Inbox;

    #if (MBM_1_SERVICE_VARS_POSITION == MBM_1_SERVICE_VARS_BELOW)

	BYTE MailboxConfig0; 			// Reserved for Mailbox UM usage
	BYTE MailboxConfig1; 			// Reserved for Mailbox UM usage

    #endif
} MBM_1_Mailbox;

//-------------------------------------------------
// C prototypes of the MBM_1 API.
//-------------------------------------------------
extern void MBM_1_InitializeMailbox(void);
extern void MBM_1_SetBusyFlag(void);
extern void MBM_1_ClearBusyFlag(void);
extern BYTE MBM_1_CheckDirtyFlag(void);

// ---------------------------------------------------------------------------
// MBM_1 global mailbox variable in RAM
// ---------------------------------------------------------------------------
extern MBM_1_Mailbox MBM_1_MyMailbox;
extern MBM_1_Mailbox* MBM_1_pMyMailbox;

#endif