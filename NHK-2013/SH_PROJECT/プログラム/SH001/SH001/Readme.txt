-------- PROJECT GENERATOR --------
PROJECT NAME :	SH001
PROJECT DIRECTORY :	F:\Dropbox\基盤班\ABU2013\nakahara\NHK-2013\プログラム\SH001\SH001
CPU SERIES :	SH-2
CPU TYPE :	SH7125
TOOLCHAIN NAME :	Renesas SuperH RISC engine Standard Toolchain
TOOLCHAIN VERSION :	9.4.0.0
GENERATION FILES :
    F:\Dropbox\基盤班\ABU2013\nakahara\NHK-2013\プログラム\SH001\SH001\dbsct.c
        Setting of B,R Section
    F:\Dropbox\基盤班\ABU2013\nakahara\NHK-2013\プログラム\SH001\SH001\typedefine.h
        Aliases of Integer Type
    F:\Dropbox\基盤班\ABU2013\nakahara\NHK-2013\プログラム\SH001\SH001\sbrk.c
        Program of sbrk
    F:\Dropbox\基盤班\ABU2013\nakahara\NHK-2013\プログラム\SH001\SH001\iodefine.h
        Definition of I/O Register
    F:\Dropbox\基盤班\ABU2013\nakahara\NHK-2013\プログラム\SH001\SH001\intprg.c
        Interrupt Program
    F:\Dropbox\基盤班\ABU2013\nakahara\NHK-2013\プログラム\SH001\SH001\vecttbl.c
        Initialize of Vector Table
    F:\Dropbox\基盤班\ABU2013\nakahara\NHK-2013\プログラム\SH001\SH001\vect.h
        Definition of Vector
    F:\Dropbox\基盤班\ABU2013\nakahara\NHK-2013\プログラム\SH001\SH001\resetprg.c
        Reset Program
    F:\Dropbox\基盤班\ABU2013\nakahara\NHK-2013\プログラム\SH001\SH001\SH001.c
        Main Program
    F:\Dropbox\基盤班\ABU2013\nakahara\NHK-2013\プログラム\SH001\SH001\sbrk.h
        Header file of sbrk file
    F:\Dropbox\基盤班\ABU2013\nakahara\NHK-2013\プログラム\SH001\SH001\stacksct.h
        Setting of Stack area
START ADDRESS OF SECTION :
 H'000000000	DVECTTBL,DINTTBL,PIntPRG
 H'000000800	PResetPRG
 H'000001000	P,C,C$BSEC,C$DSEC,D
 H'0FFFFA000	B,R
 H'0FFFFBC00	S

* When the user program is executed,
* the interrupt mask has been masked.
* 
* Program start H'1000.
* RAM start H'FFFFA000.

DATE & TIME : 2012/11/23 13:45:56
