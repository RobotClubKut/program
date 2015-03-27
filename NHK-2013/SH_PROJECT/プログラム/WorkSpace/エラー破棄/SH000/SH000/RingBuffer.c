//RingBuffer.c ibis inc. Eiji Kamiya 2008/9/5-
//Licence : New BSD
#include "RingBuffer.h"

//----------------------------------------------------------------------------
// グローバル変数の宣言
//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
//リングバッファの初期化
void InitializeRingBuffer(RingBuffer* ring)
{
	ring->start=0;
	ring->end=0;
}

//リングバッファのデータサイズ
int16 GetRingBufferSize(RingBuffer* ring)
{
	if(ring->end >= ring->start){//境をまたいでいないとき
		return ring->end -ring->start;
	}
	return RING_BUFFER_SIZE - (ring->start - ring->end);
}

//リングバッファでshortピーク
int16 GetRingBufferShort(RingBuffer* ring,int16 offset)
{
	int16 a,b;
	int16 o=(ring->start + offset)%RING_BUFFER_SIZE;
	if( o + 2 <= RING_BUFFER_SIZE){//またがないとき
		a=ring->buffer[o];
		b=ring->buffer[o+1];
	} else {//1バイトまたぐとき
		a=ring->buffer[o];
		b=ring->buffer[0];
	}
	return (a&0xff)|(b<<8);
}

//リングバッファで1byte読み込み
uint8 ReadRingBufferByte(RingBuffer* ring)
{
	uint8 a;
	
	a=ring->buffer[ring->start];
	ring->start++;
	ring->start%=RING_BUFFER_SIZE;
	return a;
}

//リングバッファでshort読み込み
int16 ReadRingBufferShort(RingBuffer* ring)
{
	int16 a,b;
	a=ring->buffer[ring->start];
	b=ring->buffer[(ring->start+1)%RING_BUFFER_SIZE];
	ring->start+=2;
	ring->start%=RING_BUFFER_SIZE;
	return (a&0xff)|(b<<8);
}

//リングバッファで配列読み込み
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

//リングバッファの空きデータサイズ
int16 GetRingBufferCapacity(RingBuffer* ring)
{
	if(ring->end >= ring->start){//境をまたいでいないとき
		return RING_BUFFER_SIZE-(ring->end -ring->start)-1;
	}
	return ring->start - ring->end -1;
}

//リングバッファで1byte書きこみ
void WriteRingBufferByte(RingBuffer* ring,uint8 ch)
{
	ring->buffer[ring->end++]=ch;
	ring->end%=RING_BUFFER_SIZE;
}

//リングバッファに配列書き込み
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
