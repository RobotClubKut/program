.include "m644Pdef.inc"

.equ	Reverse		=1		;  "1"で負論理通信、"0"で正論理送信
.equ	Tx		=4		;  送信ポート（PORTB）
.equ	LED1		=1		;  PORTB,1

;割り込み時使用STACK
.def	STACK		=R15

;汎用
.def	TEMP		=R16
.def	DATA		=R17
.def	DATA_H		=R16
.def	DATA_L		=R17

;ウエイト用
.def	CT_0		=R18
.def	CT_1		=R19
.def	CT_2		=R20

;データ
.def	Tx_DATA		=R17		;送信データ


.cseg				;プログラムメモリーへ切替。他にデータメモリ.DSEG、EEPROMの.ESEG がある
.org	$0000			;書き込みスタート番地

	JMP	RESET		; 1:リセット
	JMP	RETURN		; 2:外部割り込み要求0
	JMP	RETURN		; 3:外部割り込み要求1
	JMP	RETURN		; 4:ピン変化割込み要求0(PCINT  0～ 7 PIN)
	JMP	RETURN		; 5:ピン変化割込み要求1(PCINT  8～14 PIN)
	JMP	RETURN		; 6:ピン変化割込み要求2(PCINT 16～23 PIN)
	JMP	RETURN		; 7:ｳｫｯﾁﾄﾞｯｸﾞ計時完了
	JMP	RETURN		; 8:ﾀｲﾏ/ｶｳﾝﾀ2 比較A一致
	JMP	RETURN		; 9:ﾀｲﾏ/ｶｳﾝﾀ2 比較B一致
	JMP	RETURN		;10:ﾀｲﾏ/ｶｳﾝﾀ2 ｵｰﾊﾞｰﾌﾛｰ
	JMP	RETURN		;11:ﾀｲﾏ/ｶｳﾝﾀ1 捕獲(ｷｬﾌﾟﾁｬ)発生
	JMP	RETURN		;12:ﾀｲﾏ/ｶｳﾝﾀ1 比較A一致(長時間タイマーに使用)
	JMP	RETURN		;13:ﾀｲﾏ/ｶｳﾝﾀ1 比較B一致
	JMP	RETURN		;14:ﾀｲﾏ/ｶｳﾝﾀ1 ｵｰﾊﾞｰﾌﾛｰ
	JMP	RETURN		;15:ﾀｲﾏ/ｶｳﾝﾀ0 比較A一致
	JMP	RETURN		;16:ﾀｲﾏ/ｶｳﾝﾀ0 比較B一致
	JMP	RETURN		;17:T0オーバーフロー
	JMP	RETURN		;18:SPI 転送完了
	JMP	RETURN		;19:USART 受信完了
	JMP	RETURN		;20:USART 送信ﾊﾞｯﾌｧ空き 
	JMP	RETURN		;21:USART 送信完了
	JMP	RETURN		;22:A/D変換完了
	JMP	RETURN		;23:EEPROM 操作可
	JMP	RETURN		;24:ｱﾅﾛｸﾞ比較器出力遷移
	JMP	RETURN		;25:2線ｼﾘｱﾙ ｲﾝﾀｰﾌｪｰｽ状態変化
	JMP	RETURN		;26:SPM命令操作可

RESET:	;スタックポインタの初期化
	LDI	R16,HIGH(RAMEND)	;スタックポインタを初期化。SRAMが無い、または256ﾊﾞｲﾄ以下の場合はこの行を削除。
	OUT	SPH,R16			;SRAMが無い、または256ﾊﾞｲﾄ以下の場合はこの行を削除。(ATmega48等)
	LDI	R16,LOW(RAMEND)		;SRAMが無い場合はこの行を削除。
	OUT	SPL,R16			;SRAMが無い場合はこの行を削除。
	;ポートＢの初期化
	LDI	TEMP,0b00000010		;ポートの状態を定義。ポート入力時、0でプルダウン,1でプルアップ。
	OUT	PORTB,TEMP
	LDI	TEMP,0b00010010		;ポートの入出力設定。0で入力、1で出力。
	OUT	DDRB,TEMP
	;ポートＣの初期化
	LDI	TEMP,0b11111111		;ポートの状態を定義。ポート入力時、0でプルダウン,1でプルアップ。
	OUT	PORTC,TEMP		;赤外線LEDのポートは2SA1317経由なので0で赤外線LED点灯、1で消灯
	LDI	TEMP,0b00000000		;ポートの入出力設定。0で入力、1で出力。
	OUT	DDRC,TEMP
	;ポートＤの初期化
	LDI	TEMP,0b11111111		;ポートの状態を定義。ポート入力時、0でプルダウン,1でプルアップ。
	OUT	PORTD,TEMP
	LDI	TEMP,0b00000000		;ポートの入出力設定。0で入力、1で出力。
	OUT	DDRD,TEMP

