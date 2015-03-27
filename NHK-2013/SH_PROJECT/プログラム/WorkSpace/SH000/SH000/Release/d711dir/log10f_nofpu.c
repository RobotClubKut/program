/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/******************************************************************/
/* SPEC;                                                          */
/*   NAME = log10 : log10 value output ;                          */
/*   FUNC = log10 : output IEEE double format ;                   */
/*   CLAS = UNIT ;                                                */
/*   NOTE = SHC floating point library ;                          */
/* END;                                                           */
/******************************************************************/
#ifndef _FPD					    /* A S50001SP */

#include "fdefs.h"
#include "fexts.h"
float log10f(p)
float p;
{
    float ret;
    ret=_istos(_in_log10s(_stois(p)));
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
#define log10 log10f   				    /* A S50001SP */
#include "log10.c"				    /* A S50001SP */
#endif						    /* A S50001SP */
