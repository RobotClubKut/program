#ifndef INCLUDED_CYFITTER_H
#define INCLUDED_CYFITTER_H
#include <cydevice.h>
#include <cydevice_trm.h>

/* UP */
#define UP__0__MASK 0x20u
#define UP__0__PC CYREG_PRT4_PC5
#define UP__0__PORT 4u
#define UP__0__SHIFT 5
#define UP__AG CYREG_PRT4_AG
#define UP__AMUX CYREG_PRT4_AMUX
#define UP__BIE CYREG_PRT4_BIE
#define UP__BIT_MASK CYREG_PRT4_BIT_MASK
#define UP__BYP CYREG_PRT4_BYP
#define UP__CTL CYREG_PRT4_CTL
#define UP__DM0 CYREG_PRT4_DM0
#define UP__DM1 CYREG_PRT4_DM1
#define UP__DM2 CYREG_PRT4_DM2
#define UP__DR CYREG_PRT4_DR
#define UP__INP_DIS CYREG_PRT4_INP_DIS
#define UP__LCD_COM_SEG CYREG_PRT4_LCD_COM_SEG
#define UP__LCD_EN CYREG_PRT4_LCD_EN
#define UP__MASK 0x20u
#define UP__PORT 4u
#define UP__PRT CYREG_PRT4_PRT
#define UP__PRTDSI__CAPS_SEL CYREG_PRT4_CAPS_SEL
#define UP__PRTDSI__DBL_SYNC_IN CYREG_PRT4_DBL_SYNC_IN
#define UP__PRTDSI__OE_SEL0 CYREG_PRT4_OE_SEL0
#define UP__PRTDSI__OE_SEL1 CYREG_PRT4_OE_SEL1
#define UP__PRTDSI__OUT_SEL0 CYREG_PRT4_OUT_SEL0
#define UP__PRTDSI__OUT_SEL1 CYREG_PRT4_OUT_SEL1
#define UP__PRTDSI__SYNC_OUT CYREG_PRT4_SYNC_OUT
#define UP__PS CYREG_PRT4_PS
#define UP__SHIFT 5
#define UP__SLW CYREG_PRT4_SLW

/* Ana */
#define Ana__0__MASK 0x40u
#define Ana__0__PC CYREG_PRT6_PC6
#define Ana__0__PORT 6u
#define Ana__0__SHIFT 6
#define Ana__AG CYREG_PRT6_AG
#define Ana__AMUX CYREG_PRT6_AMUX
#define Ana__BIE CYREG_PRT6_BIE
#define Ana__BIT_MASK CYREG_PRT6_BIT_MASK
#define Ana__BYP CYREG_PRT6_BYP
#define Ana__CTL CYREG_PRT6_CTL
#define Ana__DM0 CYREG_PRT6_DM0
#define Ana__DM1 CYREG_PRT6_DM1
#define Ana__DM2 CYREG_PRT6_DM2
#define Ana__DR CYREG_PRT6_DR
#define Ana__INP_DIS CYREG_PRT6_INP_DIS
#define Ana__LCD_COM_SEG CYREG_PRT6_LCD_COM_SEG
#define Ana__LCD_EN CYREG_PRT6_LCD_EN
#define Ana__MASK 0x40u
#define Ana__PORT 6u
#define Ana__PRT CYREG_PRT6_PRT
#define Ana__PRTDSI__CAPS_SEL CYREG_PRT6_CAPS_SEL
#define Ana__PRTDSI__DBL_SYNC_IN CYREG_PRT6_DBL_SYNC_IN
#define Ana__PRTDSI__OE_SEL0 CYREG_PRT6_OE_SEL0
#define Ana__PRTDSI__OE_SEL1 CYREG_PRT6_OE_SEL1
#define Ana__PRTDSI__OUT_SEL0 CYREG_PRT6_OUT_SEL0
#define Ana__PRTDSI__OUT_SEL1 CYREG_PRT6_OUT_SEL1
#define Ana__PRTDSI__SYNC_OUT CYREG_PRT6_SYNC_OUT
#define Ana__PS CYREG_PRT6_PS
#define Ana__SHIFT 6
#define Ana__SLW CYREG_PRT6_SLW

/* BACK */
#define BACK__0__MASK 0x04u
#define BACK__0__PC CYREG_PRT4_PC2
#define BACK__0__PORT 4u
#define BACK__0__SHIFT 2
#define BACK__AG CYREG_PRT4_AG
#define BACK__AMUX CYREG_PRT4_AMUX
#define BACK__BIE CYREG_PRT4_BIE
#define BACK__BIT_MASK CYREG_PRT4_BIT_MASK
#define BACK__BYP CYREG_PRT4_BYP
#define BACK__CTL CYREG_PRT4_CTL
#define BACK__DM0 CYREG_PRT4_DM0
#define BACK__DM1 CYREG_PRT4_DM1
#define BACK__DM2 CYREG_PRT4_DM2
#define BACK__DR CYREG_PRT4_DR
#define BACK__INP_DIS CYREG_PRT4_INP_DIS
#define BACK__LCD_COM_SEG CYREG_PRT4_LCD_COM_SEG
#define BACK__LCD_EN CYREG_PRT4_LCD_EN
#define BACK__MASK 0x04u
#define BACK__PORT 4u
#define BACK__PRT CYREG_PRT4_PRT
#define BACK__PRTDSI__CAPS_SEL CYREG_PRT4_CAPS_SEL
#define BACK__PRTDSI__DBL_SYNC_IN CYREG_PRT4_DBL_SYNC_IN
#define BACK__PRTDSI__OE_SEL0 CYREG_PRT4_OE_SEL0
#define BACK__PRTDSI__OE_SEL1 CYREG_PRT4_OE_SEL1
#define BACK__PRTDSI__OUT_SEL0 CYREG_PRT4_OUT_SEL0
#define BACK__PRTDSI__OUT_SEL1 CYREG_PRT4_OUT_SEL1
#define BACK__PRTDSI__SYNC_OUT CYREG_PRT4_SYNC_OUT
#define BACK__PS CYREG_PRT4_PS
#define BACK__SHIFT 2
#define BACK__SLW CYREG_PRT4_SLW

/* DOWN */
#define DOWN__0__MASK 0x10u
#define DOWN__0__PC CYREG_PRT4_PC4
#define DOWN__0__PORT 4u
#define DOWN__0__SHIFT 4
#define DOWN__AG CYREG_PRT4_AG
#define DOWN__AMUX CYREG_PRT4_AMUX
#define DOWN__BIE CYREG_PRT4_BIE
#define DOWN__BIT_MASK CYREG_PRT4_BIT_MASK
#define DOWN__BYP CYREG_PRT4_BYP
#define DOWN__CTL CYREG_PRT4_CTL
#define DOWN__DM0 CYREG_PRT4_DM0
#define DOWN__DM1 CYREG_PRT4_DM1
#define DOWN__DM2 CYREG_PRT4_DM2
#define DOWN__DR CYREG_PRT4_DR
#define DOWN__INP_DIS CYREG_PRT4_INP_DIS
#define DOWN__LCD_COM_SEG CYREG_PRT4_LCD_COM_SEG
#define DOWN__LCD_EN CYREG_PRT4_LCD_EN
#define DOWN__MASK 0x10u
#define DOWN__PORT 4u
#define DOWN__PRT CYREG_PRT4_PRT
#define DOWN__PRTDSI__CAPS_SEL CYREG_PRT4_CAPS_SEL
#define DOWN__PRTDSI__DBL_SYNC_IN CYREG_PRT4_DBL_SYNC_IN
#define DOWN__PRTDSI__OE_SEL0 CYREG_PRT4_OE_SEL0
#define DOWN__PRTDSI__OE_SEL1 CYREG_PRT4_OE_SEL1
#define DOWN__PRTDSI__OUT_SEL0 CYREG_PRT4_OUT_SEL0
#define DOWN__PRTDSI__OUT_SEL1 CYREG_PRT4_OUT_SEL1
#define DOWN__PRTDSI__SYNC_OUT CYREG_PRT4_SYNC_OUT
#define DOWN__PS CYREG_PRT4_PS
#define DOWN__SHIFT 4
#define DOWN__SLW CYREG_PRT4_SLW