;***************************************************************************
;メインルーチン
;***************************************************************************

	;RS232C送信ポート初期化
	;ストップビット"１"を 10bit 分送信する。（10回）
	SEC				;キャリーフラグにストップビット"１"をセット
	RCALL	TxDATA_02		;キャリーフラグのデータを送信	
	SEC				;キャリーフラグにストップビット"１"をセット
	RCALL	TxDATA_02		;キャリーフラグのデータを送信	
	SEC				;キャリーフラグにストップビット"１"をセット
	RCALL	TxDATA_02		;キャリーフラグのデータを送信	
	SEC				;キャリーフラグにストップビット"１"をセット
	RCALL	TxDATA_02		;キャリーフラグのデータを送信	
	SEC				;キャリーフラグにストップビット"１"をセット
	RCALL	TxDATA_02		;キャリーフラグのデータを送信	
	SEC				;キャリーフラグにストップビット"１"をセット
	RCALL	TxDATA_02		;キャリーフラグのデータを送信	
	SEC				;キャリーフラグにストップビット"１"をセット
	RCALL	TxDATA_02		;キャリーフラグのデータを送信	
	SEC				;キャリーフラグにストップビット"１"をセット
	RCALL	TxDATA_02		;キャリーフラグのデータを送信	
	SEC				;キャリーフラグにストップビット"１"をセット
	RCALL	TxDATA_02		;キャリーフラグのデータを送信	
	SEC				;キャリーフラグにストップビット"１"をセット
	RCALL	TxDATA_02		;キャリーフラグのデータを送信	




;テスト表示
	LDI	Tx_DATA,0x21		;文字コード"!"を転送
	RCALL	TxDATA_01		;"!"を送信
	LDI	Tx_DATA,0x20		;文字コード" "を転送
	RCALL	TxDATA_01		;" "(スペース)を送信

MAIN:

RCALL	WR_START_MESSAGE		;スタートメッセージを送信する。

CALL	TM1000
	CBI	PORTB,LED1
CALL	TM1000
	SBI	PORTB,LED1
RJMP	MAIN
;■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
;サブルーチン
;■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
;---------------------------------------------------------------------------
;未定義割込みリターン
;---------------------------------------------------------------------------
RETURN:
	IN	STACK,SREG
	OUT	SREG,STACK
	RETI				;未定義割込みリターン
;---------------------------------------------------------------------------
;送信
;---------------------------------------------------------------------------
TxDATA_01:

	CLC				;キャリーフラグにスタートビット"０"をセット
	RCALL	TxDATA_02		;キャリーフラグのデータを送信	

	LSR	Tx_DATA			;右シフトしてLSB（下位ビット）をキャリーフラグにセットする。
	RCALL	TxDATA_02		;キャリーフラグのデータを送信	
	LSR	Tx_DATA			;右シフトしてLSB（下位ビット）をキャリーフラグにセットする。
	RCALL	TxDATA_02		;キャリーフラグのデータを送信	
	LSR	Tx_DATA			;右シフトしてLSB（下位ビット）をキャリーフラグにセットする。
	RCALL	TxDATA_02		;キャリーフラグのデータを送信	
	LSR	Tx_DATA			;右シフトしてLSB（下位ビット）をキャリーフラグにセットする。
	RCALL	TxDATA_02		;キャリーフラグのデータを送信	
	LSR	Tx_DATA			;右シフトしてLSB（下位ビット）をキャリーフラグにセットする。
	RCALL	TxDATA_02		;キャリーフラグのデータを送信	
	LSR	Tx_DATA			;右シフトしてLSB（下位ビット）をキャリーフラグにセットする。
	RCALL	TxDATA_02		;キャリーフラグのデータを送信	
	LSR	Tx_DATA			;右シフトしてLSB（下位ビット）をキャリーフラグにセットする。
	RCALL	TxDATA_02		;キャリーフラグのデータを送信	
	LSR	Tx_DATA			;右シフトしてLSB（下位ビット）をキャリーフラグにセットする。
	RCALL	TxDATA_02		;キャリーフラグのデータを送信	

	SEC				;キャリーフラグにストップビット"１"をセット
	RCALL	TxDATA_02		;キャリーフラグのデータを送信	
	;ウエイト代わりにストップビットを送信
	SEC				;キャリーフラグにストップビット"１"をセット
	RCALL	TxDATA_02		;キャリーフラグのデータを送信	
RET
;---------------------------------------------------------------------------
;キャリーフラグを送信
;---------------------------------------------------------------------------
TxDATA_02:
	PUSH	TEMP
	PUSH	Tx_DATA

	CLR	Tx_DATA
	ROL	Tx_DATA			;キャリーを含めた左回転させることにより、キャリーをLSBにセット。

	LDI	TEMP,Reverse
	EOR	Tx_DATA,TEMP		;排他的論理和を実行し、LSBを必要に応じて反転させる。

	BRNE	TxDATA_02_JP02
