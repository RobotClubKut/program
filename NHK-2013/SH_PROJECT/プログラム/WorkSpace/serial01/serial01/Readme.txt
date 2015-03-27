-------- PROJECT GENERATOR --------
PROJECT NAME :	serial01
PROJECT DIRECTORY :	C:\WorkSpace\kn7125eva3\serial01\serial01
CPU SERIES :	SH-2
CPU TYPE :	SH7125
TOOLCHAIN NAME :	Renesas SuperH RISC engine Standard Toolchain
TOOLCHAIN VERSION :	9.0.3.0
GENERATION FILES :
    C:\WorkSpace\kn7125eva3\serial01\serial01\dbsct.c
        Setting of B,R Section
    C:\WorkSpace\kn7125eva3\serial01\serial01\typedefine.h
        Aliases of Integer Type
    C:\WorkSpace\kn7125eva3\serial01\serial01\sbrk.c
        Program of sbrk
    C:\WorkSpace\kn7125eva3\serial01\serial01\iodefine.h
        Definition of I/O Register
    C:\WorkSpace\kn7125eva3\serial01\serial01\intprg.c
        Interrupt Program
    C:\WorkSpace\kn7125eva3\serial01\serial01\vecttbl.c
        Initialize of Vector Table
    C:\WorkSpace\kn7125eva3\serial01\serial01\vect.h
        Definition of Vector
    C:\WorkSpace\kn7125eva3\serial01\serial01\resetprg.c
        Reset Program
    C:\WorkSpace\kn7125eva3\serial01\serial01\serial01.c
        Main Program
    C:\WorkSpace\kn7125eva3\serial01\serial01\sbrk.h
        Header file of sbrk file
    C:\WorkSpace\kn7125eva3\serial01\serial01\stacksct.h
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

DATE & TIME : 2008/05/18 14:20:49
