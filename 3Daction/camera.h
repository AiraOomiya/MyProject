#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//カメラの構造体
typedef struct
{
	D3DXVECTOR3 posV; //視点
	D3DXVECTOR3 posR; //注視点
	D3DXVECTOR3 vecU; //上方向ベクトル
	D3DXVECTOR3 rot; //向き
	float fLength;	// 距離
	D3DXMATRIX mtxProjection; //プロジェクションマトリックス
	D3DXMATRIX mtxView; //ビューマトリックス
} Camera;

//プロトタイプ宣言
void InitCamera(void); //初期化処理
void UninitCamera(void); //終了処理
void UpdateCamera(void); //更新処理
void SetCamera(void); //設定処理
Camera *GetCamera(void); //カメラの取得

#endif
