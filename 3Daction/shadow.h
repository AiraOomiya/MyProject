#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

//影構造体
typedef struct
{
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 rot =D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMATRIX mtxWorldShadow; //ワールドマトリックス
	bool bUse; //弾を使用しているかどうか
} Shadow;

//プロトタイプ宣言
void InitShadow(void); //初期化処理
void UninitShadow(void); //終了処理
void UpdateShadow(void); //更新処理
void DrawShadow(void); //描画処理
int SetShadow(void); //設定処理
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos); //位置設定処理

#endif