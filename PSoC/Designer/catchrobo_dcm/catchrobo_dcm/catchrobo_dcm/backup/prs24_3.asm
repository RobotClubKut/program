;;*****************************************************************************
;;*****************************************************************************
;;  FILENAME: PRS24_3.asm
;;   Version: 3.4, Updated on 2013/5/19 at 10:44:1
;;  Generated by PSoC Designer 5.4.2946
;;
;;  DESCRIPTION: PRS24 User Module software implementation file.
;;
;;  NOTE: User Module APIs conform to the fastcall16 convention for marshalling
;;        arguments and observe the associated "Registers are volatile" policy.
;;        This means it is the caller's responsibility to preserve any values
;;        in the X and A registers that are still needed after the API functions
;;        returns. For Large Memory Model devices it is also the caller's 
;;        responsibility to perserve any value in the CUR_PP, IDX_PP, MVR_PP and 
;;        MVW_PP registers. Even though some of these registers may not be modified
;;        now, there is no guarantee that will remain the case in future releases.
;;-----------------------------------------------------------------------------
;;  Copyright (c) Cypress Semiconductor 2013. All Rights Reserved.
;;*****************************************************************************
;;*****************************************************************************


include "m8c.inc"
include "memory.inc"
include "PRS24_3.inc"

;-----------------------------------------------
;  Global Symbols
;-----------------------------------------------
export    PRS24_3_Start
export   _PRS24_3_Start
export    PRS24_3_Stop
export   _PRS24_3_Stop
export    PRS24_3_WriteSeed
export   _PRS24_3_WriteSeed
export    PRS24_3_WritePolynomial
export   _PRS24_3_WritePolynomial
export    PRS24_3_ReadPRS
export   _PRS24_3_ReadPRS

;-----------------------------------------------
;  Constant Definitions
;-----------------------------------------------
bfCONTROL_REG_START_BIT:   equ   1        ; Control register start bit

AREA UserModules (ROM, REL)

.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: PRS24_3_Start
;
;  DESCRIPTION:
;     Starts the PRS24 user module.  The PRS will begin computing the PRS
;     POLYNOMIAL when data is clocked in.
;
;-----------------------------------------------------------------------------
;
;  ARGUMENTS: None
;
;  RETURNS:   None
;
;  SIDE EFFECTS:
;    The A and X registers may be modified by this or future implementations
;    of this function.  The same is true for all RAM page pointer registers in
;    the Large Memory Model.  When necessary, it is the calling function's
;    responsibility to perserve their values across calls to fastcall16 
;    functions.
;
;  THEORY of OPERATION or PROCEDURE:
;     Set the start bit in the Control register of the LSB block.
;
;-----------------------------------------------------------------------------
 PRS24_3_Start:
_PRS24_3_Start:
   RAM_PROLOGUE RAM_USE_CLASS_1
   or    REG[PRS24_3_CONTROL_REG_LSB], bfCONTROL_REG_START_BIT
   RAM_EPILOGUE RAM_USE_CLASS_1
   ret
.ENDSECTION


.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: PRS24_3_Stop
;
;  DESCRIPTION:
;     Disables PRS24 operation.
;
;-----------------------------------------------------------------------------
;
;  ARGUMENTS:  None
;
;  RETURNS:    None
;
;  SIDE EFFECTS:
;    The A and X registers may be modified by this or future implementations
;    of this function.  The same is true for all RAM page pointer registers in
;    the Large Memory Model.  When necessary, it is the calling function's
;    responsibility to perserve their values across calls to fastcall16 
;    functions.
;
;    Writing to the Seed register will cause the seed value to be latched into
;    the Shift register.
;
;  THEORY of OPERATION or PROCEDURE:
;     Clear the start bit in the Control register of the LSB block.
;
;-----------------------------------------------------------------------------
 PRS24_3_Stop:
_PRS24_3_Stop:
   RAM_PROLOGUE RAM_USE_CLASS_1
   and   REG[PRS24_3_CONTROL_REG_LSB], ~bfCONTROL_REG_START_BIT
   RAM_EPILOGUE RAM_USE_CLASS_1
   ret
.ENDSECTION

.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: PRS24_3_WriteSeed
;
;  DESCRIPTION:
;     Initializes the PRS polynomial function with a starting seed value.
;     The PRS24 User module is stopped while the Seed value is updated and
;     upon exit, its previous start state is restored.
;
;-----------------------------------------------------------------------------
;
;  ARGUMENTS:
;     DWORD dwSeedValue - the seed value to initialize the polynomial function.
;        X register points to 4 byte dword value - MSB byte is zero.
;        Note that X points to MSB.
;
;  RETURNS:    None
;
;  SIDE EFFECTS:
;    The A and X registers may be modified by this or future implementations
;    of this function.  The same is true for all RAM page pointer registers in
;    the Large Memory Model.  When necessary, it is the calling function's
;    responsibility to perserve their values across calls to fastcall16 
;    functions.
;
;    PRS24 user module is stopped while the seed is updated.
;
;  THEORY of OPERATION or PROCEDURE:
;     Set the seed value in the Seed register.
;
;-----------------------------------------------------------------------------
_PRS24_3_WriteSeed:
 PRS24_3_WriteSeed:
   RAM_PROLOGUE RAM_USE_CLASS_2
   mov   X, SP
   ;get and save the current start state
   mov   A, REG[PRS24_3_CONTROL_REG_LSB]
   push  A

   ;stop the PRS24
   and   REG[PRS24_3_CONTROL_REG_LSB], ~bfCONTROL_REG_START_BIT

   ; Load the Seed value into the Seed register
   mov   A, [X-5]
   mov   reg[PRS24_3_SEED_REG_MSB], A
   mov   A, [X-4]
   mov   reg[PRS24_3_SEED_REG_ISB], A
   mov   A, [X-3]
   mov   reg[PRS24_3_SEED_REG_LSB], A

   ; restore the start state
   pop   A
   mov   REG[PRS24_3_CONTROL_REG_LSB], A
   RAM_EPILOGUE RAM_USE_CLASS_2
   ret
