/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*****************************************************************/
/* SPEC ;                                                        */
/*   NAME = string :                                             */
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
                                                   /* D S01006SP */

#include "lstddef.h"

#define strcpy(s1,s2) _builtin_strcpy(s1,s2)
#define strcmp(s1,s2) _builtin_strcmp(s1,s2)
