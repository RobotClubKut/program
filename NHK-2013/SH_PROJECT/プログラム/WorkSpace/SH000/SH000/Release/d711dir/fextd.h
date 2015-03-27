/********************************************************************************/
/* Copyright (C) 1992,2009 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/* inner format function prototype declalation */
/* inner double */
#if defined(_SH4) | defined(_SH4A) | defined(_SH2AFPU)
#pragma inline(_istyped)				       /* A S50001SP */
static int _istyped(IN_DOUBLE p)			       /* A S50001SP */
{							       /* A S50001SP */
  union {						       /* A S50001SP */
      IN_DOUBLE d;					       /* A S50001SP */
      long   l[2];					       /* A S50001SP */
  }pp;							       /* A S50001SP */
  int ret = 0;						       /* A S50001SP */
  pp.d = p;						       /* A S50001SP */
#ifdef _LIT                                                /* A S50001SP */
    if ( pp.l[1] < 0 )                                         /* A S50001SP */
#else                                                          /* A S50001SP */
    if ( pp.l[0] < 0 )                                         /* A S50001SP */
#endif                                                         /* A S50001SP */
      ret |= NEG;					       /* A S50001SP */
  if (p ==  0.0)					       /* A S50001SP */
      ret |= ZERO;					       /* A S50001SP */
#ifdef _LIT						       /* A S50001SP */
  else if (((pp.l[1] & ABSMASK) == EXMASKD) && (pp.l[0] == 0)) /* A S50001SP */
#else							       /* A S50001SP */
  else if (((pp.l[0] & ABSMASK) == EXMASKD) && (pp.l[1] == 0)) /* A S50001SP */
#endif							       /* A S50001SP */
      ret |= INF;					       /* A S50001SP */
  else if (!(p==p))					       /* A S50001SP */
      ret |= NAN;					       /* A S50001SP */
  return ret;						       /* A S50001SP */
}							       /* A S50001SP */
#else							       /* A S50001SP */
extern int             _istyped(IN_DOUBLE);
#endif							       /* A S50001SP */
#if defined(_SH4) | defined(_SH4A) | defined(_SH2AFPU)
#define  _in_eqd(p1,p2)  (p1 == p2)			       /* A S50001SP */
#define  _in_gtd(p1,p2)  (p1 > p2)			       /* A S50001SP */
#else							       /* A S50001SP */
extern int             _in_eqd(IN_DOUBLE, IN_DOUBLE);
extern int             _in_gtd(IN_DOUBLE, IN_DOUBLE);
#endif							       /* A S50001SP */


#if defined(_SH4) | defined(_SH4A) | defined(_SH2AFPU)
#define  _dtoid(p1)      (p1)				       /* A S50001SP */
#define  _idtod(p1)      (p1)				       /* A S50001SP */
#define  _itoid(p1)  ((IN_DOUBLE)p1)			       /* A S50001SP */
#else							       /* A S50001SP */
extern IN_DOUBLE       _dtoid(double); 
extern double          _idtod(IN_DOUBLE);
extern IN_DOUBLE       _itoid(int);
#endif							       /* A S50001SP */

#if defined(_SH4) | defined(_SH4A) | defined(_SH2AFPU)
#define  _in_addd(p1,p2)  (p1+p2)			       /* A S50001SP */
#define  _in_subd(p1,p2)  (p1-p2)			       /* A S50001SP */
#define  _in_muld(p1,p2)  (p1*p2)			       /* A S50001SP */
#define  _in_divd(p1,p2)  (p1/p2)			       /* A S50001SP */
#else							       /* A S50001SP */
extern IN_DOUBLE       _in_addd(IN_DOUBLE, IN_DOUBLE); 
extern IN_DOUBLE       _in_subd(IN_DOUBLE, IN_DOUBLE);
extern IN_DOUBLE       _in_muld(IN_DOUBLE, IN_DOUBLE);
extern IN_DOUBLE       _in_divd(IN_DOUBLE, IN_DOUBLE);
#endif							       /* A S50001SP */

#if defined(_SH4) | defined(_SH4A) | defined(_SH2AFPU)
#pragma inline(_in_truncd)				       /* A S50001SP */
static IN_DOUBLE _in_truncd(IN_DOUBLE p)		       /* A S50001SP */
{							       /* A S50001SP */
  union {						       /* A S50001SP */
      IN_DOUBLE d;					       /* A S50001SP */
      long l[2];					       /* A S50001SP */
  } pp;							       /* A S50001SP */
  long sign;						       /* A S50001SP */
  long exp;
  long INTMASK;
  int expnumber;

  INTMASK = 0xffe00000;
							       /* A S50001SP */
  pp.d = p;						       /* A S50001SP */
  /* ïÑçÜÇçƒê›íËÇ∑ÇÈèàóùÇí«â¡	A SH-B094065	*/
#ifdef _LIT						       /* A S50001SP */
  sign = pp.l[1] & SIGNMASK;
  exp = pp.l[1] & EXPMASK;
  if ( exp < 0x41e00000){
	  pp.d = (int)pp.d;
  }
  else if ( exp <0x43300000){
	  expnumber = (exp >> 20 )-1054;
	  pp.l[0]&=(INTMASK >> expnumber );
  }
  pp.l[1] |= sign;
#else							       /* A S50001SP */
  sign = pp.l[0] & SIGNMASK;
  exp = pp.l[0] & EXPMASK;
  if ( exp < 0x41e00000 ){
  	 pp.d = (int)pp.d;
  }
  else if (exp<0x43300000){
	 expnumber = (exp >> 20)-1054;
	 pp.l[1]&= (INTMASK >> expnumber );
	 }
  pp.l[0] |= sign;
#endif							       /* A S50001SP */
  return pp.d;						       /* A S50001SP */
}							       /* A S50001SP */
#else							       /* A S50001SP */
extern IN_DOUBLE       _in_truncd(IN_DOUBLE); 
#endif							       /* A S50001SP */
extern IN_DOUBLE       _in_floord(IN_DOUBLE);
extern IN_DOUBLE       _in_ceild(IN_DOUBLE);

