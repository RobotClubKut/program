-------- PROJECT GENERATOR --------
PROJECT NAME :	SH03
PROJECT DIRECTORY :	F:\Dropbox\NHK-2013\SH03\SH03
CPU SERIES :	SH-2
CPU TYPE :	SH7125
TOOLCHAIN NAME :	Renesas SuperH RISC engine Standard Toolchain
TOOLCHAIN VERSION :	9.4.0.0
GENERATION FILES :
    F:\Dropbox\NHK-2013\SH03\SH03\dbsct.c
        Setting of B,R Section
    F:\Dropbox\NHK-2013\SH03\SH03\typedefine.h
        Aliases of Integer Type
    F:\Dropbox\NHK-2013\SH03\SH03\sbrk.c
        Program of sbrk
    F:\Dropbox\NHK-2013\SH03\SH03\iodefine.h
        Definition of I/O Register
    F:\Dropbox\NHK-2013\SH03\SH03\intprg.c
        Interrupt Program
    F:\Dropbox\NHK-2013\SH03\SH03\vecttbl.c
        Initialize of Vector Table
    F:\Dropbox\NHK-2013\SH03\SH03\vect.h
        Definition of Vector
    F:\Dropbox\NHK-2013\SH03\SH03\resetprg.c
        Reset Program
    F:\Dropbox\NHK-2013\SH03\SH03\SH03.c
        Main Program
    F:\Dropbox\NHK-2013\SH03\SH03\sbrk.h
        Header file of sbrk file
    F:\Dropbox\NHK-2013\SH03\SH03\stacksct.h
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

DATE & TIME : 2013/01/18 12:29:22
