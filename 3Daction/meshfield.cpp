#include "meshfield.h"

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;
LPDIRECT3DTEXTURE9 g_pTextureMeshField = NULL;
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;
D3DXVECTOR3 g_posMeshField;
D3DXVECTOR3 g_rotMeshField;
D3DXMATRIX g_mtxWorldMeshField; //ワールドマトリックス

//メッシュフィールドの初期化
void InitMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\grass.jpg",
		&g_pTextureMeshField);

	//各種変数の初期化
	g_posMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 9,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField, NULL);

	WORD *pIdx;

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(VERTEX_3D) * 14,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField, NULL);

	//ポインタを設定
	VERTEX_3D*pVtx;

	//頂点バッファをロックし、頂点座標へのポインタを取得
	g_pVtxBuffMeshField->Lock(0, 0, (void **)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-200.0f, 0.0f, 0.0f); //左中心
	pVtx[1].pos = D3DXVECTOR3(-200.0f, 0.0f, 400.0f); //左上端
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //右下端
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 400.0f); //右上端	
	pVtx[4].pos = D3DXVECTOR3(200.0f, 0.0f, 0.0f); //左上端
	pVtx[5].pos = D3DXVECTOR3(200.0f, 0.0f, 400.0f); //右上端
	pVtx[6].pos = D3DXVECTOR3(200.0f, 0.0f, 200.0f); //左下端
	pVtx[7].pos = D3DXVECTOR3(-200.0f, 0.0f, -200.0f); //右下端
	pVtx[8].pos = D3DXVECTOR3(-200.0f, 0.0f, -200.0f); //左上端



	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //左上端
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //右上端
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //左下端
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //右下端
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //左上端
	pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //右上端
	pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //左下端
	pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //右下端
	pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //左上端


	//頂点カラー設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255); //左上端
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255); //右上端
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255); //左下端
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255); //右下端
	pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255); //左上端
	pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255); //右上端
	pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255); //左下端
	pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255); //右下端
	pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255); //左上端

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f); //左上端
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f); //右上端
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f); //左下端
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f); //右下端
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f); //左上端
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f); //右上端
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f); //左下端
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f); //右下端
	pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f); //左上端

	//頂点バッファをアンロックする
	g_pVtxBuffMeshField->Unlock();

	//インデックスバッファをロックし、頂点座標へのポインタを取得
	g_pIdxBuffMeshField->Lock(0, 0, (void **)&pIdx, 0);

	//頂点番号データの設定
	pIdx[0] = 3;
	pIdx[1] = 0;
	pIdx[2] = 4;
	pIdx[3] = 1;
	pIdx[4] = 5;
	pIdx[5] = 2;
	pIdx[6] = 2;
	pIdx[7] = 6;
	pIdx[8] = 6;
	pIdx[9] = 3;
	pIdx[10] = 7;
	pIdx[11] = 4;
	pIdx[12] = 8;
	pIdx[13] = 5;

	//インデックスバッファをアンロックする
	g_pIdxBuffMeshField->Unlock();
}	

//メッシュフィールドの終了処理
void UninitMeshfield(void)
{
	//テクスチャの破棄
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}

	//インデックスバッファの破棄
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//メッシュフィールドの更新処理
void UpdateMeshfield(void)
{

}

//メッシュフィールドの描画処理
void DrawMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldMeshField);

	//向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshField.y, g_rotMeshField.x, g_rotMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxRot);

	//位置の反映
	D3DXMatrixTranslation(&mtxTrans, g_posMeshField.x, g_posMeshField.y, g_posMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshField);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMeshField);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 12);
}