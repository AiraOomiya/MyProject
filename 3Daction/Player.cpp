#include "player.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"
#include "bullet.h"


#define LEFT (0.5f) //��
#define LEFT_UP (0.75f) //����
#define LEFT_DOWN (0.25f) //����
#define RIGHT (-0.5f) //�E
#define RIGHT_UP (-0.75f) //�E��
#define RIGHT_DOWN (-0.25f) //�E��
#define UP (1.0f) //��
#define DOWN (0.0f) //��

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturePlayer[10] = {}; //�e�N�X�`���ւ̃|�C���^
LPD3DXBUFFER g_pBuffPlayer = NULL; //�}�e���A���ւ̃|�C���^
D3DXVECTOR3 g_vtxMinPlayer, g_vtxMaxModel;//���f���̍ő�l�A�ŏ��l
D3DXMATRIX g_mtxWorldPlayer; //���[���h�}�g���b�N�X
LPD3DXMESH g_pMeshPlayer = NULL; //���b�V���ւ̃|�C���^
DWORD g_dwNumMatPlayer = 0; //�}�e���A���̐�
Player g_Player; //���f���̏��
int g_nIdxShadow = -1; //�Ώۂ̃C���f�b�N�X(�ԍ�)


//���f���̏�����
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	
	D3DXMATERIAL *pMat; //�}�e���A���f�[�^�ւ̃|�C���^
	int nNumVtx; //���_��
	DWORD dwSizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff; //���_�o�b�t�@�ւ̃|�C���^

	//�e��ϐ��̏�����
	g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\player.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffPlayer,
		NULL,
		&g_dwNumMatPlayer,
	    &g_pMeshPlayer);

	//���_���̎擾
	nNumVtx = g_pMeshPlayer->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshPlayer->GetFVF());

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//�e�N�X�`���̃t�@�C�������݂���			
		 //�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_pTexturePlayer[nCntMat]);
		}
	}

	//�e��ݒ�
	g_nIdxShadow = SetShadow();
}

//���f���̏I������
void UninitPlayer(void)
{
	//���b�V���̔j��
	if (g_pMeshPlayer != NULL)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}

	//�}�e���A���̔j��
	if (g_pBuffPlayer != NULL)
	{
		g_pBuffPlayer->Release();
		g_pBuffPlayer = NULL;
	}
}

//���f���̍X�V����
void UpdatePlayer(void)
{
	//�v���C���[�̈ʒu�X�V
	g_Player.posOld = g_Player.pos;

	//�ړ��ʂ̍X�V(����������)
	MovePlayer();

	//�e�̈ʒu�ݒ�
	SetPositionShadow(g_nIdxShadow, g_Player.pos);

	if (GetKeyboardRepeat(DIK_SPACE) == true)
	{//SPACE�L�[�������ꂽ
	 
	}


	if (GetKeyboardRepeat(DIK_LSHIFT) == true)
	{//LSHIFT�L�[�������ꂽ
	 
	}

	if (GetKeyboardRepeat(DIK_RETURN) == true)
	{//RETURN�L�[�������ꂽ
	 //�e�̐ݒ�
		SetBullet(g_Player.pos, D3DXVECTOR3(1.0f, 0.0f, 0.0f), 5, BULLETTYPE_MODEL);
		//PlaySound(SOUND_LABEL_SE_SHOT);
	}	
}

//�v���C���[�̈ړ�����
void MovePlayer(void)
{
	//�J�����̏��擾
	Camera *pCamera = GetCamera();

	if (GetKeyboardPress(DIK_A) == true)
	{//A�L�[�������ꂽ

		if (GetKeyboardPress(DIK_W) == true)
		{//����ړ�
			g_Player.pos.x += sinf((D3DX_PI * LEFT_UP + pCamera->rot.y) + g_Player.rot.y)*6.0f; //X���W
			g_Player.pos.z += cosf((D3DX_PI * LEFT_UP + pCamera->rot.y) + g_Player.rot.y)*6.0f; //Y���W
		}

		else if (GetKeyboardPress(DIK_S) == true)
		{//�����ړ�
			g_Player.pos.x += sinf((D3DX_PI * LEFT_DOWN + pCamera->rot.y) + g_Player.rot.y)*6.0f; //X���W
			g_Player.pos.z += cosf((D3DX_PI * LEFT_DOWN + pCamera->rot.y) + g_Player.rot.y)*6.0f; //Y���W
		}

		else
		{
			g_Player.pos.x += sinf((D3DX_PI * LEFT + pCamera->rot.y) + g_Player.rot.y)*6.0f; //X���W
			g_Player.pos.z += cosf((D3DX_PI * LEFT + pCamera->rot.y) + g_Player.rot.y)*6.0f; //Y���W
		}
	}

	else if (GetKeyboardPress(DIK_D) == true)
	{//D�L�[�������ꂽ								

		if (GetKeyboardPress(DIK_W) == true)
		{//	�E��ړ�							  
			g_Player.pos.x += sinf((D3DX_PI * RIGHT_UP + pCamera->rot.y) + g_Player.rot.y)*6.0f; //X���W
			g_Player.pos.z += cosf((D3DX_PI * RIGHT_UP + pCamera->rot.y) + g_Player.rot.y)*6.0f; //Y���W
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//�E���ړ�
			g_Player.pos.x += sinf((D3DX_PI * RIGHT_DOWN + pCamera->rot.y) + g_Player.rot.y)*6.0f; //X���W
			g_Player.pos.z += cosf((D3DX_PI * RIGHT_DOWN + pCamera->rot.y) + g_Player.rot.y)*6.0f; //Y���W
		}

		else
		{
			g_Player.pos.x += sinf((D3DX_PI * RIGHT + pCamera->rot.y) + g_Player.rot.y)*6.0f; //X���W
			g_Player.pos.z += cosf((D3DX_PI * RIGHT + pCamera->rot.y) + g_Player.rot.y)*6.0f; //Y���W
		}
	}

	else if (GetKeyboardPress(DIK_W) == true)
	{//W�L�[�������ꂽ
		g_Player.pos.x += sinf((D3DX_PI * UP + pCamera->rot.y) + g_Player.rot.y)*6.0f; //X���W
		g_Player.pos.z += cosf((D3DX_PI * UP + pCamera->rot.y) + g_Player.rot.y)*6.0f; //Y���W
	}

	else if (GetKeyboardPress(DIK_S) == true)
	{//S�L�[�������ꂽ
		g_Player.pos.x += sinf((D3DX_PI * DOWN + pCamera->rot.y) + g_Player.rot.y)*6.0f; //X���W
		g_Player.pos.z += cosf((D3DX_PI * DOWN + pCamera->rot.y) + g_Player.rot.y)*6.0f; //Y���W
	}

}

//���f���̕`�揈��
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef; //���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat; //�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldPlayer);

	//�����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxRot);

	//�ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPlayer);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePlayer[nCntMat]);

		//���f��(�p�[�c)�̕`��
		g_pMeshPlayer->DrawSubset(nCntMat);
	}
	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);	
}

//�v���C���[�̎擾
Player *GetPlayer(void)
{
	return &g_Player;
}