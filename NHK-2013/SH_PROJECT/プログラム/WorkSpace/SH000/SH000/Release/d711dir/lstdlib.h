/********************************************************************************/
/* Copyright (C) 1992,2009 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*****************************************************************/
/* SPEC ;                                                        */
/*   NAME = stdlib :                                             */
/*   FUNC =                                                      */
/*          ;                                                    */
/*                                                               */
/*                                                               */
/*                                                               */
/*   CLAS = UNIT ;                                               */
/*   END ;                                                       */
/*****************************************************************/
                                                   /* D S01006SP */

#include "lstddef.h"

struct _DIV_T_TAG {          /* tag define for div_t  A S01015SP */
    int quot;                /*  quotient             A S01015SP */
    int rem;                 /*  remainder            A S01015SP */
};                           /*                       A S01015SP */
struct _LDIV_T_TAG {         /* tag define for ldiv_t A S01015SP */
    long quot;               /*  quotient             A S01015SP */
    long rem;                /*  remainder            A S01015SP */
};                           /*                       A S01015SP */
struct _LLDIV_T_TAG {        /* tag define for ldiv_t A V80#1.05 */
    long long quot;          /*  quotient             A V80#1.05 */
    long long rem;           /*  remainder            A V80#1.05 */
};                           /*                       A V80#1.05 */

typedef struct _DIV_T_TAG div_t ;
typedef struct _LDIV_T_TAG ldiv_t ;
typedef struct _LLDIV_T_TAG lldiv_t ;              /* A V80#1.05 */

#define RAND_MAX  32767
#define ERANGE  1100
#define EDOM    1101
#define EDIV    1102
#define ESTRN   1104
#define ECBASE  1200
#define ETLN    1202
#define EEXP    1204
#define EEXPN   1206
#define EFLOATO 1210
#define EFLOATU 1220
#define EDBLO   1250
#define EDBLU   1260
#define ELDBLO  1270
#define ELDBLU  1280
#ifdef _DSPC
#define EFIXEDO  1400                              /* A V80#4.17 */
#define EFIXEDU  1410                              /* A V80#4.17 */
#define EACCUMO  1420                              /* A V80#4.17 */
#define EACCUMU  1430                              /* A V80#4.17 */
#define ELFIXEDO 1440                              /* A V80#4.17 */
#define ELFIXEDU 1450                              /* A V80#4.17 */
#define ELACCUMO 1460                              /* A V80#4.17 */
#define ELACCUMU 1470                              /* A V80#4.17 */
#endif /* _DSPC */

#define TYPE_F  (1)          /* float                 A S40008SP */
#define TYPE_D  (2)          /* double                A S40008SP */
#define TYPE_L  (3)          /* long double           A S40008SP */
#define TYPE_E  (4)          /* for ERANGE            A S40008SP */
#define TYPE_EF (5)          /* for ERANGE (float)    A S40008SP */
#ifdef _DSPC
#define TYPE_R  (6)          /* __fixed               A V80#4.17 */
#define TYPE_LR (7)          /* long __fixed          A V80#4.17 */
#define TYPE_A  (8)          /* __accum               A V80#4.17 */
#define TYPE_LA (9)          /* long __accum          A V80#4.17 */
#define TYPE_ELRA (0x80)     /* for ERANGE            A V80#4.17 */
#endif /* _DSPC */

/* HUGE_VALをfpuオプションとdoubleオプションに対応させる	A SH-B094057	*/
#ifndef HUGE_VAL
#if defined(_FPS)|defined(_FLT)
extern const float _HUGE_VALF;
#define HUGE_VAL  _HUGE_VALF
#else
extern const double _HUGE_VAL;
#define HUGE_VAL  _HUGE_VAL                        /* C S01006SP */
#endif
#endif

