Project:      output/stepping_test
Build Number: 0
Date:         Thu Sep 18 15:49:45 2014
Compiler:     ICCM8C
Version:      7.05.00


Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             lit   01A0   022F =    559. bytes (rel,con,rom,lit)

       Addr  Global Symbol
      -----  --------------------------------
       01F9  LoadConfigTBL_stepping_test_Bank0
       024E  LoadConfigTBL_stepping_test_Bank1
       0279  __ctype
       03CF  __lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                        func_lit   03CF   0004 =      4. bytes (rel,con,rom,proclab)

       Addr  Global Symbol
      -----  --------------------------------
       03CF  __func_lit_start
       03D3  __func_lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                     psoc_config   03D3   0173 =    371. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       03D3  LoadConfigTBL_stepping_test_Ordered
       04D8  LoadConfigInit
       04D8  _LoadConfigInit
       04EB  LoadConfig_stepping_test
       04EB  _LoadConfig_stepping_test
       0546  __psoc_config_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                     UserModules   0546   022A =    554. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       0546  _SPIM_1_ISR
       054A  SPIM_1_EnableInt
       054A  _SPIM_1_EnableInt
       054E  _SPIM_1_Start
       054E  _SPIM_1_DisableInt
       054E  SPIM_1_Start
       0553  SPIM_1_SendTxData
       0553  _SPIM_1_Stop
       0553  _SPIM_1_SendTxData
       0556  _SPIM_1_bReadRxData
       0556  SPIM_1_bReadRxData
       0556  bSPIM_1_ReadRxData
       0556  _bSPIM_1_ReadRxData
       0559  _SPIM_1_bReadStatus
       0559  SPIM_1_bReadStatus
       0559  _bSPIM_1_ReadStatus
       0559  bSPIM_1_ReadStatus
       055C  _SleepTimer_1_ISR
       0570  SleepTimer_1_EnableInt
       0570  _SleepTimer_1_EnableInt
       0574  _SleepTimer_1_DisableInt
       0574  _SleepTimer_1_Start
       0574  SleepTimer_1_Start
       0582  _SleepTimer_1_SetInterval
       0582  _SleepTimer_1_TickWait
       0582  SleepTimer_1_TickWait
       0582  _SleepTimer_1_Stop
       0594  _SleepTimer_1_bGetTimer
       0594  _LCD_1_PrCString
       0594  _SleepTimer_1_SyncWait
       0594  _SleepTimer_1_SetTimer
       0594  LCD_1_PrCString
       0594  _SleepTimer_1_bGetTickCntr
       05A6  LCD_1_HEX_STR
       05B6  _LCD_1_PrHexByte
       05B6  LCD_1_PrHexByte
       05C9  _LCD_1_PrString
       05C9  LCD_1_PrString
       05C9  _LCD_1_PrHexInt
       05DB  _LCD_1_WriteData
       05DB  _LCD_1_Write_Data
       05DB  LCD_1_WriteData
       05DB  LCD_1_Write_Data
       05EF  LCD_1_Control
       05EF  _LCD_1_Control
       069F  LCD_1_Start
       069F  LCD_1_Init
       069F  _LCD_1_Init
       069F  _LCD_1_Start
       070E  LCD_1_ROW_OFFSET
       0712  LCD_1_Position
       0712  _LCD_1_Position
       0722  LCD_1_Delay50uTimes
       0722  _LCD_1_Delay50uTimes
       0728  LCD_1_Delay50u_Table
       0730  _LCD_1_Delay50u
       0730  LCD_1_Delay50u
       0744  LCD_1_BG_TYPE1
       0744  _LCD_1_InitVBG
       074B  LCD_1_BG_TYPE2
       0752  _CS_On
       0752  CS_On
       0752  _LCD_1_InitBG
       0756  _CS_Off
       0756  CS_Off
       0756  _CS_Start
       0756  _CS_Stop
       0756  CS_Start
       0756  CS_Stop
       0758  _CS_Switch
       0758  CS_Switch
       0770  CS_GetState
       0770  CS_Invert
       0770  __UserModules_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0770   2CC3 =  11459. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       0770  __text_start
       0770  __SPIM_ISR
       07F2  _L6470_SetParam
       083F  _L6470_Run
       08DC  _main
       0ABF  _SPI_transceiver
       0AE4  _LCD_print
       0B5D  _LCD_cprint
       0BD8  __cprint
       1CE2  _strlenLMM
       1CED  _strlen
       1D08  _cstrlenLMM
       1D0B  _cstrlen
       1D2C  __plcall
       1D38  _itoa
       1E5F  _ltoa
       2016  _ultoa
       2153  _utoa
       221C  _ftoa
       257C  _isdigit
       2596  _islower
       25B0  _isspace
       25CA  _toupper
       2635  __FormatFP_1
       310B  __csdepi
       3124  _csprintf
       3433  __xidata_start
       3172  <created procedures>
       3433  __text_end
       343E  __xidata_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             TOP   0000   0168 =    360. bytes (abs,ovr,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       0068  __Start
       0165  _bGetPowerSetting
       0165  bGetPowerSetting

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                    InterruptRAM   0000   0008 =      8. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0000  SleepTimer_1_fTick
       0000  _SleepTimer_1_fTick
       0001  _SleepTimer_1_bTimerValue
       0001  SleepTimer_1_bTimerValue
       0002  _SleepTimer_1_bCountDown
       0002  SleepTimer_1_bCountDown
       0003  _SleepTimer_1_TickCount
       0003  SleepTimer_1_TickCount
       0004  _Port_0_Data_SHADE
       0004  NO_SHADOW
       0004  Port_0_Data_SHADE
       0004  _NO_SHADOW
       0005  _Port_2_Data_SHADE
       0005  Port_2_Data_SHADE
       0006  Port_0_DriveMode_0_SHADE
       0006  _Port_0_DriveMode_0_SHADE
       0007  Port_0_DriveMode_1_SHADE
       0007  _Port_0_DriveMode_1_SHADE

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
               virtual_registers   0041   000F =     15. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0041  __rZ
       0042  __rY
       0043  __rX
       0044  __r11
       0045  __r10
       0046  __r9
       0047  __r8
       0048  __r7
       0049  __r6
       004A  __r5
       004B  __r4
       004C  __r3
       004D  __r2
       004E  __r1
       004F  __r0

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0000   003B =     59. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0000  __data_start
       0021  _lcdStr

Files Linked      [ module(s) ]

./obj/boot.o	[ boot.asm ]
obj/main.o	[ main.c ]
<library>	[ _printf.s, spim_1int.asm, spim_1.asm, sleeptimer_1int.asm, sleeptimer_1.asm, psocconfigtbl.asm ]
[ psocconfig.asm, lcd_1.asm, cs.asm, rZ.asm, rY.asm, rX.asm, r11.asm, r10.asm, r9.asm, r8.asm, r7.asm, r6.asm ]
[ r5.asm, r4.asm, r3.asm, r2.asm, r1.asm, r0.asm, divmodu_16x16_16_util.asm, divmodu_32x32_32_util.asm ]
[ fp_analysiseject_util.asm, fp_clrreg_util.asm, fp_nan_res_util.asm, fp_saveres_util.asm ]
[ fp_sendtoreg_util.asm, fp_sinf_res_util.asm, fp_szero_res_util.asm, fp_type_oprnd_util.asm ]
[ fp_unnormal_util.asm, fpadd_util.asm, fpcmp_util.asm, fpdiv_util.asm, fpmul_util.asm, fpsub_util.asm ]
[ i_div16_block_util.asm, i_div32_block_util.asm, i_mulu8_block_util.asm, mul32_util.asm ]
[ strlen.s, cstrlen.s, plcall.s, itoa.s, ltoa.s, ultoa.s, utoa.s, ftoa.s, isdigit.s, islower.s, isspace.s ]
[ ctype.s, toupper.s, formatfp1.s, sprintf.s ]

Area Definitions

-blit:0x1a0.0x7fff
-bdata:0.0x6ff
-BInterruptRAM:0	allocated at: 0
-Bvirtual_registers	allocated at: 0x41
-Bstepping_test_RAM
-rwh:SSCParmBlk:0xf7.0xff