;	RJMP	TxDATA_02_JP02

TxDATA_02_JP01:
	NOP				;タイミング調整
	CBI	PORTB,Tx
	RJMP	TxDATA_02_END
TxDATA_02_JP02:
	SBI	PORTB,Tx
	RJMP	TxDATA_02_END
TxDATA_02_END:
	POP	Tx_DATA
	POP	TEMP

RET
;---------------------------------------------------------------------------
;"AVR ATmega644P one-chip microcomputer." 表示
;---------------------------------------------------------------------------
WR_START_MESSAGE:

	LDI	ZH,high(WR_START_MESSAGE_DATA * 2) 	;表示データ保存アドレスを指定。
	LDI	ZL,low (WR_START_MESSAGE_DATA * 2)
	RCALL	WRITE_01

	RET	
WR_START_MESSAGE_DATA:	.DB "AVR ATmega644P one-chip microcomputer.",13,10,0xFF	;書込みデータ ＋ CRLF ＋ 0xFF
;---------------------------------------------------------------------------
; プログラムメモリ配置データ表示
;---------------------------------------------------------------------------
;プログラムメモリはワード単位でアクセスする。１ワード２byteなので、Zレジズタ（ペア）を使用してデータを読込む。
;ZLレジスタの下位１ビットでワードの上位８ビットと下位８ビットのどちらを読み込むのかを指定する。
;したがってアドレスを2倍したものをZレジスタに書き込むことでデータを読込むことができる。
;LDI ZH,high(DATA + DATA)
;LDI ZL,low (DATA + DATA)
;LPM Rd,Z+
;DATA,Z+ は拡張間接アドレッシング命令なので、サポートされない機種の場合は、LPMでR0にロードし、Zレジスタをインクリメントする作業が必要になる。

WRITE_01:
	LPM	Tx_DATA,Z+		;Load Program Memory → Tx_DATA + Zポインタをインクリメント
	CPI	Tx_DATA,$FF		;Tx_DATA = 0xFF？ 0xFFは文字列の終了を示す。
	BREQ	WRITE_01_END

	RCALL	TxDATA_01

	RJMP	WRITE_01
WRITE_01_END:
	RET

;---------------------------------------------------------------------------
;AVRの 24bit 長時間ウエイト/タイマー
;ウエイト/タイマー = n×5+2 [クロック] 
;サブルーチンで使用の場合は上記プラス下記クロック余分に時間がかかる。
;RCALL,RET 命令で、16ビットデバイスは3+4、22ビットデバイスは4+5をプラスする。
; CALL,RET 命令で、16ビットデバイスは4+4、22ビットデバイスは5+5をプラスする。
;細かな調整は少なめに設定し、NOPで調整する。
;CT_2が上位、CT_0が下位。
;---------------------------------------------------------------------------
;CALLで呼び出した時の1ミリ秒
;20MHz時 CT_2=0x00,CT_0=0x0F,CT_0=0x9E + NOP X 0ヶ
;16MHz時 CT_2=0x00,CT_0=0x0C,CT_0=0x7E + NOP X 0ヶ
;10MHz時 CT_2=0x00,CT_0=0x07,CT_0=0xCE + NOP X 0ヶ
; 8MHz時 CT_2=0x00,CT_0=0x06,CT_0=0x3E + NOP X 0ヶ
; 1MHz時 CT_2=0x00,CT_0=0x00,CT_0=0xC6 + NOP X 0ヶ
;---------------------------------------------------------------------------
TM1:
	LDI	CT_2,0x00
	LDI	CT_1,0x00
	LDI	CT_0,0xC6
TM1_LOOP:
	;HEX_2:HEX_1:HEX_0 から１引く
	SUBI	CT_0,1		;1クロック
	SBCI	CT_1,0		;1クロック
	SBCI	CT_2,0		;1クロック
	BRNE	TM1_LOOP	;0になるまでループ。
				;ループ時2クロック、スルー時1クロック。
;	NOP			;細かな調整
;	NOP			;細かな調整
;	NOP			;細かな調整
;	NOP			;細かな調整

	RET             
;---------------------------------------------------------------------------
;CALLで呼び出した時の10ミリ秒
;20MHz時 CT_2=0x00 , CT_0=0x9C , CT_0=0x3E + NOP X 0ヶ
;16MHz時 CT_2=0x00 , CT_0=0x7C , CT_0=0xFE + NOP X 0ヶ
;10MHz時 CT_2=0x00 , CT_0=0x4E , CT_0=0x1E + NOP X 0ヶ
; 8MHz時 CT_2=0x00 , CT_0=0x3E , CT_0=0x7E + NOP X 0ヶ
; 1MHz時 CT_2=0x00 , CT_0=0x07 , CT_0=0xCE + NOP X 0ヶ
;---------------------------------------------------------------------------
TM10:
	LDI	CT_2,0x00
	LDI	CT_1,0x07
	LDI	CT_0,0xCE
