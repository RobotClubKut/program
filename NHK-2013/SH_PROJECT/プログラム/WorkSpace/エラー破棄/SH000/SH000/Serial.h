//Serial.h
//Eiji Kamiya
//Licence : New BSD

#ifndef __SERIAL_H__
#define __SERIAL_H__
#include "typedefine.h"

//初期化
void InitializeSerial(void);
//文字列送信
void SerialPuts(const char *str);
//1文字送信
void SerialPutc(char ch);
//バイト配列送信
void SerialWriteData(uint8* buf,int16 size);
//受信バッファにあるデータサイズ
int16 GetRecieveBufferDataSize();
//1文字受信
int16 SerialGetc();
//バイト配列受信
int16 SerialReadData(uint8* buf,int16 size);
#endif//__SERIAL_H__
