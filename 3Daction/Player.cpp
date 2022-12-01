#include "player.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"
#include "bullet.h"


#define LEFT (0.5f) //左
#define LEFT_UP (0.75f) //左上
#define LEFT_DOWN (0.25f) //左下
#define RIGHT (-0.5f) //右
#define RIGHT_UP (-0.75f) //右上
#define RIGHT_DOWN (-0.25f) //右下
#define UP (1.0f) //上
#define DOWN (0.0f) //下

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexturePlayer[10] = {}; //テクスチャへのポインタ
LPD3DXBUFFER g_pBuffPlayer = NULL; //マテリアルへのポインタ
D3DXVECTOR3 g_vtxMinPlayer, g_vtxMaxModel;//モデルの最大値、最小値
D3DXMATRIX g_mtxWorldPlayer; //ワールドマトリックス
LPD3DXMESH g_pMeshPlayer = NULL; //メッシュへのポインタ
DWORD g_dwNumMatPlayer = 0; //マテリアルの数
Player g_Player; //モデルの情報
int g_nIdxShadow = -1; //対象のインデックス(番号)


//モデルの初期化
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	
	D3DXMATERIAL *pMat; //マテリアルデータへのポインタ
	int nNumVtx; //頂点数
	DWORD dwSizeFVF; //頂点フォーマットのサイズ
	BYTE *pVtxBuff; //頂点バッファへのポインタ

	//各種変数の初期化
	g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\player.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffPlayer,
		NULL,
		&g_dwNumMatPlayer,
	    &g_pMeshPlayer);

	//頂点数の取得
	nNumVtx = g_pMeshPlayer->GetNumVertices();

	//頂点フォーマットのサイズを取得
	dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshPlayer->GetFVF());

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//テクスチャのファイルが存在する			
		 //テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_pTexturePlayer[nCntMat]);
		}
	}

	//影を設定
	g_nIdxShadow = SetShadow();
}

//モデルの終了処理
void UninitPlayer(void)
{
	//メッシュの破棄
	if (g_pMeshPlayer != NULL)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}

	//マテリアルの破棄
	if (g_pBuffPlayer != NULL)
	{
		g_pBuffPlayer->Release();
		g_pBuffPlayer = NULL;
	}
}

//モデルの更新処理
void UpdatePlayer(void)
{
	//プレイヤーの位置更新
	g_Player.posOld = g_Player.pos;

	//移動量の更新(増加させる)
	MovePlayer();

	//影の位置設定
	SetPositionShadow(g_nIdxShadow, g_Player.pos);

	if (GetKeyboardRepeat(DIK_SPACE) == true)
	{//SPACEキーが押された
	 
	}


	if (GetKeyboardRepeat(DIK_LSHIFT) == true)
	{//LSHIFTキーが押された
	 
	}

	if (GetKeyboardRepeat(DIK_RETURN) == true)
	{//RETURNキーが押された
	 //弾の設定
		SetBullet(g_Player.pos, D3DXVECTOR3(1.0f, 0.0f, 0.0f), 5, BULLETTYPE_MODEL);
		//PlaySound(SOUND_LABEL_SE_SHOT);
	}	
}

//プレイヤーの移動処理
void MovePlayer(void)
{
	//カメラの情報取得
	Camera *pCamera = GetCamera();

	if (GetKeyboardPress(DIK_A) == true)
	{//Aキーが押された

		if (GetKeyboardPress(DIK_W) == true)
		{//左上移動
			g_Player.pos.x += sinf((D3DX_PI * LEFT_UP + pCamera->rot.y) + g_Player.rot.y)*6.0f; //X座標
			g_Player.pos.z += cosf((D3DX_PI * LEFT_UP + pCamera->rot.y) + g_Player.rot.y)*6.0f; //Y座標
		}

		else if (GetKeyboardPress(DIK_S) == true)
		{//左下移動
			g_Player.pos.x += sinf((D3DX_PI * LEFT_DOWN + pCamera->rot.y) + g_Player.rot.y)*6.0f; //X座標
			g_Player.pos.z += cosf((D3DX_PI * LEFT_DOWN + pCamera->rot.y) + g_Player.rot.y)*6.0f; //Y座標
		}

		else
		{
			g_Player.pos.x += sinf((D3DX_PI * LEFT + pCamera->rot.y) + g_Player.rot.y)*6.0f; //X座標
			g_Player.pos.z += cosf((D3DX_PI * LEFT + pCamera->rot.y) + g_Player.rot.y)*6.0f; //Y座標
		}
	}

	else if (GetKeyboardPress(DIK_D) == true)
	{//Dキーが押された								

		if (GetKeyboardPress(DIK_W) == true)
		{//	右上移動							  
			g_Player.pos.x += sinf((D3DX_PI * RIGHT_UP + pCamera->rot.y) + g_Player.rot.y)*6.0f; //X座標
			g_Player.pos.z += cosf((D3DX_PI * RIGHT_UP + pCamera->rot.y) + g_Player.rot.y)*6.0f; //Y座標
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//右下移動
			g_Player.pos.x += sinf((D3DX_PI * RIGHT_DOWN + pCamera->rot.y) + g_Player.rot.y)*6.0f; //X座標
			g_Player.pos.z += cosf((D3DX_PI * RIGHT_DOWN + pCamera->rot.y) + g_Player.rot.y)*6.0f; //Y座標
		}

		else
		{
			g_Player.pos.x += sinf((D3DX_PI * RIGHT + pCamera->rot.y) + g_Player.rot.y)*6.0f; //X座標
			g_Player.pos.z += cosf((D3DX_PI * RIGHT + pCamera->rot.y) + g_Player.rot.y)*6.0f; //Y座標
		}
	}

	else if (GetKeyboardPress(DIK_W) == true)
	{//Wキーが押された
		g_Player.pos.x += sinf((D3DX_PI * UP + pCamera->rot.y) + g_Player.rot.y)*6.0f; //X座標
		g_Player.pos.z += cosf((D3DX_PI * UP + pCamera->rot.y) + g_Player.rot.y)*6.0f; //Y座標
	}

	else if (GetKeyboardPress(DIK_S) == true)
	{//Sキーが押された
		g_Player.pos.x += sinf((D3DX_PI * DOWN + pCamera->rot.y) + g_Player.rot.y)*6.0f; //X座標
		g_Player.pos.z += cosf((D3DX_PI * DOWN + pCamera->rot.y) + g_Player.rot.y)*6.0f; //Y座標
	}

}

//モデルの描画処理
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス
	D3DMATERIAL9 matDef; //現在のマテリアル保存用
	D3DXMATERIAL *pMat; //マテリアルデータへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldPlayer);

	//向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxRot);

	//位置の反映
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPlayer);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePlayer[nCntMat]);

		//モデル(パーツ)の描画
		g_pMeshPlayer->DrawSubset(nCntMat);
	}
	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);	
}

//プレイヤーの取得
Player *GetPlayer(void)
{
	return &g_Player;
}