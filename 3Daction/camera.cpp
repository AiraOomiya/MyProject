#include "camera.h"
#include "input.h"
#include "player.h"

#define LEFT (-0.5f) //��
#define LEFT_UP (-0.75f) //����
#define LEFT_DOWN (-0.25f) //����
#define RIGHT (0.5f) //�E
#define RIGHT_UP (0.75f) //�E��
#define RIGHT_DOWN (0.25f) //�E��
#define UP (-1.0f) //��
#define DOWN (1.0f) //��

//�O���[�o���ϐ�
Camera g_Camera;					//�J�����̏��
float  g_MaxDrawCamera = 2000.0f;	//�ő�`��͈�

//�J�����̏�����
void InitCamera(void) //����������
{
	g_Camera.posV = D3DXVECTOR3(0.0f, 400.0f, 0.0f);
	g_Camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	
	Player * pPlayer = GetPlayer();

	//���_
	g_Camera.posV.x = pPlayer->pos.x;
	g_Camera.posV.z = pPlayer->pos.z - 410;

	//�����_
	g_Camera.posR.x = pPlayer->pos.x;
	g_Camera.posR.z = pPlayer->pos.z;

	//���ꂼ��̈ʒu�̍������i�[����ϐ�
	float PosDiffX, PosDiffY, PosDiffZ;

	PosDiffX = pow(g_Camera.posR.x - g_Camera.posV.x, 2.0f);	//�Q��
	PosDiffY = pow(g_Camera.posR.y - g_Camera.posV.y, 2.0f);	//�Q��
	PosDiffZ = pow(g_Camera.posR.z - g_Camera.posV.z, 2.0f);	//�Q��

	//�����̎Z�o
	g_Camera.fLength = sqrtf(PosDiffX + PosDiffY + PosDiffZ);
}

//�J�����̏I������
void UninitCamera(void) //�I������
{
	
}

//�J�����̍X�V����
void UpdateCamera(void) //�X�V����
{
	Player * pPlayer = GetPlayer();

	//���_
	g_Camera.posV += pPlayer->pos - pPlayer->posOld;

	//�����_
	g_Camera.posR.x = pPlayer->pos.x;
	g_Camera.posR.z = pPlayer->pos.z;

	//���_�̏㉺
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

	//���_�̍��E
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


	//�����_�̏㉺
	if (GetKeyboardPress(DIK_Y) == true)
	{
		g_Camera.posR.y += 3.5f;
	}
	if (GetKeyboardPress(DIK_N) == true)
	{
		g_Camera.posR.y -= 3.5f;
	}
}


//�J�����̐ݒ菈��
void SetCamera(void) //�ݒ菈��
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera.mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjection, D3DXToRadian(45.0f),(float)SCREEN_WIDTH/(float)SCREEN_HEIGHT,10.0f, g_MaxDrawCamera);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_Camera.mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera.mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_Camera.mtxView, &g_Camera.posV, &g_Camera.posR, &g_Camera.vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_Camera.mtxView);
}

//�J�����̎擾
Camera *GetCamera(void)
{
	return &g_Camera;
}