#include "camera.h"
#include "input.h"
#include "player.h"

#define LEFT (-0.5f) //左
#define LEFT_UP (-0.75f) //左上
#define LEFT_DOWN (-0.25f) //左下
#define RIGHT (0.5f) //右
#define RIGHT_UP (0.75f) //右上
#define RIGHT_DOWN (0.25f) //右下
#define UP (-1.0f) //上
#define DOWN (1.0f) //下

//グローバル変数
Camera g_Camera;					//カメラの情報
float  g_MaxDrawCamera = 2000.0f;	//最大描画範囲

//カメラの初期化
void InitCamera(void) //初期化処理
{
	g_Camera.posV = D3DXVECTOR3(0.0f, 400.0f, 0.0f);
	g_Camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	
	Player * pPlayer = GetPlayer();

	//視点
	g_Camera.posV.x = pPlayer->pos.x;
	g_Camera.posV.z = pPlayer->pos.z - 410;

	//注視点
	g_Camera.posR.x = pPlayer->pos.x;
	g_Camera.posR.z = pPlayer->pos.z;

	//それぞれの位置の差分を格納する変数
	float PosDiffX, PosDiffY, PosDiffZ;

	PosDiffX = pow(g_Camera.posR.x - g_Camera.posV.x, 2.0f);	//２乗
	PosDiffY = pow(g_Camera.posR.y - g_Camera.posV.y, 2.0f);	//２乗
	PosDiffZ = pow(g_Camera.posR.z - g_Camera.posV.z, 2.0f);	//２乗

	//長さの算出
	g_Camera.fLength = sqrtf(PosDiffX + PosDiffY + PosDiffZ);
}

//カメラの終了処理
void UninitCamera(void) //終了処理
{
	
}

//カメラの更新処理
void UpdateCamera(void) //更新処理
{
	Player * pPlayer = GetPlayer();

	//視点
	g_Camera.posV += pPlayer->pos - pPlayer->posOld;

	//注視点
	g_Camera.posR.x = pPlayer->pos.x;
	g_Camera.posR.z = pPlayer->pos.z;

	//視点の上下
	if (GetKeyboardPress(DIK_T) == true)
	{
		g_Camera.posV.y += 2.5f;
	}
	if (GetKeyboardPress(DIK_B) == true)
	{
		g_Camera.posV.y -= 2.5f;
	}

	if (GetKeyboardPress(DIK_0) == true)
	{
		g_MaxDrawCamera += 2.0f;

		if (g_MaxDrawCamera >= 5000.0f)
		{
			g_MaxDrawCamera = 5000.0f;
		}
	}
	if (GetKeyboardPress(DIK_9) == true)
	{
		g_MaxDrawCamera -= 2.0f;

		if (g_MaxDrawCamera <= 1000.0f)
		{
			g_MaxDrawCamera = 1000.0f;
		}
	}

	//視点の左右
	if (GetKeyboardPress(DIK_Z) == true)
	{
		g_Camera.rot.y -= 0.01f;	
	}
	if (GetKeyboardPress(DIK_C) == true)
	{
		g_Camera.rot.y += 0.01f;
	}

	g_Camera.posV.x = g_Camera.posR.x + sinf(D3DX_PI - g_Camera.rot.y) * g_Camera.fLength;
	g_Camera.posV.z = g_Camera.posR.z + cosf(D3DX_PI - g_Camera.rot.y) * g_Camera.fLength;


	//注視点の上下
	if (GetKeyboardPress(DIK_Y) == true)
	{
		g_Camera.posR.y += 3.5f;
	}
	if (GetKeyboardPress(DIK_N) == true)
	{
		g_Camera.posR.y -= 3.5f;
	}
}


//カメラの設定処理
void SetCamera(void) //設定処理
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_Camera.mtxProjection);

	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjection, D3DXToRadian(45.0f),(float)SCREEN_WIDTH/(float)SCREEN_HEIGHT,10.0f, g_MaxDrawCamera);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_Camera.mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_Camera.mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_Camera.mtxView, &g_Camera.posV, &g_Camera.posR, &g_Camera.vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_Camera.mtxView);
}

//カメラの取得
Camera *GetCamera(void)
{
	return &g_Camera;
}