#include "ground.h"

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGround = NULL;
LPDIRECT3DTEXTURE9 g_pTextureGround = NULL;
D3DXVECTOR3 g_posGround;
D3DXVECTOR3 g_rotGround;
D3DXMATRIX g_mtxWorldGround; //ワールドマトリックス

//グラウンドの初期化
void InitGround(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ground.jpg",	
		&g_pTextureGround);

	//各種変数の初期化
	g_posGround = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotGround = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_3D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffGround, NULL);
	//ポインタを設定
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点座標へのポインタを取得
	g_pVtxBuffGround->Lock(0, 0, (void **)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-1500.0f, 0.0f, 1500.0f); //左上端
	pVtx[1].pos = D3DXVECTOR3(1500.0f, 0.0f, 1500.0f); //右上端
	pVtx[2].pos = D3DXVECTOR3(-1500.0f, 0.0f, -1500.0f); //左下端
	pVtx[3].pos = D3DXVECTOR3(1500.0f, 0.0f, -1500.0f); //右下端

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
	g_pVtxBuffGround->Unlock();
}

//グラウンドの終了処理
void UninitGround(void)
{
	//テクスチャの破棄
	if (g_pTextureGround != NULL)
	{
		g_pTextureGround->Release();
		g_pTextureGround = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffGround != NULL)
	{
		g_pVtxBuffGround->Release();
		g_pVtxBuffGround = NULL;
	}
}

//グラウンドの更新処理
void UpdateGround(void)
{

}

//グラウンドの描画処理
void DrawGround(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldGround);

	//向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotGround.y, g_rotGround.x, g_rotGround.z);
	D3DXMatrixMultiply(&g_mtxWorldGround, &g_mtxWorldGround, &mtxRot);

	//位置の反映
	D3DXMatrixTranslation(&mtxTrans, g_posGround.x, g_posGround.y, g_posGround.z);
	D3DXMatrixMultiply(&g_mtxWorldGround, &g_mtxWorldGround, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldGround);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffGround, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureGround);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}