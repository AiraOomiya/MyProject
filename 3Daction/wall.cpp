#include "wall.h"
#include "player.h"

#define MAX_WALL	(4)

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;
LPDIRECT3DTEXTURE9		g_pTextureWall = NULL;
D3DXMATRIX				g_mtxWorldWall;				//���[���h�}�g���b�N�X
Wall					g_aWall[MAX_WALL];			//�ǂ̏��
float					g_GroundMoveX;				//�n�ʂ����ɓ�����

//�ǂ̏�����
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\sokumen.png",
		&g_pTextureWall);		

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall, NULL);

	//�ǂ�ǂݍ���
	LoadWall();
	
	//�|�C���^��ݒ�
	VERTEX_3D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���W�ւ̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void **)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++,pVtx += 4)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-g_aWall[nCntWall].fWidth, +g_aWall[nCntWall].fHeight, +g_aWall[nCntWall].fDepth); //����[
		pVtx[1].pos = D3DXVECTOR3(+g_aWall[nCntWall].fWidth, +g_aWall[nCntWall].fHeight, -g_aWall[nCntWall].fDepth); //�E��[
		pVtx[2].pos = D3DXVECTOR3(-g_aWall[nCntWall].fWidth, 0.0f, +g_aWall[nCntWall].fDepth); //�����[
		pVtx[3].pos = D3DXVECTOR3(+g_aWall[nCntWall].fWidth, 0.0f, -g_aWall[nCntWall].fDepth); //�E���[

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //����[
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //�E��[
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //�����[
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //�E���[

		//���_�J���[�ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255); //����[
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255); //�E��[
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255); //�����[
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255); //�E���[

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f); //����[
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f); //�E��[
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f); //�����[
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f); //�E���[
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWall->Unlock();
}

//�ǂ̏I������
void UninitWall(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//�ǂ̍X�V����
void UpdateWall(void)
{
	//�|�C���^��ݒ�
	VERTEX_3D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���W�ւ̃|�C���^���擾
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

//�ǂ̕`�揈��
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldWall);

			//�����̔��f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_mtxWorldWall, &g_mtxWorldWall, &mtxRot);

			//�ʒu�̔��f
			D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldWall, &g_mtxWorldWall, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldWall);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureWall);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntWall * 4, 2);
		}		
	}
}

//�u���b�N��ǂݍ���
void LoadWall(void)
{
	int nLetter = 0; //����sw
	int nColumn = 0; //��
	int nLine = 0; //�s
	char aData[100]; //������

	FILE *pFile; //�t�@�C���|�C���^

	//�|�C���^��ݒ�
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void **)&pVtx, 0);

	//�o�b�t�@�̏�����
	memset(aData, 0, sizeof(aData));

	//�t�@�C�����J��
	pFile = fopen("data/CSV/Wall.csv", "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

		//�t�@�C������ꕶ�����ǂݍ���
		while (fgetc(pFile) != '\n');

		while (nLetter != EOF)
		{
			while (1)
			{//���̕���������
				nLetter = fgetc(pFile);

				if (nLetter == EOF)
				{
					break;
				}

				if (nLetter != '\n'&& nLetter != ',')
				{
					//�J���}or���s�o�Ȃ���Ε������Ȃ�
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

			//�o�b�t�@�̏�����
			memset(aData, 0, sizeof(aData));

			//�񐔂𑫂�
			nColumn++;

			if (nLetter == '\n')
			{//�ǂݍ��񂾕��������s���������A
				// �g�p���Ă����Ԃɂ���
				g_aWall[nLine].bUse = true;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(- g_aWall[nLine].fWidth,+ g_aWall[nLine].fHeight,+ g_aWall[nLine].fDepth); //����[
				pVtx[1].pos = D3DXVECTOR3(+ g_aWall[nLine].fWidth,+ g_aWall[nLine].fHeight,- g_aWall[nLine].fDepth); //�E��[
				pVtx[2].pos = D3DXVECTOR3(- g_aWall[nLine].fWidth, 0.0f,+ g_aWall[nLine].fDepth); //�����[
				pVtx[3].pos = D3DXVECTOR3(+ g_aWall[nLine].fWidth, 0.0f,- g_aWall[nLine].fDepth); //�E���[

				pVtx += 4;
				
				//�񐔂����������čs���𑝂₷
				nColumn = 0;
				nLine++;
			}
		}

		//�t�@�C�������
		fclose(pFile);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWall->Unlock();
}

//�ǂƂ̓����蔻��
bool CollisionWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight)
{
	Player *pPlayer = GetPlayer();
	bool bCollision = false;

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == true)
		{//�u���b�N���g�p����Ă���
			if (pPos->x + (fWidth / 2) >= g_aWall[nCntWall].pos.x - (g_aWall[nCntWall].fWidth / 2)
				&& pPos->x - (fWidth / 2) <= g_aWall[nCntWall].pos.x + (g_aWall[nCntWall].fWidth / 2)
				&& pPos->z + (fHeight / 2) >= g_aWall[nCntWall].pos.z - (g_aWall[nCntWall].fHeight / 2)
				&& pPos->z - (fHeight / 2) <= g_aWall[nCntWall].pos.z + (g_aWall[nCntWall].fHeight / 2))
			{
				if (pPosOld->z - (fHeight / 2) <= g_aWall[nCntWall].pos.z - (g_aWall[nCntWall].fHeight / 2)
					&& pPos->z + (fHeight / 2) >= g_aWall[nCntWall].pos.z + (g_aWall[nCntWall].fHeight / 2))
				{//���
						
				}

				else if (pPosOld->z + (fHeight / 2) >= g_aWall[nCntWall].pos.z + (g_aWall[nCntWall].fHeight / 2)
					&& pPos->z - (fHeight / 2) <= g_aWall[nCntWall].pos.z - (g_aWall[nCntWall].fHeight / 2))
				{//����
						
				}

				if (pPosOld->x + (fWidth / 2) <= g_aWall[nCntWall].pos.x - (g_aWall[nCntWall].fWidth / 2)
					&& pPos->x + (fWidth / 2) >= g_aWall[nCntWall].pos.x - (g_aWall[nCntWall].fWidth / 2))
				{//����
					
				}

				else if (pPosOld->x - (fWidth / 2) >= g_aWall[nCntWall].pos.x + (g_aWall[nCntWall].fWidth / 2)
					&& pPos->x - (fWidth / 2) <= g_aWall[nCntWall].pos.x + (g_aWall[nCntWall].fWidth / 2))
				{//�E��
					
				}
			}
		}
	}

	return bCollision;
}