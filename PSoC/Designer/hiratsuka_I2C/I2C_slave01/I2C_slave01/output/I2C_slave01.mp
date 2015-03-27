Project:      output/I2C_slave01
Build Number: 0
Date:         Sun Aug 11 23:54:59 2013
Compiler:     ICCM8C
Version:      7.05.00


Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             lit   0150   008C =    140. bytes (rel,con,rom,lit)

       Addr  Global Symbol
      -----  --------------------------------
       0176  LoadConfigTBL_i2c_slave01_Bank0
       01AD  LoadConfigTBL_i2c_slave01_Bank1
       01DC  __lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                     psoc_config   01DC   012C =    300. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       01DC  LoadConfigTBL_i2c_slave01_Ordered
       02A1  _LoadConfigInit
       02A1  LoadConfigInit
       02B1  _LoadConfig_i2c_slave01
       02B1  LoadConfig_i2c_slave01
       0308  __psoc_config_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                     UserModules   0308   0445 =   1093. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       0308  _Timer16_1_ISR
       030C  _Timer16_1_EnableInt
       030C  Timer16_1_EnableInt
       0310  _Timer16_1_DisableInt
       0310  Timer16_1_DisableInt
       0314  Timer16_1_Start
       0314  _Timer16_1_Start
       0318  _Timer16_1_Stop
       0318  Timer16_1_Stop
       031C  Timer16_1_WritePeriod
       031C  _Timer16_1_WritePeriod
       0322  Timer16_1_WriteCompareValue
       0322  _Timer16_1_WriteCompareValue
       0328  Timer16_1_wReadCompareValue
       0328  wTimer16_1_ReadCompareValue
       0328  _wTimer16_1_ReadCompareValue
       0328  _Timer16_1_wReadCompareValue
       032E  _Timer16_1_wReadTimerSaveCV
       032E  _wTimer16_1_ReadTimerSaveCV
       032E  wTimer16_1_ReadCounter
       032E  Timer16_1_wReadTimerSaveCV
       032E  wTimer16_1_ReadTimerSaveCV
       032E  _wTimer16_1_ReadCounter
       0360  Timer16_1_wReadTimer
       0360  _wTimer16_1_ReadTimer
       0360  wTimer16_1_CaptureCounter
       0360  _wTimer16_1_CaptureCounter
       0360  wTimer16_1_ReadTimer
       0360  _Timer16_1_wReadTimer
       0368  _LCD_1_PrCString
       0368  LCD_1_PrCString
       037A  LCD_1_HEX_STR
       038A  _LCD_1_PrHexByte
       038A  LCD_1_PrHexByte
       039D  _LCD_1_PrHexInt
       039D  LCD_1_PrHexInt
       03A4  _LCD_1_PrString
       03A4  LCD_1_PrString
       03AE  _LCD_1_Write_Data
       03AE  LCD_1_Write_Data
       03AE  _LCD_1_WriteData
       03AE  LCD_1_WriteData
       03C2  LCD_1_Control
       03C2  _LCD_1_Control
       0469  LCD_1_Start
       0469  _LCD_1_Start
       0469  _LCD_1_Init
       0469  LCD_1_Init
       04D5  LCD_1_ROW_OFFSET
       04D9  LCD_1_Position
       04D9  _LCD_1_Position
       04E5  LCD_1_Delay50uTimes
       04E5  _LCD_1_Delay50uTimes
       04EB  LCD_1_Delay50u_Table
       04F3  _LCD_1_Delay50u
       04F3  LCD_1_Delay50u
       0507  LCD_1_DrawBG
       052D  _LCD_1_DrawBG
       0556  LCD_1_DrawVBG
       0583  _LCD_1_DrawVBG
       05B3  LCD_1_InitVBG
       05B3  _LCD_1_InitVBG
       05E0  LCD_1_BG_TYPE1
       05E7  LCD_1_BG_TYPE2
       05EE  _LCD_1_InitBG
       05EE  LCD_1_InitBG
       061E  _EzI2Cs_1_ISR
       06EA  _EzI2Cs_1_Start
       06EA  EzI2Cs_1_Start
       0718  EzI2Cs_1_GetActivity
       0718  _EzI2Cs_1_GetActivity
       0720  EzI2Cs_1_GetAddr
       0720  _EzI2Cs_1_GetAddr
       0723  _EzI2Cs_1_ResumeInt
       0723  EzI2Cs_1_ResumeInt
       0725  EzI2Cs_1_EnableInt
       0725  _EzI2Cs_1_EnableInt
       0730  _EzI2Cs_1_Stop
       0730  EzI2Cs_1_Stop
       0737  _EzI2Cs_1_DisableInt
       0737  EzI2Cs_1_DisableInt
       073B  EzI2Cs_1_DisableSlave
       073B  _EzI2Cs_1_DisableSlave
       073F  _EzI2Cs_1_SetRamBuffer
       073F  EzI2Cs_1_SetRamBuffer
       074D  __UserModules_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   074D   0105 =    261. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       074D  __text_start
       074D  _main
       0797  __Timer16_1_ISR
       0852  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
               virtual_registers   0000   000F =     15. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0000  __rZ
       0001  __rY
       0002  __rX
       0003  __r11
       0004  __r10
       0005  __r9
       0006  __r8
       0007  __r7
       0008  __r6
       0009  __r5
       000A  __r4
       000B  __r3
       000C  __r2
       000D  __r1
       000E  __r0
       000F  __virtual_registers_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                    InterruptRAM   000F   000A =     10. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       000F  NO_SHADOW
       000F  _Port_0_Data_SHADE
       000F  Port_0_Data_SHADE
       000F  _NO_SHADOW
       0010  _Port_0_DriveMode_0_SHADE
       0010  Port_0_DriveMode_0_SHADE
       0011  _Port_0_DriveMode_1_SHADE
       0011  Port_0_DriveMode_1_SHADE
       0012  EzI2Cs_1_bState
       0012  EzI2Cs_1_varPage
       0012  _EzI2Cs_1_varPage
       0012  _EzI2Cs_1_bState
       0013  EzI2Cs_1_bRAM_RWoffset
       0013  _EzI2Cs_1_bRAM_RWoffset
       0014  _EzI2Cs_1_bRAM_RWcntr
       0014  EzI2Cs_1_bRAM_RWcntr
       0015  _EzI2Cs_1_pRAM_Buf_Addr_LSB
       0015  EzI2Cs_1_pRAM_Buf_Addr_LSB
       0016  EzI2Cs_1_bRAM_Buf_Size
       0016  _EzI2Cs_1_bRAM_Buf_Size
       0017  _EzI2Cs_1_bRAM_Buf_WSize
       0017  EzI2Cs_1_bRAM_Buf_WSize
       0018  EzI2Cs_1_bBusy_Flag
       0018  _EzI2Cs_1_bBusy_Flag
       0019  __InterruptRAM_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             bss   0019   0005 =      5. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0019  _MyI2C_Regs
       0019  __bss_start
       001E  __ramareas_end
       001E  __bss_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             TOP   0000   00D7 =    215. bytes (abs,ovr,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       0068  __Start
       00D4  _bGetPowerSetting
       00D4  bGetPowerSetting

Files Linked      [ module(s) ]

./obj/boot.o	[ boot.asm ]
obj/main.o	[ main.c ]
<library>	[ timer16_1int.asm, timer16_1.asm, psocconfigtbl.asm, psocconfig.asm, lcd_1.asm, ezi2cs_1int.asm ]
[ ezi2cs_1.asm, rZ.asm, rY.asm, rX.asm, r11.asm, r10.asm, r9.asm, r8.asm, r7.asm, r6.asm, r5.asm, r4.asm ]
[ r3.asm, r2.asm, r1.asm, r0.asm ]

Area Definitions

-blit:0x150.0x3fff
-bdata:0.0xff
-rwh:SSCParmBlk:0xf7.0xff