TM10_LOOP:
	;HEX_2:HEX_1:HEX_0 から１引く
	SUBI	CT_0,1		;1クロック
	SBCI	CT_1,0		;1クロック
	SBCI	CT_2,0		;1クロック
	BRNE	TM10_LOOP	;0になるまでループ。
				;ループ時2クロック、スルー時1クロック。
;	NOP			;細かな調整
;	NOP			;細かな調整
;	NOP			;細かな調整
;	NOP			;細かな調整

	RET             
;---------------------------------------------------------------------------
;CALLで呼び出した時の100ミリ秒
;20MHz時 CT_2=0x06 , CT_0=0x1A , CT_0=0x7E + NOP X 0ヶ
;16MHz時 CT_2=0x04 , CT_0=0xE1 , CT_0=0xFE + NOP X 0ヶ
;10MHz時 CT_2=0x03 , CT_0=0x0D , CT_0=0x3E + NOP X 0ヶ
; 8MHz時 CT_2=0x02 , CT_0=0x70 , CT_0=0xFE + NOP X 0ヶ
; 1MHz時 CT_2=0x00 , CT_0=0x4E , CT_0=0x1E + NOP X 0ヶ
;---------------------------------------------------------------------------
TM100:
	LDI	CT_2,0x00
	LDI	CT_1,0x4E
	LDI	CT_0,0x1E
TM100_LOOP:
	;HEX_2:HEX_1:HEX_0 から１引く
	SUBI	CT_0,1		;1クロック
	SBCI	CT_1,0		;1クロック
	SBCI	CT_2,0		;1クロック
	BRNE	TM100_LOOP	;0になるまでループ。
				;ループ時2クロック、スルー時1クロック。
;	NOP			;細かな調整
;	NOP			;細かな調整
;	NOP			;細かな調整
;	NOP			;細かな調整

	RET             
;---------------------------------------------------------------------------
;CALLで呼び出した時の500ミリ秒
;20MHz時 CT_2=0x1E , CT_0=0x84 , CT_0=0x7E + NOP X 0ヶ
;16MHz時 CT_2=0x18 , CT_0=0x69 , CT_0=0xFE + NOP X 0ヶ
;10MHz時 CT_2=0x0F , CT_0=0x42 , CT_0=0x3E + NOP X 0ヶ
; 8MHz時 CT_2=0x0C , CT_0=0x34 , CT_0=0xFE + NOP X 0ヶ
; 1MHz時 CT_2=0x01 , CT_0=0x86 , CT_0=0x9E + NOP X 0ヶ
;---------------------------------------------------------------------------
TM500:
	LDI	CT_2,0x01
	LDI	CT_1,0x86
	LDI	CT_0,0x9E
TM500_LOOP:
	;HEX_2:HEX_1:HEX_0 から１引く
	SUBI	CT_0,1		;1クロック
	SBCI	CT_1,0		;1クロック
	SBCI	CT_2,0		;1クロック
	BRNE	TM500_LOOP	;0になるまでループ。
				;ループ時2クロック、スルー時1クロック。
;	NOP			;細かな調整
;	NOP			;細かな調整
;	NOP			;細かな調整
;	NOP			;細かな調整

	RET             
;---------------------------------------------------------------------------
;CALLで呼び出した時の1000ミリ秒
;20MHz時 CT_2=0x3D , CT_0=0x08 , CT_0=0xFE + NOP X 0ヶ
;16MHz時 CT_2=0x30 , CT_0=0xD3 , CT_0=0xFE + NOP X 0ヶ
;10MHz時 CT_2=0x1E , CT_0=0x84 , CT_0=0x7E + NOP X 0ヶ
; 8MHz時 CT_2=0x18 , CT_0=0x69 , CT_0=0xFE + NOP X 0ヶ
; 1MHz時 CT_2=0x03 , CT_0=0x0D , CT_0=0x3E + NOP X 0ヶ
;---------------------------------------------------------------------------
TM1000:
	LDI	CT_2,0x03
	LDI	CT_1,0x0D
	LDI	CT_0,0x3E
TM1000_LOOP:
	;HEX_2:HEX_1:HEX_0 から１引く
	SUBI	CT_0,1		;1クロック
	SBCI	CT_1,0		;1クロック
	SBCI	CT_2,0		;1クロック
	BRNE	TM1000_LOOP	;0になるまでループ。
				;ループ時2クロック、スルー時1クロック。
;	NOP			;細かな調整
;	NOP			;細かな調整
;	NOP			;細かな調整
;	NOP			;細かな調整

	RET