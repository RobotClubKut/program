//RingBuffer ibis inc. Eiji Kamiya 2008/9/5-
//Licence : New BSD
#ifndef _RING_BUFFER_
#define _RING_BUFFER_

#include "typedefine.h"

//----------------------------------------------------------------------------
// 定数定義
//----------------------------------------------------------------------------
#define RING_BUFFER_SIZE		500		//リングバッファサイズ

//----------------------------------------------------------------------------
// 構造体定義
//----------------------------------------------------------------------------
//リングバッファ
//start==endの場合はデータが空、フルの場合は、endがstart-1
//よって最大限データが格納できるのは、RING_BUFFER_SIZE-1バイトまで。
typedef struct {
	uint8 buffer[RING_BUFFER_SIZE];		//バッファ
	int16 start;						//データ開始位置（ここが指している値を含む）
	int16 end;							//データ終了位置（ここが指している値は含まない）
} RingBuffer;							

//----------------------------------------------------------------------------
// マクロ
//----------------------------------------------------------------------------
//リングバッファが空か
#define IsRingBufferEmpty(ring_ptr) ((ring_ptr)->start==(ring_ptr)->end)

//----------------------------------------------------------------------------
// プロトタイプ宣言
//----------------------------------------------------------------------------
//リングバッファの初期化
void InitializeRingBuffer(RingBuffer* ring);
//リングバッファのデータサイズ
int16 GetRingBufferSize(RingBuffer* ring);
//リングバッファで2byteピーク
int16 GetRingBufferShort(RingBuffer* ring,int16 offset);
//リングバッファで1byte読み込み
uint8 ReadRingBufferByte(RingBuffer* ring);
//リングバッファで2byte読み込み
int16 ReadRingBufferShort(RingBuffer* ring);
//リングバッファで配列読み込み
void ReadRingBuffer(RingBuffer* ring,uint8 buf[],int16 offset,int16 size);
//リングバッファの空きデータサイズ
int16 GetRingBufferCapacity(RingBuffer* ring);
//リングバッファで1byte書きこみ
void WriteRingBufferByte(RingBuffer* ring,uint8 ch);
//リングバッファに配列書き込み
void WriteRingBuffer(RingBuffer* ring,const uint8 buf[],int16 offset,int16 size);

#endif//_RING_BUFFER_

