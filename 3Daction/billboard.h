#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"

//弾の構造体の定義
typedef struct
{
	D3DXVECTOR3 pos; //位置	
	bool bUse; //弾を使用しているかどうか
} Billboard;

//プロトタイプ宣言
void InitBillboard(void); //初期化処理
void UninitBillboard(void); //終了処理
void UpdateBillboard(void); //更新処理
void DrawBillboard(void); //描画処理

#endif
