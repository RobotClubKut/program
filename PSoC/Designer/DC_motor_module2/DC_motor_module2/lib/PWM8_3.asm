;;*****************************************************************************
;;*****************************************************************************
;;  FILENAME: PWM8_3.asm
;;   Version: 2.60, Updated on 2013/5/19 at 10:44:7
;;  Generated by PSoC Designer 5.4.2946
;;
;;  DESCRIPTION: PWM8 User Module software implementation file
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
include "PWM8_3.inc"
include "memory.inc"

;-----------------------------------------------
;  Global Symbols
;-----------------------------------------------
export  PWM8_3_EnableInt
export _PWM8_3_EnableInt
export  PWM8_3_DisableInt
export _PWM8_3_DisableInt
export  PWM8_3_Start
export _PWM8_3_Start
export  PWM8_3_Stop
export _PWM8_3_Stop
export  PWM8_3_WritePeriod
export _PWM8_3_WritePeriod
export  PWM8_3_WritePulseWidth
export _PWM8_3_WritePulseWidth
export  PWM8_3_bReadPulseWidth
export _PWM8_3_bReadPulseWidth
export  PWM8_3_bReadCounter
export _PWM8_3_bReadCounter

; The following functions are deprecated and subject to omission in future releases
;
export  bPWM8_3_ReadPulseWidth    ; deprecated
export _bPWM8_3_ReadPulseWidth    ; deprecated
export  bPWM8_3_ReadCounter       ; deprecated
export _bPWM8_3_ReadCounter       ; deprecated


AREA dc_motor_module2_RAM (RAM,REL)

;-----------------------------------------------
;  Constant Definitions
;-----------------------------------------------

INPUT_REG_NULL:                equ 0x00    ; Clear the input register


;-----------------------------------------------
; Variable Allocation
;-----------------------------------------------


AREA UserModules (ROM, REL)

.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: PWM8_3_EnableInt
;
;  DESCRIPTION:
;     Enables this PWM's interrupt by setting the interrupt enable mask bit
;     associated with this User Module. This function has no effect until and
;     unless the global interrupts are enabled (for example by using the
;     macro M8C_EnableGInt).
;-----------------------------------------------------------------------------
;
;  ARGUMENTS:    None.
;  RETURNS:      Nothing.
;  SIDE EFFECTS:
;    The A and X registers may be modified by this or future implementations
;    of this function.  The same is true for all RAM page pointer registers in
;    the Large Memory Model.  When necessary, it is the calling function's
;    responsibility to perserve their values across calls to fastcall16 
;    functions.
;
 PWM8_3_EnableInt:
_PWM8_3_EnableInt:
   RAM_PROLOGUE RAM_USE_CLASS_1
   PWM8_3_EnableInt_M
   RAM_EPILOGUE RAM_USE_CLASS_1
   ret


.ENDSECTION

.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: PWM8_3_DisableInt
;
;  DESCRIPTION:
;     Disables this PWM's interrupt by clearing the interrupt enable
;     mask bit associated with this User Module.
;-----------------------------------------------------------------------------
;
;  ARGUMENTS:    None
;  RETURNS:      Nothing
;  SIDE EFFECTS:
;    The A and X registers may be modified by this or future implementations
;    of this function.  The same is true for all RAM page pointer registers in
;    the Large Memory Model.  When necessary, it is the calling function's
;    responsibility to perserve their values across calls to fastcall16 
;    functions.
;
 PWM8_3_DisableInt:
_PWM8_3_DisableInt:
   RAM_PROLOGUE RAM_USE_CLASS_1
   PWM8_3_DisableInt_M
   RAM_EPILOGUE RAM_USE_CLASS_1
   ret


.ENDSECTION

.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: PWM8_3_Start
;
;  DESCRIPTION:
;     Sets the start bit in the Control register of this user module.  The
;     PWM will begin counting on the next input clock as soon as the
;     enable input is asserted high.
;-----------------------------------------------------------------------------
;
;  ARGUMENTS:    None
;  RETURNS:      Nothing
;  SIDE EFFECTS:
;    The A and X registers may be modified by this or future implementations
;    of this function.  The same is true for all RAM page pointer registers in
;    the Large Memory Model.  When necessary, it is the calling function's
;    responsibility to perserve their values across calls to fastcall16 
;    functions.
;
 PWM8_3_Start:
_PWM8_3_Start:
   RAM_PROLOGUE RAM_USE_CLASS_1
   PWM8_3_Start_M
   RAM_EPILOGUE RAM_USE_CLASS_1
   ret


.ENDSECTION

.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: PWM8_3_Stop
;
;  DESCRIPTION:
;     Disables PWM operation by clearing the start bit in the Control
;     register.
;-----------------------------------------------------------------------------
;
;  ARGUMENTS:    None
;  RETURNS:      Nothing
;  SIDE EFFECTS:
;    The A and X registers may be modified by this or future implementations
;    of this function.  The same is true for all RAM page pointer registers in
;    the Large Memory Model.  When necessary, it is the calling function's
;    responsibility to perserve their values across calls to fastcall16 
;    functions.
;
 PWM8_3_Stop:
_PWM8_3_Stop:
   RAM_PROLOGUE RAM_USE_CLASS_1
   PWM8_3_Stop_M
   RAM_EPILOGUE RAM_USE_CLASS_1
   ret


.ENDSECTION