/* Rx_1 */
#define Rx_1__0__MASK 0x10u
#define Rx_1__0__PC CYREG_PRT6_PC4
#define Rx_1__0__PORT 6u
#define Rx_1__0__SHIFT 4
#define Rx_1__AG CYREG_PRT6_AG
#define Rx_1__AMUX CYREG_PRT6_AMUX
#define Rx_1__BIE CYREG_PRT6_BIE
#define Rx_1__BIT_MASK CYREG_PRT6_BIT_MASK
#define Rx_1__BYP CYREG_PRT6_BYP
#define Rx_1__CTL CYREG_PRT6_CTL
#define Rx_1__DM0 CYREG_PRT6_DM0
#define Rx_1__DM1 CYREG_PRT6_DM1
#define Rx_1__DM2 CYREG_PRT6_DM2
#define Rx_1__DR CYREG_PRT6_DR
#define Rx_1__INP_DIS CYREG_PRT6_INP_DIS
#define Rx_1__LCD_COM_SEG CYREG_PRT6_LCD_COM_SEG
#define Rx_1__LCD_EN CYREG_PRT6_LCD_EN
#define Rx_1__MASK 0x10u
#define Rx_1__PORT 6u
#define Rx_1__PRT CYREG_PRT6_PRT
#define Rx_1__PRTDSI__CAPS_SEL CYREG_PRT6_CAPS_SEL
#define Rx_1__PRTDSI__DBL_SYNC_IN CYREG_PRT6_DBL_SYNC_IN
#define Rx_1__PRTDSI__OE_SEL0 CYREG_PRT6_OE_SEL0
#define Rx_1__PRTDSI__OE_SEL1 CYREG_PRT6_OE_SEL1
#define Rx_1__PRTDSI__OUT_SEL0 CYREG_PRT6_OUT_SEL0
#define Rx_1__PRTDSI__OUT_SEL1 CYREG_PRT6_OUT_SEL1
#define Rx_1__PRTDSI__SYNC_OUT CYREG_PRT6_SYNC_OUT
#define Rx_1__PS CYREG_PRT6_PS
#define Rx_1__SHIFT 4
#define Rx_1__SLW CYREG_PRT6_SLW

/* Tx_1 */
#define Tx_1__0__MASK 0x40u
#define Tx_1__0__PC CYREG_PRT4_PC6
#define Tx_1__0__PORT 4u
#define Tx_1__0__SHIFT 6
#define Tx_1__AG CYREG_PRT4_AG
#define Tx_1__AMUX CYREG_PRT4_AMUX
#define Tx_1__BIE CYREG_PRT4_BIE
#define Tx_1__BIT_MASK CYREG_PRT4_BIT_MASK
#define Tx_1__BYP CYREG_PRT4_BYP
#define Tx_1__CTL CYREG_PRT4_CTL
#define Tx_1__DM0 CYREG_PRT4_DM0
#define Tx_1__DM1 CYREG_PRT4_DM1
#define Tx_1__DM2 CYREG_PRT4_DM2
#define Tx_1__DR CYREG_PRT4_DR
#define Tx_1__INP_DIS CYREG_PRT4_INP_DIS
#define Tx_1__LCD_COM_SEG CYREG_PRT4_LCD_COM_SEG
#define Tx_1__LCD_EN CYREG_PRT4_LCD_EN
#define Tx_1__MASK 0x40u
#define Tx_1__PORT 4u
#define Tx_1__PRT CYREG_PRT4_PRT
#define Tx_1__PRTDSI__CAPS_SEL CYREG_PRT4_CAPS_SEL
#define Tx_1__PRTDSI__DBL_SYNC_IN CYREG_PRT4_DBL_SYNC_IN
#define Tx_1__PRTDSI__OE_SEL0 CYREG_PRT4_OE_SEL0
#define Tx_1__PRTDSI__OE_SEL1 CYREG_PRT4_OE_SEL1
#define Tx_1__PRTDSI__OUT_SEL0 CYREG_PRT4_OUT_SEL0
#define Tx_1__PRTDSI__OUT_SEL1 CYREG_PRT4_OUT_SEL1
#define Tx_1__PRTDSI__SYNC_OUT CYREG_PRT4_SYNC_OUT
#define Tx_1__PS CYREG_PRT4_PS
#define Tx_1__SHIFT 6
#define Tx_1__SLW CYREG_PRT4_SLW

/* FRONT */
#define FRONT__0__MASK 0x08u
#define FRONT__0__PC CYREG_PRT4_PC3
#define FRONT__0__PORT 4u
#define FRONT__0__SHIFT 3
#define FRONT__AG CYREG_PRT4_AG
#define FRONT__AMUX CYREG_PRT4_AMUX
#define FRONT__BIE CYREG_PRT4_BIE
#define FRONT__BIT_MASK CYREG_PRT4_BIT_MASK
#define FRONT__BYP CYREG_PRT4_BYP
#define FRONT__CTL CYREG_PRT4_CTL
#define FRONT__DM0 CYREG_PRT4_DM0
#define FRONT__DM1 CYREG_PRT4_DM1
#define FRONT__DM2 CYREG_PRT4_DM2
#define FRONT__DR CYREG_PRT4_DR
#define FRONT__INP_DIS CYREG_PRT4_INP_DIS
#define FRONT__LCD_COM_SEG CYREG_PRT4_LCD_COM_SEG
#define FRONT__LCD_EN CYREG_PRT4_LCD_EN
#define FRONT__MASK 0x08u
#define FRONT__PORT 4u
#define FRONT__PRT CYREG_PRT4_PRT
#define FRONT__PRTDSI__CAPS_SEL CYREG_PRT4_CAPS_SEL
#define FRONT__PRTDSI__DBL_SYNC_IN CYREG_PRT4_DBL_SYNC_IN
#define FRONT__PRTDSI__OE_SEL0 CYREG_PRT4_OE_SEL0
#define FRONT__PRTDSI__OE_SEL1 CYREG_PRT4_OE_SEL1
#define FRONT__PRTDSI__OUT_SEL0 CYREG_PRT4_OUT_SEL0
#define FRONT__PRTDSI__OUT_SEL1 CYREG_PRT4_OUT_SEL1
#define FRONT__PRTDSI__SYNC_OUT CYREG_PRT4_SYNC_OUT
#define FRONT__PS CYREG_PRT4_PS
#define FRONT__SHIFT 3
#define FRONT__SLW CYREG_PRT4_SLW

