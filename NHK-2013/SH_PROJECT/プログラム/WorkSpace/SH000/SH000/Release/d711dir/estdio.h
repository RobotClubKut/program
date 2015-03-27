/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/***********************************************************************/
/* SPEC;                                                               */
/*  NAME = stdio : header file for standard I/O function ;             */
/*                                                                     */
/*  FUNC = this header file do the following functions;                */
/*         (1) file entry table define;                                */
/*         (2) I/O macro define;                                       */
/*         (3) symbol define;                                          */
/*  CLAS = UNIT;                                                       */
/*                                                                     */
/* END;                                                                */
/***********************************************************************/

extern const int _nfiles;                               /* C S70001SP */

#pragma pack 4
extern struct _iobuf {
       unsigned char *_bufptr;          /* buffer pointer              */
                long  _bufcnt;          /* buffer count                */
       unsigned char *_bufbase;         /* buffer base pointer         */
                long  _buflen;          /* buffer length               */
                char  _ioflag1;         /* I/O control flag 1          */
                char  _ioflag2;         /* I/O control flag 2          */
                char  _iofd;
}  _iob[];                                         /* C S70001SP */
#pragma unpack

extern volatile int         _errno;                      /* C S01002SP */

typedef struct _iobuf  FILE;            /* define FILE of file-stream */

                                        /* define function of prototype  */
extern int     _fillbuf(FILE*);
extern int     _flshbuf(int,FILE*);
extern int     fclose(FILE *);
extern int     fflush(FILE *);
extern FILE   *fopen(const char *, const char *);
extern FILE   *freopen(const char *, const char *, FILE *);
extern void    setbuf(FILE *, char *);
extern int     setvbuf(FILE *, char *, int, size_t);
extern int     fprintf(FILE *, const char *, ...);
extern int     fscanf(FILE *, const char *, ...);
extern int     printf(const char * ,...);
extern int     scanf(const char * ,...);
extern int     sprintf(char *, const char * ,...);
extern int     sscanf(const char *, const char * ,...);
extern int     vfprintf(FILE *, const char *, char *);
extern int     vprintf(const char *, char *);
extern int     vsprintf(char *, const char *, char *);
extern int     fgetc(FILE *);
extern char   *fgets(char *, int, FILE *);
extern int     fputc(int , FILE *);
extern int     fputs(const char *, FILE *);
extern int     getc(FILE *);
extern int     getchar(void);
extern char   *gets(char *);
extern int     putc(int, FILE *);
extern int     putchar(int);
extern int     puts(const char *);
extern int     ungetc(int, FILE *);
extern size_t  fread(void *, size_t, size_t, FILE *);
extern size_t  fwrite(const void *, size_t, size_t, FILE *);
extern int     fseek(FILE *, long int, int);
extern long    ftell(FILE *);
extern void    rewind(FILE *);
extern void    clearerr(FILE *);
extern int     feof(FILE *);
extern int     ferror(FILE *);
extern void    perror(const char *);

