/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
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


#ifndef _REENTRANT                              /* A S70003P */
extern volatile int _errno;                        /* C S01002SP */
#else                                              /* A S70003P */
extern  int *errno_addr(void);                     /* A S70001SP */
#define _errno (*errno_addr())                     /* A S70001SP */
#endif                                             /* A S70003P */
extern const double _HUGE_VAL;                     /* C S01006SP */
extern const size_t _sbrk_size;                         /* A S70001SP */

extern double atof(const char *) ;
extern int atoi(const char *) ;
extern long int atol(const char *) ;
extern long long int atoll(const char *) ;                          /* A V80#1.05 */
extern double strtod(const char *, char **) ;
extern long int strtol(const char *, char **, int);
extern unsigned long int strtoul(const char *, char **, int);       /* A V80#1.05 */
extern long long int strtoll(const char *, char **, int);           /* A V80#1.05 */
extern unsigned long long int strtoull(const char *, char **, int); /* A V80#1.05 */
extern int rand(void) ;
extern void srand(unsigned int);
extern void *calloc(size_t, size_t);
extern void free(void *) ;
extern void *malloc(size_t);
extern void *realloc(void *, size_t) ;
extern void *bsearch(const void *, const void *, size_t, size_t,
                                  int(*)(const void*,const void*) ) ;
extern void qsort(void *, size_t, size_t,
                                  int(*)(const void*,const void*) );
extern int abs(int);
extern div_t div(int, int);
extern long int labs(long int);
extern long long int llabs(long long int);          /* A V80#1.05 */
extern ldiv_t ldiv(long int, long int);
extern lldiv_t lldiv(long long int, long long int); /* A V80#1.05 */

