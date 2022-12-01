#include "light.h"

//�O���[�o���ϐ�
D3DLIGHT9 g_light;

//���C�g�̏�����
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 vecDir; //�ݒ�p�����x�N�g��

	//���C�g�̏����N���A����
	ZeroMemory(&g_light, sizeof(D3DLIGHT9));

	//���C�g�̎�ނ�ݒ�
	g_light.Type = D3DLIGHT_DIRECTIONAL;

	//���C�g�̊g�U����ݒ�
	g_light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���C�g�̕�����ݒ�
	vecDir = D3DXVECTOR3(-0.5f, -0.8f, 0.8f);
	D3DXVec3Normalize(&vecDir, &vecDir); //�x�N�g���𐳋K��
	g_light.Direction = vecDir;

	//���C�g��ݒ肷��
	pDevice->SetLight(0, &g_light);

	//���C�g��L���ɂ���
	pDevice->LightEnable(0, TRUE);
}

//���C�g�̏I������
void UninitLight(void)
{

}

//���C�g�̍X�V����
void UpdateLight(void)
{

}