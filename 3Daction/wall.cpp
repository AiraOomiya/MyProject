#include "wall.h"
#include "player.h"

#define MAX_WALL	(4)

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;
LPDIRECT3DTEXTURE9		g_pTextureWall = NULL;
D3DXMATRIX				g_mtxWorldWall;				//ワールドマトリックス
Wall					g_aWall[MAX_WALL];			//壁の情報
float					g_GroundMoveX;				//地面を横に動かす

//壁の初期化
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\sokumen.png",
		&g_pTextureWall);		

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall, NULL);

	//壁を読み込む
	LoadWall();
	
	//ポインタを設定
	VERTEX_3D*pVtx;

	//頂点バッファをロックし、頂点座標へのポインタを取得
	g_pVtxBuffWall->Lock(0, 0, (void **)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++,pVtx += 4)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-g_aWall[nCntWall].fWidth, +g_aWall[nCntWall].fHeight, +g_aWall[nCntWall].fDepth); //左上端
		pVtx[1].pos = D3DXVECTOR3(+g_aWall[nCntWall].fWidth, +g_aWall[nCntWall].fHeight, -g_aWall[nCntWall].fDepth); //右上端
		pVtx[2].pos = D3DXVECTOR3(-g_aWall[nCntWall].fWidth, 0.0f, +g_aWall[nCntWall].fDepth); //左下端
		pVtx[3].pos = D3DXVECTOR3(+g_aWall[nCntWall].fWidth, 0.0f, -g_aWall[nCntWall].fDepth); //右下端

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
	}
	//頂点バッファをアンロックする
	g_pVtxBuffWall->Unlock();
}

//壁の終了処理
void UninitWall(void)
{
	//テクスチャの破棄
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//壁の更新処理
void UpdateWall(void)
{
	//ポインタを設定
	VERTEX_3D*pVtx;

	//頂点バッファをロックし、頂点座標へのポインタを取得
	g_pVtxBuffWall->Lock(0, 0, (void **)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_GroundMoveX = 1.0f;

		pVtx[0].tex.x = g_GroundMoveX;
		pVtx[1].tex.x = g_GroundMoveX + g_aWall[nCntWall].nSplitX;
		pVtx[2].tex.x = g_GroundMoveX;
		pVtx[3].tex.x = g_GroundMoveX + g_aWall[nCntWall].nSplitX;
		pVtx[0].tex.y = g_GroundMoveX;
		pVtx[1].tex.y = g_GroundMoveX;
		pVtx[2].tex.y = g_GroundMoveX + g_aWall[nCntWall].nSplitY;
		pVtx[3].tex.y = g_GroundMoveX + g_aWall[nCntWall].nSplitY;
	}
}

//壁の描画処理
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldWall);

			//向きの反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_mtxWorldWall, &g_mtxWorldWall, &mtxRot);

			//位置の反映
			D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldWall, &g_mtxWorldWall, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldWall);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureWall);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntWall * 4, 2);
		}		
	}
}

