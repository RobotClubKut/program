/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/* inner format function prototype declalation */
/* inner float  */
#if defined(_SH2E)|defined(_SH3E)|defined(_SH4)|defined(_SH4A)|defined(_SH2AFPU)
#pragma inline(_istypes)                                    /* A S40012SP ^ */
static int _istypes(IN_SINGLE p)                            /*            | */
{                                                           /*            | */
    union {                                                 /*            | */
        IN_SINGLE s;                                        /*            | */
        long l;                                             /*            | */
    } pp;                                                   /*            | */
    int ret = 0;                                            /*            | */
                                                            /*            | */
    pp.s = p;                                               /*            | */
    if ( pp.l < 0 )                                         /*            | */
        ret |= NEG;                                         /*            | */
    if (p ==  0.0f)                                         /*            | */
        ret |= ZERO;                                        /*            | */
    else if ( (pp.l & ABSMASK) == EXMASKF )                 /*            | */
        ret |= INF;                                         /*            | */
    else if (!(p==p))                                       /*            | */
        ret |= NAN;                                         /*            | */
    return ret;                                             /*            | */
}                                                           /* A S40012SP v */
#else
extern int             _istypes(IN_SINGLE);
#endif
#if defined(_SH2E)|defined(_SH3E)|defined(_SH4)|defined(_SH4A)|defined(_SH2AFPU)
#define _in_eqs(p1,p2)     (p1 == p2)                       /* A S40012SP   */
#define _in_gts(p1,p2)     (p1 > p2)                        /* A S40012SP   */
#else
extern int             _in_eqs(IN_SINGLE, IN_SINGLE);
extern int             _in_gts(IN_SINGLE, IN_SINGLE);
#endif

#if defined(_SH2E)|defined(_SH3E)|defined(_SH4)|defined(_SH4A)|defined(_SH2AFPU)
#define _stois(p1)     (p1)                                 /* A S40012SP ^ */
#define _istos(p1)     (p1)                                 /*            | */
#define _itois(p1)     ((IN_SINGLE)p1)                      /* A S40012SP v */
#else
extern IN_SINGLE       _stois(float); 
extern float           _istos(IN_SINGLE);
extern IN_SINGLE       _itois(int);
#endif

#if defined(_SH2E)|defined(_SH3E)|defined(_SH4)|defined(_SH4A)|defined(_SH2AFPU)
#define _in_adds(p1,p2)     (p1+p2)                         /* A S40012SP ^ */
#define _in_subs(p1,p2)     (p1-p2)                         /*            | */
#define _in_muls(p1,p2)     (p1*p2)                         /*            | */
#define _in_divs(p1,p2)     (p1/p2)                         /* A S40012SP v */
#else
extern IN_SINGLE       _in_adds(IN_SINGLE, IN_SINGLE); 
extern IN_SINGLE       _in_subs(IN_SINGLE, IN_SINGLE);
extern IN_SINGLE       _in_muls(IN_SINGLE, IN_SINGLE);
extern IN_SINGLE       _in_divs(IN_SINGLE, IN_SINGLE);
#endif

#if defined(_SH2E)|defined(_SH3E)|defined(_SH4)|defined(_SH4A)|defined(_SH2AFPU)
#pragma inline(_in_truncs)                                  /* A S40012SP ^ */
static IN_SINGLE _in_truncs(IN_SINGLE p)                    /*            | */
{                                                           /*            | */
    union {                                                 /*            | */
        IN_SINGLE s;                                        /*            | */
        long l;                                             /*            | */
    } pp;                                                   /*            | */
    long sign;                                              /*            | */
                                                            /*            | */
    pp.s = p;                                               /*            | */
    sign=pp.l&SIGNMASK;
    if ((pp.l & EXPMASK) < 0x4b000000){        /* EXP < 32 -> 23 */
        pp.s = (int)p;                                      /*            | */
	}
    pp.l|=sign;                                             /*            | */
    return pp.s;                                            /*            | */
}                                                           /* A S40012SP v */
#else
extern IN_SINGLE       _in_truncs(IN_SINGLE); 
#endif
extern IN_SINGLE       _in_floors(IN_SINGLE);
extern IN_SINGLE       _in_ceils(IN_SINGLE);

