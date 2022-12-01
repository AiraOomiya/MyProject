#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//�e�̎��
typedef enum
{
	BULLETTYPE_MODEL = 0, //�v���C���[�̒e
	BULLETTYPE_ENEMY, //�G�̒e
	BULLETTYPE_MAX,
} BULLETTYPE;

//�e�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos; //�e�̔��ˈʒu
	D3DXVECTOR3 move; //�e�̈ړ���	
	int nLife; //�e�̎���	
	bool bUse; //�e���g�p���Ă��邩�ǂ���
} Bullet;

//�v���g�^�C�v�錾
void InitBullet(void); //����������
void UninitBullet(void); //�I������
void UpdateBullet(void); //�X�V����
void DrawBullet(void); //�`�揈��
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, BULLETTYPE type); //�e�̐ݒ菈��



#endif

