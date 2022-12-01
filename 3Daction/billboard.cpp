//#include "billboard.h"
//
//#define MAX_BILLBOARD	(128)
//
////グローバル変数
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;
//LPDIRECT3DTEXTURE9 g_pTextureBillboard = NULL;
//D3DXVECTOR3 g_posBillboard;
//D3DXMATRIX g_mtxWorld; //ワールドマトリックス
//Billboard g_Billboard[MAX_BILLBOARD];
//
//							 //グラウンドの初期化
//void InitBillboard(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//
//	//テクスチャの読み込み
//	D3DXCreateTextureFromFile(pDevice,
//		"data\\TEXTURE\\grass.jpg",
//		&g_pTextureBillboard);
//
//	//各種変数の初期化
//	g_posBillboard = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//	//頂点バッファの生成
//	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_3D,
//		D3DPOOL_MANAGED,
//		&g_pVtxBuffBillboard, NULL);
//	//ポインタを設定
//	VERTEX_3D*pVtx;
//
//	//頂点バッファをロックし、頂点座標へのポインタを取得
//	g_pVtxBuffBillboard->Lock(0, 0, (void **)&pVtx, 0);
//
//	//頂点座標の設定
//	pVtx[0].pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f); //左上端
//	pVtx[1].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f); //右上端
//	pVtx[2].pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f); //左下端
//	pVtx[3].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f); //右下端
//
//	//法線ベクトルの設定
//	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f); //左上端
//	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f); //右上端
//	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f); //左下端
//	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f); //右下端
//
//	//頂点カラー設定
//	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255); //左上端
//	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255); //右上端
//	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255); //左下端
//	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255); //右下端
//
//	//テクスチャ座標の設定
//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f); //左上端
//	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f); //右上端
//	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f); //左下端
//	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f); //右下端
//
//	//頂点バッファをアンロックする
//	g_pVtxBuffBillboard->Unlock();
//}
//
////グラウンドの終了処理
//void UninitBillboard(void)
//{
//	//テクスチャの破棄
//	if (g_pTextureBillboard != NULL)
//	{
//		g_pTextureBillboard->Release();
//		g_pTextureBillboard = NULL;
//	}
//
//	//頂点バッファの破棄
//	if (g_pVtxBuffBillboard != NULL)
//	{
//		g_pVtxBuffBillboard->Release();
//		g_pVtxBuffBillboard = NULL;
//	}
//}
//
////グラウンドの更新処理
//void UpdateBillboard(void)
//{
//
//}
//
////弾の描画処理
//void DrawBillboard(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//	D3DXMATRIX mtxView, mtxTrans; //計算用マトリックス	
//
//	//Zテストを無効にする
//	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
//	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
//
//
//
//	//頂点バッファをデータストリームに設定
//	pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));
//
//	//頂点フォーマットの設定
//	pDevice->SetFVF(FVF_VERTEX_3D);
//
//	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
//	{
//		if (g_Billboard[nCntBillboard].bUse == true)
//		{//弾が使用されている
//		 //ワールドマトリックスの初期化
//			D3DXMatrixIdentity(&g_mtxWorld);
//
//			//ビューマトリックスの取得
//			pDevice->GetTransform(D3DTS_VIEW, &mtxView);
//
//			//ポリゴンをカメラに対して正面に向ける
//			D3DXMatrixInverse(&g_mtxWorld, NULL, &mtxView);//逆行列を求める
//			g_mtxWorld._41 = 0.0f;
//			g_mtxWorld._42 = 0.0f;
//			g_mtxWorld._43 = 0.0f;
//
//			//位置の反映			
//			D3DXMatrixTranslation(&mtxTrans, g_Billboard[nCntBillboard].pos.x, g_Billboard[nCntBillboard].pos.y, g_Billboard[nCntBillboard].pos.z);
//
//			D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxTrans);
//
//			//ワールドマトリックスの設定
//			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);
//
//			//テクスチャの設定
//			pDevice->SetTexture(0, g_pTextureBillboard);
//
//			//ポリゴンの描画
//			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBillboard * 4, 2);
//		}
//	}
//
//	//Zテストを有効にする
//	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
//	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
//}