/* PWM_1_PWMUDB */
#define PWM_1_PWMUDB_genblk1_ctrlreg__16BIT_CONTROL_AUX_CTL_REG CYREG_B0_UDB02_03_ACTL
#define PWM_1_PWMUDB_genblk1_ctrlreg__16BIT_CONTROL_CONTROL_REG CYREG_B0_UDB02_03_CTL
#define PWM_1_PWMUDB_genblk1_ctrlreg__16BIT_CONTROL_COUNT_REG CYREG_B0_UDB02_03_CTL
#define PWM_1_PWMUDB_genblk1_ctrlreg__16BIT_COUNT_CONTROL_REG CYREG_B0_UDB02_03_CTL
#define PWM_1_PWMUDB_genblk1_ctrlreg__16BIT_COUNT_COUNT_REG CYREG_B0_UDB02_03_CTL
#define PWM_1_PWMUDB_genblk1_ctrlreg__16BIT_MASK_MASK_REG CYREG_B0_UDB02_03_MSK
#define PWM_1_PWMUDB_genblk1_ctrlreg__16BIT_MASK_PERIOD_REG CYREG_B0_UDB02_03_MSK
#define PWM_1_PWMUDB_genblk1_ctrlreg__16BIT_PERIOD_MASK_REG CYREG_B0_UDB02_03_MSK
#define PWM_1_PWMUDB_genblk1_ctrlreg__16BIT_PERIOD_PERIOD_REG CYREG_B0_UDB02_03_MSK
#define PWM_1_PWMUDB_genblk1_ctrlreg__7__MASK 0x80u
#define PWM_1_PWMUDB_genblk1_ctrlreg__7__POS 7
#define PWM_1_PWMUDB_genblk1_ctrlreg__CONTROL_AUX_CTL_REG CYREG_B0_UDB02_ACTL
#define PWM_1_PWMUDB_genblk1_ctrlreg__CONTROL_REG CYREG_B0_UDB02_CTL
#define PWM_1_PWMUDB_genblk1_ctrlreg__CONTROL_ST_REG CYREG_B0_UDB02_ST_CTL
#define PWM_1_PWMUDB_genblk1_ctrlreg__COUNT_REG CYREG_B0_UDB02_CTL
#define PWM_1_PWMUDB_genblk1_ctrlreg__COUNT_ST_REG CYREG_B0_UDB02_ST_CTL
#define PWM_1_PWMUDB_genblk1_ctrlreg__MASK 0x80u
#define PWM_1_PWMUDB_genblk1_ctrlreg__MASK_CTL_AUX_CTL_REG CYREG_B0_UDB02_MSK_ACTL
#define PWM_1_PWMUDB_genblk1_ctrlreg__PER_CTL_AUX_CTL_REG CYREG_B0_UDB02_MSK_ACTL
#define PWM_1_PWMUDB_genblk1_ctrlreg__PERIOD_REG CYREG_B0_UDB02_MSK
#define PWM_1_PWMUDB_genblk8_stsreg__0__MASK 0x01u
#define PWM_1_PWMUDB_genblk8_stsreg__0__POS 0
#define PWM_1_PWMUDB_genblk8_stsreg__1__MASK 0x02u
#define PWM_1_PWMUDB_genblk8_stsreg__1__POS 1
#define PWM_1_PWMUDB_genblk8_stsreg__16BIT_STATUS_AUX_CTL_REG CYREG_B0_UDB01_02_ACTL
#define PWM_1_PWMUDB_genblk8_stsreg__16BIT_STATUS_REG CYREG_B0_UDB01_02_ST
#define PWM_1_PWMUDB_genblk8_stsreg__2__MASK 0x04u
#define PWM_1_PWMUDB_genblk8_stsreg__2__POS 2
#define PWM_1_PWMUDB_genblk8_stsreg__3__MASK 0x08u
#define PWM_1_PWMUDB_genblk8_stsreg__3__POS 3
#define PWM_1_PWMUDB_genblk8_stsreg__5__MASK 0x20u
#define PWM_1_PWMUDB_genblk8_stsreg__5__POS 5
#define PWM_1_PWMUDB_genblk8_stsreg__MASK 0x2Fu
#define PWM_1_PWMUDB_genblk8_stsreg__MASK_REG CYREG_B0_UDB01_MSK
#define PWM_1_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG CYREG_B0_UDB01_ACTL
#define PWM_1_PWMUDB_genblk8_stsreg__STATUS_REG CYREG_B0_UDB01_ST
#define PWM_1_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG CYREG_B0_UDB01_02_A0
#define PWM_1_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG CYREG_B0_UDB01_02_A1
#define PWM_1_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG CYREG_B0_UDB01_02_D0
#define PWM_1_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG CYREG_B0_UDB01_02_D1
#define PWM_1_PWMUDB_sP8_pwmdp_u0__16BIT_DP_AUX_CTL_REG CYREG_B0_UDB01_02_ACTL
#define PWM_1_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG CYREG_B0_UDB01_02_F0
#define PWM_1_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG CYREG_B0_UDB01_02_F1
#define PWM_1_PWMUDB_sP8_pwmdp_u0__A0_A1_REG CYREG_B0_UDB01_A0_A1
#define PWM_1_PWMUDB_sP8_pwmdp_u0__A0_REG CYREG_B0_UDB01_A0
#define PWM_1_PWMUDB_sP8_pwmdp_u0__A1_REG CYREG_B0_UDB01_A1
#define PWM_1_PWMUDB_sP8_pwmdp_u0__D0_D1_REG CYREG_B0_UDB01_D0_D1
#define PWM_1_PWMUDB_sP8_pwmdp_u0__D0_REG CYREG_B0_UDB01_D0
#define PWM_1_PWMUDB_sP8_pwmdp_u0__D1_REG CYREG_B0_UDB01_D1
#define PWM_1_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG CYREG_B0_UDB01_ACTL
#define PWM_1_PWMUDB_sP8_pwmdp_u0__F0_F1_REG CYREG_B0_UDB01_F0_F1
#define PWM_1_PWMUDB_sP8_pwmdp_u0__F0_REG CYREG_B0_UDB01_F0
#define PWM_1_PWMUDB_sP8_pwmdp_u0__F1_REG CYREG_B0_UDB01_F1

