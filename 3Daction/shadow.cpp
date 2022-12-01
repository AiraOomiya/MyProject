#include "shadow.h"
#include "player.h"

//�}�N����`
#define MAX_SHADOW	(256) //�e�̍ő吔

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;
Shadow g_aShadow[MAX_SHADOW]; //�e�̏��

//�e�̏�����
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\shadow000.jpg",
		&g_pTextureShadow);

	//�e��ϐ��̏�����
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_aShadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].mtxWorldShadow;
		g_aShadow[nCntShadow].bUse = false; //�g�p���Ă��Ȃ���Ԃɂ���		

	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow, NULL);

	//�|�C���^��ݒ�
	VERTEX_3D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���W�ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-10.0f, 0.0f, 10.0f); //����[
	pVtx[1].pos = D3DXVECTOR3(10.0f, 0.0f, 10.0f); //�E��[
	pVtx[2].pos = D3DXVECTOR3(-10.0f, 0.0f, -10.0f); //�����[
	pVtx[3].pos = D3DXVECTOR3(10.0f, 0.0f, -10.0f); //�E���[

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

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();
}

//�e�̏I������
void UninitShadow(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//�e�̍X�V����
void UpdateShadow(void)
{

}

//�e�̕`�揈��
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X

	//���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aShadow[nCntShadow].mtxWorldShadow);

		//�����̔��f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aShadow[nCntShadow].rot.x,g_aShadow[nCntShadow].rot.y,g_aShadow[nCntShadow].rot.z);
		D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorldShadow, &g_aShadow[nCntShadow].mtxWorldShadow, &mtxRot);

		//�ʒu�̔��f
		D3DXMatrixTranslation(&mtxTrans, g_aShadow[nCntShadow].pos.x, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z);
		D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorldShadow, &g_aShadow[nCntShadow].mtxWorldShadow, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aShadow[nCntShadow].mtxWorldShadow);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureShadow);

		//�e�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntShadow * 4, 2);
	}

	//�ʏ퍇���ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//�e�̐ݒ菈��
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

//�e�̈ʒu�ݒ菈��
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos)
{
	g_aShadow[nIdxShadow].pos = pos;
}