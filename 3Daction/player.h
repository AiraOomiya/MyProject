#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//�v���C���[�̍\����
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	bool bJump;
	bool bUse;	
} Player;

//�v���g�^�C�v�錾
void InitPlayer(void);		//����������
void UninitPlayer(void);	//�I������
void UpdatePlayer(void);	//�X�V����
void DrawPlayer(void);		//�`�揈��
Player * GetPlayer(void);	//�J�����̎擾
void MovePlayer(void);		//�v���C���[�̈ړ�����


#endif
