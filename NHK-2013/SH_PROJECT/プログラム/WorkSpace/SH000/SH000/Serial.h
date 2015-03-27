//Serial.h
//Eiji Kamiya
//Licence : New BSD

#ifndef __SERIAL_H__
#define __SERIAL_H__
#include "typedefine.h"

//������
void InitializeSerial(void);
//�����񑗐M
void SerialPuts(const char *str);
//1�������M
void SerialPutc(char ch);
//�o�C�g�z�񑗐M
void SerialWriteData(uint8* buf,int16 size);
//��M�o�b�t�@�ɂ���f�[�^�T�C�Y
int16 GetRecieveBufferDataSize();
//1������M
int16 SerialGetc();
//�o�C�g�z���M
int16 SerialReadData(uint8* buf,int16 size);
#endif//__SERIAL_H__
