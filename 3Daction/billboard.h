#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"

//�e�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos; //�ʒu	
	bool bUse; //�e���g�p���Ă��邩�ǂ���
} Billboard;

//�v���g�^�C�v�錾
void InitBillboard(void); //����������
void UninitBillboard(void); //�I������
void UpdateBillboard(void); //�X�V����
void DrawBillboard(void); //�`�揈��

#endif
