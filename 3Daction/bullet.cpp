#include "main.h"
#include "bullet.h"
//#include "explosion.h"
//#include "enemy.h"
#include "player.h"
//#include "sound.h"


//マクロ定義
#define MAX_BULLET	(128) //弾の最大数

//void CollisionEnemy(Bullet *pBullet); //敵の状態(当たり判定)
//void CollisionPlayer(Bullet *pBullet); //プレイヤーの状態(当たり判定)

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL; //頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL; //テクスチャのポインタ
D3DXMATRIX g_mtxWorld; //ワールドマトリックス
Bullet g_aBullet[MAX_BULLET]; //弾の情報
float g_fLengthBullet; //対角線の長さ
float g_AngleBullet; //対角線の角度


//弾の初期化処理
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet; //ローカル変数

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, //
		"data\\texture\\bullet1.png",  //弾①
		&g_pTextureBullet);            //

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	//弾の情報の初期化処理
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //弾の発射位置
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //弾の移動量
		g_aBullet[nCntBullet].nLife = 100;//弾の寿命
		g_aBullet[nCntBullet].bUse = false; //使用していない状態にする		
	}

	//ポインタを設定
	VERTEX_3D *pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void **)&pVtx, 0);

	//対角線の長さを算出する
	g_fLengthBullet = sqrt(200.0f * 200.0f + 400.0f * 400.0f);

	//対角線の角度を算出する
	g_AngleBullet = atan2f(200.0f, 400.0f);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-2.5f, 5.0f, 0.0f); //左上端
		pVtx[1].pos = D3DXVECTOR3(+2.5f, 5.0f, 0.0f); //右上端
		pVtx[2].pos = D3DXVECTOR3(-2.5f, 0.0f, 0.0f); //左下端
		pVtx[3].pos = D3DXVECTOR3(+2.5f, 0.0f, 0.0f); //右下端
		
		//法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0f,1.0f,0.0f); //左上端
		pVtx[1].nor = D3DXVECTOR3(0.0f,1.0f,0.0f); //右上端
		pVtx[2].nor = D3DXVECTOR3(0.0f,1.0f,0.0f); //左下端
		pVtx[3].nor = D3DXVECTOR3(0.0f,1.0f,0.0f); //右下端

		//頂点カラー設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //左上端
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //右上端
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //左下端
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //右下端

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f); //左上端
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f); //右上端
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f); //左下端
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f); //右下端

		pVtx += 4; //頂点データのポインタを四つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//弾の終了処理
void UninitBullet(void)
{
	//テクスチャの破棄
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//弾の更新処理
void UpdateBullet(void)
{

	int nCntBullet; //ローカル変数

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//弾が使用されている
			//if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			//{//プレイヤーの弾
			// //敵と弾の当たり判定
			//	CollisionEnemy(&g_aBullet[nCntBullet]);
			//}
			//else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
			//{//敵の弾
			// //敵と弾の当たり判定
			//	CollisionPlayer(&g_aBullet[nCntBullet]);
			//}

			//弾の位置の更新
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;			

			//弾の寿命のカウントダウン
			g_aBullet[nCntBullet].nLife--; //体力の減少
			if (g_aBullet[nCntBullet].nLife <= 0)
			{
				//SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)); //爆発の設定
				g_aBullet[nCntBullet].bUse = false; //使用していない状態にする
			}
		}		
	}	
}



//弾の描画処理
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxTrans; //計算用マトリックス

	// アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 255);

	//Zテストを無効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//弾が使用されている
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorld);

			//ビューマトリックスの取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ポリゴンをカメラに対して正面に向ける
			D3DXMatrixInverse(&g_mtxWorld, NULL, &mtxView);//逆行列を求める
			g_mtxWorld._41 = 0.0f;
			g_mtxWorld._42 = 0.0f;
			g_mtxWorld._43 = 0.0f;

			//位置の反映			
			D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);

			D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBullet);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}
	}
	
	//Zテストを有効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// アルファテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}

//弾の設定処理
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, BULLETTYPE type)
{
	int nCntBullet; //ローカル変数

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{//弾が使用されていない
			g_aBullet[nCntBullet].pos = pos + D3DXVECTOR3(0.0f, 9.0f, 0.0f);

			g_aBullet[nCntBullet].move = move; //XYZ座標の位置			
			g_aBullet[nCntBullet].nLife = 100; //体力			
			g_aBullet[nCntBullet].bUse = true; //使用している状態にする			

			break;

		}
	}	
}

////敵の状態(当たり判定)
//void CollisionEnemy(Bullet *pBullet)
//{
//	Enemy *pEnemy = GetEnemy(); //敵のポインタ
//	int nCntEnemy; //ローカル変数
//
//	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
//	{
//		if (pEnemy->bUse == true)
//		{//敵が使用されている
//			if (pBullet->pos.x >= pEnemy->pos.x - 50.0f     //敵ポリゴンの左上端
//				&& pBullet->pos.x <= pEnemy->pos.x + 50.0f  //敵ポリゴンの右上端  
//				&& pBullet->pos.y >= pEnemy->pos.y - 50.0f  //敵ポリゴンの左下端
//				&& pBullet->pos.y <= pEnemy->pos.y + 50.0f) //敵ポリゴンの右下端
//			{//敵と弾が当たった
//			 //敵のヒット処理
//				HitEnemy(nCntEnemy, 1);
//				PlaySound(SOUND_LABEL_SE_HIT);
//				pBullet->bUse = false; //使用していない状態にする				
//			}
//		}
//	}
//}
//
////プレイヤーの状態(当たり判定)
//void CollisionPlayer(Bullet *pBullet)
//{
//	Player *pPlayer = GetPlayer(); //プレイヤーのポインタ
//	int nCntPlayer; //ローカル変数
//
//	for (nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++, pPlayer++)
//	{
//		if (pBullet->pos.x >= pPlayer->pos.x - 64.0f     //プレイヤーポリゴンの左上端
//			&& pBullet->pos.x <= pPlayer->pos.x + 64.0f	 //プレイヤーポリゴンの右上端
//			&& pBullet->pos.y >= pPlayer->pos.y - 64.0f	 //プレイヤーポリゴンの左下端
//			&& pBullet->pos.y <= pPlayer->pos.y + 64.0f) //プレイヤーポリゴンの右下端
//		{//プレイヤーと弾が当たった				
//		 //プレイヤーのヒット処理
//			HitPlayer(nCntPlayer, 1);
//			PlaySound(SOUND_LABEL_SE_HIT);
//			pBullet->bUse = false; //使用していない状態にする
//		}
//	}
//}