/* PWM_2_PWMUDB */
#define PWM_2_PWMUDB_genblk1_ctrlreg__16BIT_CONTROL_AUX_CTL_REG CYREG_B0_UDB04_05_ACTL
#define PWM_2_PWMUDB_genblk1_ctrlreg__16BIT_CONTROL_CONTROL_REG CYREG_B0_UDB04_05_CTL
#define PWM_2_PWMUDB_genblk1_ctrlreg__16BIT_CONTROL_COUNT_REG CYREG_B0_UDB04_05_CTL
#define PWM_2_PWMUDB_genblk1_ctrlreg__16BIT_COUNT_CONTROL_REG CYREG_B0_UDB04_05_CTL
#define PWM_2_PWMUDB_genblk1_ctrlreg__16BIT_COUNT_COUNT_REG CYREG_B0_UDB04_05_CTL
#define PWM_2_PWMUDB_genblk1_ctrlreg__16BIT_MASK_MASK_REG CYREG_B0_UDB04_05_MSK
#define PWM_2_PWMUDB_genblk1_ctrlreg__16BIT_MASK_PERIOD_REG CYREG_B0_UDB04_05_MSK
#define PWM_2_PWMUDB_genblk1_ctrlreg__16BIT_PERIOD_MASK_REG CYREG_B0_UDB04_05_MSK
#define PWM_2_PWMUDB_genblk1_ctrlreg__16BIT_PERIOD_PERIOD_REG CYREG_B0_UDB04_05_MSK
#define PWM_2_PWMUDB_genblk1_ctrlreg__7__MASK 0x80u
#define PWM_2_PWMUDB_genblk1_ctrlreg__7__POS 7
#define PWM_2_PWMUDB_genblk1_ctrlreg__CONTROL_AUX_CTL_REG CYREG_B0_UDB04_ACTL
#define PWM_2_PWMUDB_genblk1_ctrlreg__CONTROL_REG CYREG_B0_UDB04_CTL
#define PWM_2_PWMUDB_genblk1_ctrlreg__CONTROL_ST_REG CYREG_B0_UDB04_ST_CTL
#define PWM_2_PWMUDB_genblk1_ctrlreg__COUNT_REG CYREG_B0_UDB04_CTL
#define PWM_2_PWMUDB_genblk1_ctrlreg__COUNT_ST_REG CYREG_B0_UDB04_ST_CTL
#define PWM_2_PWMUDB_genblk1_ctrlreg__MASK 0x80u
#define PWM_2_PWMUDB_genblk1_ctrlreg__MASK_CTL_AUX_CTL_REG CYREG_B0_UDB04_MSK_ACTL
#define PWM_2_PWMUDB_genblk1_ctrlreg__PER_CTL_AUX_CTL_REG CYREG_B0_UDB04_MSK_ACTL
#define PWM_2_PWMUDB_genblk1_ctrlreg__PERIOD_REG CYREG_B0_UDB04_MSK
#define PWM_2_PWMUDB_genblk8_stsreg__0__MASK 0x01u
#define PWM_2_PWMUDB_genblk8_stsreg__0__POS 0
#define PWM_2_PWMUDB_genblk8_stsreg__1__MASK 0x02u
#define PWM_2_PWMUDB_genblk8_stsreg__1__POS 1
#define PWM_2_PWMUDB_genblk8_stsreg__16BIT_STATUS_AUX_CTL_REG CYREG_B0_UDB07_08_ACTL
#define PWM_2_PWMUDB_genblk8_stsreg__16BIT_STATUS_REG CYREG_B0_UDB07_08_ST
#define PWM_2_PWMUDB_genblk8_stsreg__2__MASK 0x04u
#define PWM_2_PWMUDB_genblk8_stsreg__2__POS 2
#define PWM_2_PWMUDB_genblk8_stsreg__3__MASK 0x08u
#define PWM_2_PWMUDB_genblk8_stsreg__3__POS 3
#define PWM_2_PWMUDB_genblk8_stsreg__5__MASK 0x20u
#define PWM_2_PWMUDB_genblk8_stsreg__5__POS 5
#define PWM_2_PWMUDB_genblk8_stsreg__MASK 0x2Fu
#define PWM_2_PWMUDB_genblk8_stsreg__MASK_REG CYREG_B0_UDB07_MSK
#define PWM_2_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG CYREG_B0_UDB07_ACTL
#define PWM_2_PWMUDB_genblk8_stsreg__STATUS_REG CYREG_B0_UDB07_ST
#define PWM_2_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG CYREG_B0_UDB07_08_A0
#define PWM_2_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG CYREG_B0_UDB07_08_A1
#define PWM_2_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG CYREG_B0_UDB07_08_D0
#define PWM_2_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG CYREG_B0_UDB07_08_D1
#define PWM_2_PWMUDB_sP8_pwmdp_u0__16BIT_DP_AUX_CTL_REG CYREG_B0_UDB07_08_ACTL
#define PWM_2_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG CYREG_B0_UDB07_08_F0
#define PWM_2_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG CYREG_B0_UDB07_08_F1
#define PWM_2_PWMUDB_sP8_pwmdp_u0__A0_A1_REG CYREG_B0_UDB07_A0_A1
#define PWM_2_PWMUDB_sP8_pwmdp_u0__A0_REG CYREG_B0_UDB07_A0
#define PWM_2_PWMUDB_sP8_pwmdp_u0__A1_REG CYREG_B0_UDB07_A1
#define PWM_2_PWMUDB_sP8_pwmdp_u0__D0_D1_REG CYREG_B0_UDB07_D0_D1
#define PWM_2_PWMUDB_sP8_pwmdp_u0__D0_REG CYREG_B0_UDB07_D0
#define PWM_2_PWMUDB_sP8_pwmdp_u0__D1_REG CYREG_B0_UDB07_D1
#define PWM_2_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG CYREG_B0_UDB07_ACTL
#define PWM_2_PWMUDB_sP8_pwmdp_u0__F0_F1_REG CYREG_B0_UDB07_F0_F1
#define PWM_2_PWMUDB_sP8_pwmdp_u0__F0_REG CYREG_B0_UDB07_F0
#define PWM_2_PWMUDB_sP8_pwmdp_u0__F1_REG CYREG_B0_UDB07_F1

/* isr_1 */
#define isr_1__ES2_PATCH 0u
#define isr_1__INTC_CLR_EN_REG CYREG_INTC_CLR_EN0
#define isr_1__INTC_CLR_PD_REG CYREG_INTC_CLR_PD0
#define isr_1__INTC_MASK 0x04u
#define isr_1__INTC_NUMBER 2u
#define isr_1__INTC_PRIOR_NUM 7u
#define isr_1__INTC_PRIOR_REG CYREG_INTC_PRIOR2
#define isr_1__INTC_SET_EN_REG CYREG_INTC_SET_EN0
#define isr_1__INTC_SET_PD_REG CYREG_INTC_SET_PD0
#define isr_1__INTC_VECT (CYREG_INTC_VECT_MBASE+0x04u)