.ENDSECTION

.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: PRS24_3_WritePolynomial
;
;  DESCRIPTION:
;     Initializes the PRS polynomial value.
;     The PRS24 User module is stopped while the polynomial value is updated and
;     upon exit, its previous start state is restored.
;
;-----------------------------------------------------------------------------
;
;  ARGUMENTS:
;     dwPolynomial - the polynomial to load into the polynomial register
;        X register points to 4 byte dword value - MSB byte is zero.
;        Note that X points to MSB.
;
;  RETURNS: None
;
;  SIDE EFFECTS:
;    The A and X registers may be modified by this or future implementations
;    of this function.  The same is true for all RAM page pointer registers in
;    the Large Memory Model.  When necessary, it is the calling function's
;    responsibility to perserve their values across calls to fastcall16 
;    functions.
;
;    PRS24 user module is stopped while the polynomial is updated.
;
;  THEORY of OPERATION or PROCEDURE:
;     Set the polynomial value in the Polynomial register
;
;-----------------------------------------------------------------------------
_PRS24_3_WritePolynomial:
 PRS24_3_WritePolynomial:
   RAM_PROLOGUE RAM_USE_CLASS_2
   mov   X, SP

   ;get and save the current start state
   mov   A, REG[PRS24_3_CONTROL_REG_LSB]
   push  A

   ;stop the PRS24
   and   REG[PRS24_3_CONTROL_REG_LSB], ~bfCONTROL_REG_START_BIT

   ; Load the polynomial into the PRS24 Polynomial register
   mov   A, [X-5]
   mov   reg[PRS24_3_POLY_REG_MSB], A
   mov   A, [X-4]
   mov   reg[PRS24_3_POLY_REG_ISB], A
   mov   A, [X-3]
   mov   reg[PRS24_3_POLY_REG_LSB], A

   ; restore the start state
   pop   A
   mov   REG[PRS24_3_CONTROL_REG_LSB], A
   RAM_EPILOGUE RAM_USE_CLASS_2
   ret
.ENDSECTION


.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: PRS24_3_ReadPRS
;
;  DESCRIPTION:
;     Reads the currently computed PRS polynomial function value.
;
;-----------------------------------------------------------------------------
;
;  ARGUMENTS:
;     DWORD * pdwPRSNumber - a pointer to a DWORD buffer to put the PRS computed
;        value.
;        The pointer is passed in the X register.
;        X points to the MSB of the DWORD
;
;  RETURNS:
;     The read value is placed in the data buffer pointed to by pdwPRSNumber as
;     passed in the X register.
;
;  SIDE EFFECTS:
;    The A and X registers may be modified by this or future implementations
;    of this function.  The same is true for all RAM page pointer registers in
;    the Large Memory Model.  When necessary, it is the calling function's
;    responsibility to perserve their values across calls to fastcall16 
;    functions.
;          
;    Currently only the page pointer registers listed below are modified:
;          IDX_PP
;
;     The seed value is lost.
;
;  THEORY of OPERATION or PROCEDURE:
;     1) Read the Shift register - PRS value is transferred to Seed register
;     2) Read the Seed register.
;
;-----------------------------------------------------------------------------
 PRS24_3_ReadPRS:
_PRS24_3_ReadPRS:
   RAM_PROLOGUE RAM_USE_CLASS_3
   RAM_SETPAGE_IDX A 

   ; set the MSB byte of the DWORD return data to 0 - not used.
   mov   [X], 0
   ;-------------
   ;  MSB BYTE
   ;-------------
   ; Read the Shift register.  This causes the current
   ;  PRS computed number to be transferred to the Seed register.
   mov   A, reg[PRS24_3_SHIFT_REG_MSB]

   ; Read the PRS computed value
   mov   A, reg[PRS24_3_SEED_REG_MSB]
   mov   [X+1], A

   ;-------------
   ;  ISB BYTE
   ;-------------
   ; Read the Shift register.  This causes the current
   ;  PRS computed number to be transferred to the Seed register.
   mov   A, reg[PRS24_3_SHIFT_REG_ISB]

   ; Read the PRS computed value
   mov   A, reg[PRS24_3_SEED_REG_ISB]
   mov   [X+2], A

   ;-------------
   ;  LSB BYTE
   ;-------------
   ; Read the Shift register.  This causes the current
   ;  PRS computed number to be transferred to the Seed register.
   mov   A, reg[PRS24_3_SHIFT_REG_LSB]

   ; Read the PRS computed value
   mov   A, reg[PRS24_3_SEED_REG_LSB]
   mov   [X+3], A

   RAM_EPILOGUE RAM_USE_CLASS_3
   ret
.ENDSECTION

; End of File PRS24_3.asm
