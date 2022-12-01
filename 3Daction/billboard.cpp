//#include "billboard.h"
//
//#define MAX_BILLBOARD	(128)
//
////�O���[�o���ϐ�
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;
//LPDIRECT3DTEXTURE9 g_pTextureBillboard = NULL;
//D3DXVECTOR3 g_posBillboard;
//D3DXMATRIX g_mtxWorld; //���[���h�}�g���b�N�X
//Billboard g_Billboard[MAX_BILLBOARD];
//
//							 //�O���E���h�̏�����
//void InitBillboard(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//
//	//�e�N�X�`���̓ǂݍ���
//	D3DXCreateTextureFromFile(pDevice,
//		"data\\TEXTURE\\grass.jpg",
//		&g_pTextureBillboard);
//
//	//�e��ϐ��̏�����
//	g_posBillboard = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//	//���_�o�b�t�@�̐���
//	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_3D,
//		D3DPOOL_MANAGED,
//		&g_pVtxBuffBillboard, NULL);
//	//�|�C���^��ݒ�
//	VERTEX_3D*pVtx;
//
//	//���_�o�b�t�@�����b�N���A���_���W�ւ̃|�C���^���擾
//	g_pVtxBuffBillboard->Lock(0, 0, (void **)&pVtx, 0);
//
//	//���_���W�̐ݒ�
//	pVtx[0].pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f); //����[
//	pVtx[1].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f); //�E��[
//	pVtx[2].pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f); //�����[
//	pVtx[3].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f); //�E���[
//
//	//�@���x�N�g���̐ݒ�
//	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f); //����[
//	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f); //�E��[
//	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f); //�����[
//	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f); //�E���[
//
//	//���_�J���[�ݒ�
//	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255); //����[
//	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255); //�E��[
//	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255); //�����[
//	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255); //�E���[
//
//	//�e�N�X�`�����W�̐ݒ�
//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f); //����[
//	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f); //�E��[
//	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f); //�����[
//	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f); //�E���[
//
//	//���_�o�b�t�@���A�����b�N����
//	g_pVtxBuffBillboard->Unlock();
//}
//
////�O���E���h�̏I������
//void UninitBillboard(void)
//{
//	//�e�N�X�`���̔j��
//	if (g_pTextureBillboard != NULL)
//	{
//		g_pTextureBillboard->Release();
//		g_pTextureBillboard = NULL;
//	}
//
//	//���_�o�b�t�@�̔j��
//	if (g_pVtxBuffBillboard != NULL)
//	{
//		g_pVtxBuffBillboard->Release();
//		g_pVtxBuffBillboard = NULL;
//	}
//}
//
////�O���E���h�̍X�V����
//void UpdateBillboard(void)
//{
//
//}
//
////�e�̕`�揈��
//void DrawBillboard(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//	D3DXMATRIX mtxView, mtxTrans; //�v�Z�p�}�g���b�N�X	
//
//	//Z�e�X�g�𖳌��ɂ���
//	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
//	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
//
//
//
//	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
//	pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));
//
//	//���_�t�H�[�}�b�g�̐ݒ�
//	pDevice->SetFVF(FVF_VERTEX_3D);
//
//	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
//	{
//		if (g_Billboard[nCntBillboard].bUse == true)
//		{//�e���g�p����Ă���
//		 //���[���h�}�g���b�N�X�̏�����
//			D3DXMatrixIdentity(&g_mtxWorld);
//
//			//�r���[�}�g���b�N�X�̎擾
//			pDevice->GetTransform(D3DTS_VIEW, &mtxView);
//
//			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
//			D3DXMatrixInverse(&g_mtxWorld, NULL, &mtxView);//�t�s������߂�
//			g_mtxWorld._41 = 0.0f;
//			g_mtxWorld._42 = 0.0f;
//			g_mtxWorld._43 = 0.0f;
//
//			//�ʒu�̔��f			
//			D3DXMatrixTranslation(&mtxTrans, g_Billboard[nCntBillboard].pos.x, g_Billboard[nCntBillboard].pos.y, g_Billboard[nCntBillboard].pos.z);
//
//			D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxTrans);
//
//			//���[���h�}�g���b�N�X�̐ݒ�
//			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);
//
//			//�e�N�X�`���̐ݒ�
//			pDevice->SetTexture(0, g_pTextureBillboard);
//
//			//�|���S���̕`��
//			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBillboard * 4, 2);
//		}
//	}
//
//	//Z�e�X�g��L���ɂ���
//	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
//	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
//}