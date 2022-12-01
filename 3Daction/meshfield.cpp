#include "meshfield.h"

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;
LPDIRECT3DTEXTURE9 g_pTextureMeshField = NULL;
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;
D3DXVECTOR3 g_posMeshField;
D3DXVECTOR3 g_rotMeshField;
D3DXMATRIX g_mtxWorldMeshField; //���[���h�}�g���b�N�X

//���b�V���t�B�[���h�̏�����
void InitMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\grass.jpg",
		&g_pTextureMeshField);

	//�e��ϐ��̏�����
	g_posMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 9,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField, NULL);

	WORD *pIdx;

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(VERTEX_3D) * 14,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField, NULL);

	//�|�C���^��ݒ�
	VERTEX_3D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���W�ւ̃|�C���^���擾
	g_pVtxBuffMeshField->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-200.0f, 0.0f, 0.0f); //�����S
	pVtx[1].pos = D3DXVECTOR3(-200.0f, 0.0f, 400.0f); //����[
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�E���[
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 400.0f); //�E��[	
	pVtx[4].pos = D3DXVECTOR3(200.0f, 0.0f, 0.0f); //����[
	pVtx[5].pos = D3DXVECTOR3(200.0f, 0.0f, 400.0f); //�E��[
	pVtx[6].pos = D3DXVECTOR3(200.0f, 0.0f, 200.0f); //�����[
	pVtx[7].pos = D3DXVECTOR3(-200.0f, 0.0f, -200.0f); //�E���[
	pVtx[8].pos = D3DXVECTOR3(-200.0f, 0.0f, -200.0f); //����[



	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //����[
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //�E��[
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //�����[
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //�E���[
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //����[
	pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //�E��[
	pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //�����[
	pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //�E���[
	pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //����[


	//���_�J���[�ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255); //����[
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255); //�E��[
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255); //�����[
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255); //�E���[
	pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255); //����[
	pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255); //�E��[
	pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255); //�����[
	pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255); //�E���[
	pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255); //����[

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f); //����[
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f); //�E��[
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f); //�����[
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f); //�E���[
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f); //����[
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f); //�E��[
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f); //�����[
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f); //�E���[
	pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f); //����[

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshField->Unlock();

	//�C���f�b�N�X�o�b�t�@�����b�N���A���_���W�ւ̃|�C���^���擾
	g_pIdxBuffMeshField->Lock(0, 0, (void **)&pIdx, 0);

	//���_�ԍ��f�[�^�̐ݒ�
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

	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pIdxBuffMeshField->Unlock();
}	

//���b�V���t�B�[���h�̏I������
void UninitMeshfield(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//���b�V���t�B�[���h�̍X�V����
void UpdateMeshfield(void)
{

}

//���b�V���t�B�[���h�̕`�揈��
void DrawMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshField);

	//�����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshField.y, g_rotMeshField.x, g_rotMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxRot);

	//�ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshField.x, g_posMeshField.y, g_posMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshField);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshField);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 12);
}