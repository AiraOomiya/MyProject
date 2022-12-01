#include "main.h"
#include "bullet.h"
//#include "explosion.h"
//#include "enemy.h"
#include "player.h"
//#include "sound.h"


//�}�N����`
#define MAX_BULLET	(128) //�e�̍ő吔

//void CollisionEnemy(Bullet *pBullet); //�G�̏��(�����蔻��)
//void CollisionPlayer(Bullet *pBullet); //�v���C���[�̏��(�����蔻��)

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL; //���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL; //�e�N�X�`���̃|�C���^
D3DXMATRIX g_mtxWorld; //���[���h�}�g���b�N�X
Bullet g_aBullet[MAX_BULLET]; //�e�̏��
float g_fLengthBullet; //�Ίp���̒���
float g_AngleBullet; //�Ίp���̊p�x


//�e�̏���������
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet; //���[�J���ϐ�

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, //
		"data\\texture\\bullet1.png",  //�e�@
		&g_pTextureBullet);            //

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	//�e�̏��̏���������
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�e�̔��ˈʒu
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�e�̈ړ���
		g_aBullet[nCntBullet].nLife = 100;//�e�̎���
		g_aBullet[nCntBullet].bUse = false; //�g�p���Ă��Ȃ���Ԃɂ���		
	}

	//�|�C���^��ݒ�
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void **)&pVtx, 0);

	//�Ίp���̒������Z�o����
	g_fLengthBullet = sqrt(200.0f * 200.0f + 400.0f * 400.0f);

	//�Ίp���̊p�x���Z�o����
	g_AngleBullet = atan2f(200.0f, 400.0f);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-2.5f, 5.0f, 0.0f); //����[
		pVtx[1].pos = D3DXVECTOR3(+2.5f, 5.0f, 0.0f); //�E��[
		pVtx[2].pos = D3DXVECTOR3(-2.5f, 0.0f, 0.0f); //�����[
		pVtx[3].pos = D3DXVECTOR3(+2.5f, 0.0f, 0.0f); //�E���[
		
		//�@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f,1.0f,0.0f); //����[
		pVtx[1].nor = D3DXVECTOR3(0.0f,1.0f,0.0f); //�E��[
		pVtx[2].nor = D3DXVECTOR3(0.0f,1.0f,0.0f); //�����[
		pVtx[3].nor = D3DXVECTOR3(0.0f,1.0f,0.0f); //�E���[

		//���_�J���[�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //����[
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //�E��[
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //�����[
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //�E���[

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f); //����[
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f); //�E��[
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f); //�����[
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f); //�E���[

		pVtx += 4; //���_�f�[�^�̃|�C���^���l���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//�e�̏I������
void UninitBullet(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//�e�̍X�V����
void UpdateBullet(void)
{

	int nCntBullet; //���[�J���ϐ�

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//�e���g�p����Ă���
			//if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			//{//�v���C���[�̒e
			// //�G�ƒe�̓����蔻��
			//	CollisionEnemy(&g_aBullet[nCntBullet]);
			//}
			//else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
			//{//�G�̒e
			// //�G�ƒe�̓����蔻��
			//	CollisionPlayer(&g_aBullet[nCntBullet]);
			//}

			//�e�̈ʒu�̍X�V
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;			

			//�e�̎����̃J�E���g�_�E��
			g_aBullet[nCntBullet].nLife--; //�̗͂̌���
			if (g_aBullet[nCntBullet].nLife <= 0)
			{
				//SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)); //�����̐ݒ�
				g_aBullet[nCntBullet].bUse = false; //�g�p���Ă��Ȃ���Ԃɂ���
			}
		}		
	}	
}



//�e�̕`�揈��
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxTrans; //�v�Z�p�}�g���b�N�X

	// �A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 255);

	//Z�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//�e���g�p����Ă���
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorld);

			//�r���[�}�g���b�N�X�̎擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&g_mtxWorld, NULL, &mtxView);//�t�s������߂�
			g_mtxWorld._41 = 0.0f;
			g_mtxWorld._42 = 0.0f;
			g_mtxWorld._43 = 0.0f;

			//�ʒu�̔��f			
			D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);

			D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBullet);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}
	}
	
	//Z�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// �A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}

//�e�̐ݒ菈��
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, BULLETTYPE type)
{
	int nCntBullet; //���[�J���ϐ�

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{//�e���g�p����Ă��Ȃ�
			g_aBullet[nCntBullet].pos = pos + D3DXVECTOR3(0.0f, 9.0f, 0.0f);

			g_aBullet[nCntBullet].move = move; //XYZ���W�̈ʒu			
			g_aBullet[nCntBullet].nLife = 100; //�̗�			
			g_aBullet[nCntBullet].bUse = true; //�g�p���Ă����Ԃɂ���			

			break;

		}
	}	
}

////�G�̏��(�����蔻��)
//void CollisionEnemy(Bullet *pBullet)
//{
//	Enemy *pEnemy = GetEnemy(); //�G�̃|�C���^
//	int nCntEnemy; //���[�J���ϐ�
//
//	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
//	{
//		if (pEnemy->bUse == true)
//		{//�G���g�p����Ă���
//			if (pBullet->pos.x >= pEnemy->pos.x - 50.0f     //�G�|���S���̍���[
//				&& pBullet->pos.x <= pEnemy->pos.x + 50.0f  //�G�|���S���̉E��[  
//				&& pBullet->pos.y >= pEnemy->pos.y - 50.0f  //�G�|���S���̍����[
//				&& pBullet->pos.y <= pEnemy->pos.y + 50.0f) //�G�|���S���̉E���[
//			{//�G�ƒe����������
//			 //�G�̃q�b�g����
//				HitEnemy(nCntEnemy, 1);
//				PlaySound(SOUND_LABEL_SE_HIT);
//				pBullet->bUse = false; //�g�p���Ă��Ȃ���Ԃɂ���				
//			}
//		}
//	}
//}
//
////�v���C���[�̏��(�����蔻��)
//void CollisionPlayer(Bullet *pBullet)
//{
//	Player *pPlayer = GetPlayer(); //�v���C���[�̃|�C���^
//	int nCntPlayer; //���[�J���ϐ�
//
//	for (nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++, pPlayer++)
//	{
//		if (pBullet->pos.x >= pPlayer->pos.x - 64.0f     //�v���C���[�|���S���̍���[
//			&& pBullet->pos.x <= pPlayer->pos.x + 64.0f	 //�v���C���[�|���S���̉E��[
//			&& pBullet->pos.y >= pPlayer->pos.y - 64.0f	 //�v���C���[�|���S���̍����[
//			&& pBullet->pos.y <= pPlayer->pos.y + 64.0f) //�v���C���[�|���S���̉E���[
//		{//�v���C���[�ƒe����������				
//		 //�v���C���[�̃q�b�g����
//			HitPlayer(nCntPlayer, 1);
//			PlaySound(SOUND_LABEL_SE_HIT);
//			pBullet->bUse = false; //�g�p���Ă��Ȃ���Ԃɂ���
//		}
//	}
//}