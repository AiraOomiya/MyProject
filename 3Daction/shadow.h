#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

//�e�\����
typedef struct
{
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 rot =D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMATRIX mtxWorldShadow; //���[���h�}�g���b�N�X
	bool bUse; //�e���g�p���Ă��邩�ǂ���
} Shadow;

//�v���g�^�C�v�錾
void InitShadow(void); //����������
void UninitShadow(void); //�I������
void UpdateShadow(void); //�X�V����
void DrawShadow(void); //�`�揈��
int SetShadow(void); //�ݒ菈��
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos); //�ʒu�ݒ菈��

#endif