#if defined(_SH4) | defined(_SH4A) | defined(_SH2AFPU)
#ifdef _FPS						       /* A S50001SP */
#define  _in_sqrtd     _builtin_sqrtf			       /* A S50001SP */
#else							       /* A S50001SP */
#define  _in_sqrtd     _builtin_sqrt			       /* A S50001SP */
#endif							       /* A S50001SP */
#else							       /* A S50001SP */
extern IN_DOUBLE       _in_sqrtd(IN_DOUBLE);
#endif							       /* A S50001SP */

extern IN_DOUBLE       _in_sind(IN_DOUBLE);
extern IN_DOUBLE       _in_cosd(IN_DOUBLE);
extern IN_DOUBLE       _in_tand(IN_DOUBLE);
extern IN_DOUBLE       _in_asind(IN_DOUBLE);
extern IN_DOUBLE       _in_acosd(IN_DOUBLE);
extern IN_DOUBLE       _in_atand(IN_DOUBLE);
extern IN_DOUBLE       _in_atan2d(IN_DOUBLE, IN_DOUBLE);

extern IN_DOUBLE       _in_sinhd(IN_DOUBLE);
extern IN_DOUBLE       _in_coshd(IN_DOUBLE);
extern IN_DOUBLE       _in_tanhd(IN_DOUBLE);
extern IN_DOUBLE       _in_logd(IN_DOUBLE);
extern IN_DOUBLE       _in_log10d(IN_DOUBLE);
extern IN_DOUBLE       _in_expd(IN_DOUBLE);
extern IN_DOUBLE       _in_powd(IN_DOUBLE, IN_DOUBLE);
extern IN_DOUBLE       _in_modfd(IN_DOUBLE, IN_DOUBLE*);
extern IN_DOUBLE       _in_fmodd(IN_DOUBLE, IN_DOUBLE, unsigned*);
extern IN_DOUBLE       _in_ldexpd(IN_DOUBLE, int);

#if defined(_SH4) | defined(_SH4A) | defined(_SH2AFPU)
#pragma inline(_polinod)				       /* A S50001SP */
static IN_DOUBLE _polinod(IN_DOUBLE x,IN_DOUBLE *p,int dim)    /* A S50001SP */
{							       /* A S50001SP */
  IN_DOUBLE process = *p++;				       /* A S50001SP */
  do {							       /* A S50001SP */
      process = *p++ + process * x;			       /* A S50001SP */
  } while (--dim > 0);					       /* A S50001SP */
  return process;					       /* A S50001SP */
}							       /* A S50001SP */
#else							       /* A S50001SP */
extern IN_DOUBLE       _polinod(IN_DOUBLE, IN_DOUBLE*, int);
#endif							       /* A S50001SP */
extern IN_DOUBLE       _app_sind(IN_DOUBLE);
extern IN_DOUBLE       _app_cosd(IN_DOUBLE);
extern IN_DOUBLE       _app_atand(IN_DOUBLE);

/* constant data */
extern IN_DOUBLE _IFNAND;
extern IN_DOUBLE _IFZEROD;
extern IN_DOUBLE _IFINFD;
extern IN_DOUBLE _IFONED;
extern IN_DOUBLE _HALFD;
extern IN_DOUBLE _QUOTD;
extern IN_DOUBLE _TWOD;
extern IN_DOUBLE _FOURD;
extern IN_DOUBLE _PAID;
extern IN_DOUBLE _2PAID;
extern IN_DOUBLE _HLFPAID;
extern IN_DOUBLE _QUOPAID;
extern IN_DOUBLE _LOGE2D;

extern IN_DOUBLE _NIFZEROD;
extern IN_DOUBLE _NIFINFD;
extern IN_DOUBLE _NIFONED;
extern IN_DOUBLE _NHALFD;
extern IN_DOUBLE _NQUOTD;
extern IN_DOUBLE _NTWOD;
extern IN_DOUBLE _NFOURD;
extern IN_DOUBLE _NPAID;
extern IN_DOUBLE _N2PAID;
extern IN_DOUBLE _NHLFPAID;
extern IN_DOUBLE _NQUOPAID;
extern IN_DOUBLE _NLOGE2D;