/* UART_1_BUART */
#define UART_1_BUART_sRX_RxBitCounter__16BIT_CONTROL_AUX_CTL_REG CYREG_B0_UDB03_04_ACTL
#define UART_1_BUART_sRX_RxBitCounter__16BIT_CONTROL_CONTROL_REG CYREG_B0_UDB03_04_CTL
#define UART_1_BUART_sRX_RxBitCounter__16BIT_CONTROL_COUNT_REG CYREG_B0_UDB03_04_CTL
#define UART_1_BUART_sRX_RxBitCounter__16BIT_COUNT_CONTROL_REG CYREG_B0_UDB03_04_CTL
#define UART_1_BUART_sRX_RxBitCounter__16BIT_COUNT_COUNT_REG CYREG_B0_UDB03_04_CTL
#define UART_1_BUART_sRX_RxBitCounter__16BIT_MASK_MASK_REG CYREG_B0_UDB03_04_MSK
#define UART_1_BUART_sRX_RxBitCounter__16BIT_MASK_PERIOD_REG CYREG_B0_UDB03_04_MSK
#define UART_1_BUART_sRX_RxBitCounter__16BIT_PERIOD_MASK_REG CYREG_B0_UDB03_04_MSK
#define UART_1_BUART_sRX_RxBitCounter__16BIT_PERIOD_PERIOD_REG CYREG_B0_UDB03_04_MSK
#define UART_1_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG CYREG_B0_UDB03_ACTL
#define UART_1_BUART_sRX_RxBitCounter__CONTROL_REG CYREG_B0_UDB03_CTL
#define UART_1_BUART_sRX_RxBitCounter__CONTROL_ST_REG CYREG_B0_UDB03_ST_CTL
#define UART_1_BUART_sRX_RxBitCounter__COUNT_REG CYREG_B0_UDB03_CTL
#define UART_1_BUART_sRX_RxBitCounter__COUNT_ST_REG CYREG_B0_UDB03_ST_CTL
#define UART_1_BUART_sRX_RxBitCounter__MASK_CTL_AUX_CTL_REG CYREG_B0_UDB03_MSK_ACTL
#define UART_1_BUART_sRX_RxBitCounter__PER_CTL_AUX_CTL_REG CYREG_B0_UDB03_MSK_ACTL
#define UART_1_BUART_sRX_RxBitCounter__PERIOD_REG CYREG_B0_UDB03_MSK
#define UART_1_BUART_sRX_RxBitCounter_ST__16BIT_STATUS_AUX_CTL_REG CYREG_B0_UDB03_04_ACTL
#define UART_1_BUART_sRX_RxBitCounter_ST__16BIT_STATUS_REG CYREG_B0_UDB03_04_ST
#define UART_1_BUART_sRX_RxBitCounter_ST__MASK_REG CYREG_B0_UDB03_MSK
#define UART_1_BUART_sRX_RxBitCounter_ST__MASK_ST_AUX_CTL_REG CYREG_B0_UDB03_MSK_ACTL
#define UART_1_BUART_sRX_RxBitCounter_ST__PER_ST_AUX_CTL_REG CYREG_B0_UDB03_MSK_ACTL
#define UART_1_BUART_sRX_RxBitCounter_ST__STATUS_AUX_CTL_REG CYREG_B0_UDB03_ACTL
#define UART_1_BUART_sRX_RxBitCounter_ST__STATUS_CNT_REG CYREG_B0_UDB03_ST_CTL
#define UART_1_BUART_sRX_RxBitCounter_ST__STATUS_CONTROL_REG CYREG_B0_UDB03_ST_CTL
#define UART_1_BUART_sRX_RxBitCounter_ST__STATUS_REG CYREG_B0_UDB03_ST
#define UART_1_BUART_sRX_RxShifter_u0__16BIT_A0_REG CYREG_B0_UDB03_04_A0
#define UART_1_BUART_sRX_RxShifter_u0__16BIT_A1_REG CYREG_B0_UDB03_04_A1
#define UART_1_BUART_sRX_RxShifter_u0__16BIT_D0_REG CYREG_B0_UDB03_04_D0
#define UART_1_BUART_sRX_RxShifter_u0__16BIT_D1_REG CYREG_B0_UDB03_04_D1
#define UART_1_BUART_sRX_RxShifter_u0__16BIT_DP_AUX_CTL_REG CYREG_B0_UDB03_04_ACTL
#define UART_1_BUART_sRX_RxShifter_u0__16BIT_F0_REG CYREG_B0_UDB03_04_F0
#define UART_1_BUART_sRX_RxShifter_u0__16BIT_F1_REG CYREG_B0_UDB03_04_F1
#define UART_1_BUART_sRX_RxShifter_u0__A0_A1_REG CYREG_B0_UDB03_A0_A1
#define UART_1_BUART_sRX_RxShifter_u0__A0_REG CYREG_B0_UDB03_A0
#define UART_1_BUART_sRX_RxShifter_u0__A1_REG CYREG_B0_UDB03_A1
#define UART_1_BUART_sRX_RxShifter_u0__D0_D1_REG CYREG_B0_UDB03_D0_D1
#define UART_1_BUART_sRX_RxShifter_u0__D0_REG CYREG_B0_UDB03_D0
#define UART_1_BUART_sRX_RxShifter_u0__D1_REG CYREG_B0_UDB03_D1
#define UART_1_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG CYREG_B0_UDB03_ACTL
#define UART_1_BUART_sRX_RxShifter_u0__F0_F1_REG CYREG_B0_UDB03_F0_F1
#define UART_1_BUART_sRX_RxShifter_u0__F0_REG CYREG_B0_UDB03_F0
#define UART_1_BUART_sRX_RxShifter_u0__F1_REG CYREG_B0_UDB03_F1
#define UART_1_BUART_sRX_RxShifter_u0__MSK_DP_AUX_CTL_REG CYREG_B0_UDB03_MSK_ACTL
#define UART_1_BUART_sRX_RxShifter_u0__PER_DP_AUX_CTL_REG CYREG_B0_UDB03_MSK_ACTL
#define UART_1_BUART_sRX_RxSts__16BIT_STATUS_AUX_CTL_REG CYREG_B0_UDB05_06_ACTL
#define UART_1_BUART_sRX_RxSts__16BIT_STATUS_REG CYREG_B0_UDB05_06_ST
#define UART_1_BUART_sRX_RxSts__3__MASK 0x08u
#define UART_1_BUART_sRX_RxSts__3__POS 3
#define UART_1_BUART_sRX_RxSts__4__MASK 0x10u
#define UART_1_BUART_sRX_RxSts__4__POS 4
#define UART_1_BUART_sRX_RxSts__5__MASK 0x20u
#define UART_1_BUART_sRX_RxSts__5__POS 5
#define UART_1_BUART_sRX_RxSts__MASK 0x38u
#define UART_1_BUART_sRX_RxSts__MASK_REG CYREG_B0_UDB05_MSK
#define UART_1_BUART_sRX_RxSts__STATUS_AUX_CTL_REG CYREG_B0_UDB05_ACTL
#define UART_1_BUART_sRX_RxSts__STATUS_REG CYREG_B0_UDB05_ST
#define UART_1_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_A0_REG CYREG_B0_UDB06_07_A0
#define UART_1_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_A1_REG CYREG_B0_UDB06_07_A1
#define UART_1_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_D0_REG CYREG_B0_UDB06_07_D0
#define UART_1_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_D1_REG CYREG_B0_UDB06_07_D1
#define UART_1_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_DP_AUX_CTL_REG CYREG_B0_UDB06_07_ACTL
#define UART_1_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_F0_REG CYREG_B0_UDB06_07_F0
#define UART_1_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_F1_REG CYREG_B0_UDB06_07_F1
#define UART_1_BUART_sTX_sCLOCK_TxBitClkGen__A0_A1_REG CYREG_B0_UDB06_A0_A1
#define UART_1_BUART_sTX_sCLOCK_TxBitClkGen__A0_REG CYREG_B0_UDB06_A0
#define UART_1_BUART_sTX_sCLOCK_TxBitClkGen__A1_REG CYREG_B0_UDB06_A1
#define UART_1_BUART_sTX_sCLOCK_TxBitClkGen__D0_D1_REG CYREG_B0_UDB06_D0_D1
#define UART_1_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG CYREG_B0_UDB06_D0
#define UART_1_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG CYREG_B0_UDB06_D1
#define UART_1_BUART_sTX_sCLOCK_TxBitClkGen__DP_AUX_CTL_REG CYREG_B0_UDB06_ACTL
#define UART_1_BUART_sTX_sCLOCK_TxBitClkGen__F0_F1_REG CYREG_B0_UDB06_F0_F1
#define UART_1_BUART_sTX_sCLOCK_TxBitClkGen__F0_REG CYREG_B0_UDB06_F0
#define UART_1_BUART_sTX_sCLOCK_TxBitClkGen__F1_REG CYREG_B0_UDB06_F1
#define UART_1_BUART_sTX_TxShifter_u0__16BIT_A0_REG CYREG_B0_UDB05_06_A0
#define UART_1_BUART_sTX_TxShifter_u0__16BIT_A1_REG CYREG_B0_UDB05_06_A1
#define UART_1_BUART_sTX_TxShifter_u0__16BIT_D0_REG CYREG_B0_UDB05_06_D0
#define UART_1_BUART_sTX_TxShifter_u0__16BIT_D1_REG CYREG_B0_UDB05_06_D1
#define UART_1_BUART_sTX_TxShifter_u0__16BIT_DP_AUX_CTL_REG CYREG_B0_UDB05_06_ACTL
#define UART_1_BUART_sTX_TxShifter_u0__16BIT_F0_REG CYREG_B0_UDB05_06_F0
#define UART_1_BUART_sTX_TxShifter_u0__16BIT_F1_REG CYREG_B0_UDB05_06_F1
#define UART_1_BUART_sTX_TxShifter_u0__A0_A1_REG CYREG_B0_UDB05_A0_A1
#define UART_1_BUART_sTX_TxShifter_u0__A0_REG CYREG_B0_UDB05_A0
#define UART_1_BUART_sTX_TxShifter_u0__A1_REG CYREG_B0_UDB05_A1
#define UART_1_BUART_sTX_TxShifter_u0__D0_D1_REG CYREG_B0_UDB05_D0_D1
#define UART_1_BUART_sTX_TxShifter_u0__D0_REG CYREG_B0_UDB05_D0
#define UART_1_BUART_sTX_TxShifter_u0__D1_REG CYREG_B0_UDB05_D1
#define UART_1_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG CYREG_B0_UDB05_ACTL
#define UART_1_BUART_sTX_TxShifter_u0__F0_F1_REG CYREG_B0_UDB05_F0_F1
#define UART_1_BUART_sTX_TxShifter_u0__F0_REG CYREG_B0_UDB05_F0
#define UART_1_BUART_sTX_TxShifter_u0__F1_REG CYREG_B0_UDB05_F1
#define UART_1_BUART_sTX_TxSts__0__MASK 0x01u
#define UART_1_BUART_sTX_TxSts__0__POS 0
#define UART_1_BUART_sTX_TxSts__1__MASK 0x02u
#define UART_1_BUART_sTX_TxSts__1__POS 1
#define UART_1_BUART_sTX_TxSts__16BIT_STATUS_AUX_CTL_REG CYREG_B0_UDB06_07_ACTL
#define UART_1_BUART_sTX_TxSts__16BIT_STATUS_REG CYREG_B0_UDB06_07_ST
#define UART_1_BUART_sTX_TxSts__2__MASK 0x04u
#define UART_1_BUART_sTX_TxSts__2__POS 2
#define UART_1_BUART_sTX_TxSts__3__MASK 0x08u
#define UART_1_BUART_sTX_TxSts__3__POS 3
#define UART_1_BUART_sTX_TxSts__MASK 0x0Fu
#define UART_1_BUART_sTX_TxSts__MASK_REG CYREG_B0_UDB06_MSK
#define UART_1_BUART_sTX_TxSts__STATUS_AUX_CTL_REG CYREG_B0_UDB06_ACTL
#define UART_1_BUART_sTX_TxSts__STATUS_REG CYREG_B0_UDB06_ST

