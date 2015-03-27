//RingBuffer.c ibis inc. Eiji Kamiya 2008/9/5-
//Licence : New BSD
#include "RingBuffer.h"

//----------------------------------------------------------------------------
// �O���[�o���ϐ��̐錾
//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
//�����O�o�b�t�@�̏�����
void InitializeRingBuffer(RingBuffer* ring)
{
	ring->start=0;
	ring->end=0;
}

//�����O�o�b�t�@�̃f�[�^�T�C�Y
int16 GetRingBufferSize(RingBuffer* ring)
{
	if(ring->end >= ring->start){//�����܂����ł��Ȃ��Ƃ�
		return ring->end -ring->start;
	}
	return RING_BUFFER_SIZE - (ring->start - ring->end);
}

//�����O�o�b�t�@��short�s�[�N
int16 GetRingBufferShort(RingBuffer* ring,int16 offset)
{
	int16 a,b;
	int16 o=(ring->start + offset)%RING_BUFFER_SIZE;
	if( o + 2 <= RING_BUFFER_SIZE){//�܂����Ȃ��Ƃ�
		a=ring->buffer[o];
		b=ring->buffer[o+1];
	} else {//1�o�C�g�܂����Ƃ�
		a=ring->buffer[o];
		b=ring->buffer[0];
	}
	return (a&0xff)|(b<<8);
}

//�����O�o�b�t�@��1byte�ǂݍ���
uint8 ReadRingBufferByte(RingBuffer* ring)
{
	uint8 a;
	
	a=ring->buffer[ring->start];
	ring->start++;
	ring->start%=RING_BUFFER_SIZE;
	return a;
}

//�����O�o�b�t�@��short�ǂݍ���
int16 ReadRingBufferShort(RingBuffer* ring)
{
	int16 a,b;
	a=ring->buffer[ring->start];
	b=ring->buffer[(ring->start+1)%RING_BUFFER_SIZE];
	ring->start+=2;
	ring->start%=RING_BUFFER_SIZE;
	return (a&0xff)|(b<<8);
}

//�����O�o�b�t�@�Ŕz��ǂݍ���
void ReadRingBuffer(RingBuffer* ring,uint8 buf[],int16 offset,int16 size)
{
	int16 i;
	uint8* p=buf+offset;
	
	for(i=0;i<size;i++){
		*(p++)=ring->buffer[ring->start];
		ring->start++;
		ring->start%=RING_BUFFER_SIZE;
	}
}

//�����O�o�b�t�@�̋󂫃f�[�^�T�C�Y
int16 GetRingBufferCapacity(RingBuffer* ring)
{
	if(ring->end >= ring->start){//�����܂����ł��Ȃ��Ƃ�
		return RING_BUFFER_SIZE-(ring->end -ring->start)-1;
	}
	return ring->start - ring->end -1;
}

//�����O�o�b�t�@��1byte��������
void WriteRingBufferByte(RingBuffer* ring,uint8 ch)
{
	ring->buffer[ring->end++]=ch;
	ring->end%=RING_BUFFER_SIZE;
}

//�����O�o�b�t�@�ɔz�񏑂�����
void WriteRingBuffer(RingBuffer* ring,const uint8 buf[],int16 offset,int16 size)
{
	int16 i;
	uint8* p=buf+offset;
	for(i=0;i<size;i++){
		ring->buffer[ring->end]=*(p++);
		ring->end++;
		ring->end%=RING_BUFFER_SIZE;
	}
}
