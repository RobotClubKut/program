;;*****************************************************************************
;;*****************************************************************************
;;  FILENAME: PRS8_2.inc
;;   Version: 3.4, Updated on 2013/5/19 at 10:44:3
;;  Generated by PSoC Designer 5.4.2946
;;
;;  DESCRIPTION: Assembler declarations for the PRS8 user module interface.
;;-----------------------------------------------------------------------------
;;  Copyright (c) Cypress Semiconductor 2013. All Rights Reserved.
;;*****************************************************************************
;;*****************************************************************************

include "m8c.inc"

;--------------------------------------------------
; Constants for PRS8_2 API's.
;--------------------------------------------------

;--------------------------------------------------
; Register Address Constants for PRS8_2
;--------------------------------------------------
PRS8_2_CONTROL_REG: equ 27h                      ;Control register LSB
PRS8_2_SHIFT_REG:   equ 24h                      ;Shift register LSB
PRS8_2_POLY_REG:    equ 25h                      ;Polynomial register LSB
PRS8_2_SEED_REG:    equ 26h                      ;Seed register LSB
PRS8_2_FUNC_REG:    equ 24h                      ;Function register LSB
PRS8_2_INPUT_REG:   equ 25h                      ;Input register LSB
PRS8_2_OUTPUT_REG:  equ 26h                      ;Output register LSB

; end of file PRS8_2.inc