/* UART_1_IntClock */
#define UART_1_IntClock__CFG0 CYREG_CLKDIST_DCFG3_CFG0
#define UART_1_IntClock__CFG1 CYREG_CLKDIST_DCFG3_CFG1
#define UART_1_IntClock__CFG2 CYREG_CLKDIST_DCFG3_CFG2
#define UART_1_IntClock__CFG2_SRC_SEL_MASK 0x07u
#define UART_1_IntClock__INDEX 0x03u
#define UART_1_IntClock__PM_ACT_CFG CYREG_PM_ACT_CFG2
#define UART_1_IntClock__PM_ACT_MSK 0x08u
#define UART_1_IntClock__PM_STBY_CFG CYREG_PM_STBY_CFG2
#define UART_1_IntClock__PM_STBY_MSK 0x08u

/* UART_1_RXInternalInterrupt */
#define UART_1_RXInternalInterrupt__ES2_PATCH 0u
#define UART_1_RXInternalInterrupt__INTC_CLR_EN_REG CYREG_INTC_CLR_EN0
#define UART_1_RXInternalInterrupt__INTC_CLR_PD_REG CYREG_INTC_CLR_PD0
#define UART_1_RXInternalInterrupt__INTC_MASK 0x01u
#define UART_1_RXInternalInterrupt__INTC_NUMBER 0u
#define UART_1_RXInternalInterrupt__INTC_PRIOR_NUM 7u
#define UART_1_RXInternalInterrupt__INTC_PRIOR_REG CYREG_INTC_PRIOR0
#define UART_1_RXInternalInterrupt__INTC_SET_EN_REG CYREG_INTC_SET_EN0
#define UART_1_RXInternalInterrupt__INTC_SET_PD_REG CYREG_INTC_SET_PD0
#define UART_1_RXInternalInterrupt__INTC_VECT (CYREG_INTC_VECT_MBASE+0x00u)

/* UART_1_TXInternalInterrupt */
#define UART_1_TXInternalInterrupt__ES2_PATCH 0u
#define UART_1_TXInternalInterrupt__INTC_CLR_EN_REG CYREG_INTC_CLR_EN0
#define UART_1_TXInternalInterrupt__INTC_CLR_PD_REG CYREG_INTC_CLR_PD0
#define UART_1_TXInternalInterrupt__INTC_MASK 0x02u
#define UART_1_TXInternalInterrupt__INTC_NUMBER 1u
#define UART_1_TXInternalInterrupt__INTC_PRIOR_NUM 7u
#define UART_1_TXInternalInterrupt__INTC_PRIOR_REG CYREG_INTC_PRIOR1
#define UART_1_TXInternalInterrupt__INTC_SET_EN_REG CYREG_INTC_SET_EN0
#define UART_1_TXInternalInterrupt__INTC_SET_PD_REG CYREG_INTC_SET_PD0
#define UART_1_TXInternalInterrupt__INTC_VECT (CYREG_INTC_VECT_MBASE+0x02u)

/* Clock_1 */
#define Clock_1__CFG0 CYREG_CLKDIST_DCFG1_CFG0
#define Clock_1__CFG1 CYREG_CLKDIST_DCFG1_CFG1
#define Clock_1__CFG2 CYREG_CLKDIST_DCFG1_CFG2
#define Clock_1__CFG2_SRC_SEL_MASK 0x07u
#define Clock_1__INDEX 0x01u
#define Clock_1__PM_ACT_CFG CYREG_PM_ACT_CFG2
#define Clock_1__PM_ACT_MSK 0x02u
#define Clock_1__PM_STBY_CFG CYREG_PM_STBY_CFG2
#define Clock_1__PM_STBY_MSK 0x02u

/* Clock_2 */
#define Clock_2__CFG0 CYREG_CLKDIST_DCFG2_CFG0
#define Clock_2__CFG1 CYREG_CLKDIST_DCFG2_CFG1
#define Clock_2__CFG2 CYREG_CLKDIST_DCFG2_CFG2
#define Clock_2__CFG2_SRC_SEL_MASK 0x07u
#define Clock_2__INDEX 0x02u
#define Clock_2__PM_ACT_CFG CYREG_PM_ACT_CFG2
#define Clock_2__PM_ACT_MSK 0x04u
#define Clock_2__PM_STBY_CFG CYREG_PM_STBY_CFG2
#define Clock_2__PM_STBY_MSK 0x04u

/* Clock_4 */
#define Clock_4__CFG0 CYREG_CLKDIST_DCFG4_CFG0
#define Clock_4__CFG1 CYREG_CLKDIST_DCFG4_CFG1
#define Clock_4__CFG2 CYREG_CLKDIST_DCFG4_CFG2
#define Clock_4__CFG2_SRC_SEL_MASK 0x07u
#define Clock_4__INDEX 0x04u
#define Clock_4__PM_ACT_CFG CYREG_PM_ACT_CFG2
#define Clock_4__PM_ACT_MSK 0x10u
#define Clock_4__PM_STBY_CFG CYREG_PM_STBY_CFG2
#define Clock_4__PM_STBY_MSK 0x10u

/* ADC_DelSig_1_DEC */
#define ADC_DelSig_1_DEC__COHER CYREG_DEC_COHER
#define ADC_DelSig_1_DEC__CR CYREG_DEC_CR
#define ADC_DelSig_1_DEC__DR1 CYREG_DEC_DR1
#define ADC_DelSig_1_DEC__DR2 CYREG_DEC_DR2
#define ADC_DelSig_1_DEC__DR2H CYREG_DEC_DR2H
#define ADC_DelSig_1_DEC__GCOR CYREG_DEC_GCOR
#define ADC_DelSig_1_DEC__GCORH CYREG_DEC_GCORH
#define ADC_DelSig_1_DEC__GVAL CYREG_DEC_GVAL
#define ADC_DelSig_1_DEC__OCOR CYREG_DEC_OCOR
#define ADC_DelSig_1_DEC__OCORH CYREG_DEC_OCORH
#define ADC_DelSig_1_DEC__OCORM CYREG_DEC_OCORM
#define ADC_DelSig_1_DEC__OUTSAMP CYREG_DEC_OUTSAMP
#define ADC_DelSig_1_DEC__OUTSAMPH CYREG_DEC_OUTSAMPH
#define ADC_DelSig_1_DEC__OUTSAMPM CYREG_DEC_OUTSAMPM
#define ADC_DelSig_1_DEC__OUTSAMPS CYREG_DEC_OUTSAMPS
#define ADC_DelSig_1_DEC__PM_ACT_CFG CYREG_PM_ACT_CFG10
#define ADC_DelSig_1_DEC__PM_ACT_MSK 0x01u
#define ADC_DelSig_1_DEC__PM_STBY_CFG CYREG_PM_STBY_CFG10
#define ADC_DelSig_1_DEC__PM_STBY_MSK 0x01u
#define ADC_DelSig_1_DEC__SHIFT1 CYREG_DEC_SHIFT1
#define ADC_DelSig_1_DEC__SHIFT2 CYREG_DEC_SHIFT2
#define ADC_DelSig_1_DEC__SR CYREG_DEC_SR
#define ADC_DelSig_1_DEC__TRIM__M1 CYREG_FLSHID_CUST_TABLES_DEC_M1
#define ADC_DelSig_1_DEC__TRIM__M2 CYREG_FLSHID_CUST_TABLES_DEC_M2
#define ADC_DelSig_1_DEC__TRIM__M3 CYREG_FLSHID_CUST_TABLES_DEC_M3
#define ADC_DelSig_1_DEC__TRIM__M4 CYREG_FLSHID_CUST_TABLES_DEC_M4
#define ADC_DelSig_1_DEC__TRIM__M5 CYREG_FLSHID_CUST_TABLES_DEC_M5
#define ADC_DelSig_1_DEC__TRIM__M6 CYREG_FLSHID_CUST_TABLES_DEC_M6
#define ADC_DelSig_1_DEC__TRIM__M7 CYREG_FLSHID_CUST_TABLES_DEC_M7
#define ADC_DelSig_1_DEC__TRIM__M8 CYREG_FLSHID_CUST_TABLES_DEC_M8

