/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*****************************************************************/
/* SPEC ;                                                        */
/*   NAME = estrtok :                                            */
/*   FUNC =                                                      */
/*          ;                                                    */
/*                                                               */
/*                                                               */
/*                                                               */
/*   CLAS = UNIT ;                                               */
/*   LINK =                                                      */
/*   NOTE =                                                      */
/*          ;                                                    */
/*                                                               */
/*   END ;                                                       */
/*****************************************************************/

#ifndef _REENTRANT                              /* A S70003P  */
extern volatile int         _errno;                /* A S70003P  */
#else                                              /* A S70003P  */
extern  int *errno_addr(void);                     /* C S70001SP */
#define _errno (*errno_addr())                     /* A S70001SP */
#endif                                             /* A S70003P  */

extern char *strpbrk(const char *, const char *);
extern char *strtok(char *, const char *);
static char *_strtok(char *, const char *);        /* C S70001SP */
