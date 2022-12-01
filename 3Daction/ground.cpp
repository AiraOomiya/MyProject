#include "ground.h"

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGround = NULL;
LPDIRECT3DTEXTURE9 g_pTextureGround = NULL;
D3DXVECTOR3 g_posGround;
D3DXVECTOR3 g_rotGround;
D3DXMATRIX g_mtxWorldGround; //���[���h�}�g���b�N�X

//�O���E���h�̏�����
void InitGround(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ground.jpg",	
		&g_pTextureGround);

	//�e��ϐ��̏�����
	g_posGround = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotGround = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_3D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffGround, NULL);
	//�|�C���^��ݒ�
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���W�ւ̃|�C���^���擾
	g_pVtxBuffGround->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-1500.0f, 0.0f, 1500.0f); //����[
	pVtx[1].pos = D3DXVECTOR3(1500.0f, 0.0f, 1500.0f); //�E��[
	pVtx[2].pos = D3DXVECTOR3(-1500.0f, 0.0f, -1500.0f); //�����[
	pVtx[3].pos = D3DXVECTOR3(1500.0f, 0.0f, -1500.0f); //�E���[

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
	g_pVtxBuffGround->Unlock();
}

//�O���E���h�̏I������
void UninitGround(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureGround != NULL)
	{
		g_pTextureGround->Release();
		g_pTextureGround = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffGround != NULL)
	{
		g_pVtxBuffGround->Release();
		g_pVtxBuffGround = NULL;
	}
}

//�O���E���h�̍X�V����
void UpdateGround(void)
{

}

//�O���E���h�̕`�揈��
void DrawGround(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldGround);

	//�����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotGround.y, g_rotGround.x, g_rotGround.z);
	D3DXMatrixMultiply(&g_mtxWorldGround, &g_mtxWorldGround, &mtxRot);

	//�ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, g_posGround.x, g_posGround.y, g_posGround.z);
	D3DXMatrixMultiply(&g_mtxWorldGround, &g_mtxWorldGround, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldGround);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffGround, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureGround);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}