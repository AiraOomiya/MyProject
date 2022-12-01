#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"

//壁構造体の定義
typedef struct
{
	D3DXVECTOR3 pos; //壁の位置
	D3DXVECTOR3 rot; //壁の向き
	int nType; //壁の種類
	int nSplitX;//横の分割数
	int nSplitY;//縦の分割数	
	float fWidth; //壁の幅
	float fHeight; //壁の高さ
	float fDepth; //壁の奥行き
	bool bUse; //壁を使用しているかどうか
} Wall;

//ブロックの状態
typedef enum
{
	WALLSTATE_NORMAL = 0,	
	WALLSTATE_MAX
} WALLSTATE;

//プロトタイプ宣言
void InitWall(void); //初期化処理
void UninitWall(void); //終了処理
void UpdateWall(void); //更新処理
void DrawWall(void); //描画処理
void LoadWall(void);
bool CollisionWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight);

#endif
