Project:      output/catchrobo_dcm
Build Number: 0
Date:         Thu Aug 22 12:22:26 2013
Compiler:     ICCM8C
Version:      7.05.00


Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             lit   01A0   01D6 =    470. bytes (rel,con,rom,lit)

       Addr  Global Symbol
      -----  --------------------------------
       0220  __ctype
       0376  __lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                        func_lit   0376   0004 =      4. bytes (rel,con,rom,proclab)

       Addr  Global Symbol
      -----  --------------------------------
       0376  __func_lit_start
       037A  __func_lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                     psoc_config   037A   02B9 =    697. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       037A  LoadConfigTBL_catchrobo_dcm
       061A  LoadConfigInit
       061A  _LoadConfigInit
       062D  LoadConfig_catchrobo_dcm
       062D  _LoadConfig_catchrobo_dcm
       0633  __psoc_config_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                     UserModules   0633   03C0 =    960. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       0633  _Timer8_1_ISR
       0637  _Timer8_1_EnableInt
       0637  Timer8_1_EnableInt
       063B  _Timer8_1_DisableInt
       063B  Timer8_1_DisableInt
       063F  _Timer8_1_Start
       063F  Timer8_1_Start
       0643  _Timer8_1_WritePeriod
       0643  bTimer8_1_CaptureCounter
       0643  bTimer8_1_ReadTimer
       0643  _Timer8_1_bReadTimer
       0643  _bTimer8_1_ReadCompareValue
       0643  _bTimer8_1_ReadCounter
       0643  _bTimer8_1_ReadTimer
       0643  _Timer8_1_bReadCompareValue
       0643  _Timer8_1_WriteCompareValue
       0643  _Timer8_1_bReadTimerSaveCV
       0643  PRS32_3_Start
       0643  _bTimer8_1_ReadTimerSaveCV
       0643  bTimer8_1_ReadCounter
       0643  _PRS32_3_Start
       0643  bTimer8_1_ReadTimerSaveCV
       0643  _Timer8_1_Stop
       0643  bTimer8_1_ReadCompareValue
       0643  _bTimer8_1_CaptureCounter
       0647  _PRS32_3_WriteSeed
       0647  PRS32_3_WriteSeed
       0647  _PRS32_3_Stop
       0666  _PRS32_3_WritePolynomial
       0666  PRS32_3_WritePolynomial
       0685  _PRS32_2_Start
       0685  _PRS32_3_ReadPRS
       0685  PRS32_2_Start
       0689  PRS32_2_WriteSeed
       0689  _PRS32_2_WriteSeed
       0689  _PRS32_2_Stop
       06A8  PRS32_2_WritePolynomial
       06A8  _PRS32_2_WritePolynomial
       06C7  PRS32_1_Start
       06C7  _PRS32_2_ReadPRS
       06C7  _PRS32_1_Start
       06CB  PRS32_1_WriteSeed
       06CB  _PRS32_1_WriteSeed
       06CB  _PRS32_1_Stop
       06EA  _PRS32_1_WritePolynomial
       06EA  PRS32_1_WritePolynomial
       0709  _LCD_1_PrCString
       0709  _PRS32_1_ReadPRS
       0709  LCD_1_PrCString
       071B  LCD_1_HEX_STR
       072B  _LCD_1_PrHexByte
       072B  LCD_1_PrHexByte
       073E  _LCD_1_PrHexInt
       073E  LCD_1_PrString
       073E  _LCD_1_PrString
       0750  LCD_1_Write_Data
       0750  LCD_1_WriteData
       0750  _LCD_1_WriteData
       0750  _LCD_1_Write_Data
       0764  _LCD_1_Control
       0764  LCD_1_Control
       0814  LCD_1_Start
       0814  _LCD_1_Start
       0814  _LCD_1_Init
       0814  LCD_1_Init
       0883  LCD_1_ROW_OFFSET
       0887  LCD_1_Position
       0887  _LCD_1_Position
       0897  _LCD_1_Delay50uTimes
       0897  LCD_1_Delay50uTimes
       089D  LCD_1_Delay50u_Table
       08A5  LCD_1_Delay50u
       08A5  _LCD_1_Delay50u
       08B9  _EzI2Cs_1_ISR
       099C  _EzI2Cs_1_Start
       099C  EzI2Cs_1_Start
       09CD  _EzI2Cs_1_GetActivity
       09CD  _EzI2Cs_1_GetAddr
       09CD  EzI2Cs_1_ResumeInt
       09CD  _EzI2Cs_1_ResumeInt
       09CF  EzI2Cs_1_EnableInt
       09CF  _EzI2Cs_1_EnableInt
       09DA  _EzI2Cs_1_DisableSlave
       09DA  _EzI2Cs_1_Stop
       09DA  _EzI2Cs_1_SetRamBuffer
       09DA  EzI2Cs_1_SetRamBuffer
       09DA  _EzI2Cs_1_DisableInt
       09F3  __UserModules_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   09F3   3B58 =  15192. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       09F3  __text_start
       09F3  _main
       0C59  __Timer8_1_ISR
       1657  _putchar
       169F  __cprint
       24C4  _MBM_1_InitializeMailbox
       24CE  _MBM_1_SetBusyFlag
       24D2  _MBM_1_ClearBusyFlag
       24D6  _MBM_1_CheckDirtyFlag
       2AA3  _strlenLMM
       2AAE  _strlen
       2AC9  _cstrlenLMM
       2ACC  _cstrlen
       2AED  __plcall
       2AF9  _itoa
       2CD2  _ltoa
       2F4B  _ultoa
       3102  _utoa
       3245  _ftoa
       368B  _isdigit
       36AC  _islower
       36CD  _isspace
       36EE  _toupper
       3769  __FormatFP_1
       4509  _cprintf
       454B  __xidata_start
       454B  __text_end
       4555  __xidata_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             TOP   0000   018C =    396. bytes (abs,ovr,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       0068  __Start
       0189  _bGetPowerSetting
       0189  bGetPowerSetting

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                    InterruptRAM   0000   000D =     13. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0000  Port_0_Data_SHADE
       0000  NO_SHADOW
       0000  _Port_0_Data_SHADE
       0000  _NO_SHADOW
       0001  _Port_1_Data_SHADE
       0001  Port_1_Data_SHADE
       0002  _Port_2_Data_SHADE
       0002  Port_2_Data_SHADE
       0003  _Port_0_DriveMode_0_SHADE
       0003  Port_0_DriveMode_0_SHADE
       0004  _Port_0_DriveMode_1_SHADE
       0004  Port_0_DriveMode_1_SHADE
       0005  _EzI2Cs_1_varPage
       0005  EzI2Cs_1_bState
       0005  _EzI2Cs_1_bState
       0005  EzI2Cs_1_varPage
       0006  _EzI2Cs_1_bRAM_RWoffset
       0006  EzI2Cs_1_bRAM_RWoffset
       0007  EzI2Cs_1_bRAM_RWcntr
       0007  _EzI2Cs_1_bRAM_RWcntr
       0008  EzI2Cs_1_pRAM_Buf_Addr_MSB
       0008  _EzI2Cs_1_pRAM_Buf_Addr_MSB
       0009  _EzI2Cs_1_pRAM_Buf_Addr_LSB
       0009  EzI2Cs_1_pRAM_Buf_Addr_LSB
       000A  EzI2Cs_1_bRAM_Buf_Size
       000A  _EzI2Cs_1_bRAM_Buf_Size
       000B  _EzI2Cs_1_bRAM_Buf_WSize
       000B  EzI2Cs_1_bRAM_Buf_WSize
       000C  _EzI2Cs_1_bBusy_Flag
       000C  EzI2Cs_1_bBusy_Flag

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
               virtual_registers   003B   000F =     15. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       003B  __rZ
       003C  __rY
       003D  __rX
       003E  __r11
       003F  __r10
       0040  __r9
       0041  __r8
       0042  __r7
       0043  __r6
       0044  __r5
       0045  __r4
       0046  __r3
       0047  __r2
       0048  __r1
       0049  __r0

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0000   0067 =    103. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0000  __data_start
       0026  _MBM_1_MyMailbox
       0059  _OutboxBuff
       0067  _InboxBuff
       006C  _MBM_1_pMyMailbox
       006E  _ct

Files Linked      [ module(s) ]

./obj/boot.o	[ boot.asm ]
obj/main.o	[ main.c ]
<library>	[ _printf.s, timer8_1int.asm, timer8_1.asm, psocconfigtbl.asm, psocconfig.asm, prs32_3.asm, prs32_2.asm ]
[ prs32_1.asm, mbm_1.c, lcd_1.asm, ezi2cs_1int.asm, ezi2cs_1.asm, rZ.asm, rY.asm, rX.asm, r11.asm, r10.asm ]
[ r9.asm, r8.asm, r7.asm, r6.asm, r5.asm, r4.asm, r3.asm, r2.asm, r1.asm, r0.asm, divmod_16x16_16_util.asm ]
[ divmodu_16x16_16_util.asm, divmodu_32x32_32_util.asm, fp_analysiseject_util.asm, fp_clrreg_util.asm ]
[ fp_nan_res_util.asm, fp_saveres_util.asm, fp_sendtoreg_util.asm, fp_sinf_res_util.asm, fp_szero_res_util.asm ]
[ fp_type_oprnd_util.asm, fp_unnormal_util.asm, fpadd_util.asm, fpcmp_util.asm, fpdiv_util.asm ]
[ fpmul_util.asm, fpsub_util.asm, i_div16_block_util.asm, i_div32_block_util.asm, i_mulu8_block_util.asm ]
[ mul32_util.asm, strlen.s, cstrlen.s, plcall.s, itoa.s, ltoa.s, ultoa.s, utoa.s, ftoa.s, isdigit.s, islower.s ]
[ isspace.s, ctype.s, toupper.s, formatfp1.s, printf.s ]

Area Definitions

-blit:0x1a0.0x7fff
-bdata:0.0x6ff
-BInterruptRAM:0	allocated at: 0
-Bvirtual_registers	allocated at: 0x3b
-Bcatchrobo_dcm_RAM	allocated at: 0
-rwh:SSCParmBlk:0xf7.0xff

