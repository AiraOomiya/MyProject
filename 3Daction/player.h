#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//プレイヤーの構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	bool bJump;
	bool bUse;	
} Player;

//プロトタイプ宣言
void InitPlayer(void);		//初期化処理
void UninitPlayer(void);	//終了処理
void UpdatePlayer(void);	//更新処理
void DrawPlayer(void);		//描画処理
Player * GetPlayer(void);	//カメラの取得
void MovePlayer(void);		//プレイヤーの移動処理


#endif
