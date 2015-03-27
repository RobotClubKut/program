/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/******************************************************************/
/* SPEC;                                                          */
/*   NAME = sinh : hyperbolic-sin value output ;                  */
/*   FUNC = sinh : output IEEE double format ;                    */
/*   CLAS = UNIT ;                                                */
/*   NOTE = SHC floating point library ;                          */
/* END;                                                           */
/******************************************************************/
#ifndef _FPD					    /* A S50001SP */

#include "fdefs.h"
#include "fexts.h"
float sinhf(p)
float p;
{
    float ret;
    ret=_istos(_in_sinhs(_stois(p)));
    if (isEMAXf(ret)){
        if (isMANTf(ret)){
            _errno = EDOM;
        }
        else {
            _errno = ERANGE;
        }
    }
    return ret;
}

#else						    /* A S50001SP */
#define sinh sinhf 				    /* A S50001SP */
#include "sinh.c"				    /* A S50001SP */
#endif						    /* A S50001SP */
