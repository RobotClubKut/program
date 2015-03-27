Project:      output/DC_motor_module
Build Number: 0
Date:         Sun Aug 18 16:42:28 2013
Compiler:     ICCM8C
Version:      7.05.00


Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             lit   01A0   0098 =    152. bytes (rel,con,rom,lit)

       Addr  Global Symbol
      -----  --------------------------------
       01A0  LoadConfigTBL_dc_motor_module_Bank0
       0201  LoadConfigTBL_dc_motor_module_Bank1
       0238  __lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                        func_lit   0238   0002 =      2. bytes (rel,con,rom,proclab)

       Addr  Global Symbol
      -----  --------------------------------
       0238  __func_lit_start
       023A  __func_lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                     psoc_config   023A   0170 =    368. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       023A  LoadConfigTBL_dc_motor_module_Ordered
       033F  _LoadConfigInit
       033F  LoadConfigInit
       034F  _LoadConfig_dc_motor_module
       034F  LoadConfig_dc_motor_module
       03AA  __psoc_config_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                     UserModules   03AA   019B =    411. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       03AA  _SleepTimer_1_ISR
       03CA  SleepTimer_1_EnableInt
       03CA  _SleepTimer_1_EnableInt
       03CE  _SleepTimer_1_DisableInt
       03CE  SleepTimer_1_Start
       03CE  _SleepTimer_1_Start
       03E2  _SleepTimer_1_Stop
       03E2  _SleepTimer_1_SetInterval
       03E2  SleepTimer_1_SetInterval
       03F8  _PWM8_3_DisableInt
       03F8  PWM8_3_Start
       03F8  _PWM8_3_EnableInt
       03F8  _SleepTimer_1_TickWait
       03F8  _SleepTimer_1_SetTimer
       03F8  _SleepTimer_1_SyncWait
       03F8  _SleepTimer_1_iGetTickCntr
       03F8  _PWM8_3_Start
       03F8  _SleepTimer_1_lGetTickCntr
       03F8  _SleepTimer_1_bGetTickCntr
       03F8  _SleepTimer_1_bGetTimer
       03FC  _PWM8_3_WritePeriod
       03FC  _PWM8_3_WritePulseWidth
       03FC  PWM8_3_WritePulseWidth
       03FC  _PWM8_3_Stop
       03FF  _PWM8_3_bReadPulseWidth
       03FF  _bPWM8_3_ReadPulseWidth
       03FF  _PWM8_2_EnableInt
       03FF  _bPWM8_3_ReadCounter
       03FF  PWM8_2_Start
       03FF  _PWM8_3_bReadCounter
       03FF  bPWM8_3_ReadCounter
       03FF  bPWM8_3_ReadPulseWidth
       03FF  _PWM8_2_DisableInt
       03FF  _PWM8_2_Start
       0403  _PWM8_2_WritePeriod
       0403  PWM8_2_WritePulseWidth
       0403  _PWM8_2_WritePulseWidth
       0403  _PWM8_2_Stop
       0406  _PWM8_1_DisableInt
       0406  _PWM8_1_EnableInt
       0406  _PWM8_1_Start
       0406  _PWM8_2_bReadPulseWidth
       0406  bPWM8_2_ReadCounter
       0406  _bPWM8_2_ReadPulseWidth
       0406  _PWM8_2_bReadCounter
       0406  _bPWM8_2_ReadCounter
       0406  PWM8_1_Start
       0406  bPWM8_2_ReadPulseWidth
       040A  _PWM8_1_Stop
       040A  PWM8_1_WritePulseWidth
       040A  _PWM8_1_WritePulseWidth
       040A  _PWM8_1_WritePeriod
       040D  _PWM8_1_bReadPulseWidth
       040D  _bPWM8_1_ReadPulseWidth
       040D  _PWM8_1_bReadCounter
       040D  _EzI2Cs_1_ISR
       040D  bPWM8_1_ReadPulseWidth
       040D  _bPWM8_1_ReadCounter
       040D  bPWM8_1_ReadCounter
       04F0  EzI2Cs_1_Start
       04F0  _EzI2Cs_1_Start
       0521  EzI2Cs_1_EnableInt
       0521  _EzI2Cs_1_GetActivity
       0521  _EzI2Cs_1_ResumeInt
       0521  _EzI2Cs_1_GetAddr
       0521  _EzI2Cs_1_EnableInt
       052C  _EzI2Cs_1_SetRamBuffer
       052C  _EzI2Cs_1_DisableSlave
       052C  EzI2Cs_1_SetRamBuffer
       052C  _EzI2Cs_1_DisableInt
       052C  _EzI2Cs_1_Stop
       0545  __UserModules_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0545   0178 =    376. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       0545  __text_start
       0545  _main
       0680  _MBM_1_InitializeMailbox
       068A  _MBM_1_SetBusyFlag
       068E  _MBM_1_ClearBusyFlag
       0692  _MBM_1_CheckDirtyFlag
       06A2  <created procedures>
       06BD  __text_end
       06BD  __xidata_start
       06C3  __xidata_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             TOP   0000   0165 =    357. bytes (abs,ovr,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       0068  __Start
       0162  _bGetPowerSetting
       0162  bGetPowerSetting

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                    InterruptRAM   0000   0012 =     18. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0000  SleepTimer_1_fTick
       0000  _SleepTimer_1_fTick
       0001  SleepTimer_1_bTimerValue
       0001  _SleepTimer_1_bTimerValue
       0002  SleepTimer_1_bCountDown
       0002  _SleepTimer_1_bCountDown
       0003  SleepTimer_1_TickCount
       0003  _SleepTimer_1_TickCount
       0007  NO_SHADOW
       0007  _NO_SHADOW
       0007  Port_0_Data_SHADE
       0007  _Port_0_Data_SHADE
       0008  Port_0_DriveMode_0_SHADE
       0008  _Port_0_DriveMode_0_SHADE
       0009  Port_0_DriveMode_1_SHADE
       0009  _Port_0_DriveMode_1_SHADE
       000A  EzI2Cs_1_bState
       000A  _EzI2Cs_1_bState
       000A  _EzI2Cs_1_varPage
       000A  EzI2Cs_1_varPage
       000B  _EzI2Cs_1_bRAM_RWoffset
       000B  EzI2Cs_1_bRAM_RWoffset
       000C  _EzI2Cs_1_bRAM_RWcntr
       000C  EzI2Cs_1_bRAM_RWcntr
       000D  EzI2Cs_1_pRAM_Buf_Addr_MSB
       000D  _EzI2Cs_1_pRAM_Buf_Addr_MSB
       000E  _EzI2Cs_1_pRAM_Buf_Addr_LSB
       000E  EzI2Cs_1_pRAM_Buf_Addr_LSB
       000F  _EzI2Cs_1_bRAM_Buf_Size
       000F  EzI2Cs_1_bRAM_Buf_Size
       0010  _EzI2Cs_1_bRAM_Buf_WSize
       0010  EzI2Cs_1_bRAM_Buf_WSize
       0011  _EzI2Cs_1_bBusy_Flag
       0011  EzI2Cs_1_bBusy_Flag

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
               virtual_registers   0024   0002 =      2. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0024  __r1
       0025  __r0

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0000   0012 =     18. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0000  __data_start
       0012  _MBM_1_MyMailbox
       0022  _MBM_1_pMyMailbox

Files Linked      [ module(s) ]

./obj/boot.o	[ boot.asm ]
obj/main.o	[ main.c ]
<library>	[ sleeptimer_1int.asm, sleeptimer_1.asm, pwm8_3.asm, pwm8_2.asm, pwm8_1.asm, psocconfigtbl.asm ]
[ psocconfig.asm, mbm_1.c, ezi2cs_1int.asm, ezi2cs_1.asm, r1.asm, r0.asm ]

Area Definitions

-blit:0x1a0.0x7fff
-bdata:0.0x6ff
-BInterruptRAM:0	allocated at: 0
-Bvirtual_registers	allocated at: 0x24
-Bdc_motor_module_RAM	allocated at: 0
-rwh:SSCParmBlk:0xf7.0xff