#if defined(_SH3E)|defined(_SH4)|defined(_SH4A)|defined(_SH2AFPU) /*AS50001SP*/
#ifdef _FPD						     /* A S50001SP */
#define _in_sqrts      _builtin_sqrt			     /* A S50001SP */
#else							     /* A S50001SP */
#define _in_sqrts      _builtin_sqrtf                       /* A S40012SP  */
#endif							     /* A S50001SP */
#else
#ifndef _SH2E                                                /* A S50008SP */
extern IN_SINGLE       _in_sqrts(IN_SINGLE);
#endif                                                       /* A S50008SP */
#endif

extern IN_SINGLE       _in_sins(IN_SINGLE);
extern IN_SINGLE       _in_coss(IN_SINGLE);
extern IN_SINGLE       _in_tans(IN_SINGLE);
extern IN_SINGLE       _in_asins(IN_SINGLE);
extern IN_SINGLE       _in_acoss(IN_SINGLE);
extern IN_SINGLE       _in_atans(IN_SINGLE);
extern IN_SINGLE       _in_atan2s(IN_SINGLE, IN_SINGLE);

extern IN_SINGLE       _in_sinhs(IN_SINGLE);
extern IN_SINGLE       _in_coshs(IN_SINGLE);
extern IN_SINGLE       _in_tanhs(IN_SINGLE);
extern IN_SINGLE       _in_logs(IN_SINGLE);
extern IN_SINGLE       _in_log10s(IN_SINGLE);
extern IN_SINGLE       _in_exps(IN_SINGLE);
extern IN_SINGLE       _in_pows(IN_SINGLE, IN_SINGLE);
extern IN_SINGLE       _in_modfs(IN_SINGLE, IN_SINGLE*);
extern IN_SINGLE       _in_fmods(IN_SINGLE, IN_SINGLE, unsigned*);
extern IN_SINGLE       _in_ldexps(IN_SINGLE, int);

#if defined(_SH2E)|defined(_SH3E)|defined(_SH4)|defined(_SH4A)|defined(_SH2AFPU)
#pragma inline(_polinos)                                     /* A S40012SP ^ */
static IN_SINGLE _polinos(IN_SINGLE x,IN_SINGLE *p,int dim)  /*            | */
{                                                            /*            | */
    IN_SINGLE process = *p++;                                /*            | */
    do {                                                     /*            | */
        process = *p++ + process * x;                        /*            | */
    } while (--dim > 0);                                     /*            | */
    return process;                                          /*            | */
}                                                            /* A S40012SP v */
#else
extern IN_SINGLE       _polinos(IN_SINGLE, IN_SINGLE*, int);
#endif
extern IN_SINGLE       _app_sins(IN_SINGLE);
extern IN_SINGLE       _app_coss(IN_SINGLE);
extern IN_SINGLE       _app_atans(IN_SINGLE);

/* constant data */
extern IN_SINGLE _IFNANS;
extern IN_SINGLE _IFZEROS;
extern IN_SINGLE _IFINFS;
extern IN_SINGLE _IFONES;
extern IN_SINGLE _HALFS;
extern IN_SINGLE _QUOTS;
extern IN_SINGLE _TWOS;
extern IN_SINGLE _FOURS;
extern IN_SINGLE _PAIS;
extern IN_SINGLE _2PAIS;
extern IN_SINGLE _HLFPAIS;
extern IN_SINGLE _QUOPAIS;
extern IN_SINGLE _LOGE2S;

extern IN_SINGLE _NIFZEROS;
extern IN_SINGLE _NIFINFS;
extern IN_SINGLE _NIFONES;
extern IN_SINGLE _NHALFS;
extern IN_SINGLE _NQUOTS;
extern IN_SINGLE _NTWOS;
extern IN_SINGLE _NFOURS;
extern IN_SINGLE _NPAIS;
extern IN_SINGLE _N2PAIS;
extern IN_SINGLE _NHLFPAIS;
extern IN_SINGLE _NQUOPAIS;
extern IN_SINGLE _NLOGE2S;