/* ADC_DelSig_1_DSM */
#define ADC_DelSig_1_DSM__BUF0 CYREG_DSM0_BUF0
#define ADC_DelSig_1_DSM__BUF1 CYREG_DSM0_BUF1
#define ADC_DelSig_1_DSM__BUF2 CYREG_DSM0_BUF2
#define ADC_DelSig_1_DSM__BUF3 CYREG_DSM0_BUF3
#define ADC_DelSig_1_DSM__CLK CYREG_DSM0_CLK
#define ADC_DelSig_1_DSM__CR0 CYREG_DSM0_CR0
#define ADC_DelSig_1_DSM__CR1 CYREG_DSM0_CR1
#define ADC_DelSig_1_DSM__CR10 CYREG_DSM0_CR10
#define ADC_DelSig_1_DSM__CR11 CYREG_DSM0_CR11
#define ADC_DelSig_1_DSM__CR12 CYREG_DSM0_CR12
#define ADC_DelSig_1_DSM__CR13 CYREG_DSM0_CR13
#define ADC_DelSig_1_DSM__CR14 CYREG_DSM0_CR14
#define ADC_DelSig_1_DSM__CR15 CYREG_DSM0_CR15
#define ADC_DelSig_1_DSM__CR16 CYREG_DSM0_CR16
#define ADC_DelSig_1_DSM__CR17 CYREG_DSM0_CR17
#define ADC_DelSig_1_DSM__CR2 CYREG_DSM0_CR2
#define ADC_DelSig_1_DSM__CR3 CYREG_DSM0_CR3
#define ADC_DelSig_1_DSM__CR4 CYREG_DSM0_CR4
#define ADC_DelSig_1_DSM__CR5 CYREG_DSM0_CR5
#define ADC_DelSig_1_DSM__CR6 CYREG_DSM0_CR6
#define ADC_DelSig_1_DSM__CR7 CYREG_DSM0_CR7
#define ADC_DelSig_1_DSM__CR8 CYREG_DSM0_CR8
#define ADC_DelSig_1_DSM__CR9 CYREG_DSM0_CR9
#define ADC_DelSig_1_DSM__DEM0 CYREG_DSM0_DEM0
#define ADC_DelSig_1_DSM__DEM1 CYREG_DSM0_DEM1
#define ADC_DelSig_1_DSM__MISC CYREG_DSM0_MISC
#define ADC_DelSig_1_DSM__OUT0 CYREG_DSM0_OUT0
#define ADC_DelSig_1_DSM__OUT1 CYREG_DSM0_OUT1
#define ADC_DelSig_1_DSM__REF0 CYREG_DSM0_REF0
#define ADC_DelSig_1_DSM__REF1 CYREG_DSM0_REF1
#define ADC_DelSig_1_DSM__REF2 CYREG_DSM0_REF2
#define ADC_DelSig_1_DSM__REF3 CYREG_DSM0_REF3
#define ADC_DelSig_1_DSM__RSVD1 CYREG_DSM0_RSVD1
#define ADC_DelSig_1_DSM__SW0 CYREG_DSM0_SW0
#define ADC_DelSig_1_DSM__SW2 CYREG_DSM0_SW2
#define ADC_DelSig_1_DSM__SW3 CYREG_DSM0_SW3
#define ADC_DelSig_1_DSM__SW4 CYREG_DSM0_SW4
#define ADC_DelSig_1_DSM__SW6 CYREG_DSM0_SW6
#define ADC_DelSig_1_DSM__TR0 CYREG_NPUMP_DSM_TR0
#define ADC_DelSig_1_DSM__TST0 CYREG_DSM0_TST0
#define ADC_DelSig_1_DSM__TST1 CYREG_DSM0_TST1

/* ADC_DelSig_1_Ext_CP_Clk */
#define ADC_DelSig_1_Ext_CP_Clk__CFG0 CYREG_CLKDIST_DCFG0_CFG0
#define ADC_DelSig_1_Ext_CP_Clk__CFG1 CYREG_CLKDIST_DCFG0_CFG1
#define ADC_DelSig_1_Ext_CP_Clk__CFG2 CYREG_CLKDIST_DCFG0_CFG2
#define ADC_DelSig_1_Ext_CP_Clk__CFG2_SRC_SEL_MASK 0x07u
#define ADC_DelSig_1_Ext_CP_Clk__INDEX 0x00u
#define ADC_DelSig_1_Ext_CP_Clk__PM_ACT_CFG CYREG_PM_ACT_CFG2
#define ADC_DelSig_1_Ext_CP_Clk__PM_ACT_MSK 0x01u
#define ADC_DelSig_1_Ext_CP_Clk__PM_STBY_CFG CYREG_PM_STBY_CFG2
#define ADC_DelSig_1_Ext_CP_Clk__PM_STBY_MSK 0x01u

/* ADC_DelSig_1_IRQ */
#define ADC_DelSig_1_IRQ__ES2_PATCH 0u
#define ADC_DelSig_1_IRQ__INTC_CLR_EN_REG CYREG_INTC_CLR_EN3
#define ADC_DelSig_1_IRQ__INTC_CLR_PD_REG CYREG_INTC_CLR_PD3
#define ADC_DelSig_1_IRQ__INTC_MASK 0x20u
#define ADC_DelSig_1_IRQ__INTC_NUMBER 29u
#define ADC_DelSig_1_IRQ__INTC_PRIOR_NUM 7u
#define ADC_DelSig_1_IRQ__INTC_PRIOR_REG CYREG_INTC_PRIOR29
#define ADC_DelSig_1_IRQ__INTC_SET_EN_REG CYREG_INTC_SET_EN3
#define ADC_DelSig_1_IRQ__INTC_SET_PD_REG CYREG_INTC_SET_PD3
#define ADC_DelSig_1_IRQ__INTC_VECT (CYREG_INTC_VECT_MBASE+0x3Au)

/* ADC_DelSig_1_theACLK */
#define ADC_DelSig_1_theACLK__CFG0 CYREG_CLKDIST_ACFG0_CFG0
#define ADC_DelSig_1_theACLK__CFG1 CYREG_CLKDIST_ACFG0_CFG1
#define ADC_DelSig_1_theACLK__CFG2 CYREG_CLKDIST_ACFG0_CFG2
#define ADC_DelSig_1_theACLK__CFG2_SRC_SEL_MASK 0x07u
#define ADC_DelSig_1_theACLK__CFG3 CYREG_CLKDIST_ACFG0_CFG3
#define ADC_DelSig_1_theACLK__CFG3_PHASE_DLY_MASK 0x0Fu
#define ADC_DelSig_1_theACLK__INDEX 0x00u
#define ADC_DelSig_1_theACLK__PM_ACT_CFG CYREG_PM_ACT_CFG1
#define ADC_DelSig_1_theACLK__PM_ACT_MSK 0x01u
#define ADC_DelSig_1_theACLK__PM_STBY_CFG CYREG_PM_STBY_CFG1
#define ADC_DelSig_1_theACLK__PM_STBY_MSK 0x01u

