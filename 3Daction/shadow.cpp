#include "shadow.h"
#include "player.h"

//マクロ定義
#define MAX_SHADOW	(256) //影の最大数

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;
Shadow g_aShadow[MAX_SHADOW]; //影の情報

//影の初期化
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\shadow000.jpg",
		&g_pTextureShadow);

	//各種変数の初期化
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_aShadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].mtxWorldShadow;
		g_aShadow[nCntShadow].bUse = false; //使用していない状態にする		

	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow, NULL);

	//ポインタを設定
	VERTEX_3D*pVtx;

	//頂点バッファをロックし、頂点座標へのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void **)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-10.0f, 0.0f, 10.0f); //左上端
	pVtx[1].pos = D3DXVECTOR3(10.0f, 0.0f, 10.0f); //右上端
	pVtx[2].pos = D3DXVECTOR3(-10.0f, 0.0f, -10.0f); //左下端
	pVtx[3].pos = D3DXVECTOR3(10.0f, 0.0f, -10.0f); //右下端

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //左上端
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //右上端
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //左下端
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //右下端

	//頂点カラー設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255); //左上端
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255); //右上端
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255); //左下端
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255); //右下端

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f); //左上端
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f); //右上端
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f); //左下端
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f); //右下端

	//頂点バッファをアンロックする
	g_pVtxBuffShadow->Unlock();
}

//影の終了処理
void UninitShadow(void)
{
	//テクスチャの破棄
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//影の更新処理
void UpdateShadow(void)
{

}

//影の描画処理
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス

	//減算合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aShadow[nCntShadow].mtxWorldShadow);

		//向きの反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aShadow[nCntShadow].rot.x,g_aShadow[nCntShadow].rot.y,g_aShadow[nCntShadow].rot.z);
		D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorldShadow, &g_aShadow[nCntShadow].mtxWorldShadow, &mtxRot);

		//位置の反映
		D3DXMatrixTranslation(&mtxTrans, g_aShadow[nCntShadow].pos.x, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z);
		D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorldShadow, &g_aShadow[nCntShadow].mtxWorldShadow, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aShadow[nCntShadow].mtxWorldShadow);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureShadow);

		//影の描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntShadow * 4, 2);
	}

	//通常合成に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//影の設定処理
int SetShadow(void)
{	
	int nCntShadow = -1;

	for (nCntShadow; nCntShadow < MAX_SHADOW; nCntShadow++)
	{		
		if (g_aShadow[nCntShadow].bUse == false && nCntShadow != -1)
		{
			break;
		}
	}	
	return nCntShadow;
}

//影の位置設定処理
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos)
{
	g_aShadow[nIdxShadow].pos = pos;
}