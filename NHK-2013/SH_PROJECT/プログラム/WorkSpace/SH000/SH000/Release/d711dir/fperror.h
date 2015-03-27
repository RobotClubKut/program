/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
#ifndef _REENTRANT                      /* FFPLB-024 (A)              */
extern volatile int _errno;             /* FFPLB-024 (A)              */
#else                                   /* FFPLB-024 (A)              */
extern int *errno_addr(void);           /* FFPLB-024 (A)              */
#define _errno (*errno_addr())          /* FFPLB-024 (A)              */
extern const double _HUGE_VAL;          /* FFPLB-024 (A)              */
#endif                                  /* FFPLB-024 (A)              */

#define ERANGE 1100                     /* FFPLB-024 (A)              */
#define EDOM   1101                     /* FFPLB-024 (A)              */