/* Miscellaneous */
#define BCLK__BUS_CLK__HZ 24000000U
#define BCLK__BUS_CLK__KHZ 24000U
#define BCLK__BUS_CLK__MHZ 24U
#define CYDEV_CHIP_DIE_LEOPARD 1u
#define CYDEV_CHIP_DIE_PANTHER 4u
#define CYDEV_CHIP_DIE_PSOC4A 2u
#define CYDEV_CHIP_DIE_PSOC5LP 5u
#define CYDEV_CHIP_DIE_UNKNOWN 0u
#define CYDEV_CHIP_FAMILY_PSOC3 1u
#define CYDEV_CHIP_FAMILY_PSOC4 2u
#define CYDEV_CHIP_FAMILY_PSOC5 3u
#define CYDEV_CHIP_FAMILY_UNKNOWN 0u
#define CYDEV_CHIP_FAMILY_USED CYDEV_CHIP_FAMILY_PSOC3
#define CYDEV_CHIP_JTAG_ID 0x1E09E069u
#define CYDEV_CHIP_MEMBER_3A 1u
#define CYDEV_CHIP_MEMBER_4A 2u
#define CYDEV_CHIP_MEMBER_4D 3u
#define CYDEV_CHIP_MEMBER_5A 4u
#define CYDEV_CHIP_MEMBER_5B 5u
#define CYDEV_CHIP_MEMBER_UNKNOWN 0u
#define CYDEV_CHIP_MEMBER_USED CYDEV_CHIP_MEMBER_3A
#define CYDEV_CHIP_DIE_EXPECT CYDEV_CHIP_MEMBER_USED
#define CYDEV_CHIP_DIE_ACTUAL CYDEV_CHIP_DIE_EXPECT
#define CYDEV_CHIP_REV_LEOPARD_ES1 0u
#define CYDEV_CHIP_REV_LEOPARD_ES2 1u
#define CYDEV_CHIP_REV_LEOPARD_ES3 3u
#define CYDEV_CHIP_REV_LEOPARD_PRODUCTION 3u
#define CYDEV_CHIP_REV_PANTHER_ES0 0u
#define CYDEV_CHIP_REV_PANTHER_ES1 1u
#define CYDEV_CHIP_REV_PANTHER_PRODUCTION 1u
#define CYDEV_CHIP_REV_PSOC4A_ES0 17u
#define CYDEV_CHIP_REV_PSOC4A_PRODUCTION 17u
#define CYDEV_CHIP_REV_PSOC5LP_ES0 0u
#define CYDEV_CHIP_REV_PSOC5LP_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_3A_ES1 0u
#define CYDEV_CHIP_REVISION_3A_ES2 1u
#define CYDEV_CHIP_REVISION_3A_ES3 3u
#define CYDEV_CHIP_REVISION_3A_PRODUCTION 3u
#define CYDEV_CHIP_REVISION_4A_ES0 17u
#define CYDEV_CHIP_REVISION_4A_PRODUCTION 17u
#define CYDEV_CHIP_REVISION_4D_ES0 0u
#define CYDEV_CHIP_REVISION_4D_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_5A_ES0 0u
#define CYDEV_CHIP_REVISION_5A_ES1 1u
#define CYDEV_CHIP_REVISION_5A_PRODUCTION 1u
#define CYDEV_CHIP_REVISION_5B_ES0 0u
#define CYDEV_CHIP_REVISION_5B_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_USED CYDEV_CHIP_REVISION_3A_PRODUCTION
#define CYDEV_CHIP_REV_EXPECT CYDEV_CHIP_REVISION_USED
#define CYDEV_CONFIG_FASTBOOT_ENABLED 1
#define CYDEV_CONFIG_UNUSED_IO_AllowButWarn 0
#define CYDEV_CONFIG_UNUSED_IO CYDEV_CONFIG_UNUSED_IO_AllowButWarn
#define CYDEV_CONFIG_UNUSED_IO_AllowWithInfo 1
#define CYDEV_CONFIG_UNUSED_IO_Disallowed 2
#define CYDEV_CONFIGURATION_CLEAR_SRAM 1
#define CYDEV_CONFIGURATION_COMPRESSED 1
#define CYDEV_CONFIGURATION_DMA 0
#define CYDEV_CONFIGURATION_ECC 1
#define CYDEV_CONFIGURATION_IMOENABLED CYDEV_CONFIG_FASTBOOT_ENABLED
#define CYDEV_CONFIGURATION_MODE_COMPRESSED 0
#define CYDEV_CONFIGURATION_MODE CYDEV_CONFIGURATION_MODE_COMPRESSED
#define CYDEV_CONFIGURATION_MODE_DMA 2
#define CYDEV_CONFIGURATION_MODE_UNCOMPRESSED 1
#define CYDEV_DEBUG_ENABLE_MASK 0x01u
#define CYDEV_DEBUG_ENABLE_REGISTER CYREG_MLOGIC_DEBUG
#define CYDEV_DEBUGGING_DPS_Disable 3
#define CYDEV_DEBUGGING_DPS_JTAG_4 1
#define CYDEV_DEBUGGING_DPS_JTAG_5 0
#define CYDEV_DEBUGGING_DPS_SWD 2
#define CYDEV_DEBUGGING_DPS_SWD_SWV 6
#define CYDEV_DEBUGGING_DPS CYDEV_DEBUGGING_DPS_SWD_SWV
#define CYDEV_DEBUGGING_ENABLE 1
#define CYDEV_DEBUGGING_XRES 0
#define CYDEV_DMA_CHANNELS_AVAILABLE 24u
#define CYDEV_ECC_ENABLE 0
#define CYDEV_INSTRUCT_CACHE_ENABLED 1
#define CYDEV_INTR_RISING 0x00000007u
#define CYDEV_PROJ_TYPE 0
#define CYDEV_PROJ_TYPE_BOOTLOADER 1
#define CYDEV_PROJ_TYPE_LOADABLE 2
#define CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER 3
#define CYDEV_PROJ_TYPE_STANDARD 0
#define CYDEV_PROTECTION_ENABLE 0
#define CYDEV_VARIABLE_VDDA 0
#define CYDEV_VDDA 5.0
#define CYDEV_VDDA_MV 5000
#define CYDEV_VDDD 5.0
#define CYDEV_VDDD_MV 5000
#define CYDEV_VDDIO0 5.0
#define CYDEV_VDDIO0_MV 5000
#define CYDEV_VDDIO1 5.0
#define CYDEV_VDDIO1_MV 5000
#define CYDEV_VDDIO2 5.0
#define CYDEV_VDDIO2_MV 5000
#define CYDEV_VDDIO3 5.0
#define CYDEV_VDDIO3_MV 5000
#define CYDEV_VIO0 5
#define CYDEV_VIO0_MV 5000
#define CYDEV_VIO1 5
#define CYDEV_VIO1_MV 5000
#define CYDEV_VIO2 5
#define CYDEV_VIO2_MV 5000
#define CYDEV_VIO3 5
#define CYDEV_VIO3_MV 5000
#define CYIPBLOCK_DP8051_VERSION 0
#define CYIPBLOCK_P3_ANAIF_VERSION 0
#define CYIPBLOCK_P3_CAPSENSE_VERSION 0
#define CYIPBLOCK_P3_COMP_VERSION 0
#define CYIPBLOCK_P3_DECIMATOR_VERSION 0
#define CYIPBLOCK_P3_DMA_VERSION 0
#define CYIPBLOCK_P3_DRQ_VERSION 0
#define CYIPBLOCK_P3_DSM_VERSION 0
#define CYIPBLOCK_P3_EMIF_VERSION 0
#define CYIPBLOCK_P3_I2C_VERSION 0
#define CYIPBLOCK_P3_LCD_VERSION 0
#define CYIPBLOCK_P3_LPF_VERSION 0
#define CYIPBLOCK_P3_PM_VERSION 0
#define CYIPBLOCK_P3_TIMER_VERSION 0
#define CYIPBLOCK_P3_VIDAC_VERSION 0
#define CYIPBLOCK_P3_VREF_VERSION 0
#define CYIPBLOCK_S8_GPIO_VERSION 0
#define CYIPBLOCK_S8_IRQ_VERSION 0
#define CYIPBLOCK_S8_SIO_VERSION 0
#define CYIPBLOCK_S8_UDB_VERSION 0
#define DMA_CHANNELS_USED__MASK0 0x00000000u
#define CYDEV_BOOTLOADER_ENABLE 0

#endif /* INCLUDED_CYFITTER_H */