//ブロックを読み込む
void LoadWall(void)
{
	int nLetter = 0; //文字sw
	int nColumn = 0; //列
	int nLine = 0; //行
	char aData[100]; //文字列

	FILE *pFile; //ファイルポインタ

	//ポインタを設定
	VERTEX_3D *pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffWall->Lock(0, 0, (void **)&pVtx, 0);

	//バッファの初期化
	memset(aData, 0, sizeof(aData));

	//ファイルを開く
	pFile = fopen("data/CSV/Wall.csv", "r");

	if (pFile != NULL)
	{//ファイルが開けた場合

		//ファイルから一文字ずつ読み込む
		while (fgetc(pFile) != '\n');

		while (nLetter != EOF)
		{
			while (1)
			{//一列の文字列を作る
				nLetter = fgetc(pFile);

				if (nLetter == EOF)
				{
					break;
				}

				if (nLetter != '\n'&& nLetter != ',')
				{
					//カンマor改行出なければ文字をつなぐ
					strcat(aData, (const char*)&nLetter);
				}
				else
				{
					break;
				}
			}

			switch (nColumn)
			{
			case 0:
				g_aWall[nLine].nType = atoi(aData);
				break;

			case 1:
				g_aWall[nLine].rot.x = atof(aData) / 100.0f;
				break;

			case 2:
				g_aWall[nLine].rot.y = atof(aData) / 100.0f;
				break;

			case 3:
				g_aWall[nLine].rot.z = atof(aData) / 100.0f;
				break;

			case 4:
				g_aWall[nLine].fWidth = atof(aData);
				break;

			case 5:
				g_aWall[nLine].fHeight = atof(aData);
				break;			

			case 6:
				g_aWall[nLine].nSplitX = atoi(aData);
				break;

			case 7:
				g_aWall[nLine].nSplitY = atoi(aData);
				break;

			case 8:
				g_aWall[nLine].pos.x = atof(aData);
				break;
					
			case 9:
				g_aWall[nLine].pos.y = atof(aData);
				break;				   
									   
			case 10:				   
				g_aWall[nLine].pos.z = atof(aData);
				break;
			}

			//バッファの初期化
			memset(aData, 0, sizeof(aData));

			//列数を足す
			nColumn++;

			if (nLetter == '\n')
			{//読み込んだ文字が改行だった時、
				// 使用している状態にする
				g_aWall[nLine].bUse = true;

				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(- g_aWall[nLine].fWidth,+ g_aWall[nLine].fHeight,+ g_aWall[nLine].fDepth); //左上端
				pVtx[1].pos = D3DXVECTOR3(+ g_aWall[nLine].fWidth,+ g_aWall[nLine].fHeight,- g_aWall[nLine].fDepth); //右上端
				pVtx[2].pos = D3DXVECTOR3(- g_aWall[nLine].fWidth, 0.0f,+ g_aWall[nLine].fDepth); //左下端
				pVtx[3].pos = D3DXVECTOR3(+ g_aWall[nLine].fWidth, 0.0f,- g_aWall[nLine].fDepth); //右下端

				pVtx += 4;
				
				//列数を初期化して行数を増やす
				nColumn = 0;
				nLine++;
			}
		}

		//ファイルを閉じる
		fclose(pFile);
	}

	//頂点バッファをアンロックする
	g_pVtxBuffWall->Unlock();
}

//壁との当たり判定
bool CollisionWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight)
{
	Player *pPlayer = GetPlayer();
	bool bCollision = false;

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == true)
		{//ブロックが使用されている
			if (pPos->x + (fWidth / 2) >= g_aWall[nCntWall].pos.x - (g_aWall[nCntWall].fWidth / 2)
				&& pPos->x - (fWidth / 2) <= g_aWall[nCntWall].pos.x + (g_aWall[nCntWall].fWidth / 2)
				&& pPos->z + (fHeight / 2) >= g_aWall[nCntWall].pos.z - (g_aWall[nCntWall].fHeight / 2)
				&& pPos->z - (fHeight / 2) <= g_aWall[nCntWall].pos.z + (g_aWall[nCntWall].fHeight / 2))
			{
				if (pPosOld->z - (fHeight / 2) <= g_aWall[nCntWall].pos.z - (g_aWall[nCntWall].fHeight / 2)
					&& pPos->z + (fHeight / 2) >= g_aWall[nCntWall].pos.z + (g_aWall[nCntWall].fHeight / 2))
				{//上壁
						
				}

				else if (pPosOld->z + (fHeight / 2) >= g_aWall[nCntWall].pos.z + (g_aWall[nCntWall].fHeight / 2)
					&& pPos->z - (fHeight / 2) <= g_aWall[nCntWall].pos.z - (g_aWall[nCntWall].fHeight / 2))
				{//下壁
						
				}

				if (pPosOld->x + (fWidth / 2) <= g_aWall[nCntWall].pos.x - (g_aWall[nCntWall].fWidth / 2)
					&& pPos->x + (fWidth / 2) >= g_aWall[nCntWall].pos.x - (g_aWall[nCntWall].fWidth / 2))
				{//左壁
					
				}

				else if (pPosOld->x - (fWidth / 2) >= g_aWall[nCntWall].pos.x + (g_aWall[nCntWall].fWidth / 2)
					&& pPos->x - (fWidth / 2) <= g_aWall[nCntWall].pos.x + (g_aWall[nCntWall].fWidth / 2))
				{//右壁
					
				}
			}
		}
	}

	return bCollision;
}