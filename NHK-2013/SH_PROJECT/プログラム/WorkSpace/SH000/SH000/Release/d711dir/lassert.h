/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/***********************************************************************/
/* SPEC;                                                               */
/*  NAME = assert.h : debug macro define          ;                    */
/*                                                                     */
/*  FUNC = this module do the following functions;                     */
/*         (1) if NDEBUG defined assert(x) = (void)0;                  */
/*  CLAS = UNIT;                                                       */
/*                                                                     */
/* END;                                                                */
/***********************************************************************/
#include <stdio.h>
                                                         /* D S01006SP */
#ifdef NDEBUG
#ifdef assert
#undef assert
#endif
#define assert(x) ((void)0)
#else
#ifdef assert
#undef assert
#endif
#define       assert(x) (fprintf(stderr,\
              "ASSERTION FAILED: "#x" FILE %s,LINE %d \n", \
              __FILE__,__LINE__),abort())
#endif
