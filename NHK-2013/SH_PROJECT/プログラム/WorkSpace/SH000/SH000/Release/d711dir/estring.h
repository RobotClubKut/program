/********************************************************************************/
/* Copyright (C) 1992,2007 Renesas Technology Corp. and Renesas Solutions Corp. */
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

#ifndef _REENTRANT                              /* A S70003P  */
extern volatile int         _errno;                /* A S70003P  */
#else                                              /* A S70003P  */
#define _errno (*errno_addr())                        /* A S70001SP */
int  *errno_addr(void);                               /* C S70001SP */
#endif                                             /* A S70003P  */

extern void *memcpy(void *, const void *, size_t);
extern void *memmove(void *, const void *, size_t);  /* A S30002SP */
extern char *strcpy(char *, const char *);
extern char *strncpy(char *, const char *, size_t);
extern char *strcat(char *, const char *);
extern char *strncat(char *, const char *,size_t);
extern int  memcmp(const void *, const void *,size_t);
extern int  strcmp(const char *, const char *);
extern int  strncmp(const char *, const char *, size_t);
extern void *memchr(const void *, int, size_t);
extern char *strchr(const char *, int);
extern size_t strcspn(const char *, const char *);
extern char *strpbrk(const char *, const char *);
extern char *strrchr(const char *, int);
extern size_t strspn(const char *, const char *);
extern char *strstr(const char *, const char *);
extern char *strtok(char *, const char *);
extern void *memset(void *, int, size_t);
extern char *strerror(int);
extern size_t strlen(const char *);

#ifndef EMALRESM                                       /* A S70001SP */
#define EMALRESM 2100 /* malloc semaphore reserve error * A S70001SP */
#endif                                                 /* A S70001SP */
#ifndef ETOKRESM                                       /* A S70001SP V92B160 */
#define ETOKRESM 2110 /* strtok semaphore reserve error * A S70001SP */
#endif                                                 /* A S70001SP */
#ifndef EIOBRESM                                       /* A S70001SP V92B160 */
#define EIOBRESM 2120 /* _iob   semaphore reserve error * A S70001SP */
#endif                                                 /* A S70001SP */
#ifndef EMALFRSM                                       /* A S70001SP V92B160 */
#define EMALFRSM 2101 /* malloc semaphore free error    * A S70001SP */
#endif                                                 /* A S70001SP */
#ifndef ETOKFRSM                                       /* A S70001SP V92B160 */
#define ETOKFRSM 2111 /* strtok semaphore free error    * A S70001SP */
#endif                                                 /* A S70001SP */
#ifndef EIOBFRSM                                       /* A S70001SP V92B160 */
#define EIOBFRSM 2121 /* _iob   semaphore free error    * A S70001SP */
#endif                                                 /* A S70001SP */
