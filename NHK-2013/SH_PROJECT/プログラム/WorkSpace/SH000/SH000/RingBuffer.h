//RingBuffer ibis inc. Eiji Kamiya 2008/9/5-
//Licence : New BSD
#ifndef _RING_BUFFER_
#define _RING_BUFFER_

#include "typedefine.h"

//----------------------------------------------------------------------------
// �萔��`
//----------------------------------------------------------------------------
#define RING_BUFFER_SIZE		500		//�����O�o�b�t�@�T�C�Y

//----------------------------------------------------------------------------
// �\���̒�`
//----------------------------------------------------------------------------
//�����O�o�b�t�@
//start==end�̏ꍇ�̓f�[�^����A�t���̏ꍇ�́Aend��start-1
//����čő���f�[�^���i�[�ł���̂́ARING_BUFFER_SIZE-1�o�C�g�܂ŁB
typedef struct {
	uint8 buffer[RING_BUFFER_SIZE];		//�o�b�t�@
	int16 start;						//�f�[�^�J�n�ʒu�i�������w���Ă���l���܂ށj
	int16 end;							//�f�[�^�I���ʒu�i�������w���Ă���l�͊܂܂Ȃ��j
} RingBuffer;							

//----------------------------------------------------------------------------
// �}�N��
//----------------------------------------------------------------------------
//�����O�o�b�t�@����
#define IsRingBufferEmpty(ring_ptr) ((ring_ptr)->start==(ring_ptr)->end)

//----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//----------------------------------------------------------------------------
//�����O�o�b�t�@�̏�����
void InitializeRingBuffer(RingBuffer* ring);
//�����O�o�b�t�@�̃f�[�^�T�C�Y
int16 GetRingBufferSize(RingBuffer* ring);
//�����O�o�b�t�@��2byte�s�[�N
int16 GetRingBufferShort(RingBuffer* ring,int16 offset);
//�����O�o�b�t�@��1byte�ǂݍ���
uint8 ReadRingBufferByte(RingBuffer* ring);
//�����O�o�b�t�@��2byte�ǂݍ���
int16 ReadRingBufferShort(RingBuffer* ring);
//�����O�o�b�t�@�Ŕz��ǂݍ���
void ReadRingBuffer(RingBuffer* ring,uint8 buf[],int16 offset,int16 size);
//�����O�o�b�t�@�̋󂫃f�[�^�T�C�Y
int16 GetRingBufferCapacity(RingBuffer* ring);
//�����O�o�b�t�@��1byte��������
void WriteRingBufferByte(RingBuffer* ring,uint8 ch);
//�����O�o�b�t�@�ɔz�񏑂�����
void WriteRingBuffer(RingBuffer* ring,const uint8 buf[],int16 offset,int16 size);

#endif//_RING_BUFFER_