.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: PWM8_3_WritePeriod
;
;  DESCRIPTION:
;     Write the 8-bit period value into the Period register (DR1).
;-----------------------------------------------------------------------------
;
;  ARGUMENTS: fastcall16 BYTE bPeriodValue (passed in A)
;  RETURNS:   Nothing
;  SIDE EFFECTS:
;    If the PWM user module is stopped, then this value will also be
;    latched into the Count register (DR0).
;    
;    The A and X registers may be modified by this or future implementations
;    of this function.  The same is true for all RAM page pointer registers in
;    the Large Memory Model.  When necessary, it is the calling function's
;    responsibility to perserve their values across calls to fastcall16 
;    functions.
;
 PWM8_3_WritePeriod:
_PWM8_3_WritePeriod:
   RAM_PROLOGUE RAM_USE_CLASS_1
   mov   reg[PWM8_3_PERIOD_REG], A
   RAM_EPILOGUE RAM_USE_CLASS_1
   ret


.ENDSECTION

.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: PWM8_3_WritePulseWidth
;
;  DESCRIPTION:
;     Writes compare value into the Compare register (DR2).
;-----------------------------------------------------------------------------
;
;  ARGUMENTS:    fastcall16 BYTE bCompareValue (passed in A)
;  RETURNS:      Nothing
;  SIDE EFFECTS:
;    The A and X registers may be modified by this or future implementations
;    of this function.  The same is true for all RAM page pointer registers in
;    the Large Memory Model.  When necessary, it is the calling function's
;    responsibility to perserve their values across calls to fastcall16 
;    functions.
;
 PWM8_3_WritePulseWidth:
_PWM8_3_WritePulseWidth:
   RAM_PROLOGUE RAM_USE_CLASS_1
   mov   reg[PWM8_3_COMPARE_REG], A
   RAM_EPILOGUE RAM_USE_CLASS_1
   ret


.ENDSECTION

.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: PWM8_3_bReadPulseWidth
;
;  DESCRIPTION:
;     Reads the Compare register.
;-----------------------------------------------------------------------------
;
;  ARGUMENTS:    None
;  RETURNS:      fastcall16 BYTE bCompareValue (value of DR2 in the A register)
;  SIDE EFFECTS:
;    The A and X registers may be modified by this or future implementations
;    of this function.  The same is true for all RAM page pointer registers in
;    the Large Memory Model.  When necessary, it is the calling function's
;    responsibility to perserve their values across calls to fastcall16 
;    functions.
;
 PWM8_3_bReadPulseWidth:
_PWM8_3_bReadPulseWidth:
 bPWM8_3_ReadPulseWidth:                         ; this name deprecated
_bPWM8_3_ReadPulseWidth:                         ; this name deprecated
   RAM_PROLOGUE RAM_USE_CLASS_1
   mov   A, reg[PWM8_3_COMPARE_REG]
   RAM_EPILOGUE RAM_USE_CLASS_1
   ret


.ENDSECTION

.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: PWM8_3_bReadCounter
;
;  DESCRIPTION:
;     Returns the value in the Count register (DR0), preserving the value in
;     the compare register (DR2). Interrupts are prevented during the transfer
;     from the Count to the Compare registers by holding the clock low in
;     the PSoC block.
;-----------------------------------------------------------------------------
;
;  ARGUMENTS: None
;  RETURNS:   fastcall16 BYTE bCount (value of DR0 in the A register)
;  SIDE EFFECTS:
;     1) The user module is stopped momentarily and one or more counts may be missed.
;     2) The A and X registers may be modified by this or future implementations
;        of this function.  The same is true for all RAM page pointer registers in
;        the Large Memory Model.  When necessary, it is the calling function's
;        responsibility to perserve their values across calls to fastcall16 
;        functions.
;
 PWM8_3_bReadCounter:
_PWM8_3_bReadCounter:
 bPWM8_3_ReadCounter:                            ; this name deprecated
_bPWM8_3_ReadCounter:                            ; this name deprecated

   bOrigCompareValue:      EQU   0               ; Frame offset to temp Compare store
   bOrigClockSetting:      EQU   1               ; Frame offset to temp Input   store
   wCounter:               EQU   2               ; Frame offset to temp Count   store
   STACK_FRAME_SIZE:       EQU   3               ; max stack frame size is 3 bytes

   RAM_PROLOGUE RAM_USE_CLASS_2
   mov   X, SP                                   ; X <- stack frame pointer
   mov   A, reg[PWM8_3_COMPARE_REG]              ; Save the Compare register on the stack
   push  A                                       ;
   PWM8_3_Stop_M                                 ; Disable (stop) the PWM
   M8C_SetBank1                                  ;
   mov   A, reg[PWM8_3_INPUT_REG]                ; save the clock input setting
   push  A                                       ;   on the stack (now 2 bytes) and ...
                                                 ;   hold the clock low:
   mov   reg[PWM8_3_INPUT_REG], INPUT_REG_NULL
   M8C_SetBank0
                                                 ; Extract the Count via DR2 register
   mov   A, reg[PWM8_3_COUNTER_REG]              ; DR2 <- DR0
   mov   A, reg[PWM8_3_COMPARE_REG]              ; Stash the Count on the stack
   push  A                                       ;  -stack frame is now 3 bytes
   mov   A, [X+bOrigCompareValue]                ; Restore the Compare register
   mov   reg[PWM8_3_COMPARE_REG], A
   M8C_SetBank1                                  ; Restore the PWM operation:
   mov   A, [X+bOrigClockSetting]                ;   First, the clock setting...
   mov   reg[PWM8_3_INPUT_REG], A                ;
   M8C_SetBank0                                  ;
   PWM8_3_Start_M                                ;   then re-enable the PWM.
   pop   A                                       ; Setup the return value
   ADD   SP, -(STACK_FRAME_SIZE-1)               ; Zap remainder of stack frame
   RAM_EPILOGUE RAM_USE_CLASS_2
   ret

.ENDSECTION

; End of File PWM8_3.asm
