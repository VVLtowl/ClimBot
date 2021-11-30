//=============================================================================
//
// �����蔻�菈�� [collision.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "common.h"

#include "collision.h"
//#include "block.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �\���̒�`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************


//=============================================================================
// �����蔻�菈��
//=============================================================================
void UpdateCollision(void)
{
	//PLAYER_SW* playerSW = GetSWPlayer();
	//SWINGER_BASE* leftHand = playerSW->p_leftHand;
	//SWINGER_BASE* rightHand = playerSW->p_rightHand;
	//SWINGER_BASE* body = playerSW->p_body;

	////�e��enemy
	//{
	//	for (int i = 0; i < BULLET_MAX; i++)
	//	{
	//		BULLET* bullet = GetBullet(i);
	//		if (bullet->use)
	//		{
	//			for (int j = 0; j < ENEMY_MAX; j++)
	//			{
	//				ENEMY* enemy = GetEnemy(j);
	//				if (enemy->use)
	//				{
	//					D3DXVECTOR2 pos1 = bullet->obj.worldPos;
	//					D3DXVECTOR2 pos2 = enemy->obj.worldPos;
	//					float radius1 = bullet->obj.size.x / 2;
	//					float radius2 = enemy->obj.size.x / 2;
	//					if (CollisionBC(pos1, pos2, radius1, radius2))
	//					{
	//						//to do 
	//					}
	//				}
	//			}
	//		}
	//	}
	//}

	//// �U��q��enemy(��Q���Ƃ̏Ռ��e�X�g)
	//{
	//	for (int i = 0; i < ENEMY_MAX; i++)
	//	{
	//		ENEMY* enemy = GetEnemy(i);
	//		if (enemy->use)
	//		{

	//			for (int j = 0; j < MAX_SWINGER; j++)
	//			{
	//				SWINGER_BASE* swinger = GetSwinger(j);
	//				if (swinger->use)
	//				{
	//					D3DXVECTOR2 pos1 = swinger->obj.worldPos;
	//					D3DXVECTOR2 pos2 = enemy->obj.worldPos;
	//					float radius1 = swinger->obj.size.x / 2;
	//					float radius2 = enemy->obj.size.x / 2;
	//					if (CollisionBC(pos1, pos2, radius1, radius2))
	//					{
	//						//to do 
	//						break;
	//					}
	//				}
	//			}
	//		}
	//	}
	//}
	//// hand�U��q��block
	//{
	//	SetCanCatch(leftHand,nullptr,false);
	//	SetCanCatch(rightHand,nullptr,false);

	//	for (int y = 0; y < MAP_BLOCK_Y_NUM; y++)
	//	{
	//		for (int x = 0; x < MAP_BLOCK_X_NUM; x++)
	//		{
	//			BLOCK* block = GetBlock(y, x);
	//			if (block->use)
	//			{
	//				if (block->colType == BlockColType::circle)
	//				{
	//					//left hand
	//					D3DXVECTOR2 pos1 = leftHand->obj.worldPos;
	//					D3DXVECTOR2 pos2 = block->obj.worldPos;
	//					
	//					//edit by �t�W�^
	//					//D3DXVECTOR2 difference = pos2 - pos1;

	//					float radius1 = leftHand->obj.size.x/2;
	//					float radius2 = block->obj.size.x/2;
	//					if (CollisionBC(pos1, pos2, radius1, radius2))
	//					{
	//						SetCanCatch(leftHand, block, true);

	//						//edit by �t�W�^
	//						//edit by tou 
	//						//if (leftHand->isCatch)
	//						//{
	//						//	SetSwingerCenterPos(pos2);
	//						//}
	//							/*SetSWPlayerPos({ body->obj.worldPos + difference }, { rightHand->obj.worldPos + difference }, { pos2.x,pos2.y });*/
	//					}
	//					//right hand
	//					//difference = pos2 - pos1;

	//					pos1 = rightHand->obj.worldPos;
	//					radius1 = rightHand->obj.size.x/2;
	//					if (CollisionBC(pos1, pos2, radius1, radius2))
	//					{
	//						SetCanCatch(rightHand, block, true);

	//						//edit by �t�W�^
	//						//edit by tou 
	//						//if (rightHand->isCatch)
	//						//{
	//						//	SetSwingerCenterPos(pos2);
	//						//}
	//					}
	//				}
	//				else if (block->colType == BlockColType::box)
	//				{
	//					//left hand
	//					D3DXVECTOR2 pos1 = leftHand->obj.worldPos;
	//					D3DXVECTOR2 pos2 = block->obj.worldPos;
	//					D3DXVECTOR2 size1 = leftHand->obj.size;
	//					D3DXVECTOR2 size2 = block->obj.size;
	//					if (CollisionBB(pos1, pos2, size1, size2))
	//					{
	//						SetCanCatch(leftHand,block, true);
	//					}
	//					//right hand
	//					pos1 = rightHand->obj.worldPos;
	//					size1 = rightHand->obj.size;
	//					if (CollisionBB(pos1, pos2, size1, size2))
	//					{
	//						SetCanCatch(rightHand, block, true);
	//					}
	//				}
	//				else if (block->colType == BlockColType::capsule)
	//				{
	//					D3DXVECTOR2 pos1 = leftHand->obj.worldPos;
	//					float radius1 = leftHand->obj.size.x / 2;

	//					D3DXVECTOR2 pos2 = block->obj.worldPos;
	//					float radius2 = block->obj.size.y / 2;
	//					D3DXVECTOR2 recVec = block->rectVec;

	//					if (CollisionCsC(pos1, pos2, recVec, radius1, radius2))
	//					{
	//						SetCanCatch(leftHand, block, true);
	//						//if (leftHand->isCatch)
	//						//{
	//						//	AddBlockSonObj(y, x, &leftHand->obj);
	//						//}
	//						//else
	//						//{
	//						//	RemoveBlockSonObj(y, x, &leftHand->obj);
	//						//}
	//					}

	//					pos1 = rightHand->obj.worldPos;
	//					radius1 = rightHand->obj.size.x / 2;
	//					if (CollisionCsC(pos1, pos2, recVec, radius1, radius2))
	//					{
	//						SetCanCatch(rightHand, block, true);
	//						//if (rightHand->isCatch)
	//						//{
	//						//	AddBlockSonObj(y, x, &rightHand->obj);
	//						//}
	//						//else
	//						//{
	//						//	RemoveBlockSonObj(y, x, &rightHand->obj);
	//						//}
	//					}
	//				}
	//			}
	//		}
	//	}
	//}

}

//=============================================================================
// BB�ɂ�铖���蔻�菈��
// ��]�͍l�����Ȃ�
// �߂�l�F�������Ă���true
//=============================================================================
bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
	D3DXVECTOR2 min1, max1;
	D3DXVECTOR2 min2, max2;

	min1.x = pos1.x - size1.x / 2;
	min1.y = pos1.y - size1.y / 2;
	max1.x = pos1.x + size1.x / 2;
	max1.y = pos1.y + size1.y / 2;

	min2.x = pos2.x - size2.x / 2;
	min2.y = pos2.y - size2.y / 2;
	max2.x = pos2.x + size2.x / 2;
	max2.y = pos2.y + size2.y / 2;

	//X���̔���
	if (min1.x < max2.x && max1.x > min2.x)
	{
		//Y���̔���
		if (min1.y < max2.y && max1.y > min2.y)
		{
			//�S�Ă̏�����TRUE�Ȃ�q�b�g����
			return true;
		}
	}

	return false;
}

//=============================================================================
// BC�ɂ�铖���蔻�菈��
// �T�C�Y�͔��a
// �߂�l�F�������Ă���true
//=============================================================================
bool CollisionBC(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float radius1, float radius2)
{
	//pos1��pos2���Ȃ��x�N�g�������
	D3DXVECTOR2 vDistance = pos1 - pos2;

	//vDistance�̃x�N�g�����𓾂�
	float length;
//	length = D3DXVec2Length(&vDistance);
	length = D3DXVec2LengthSq(&vDistance);

//	float size = size1 + size2;
	float size = (radius1 + radius2) * (radius1 + radius2);

	//1��2�̔��a�𑫂��Ĕ��肷��
	//�����̃x�N�g�����̕������������
	//�q�b�g���Ă���
	if (length < size)
	{
		return true;
	}

	return false;
}

//=============================================================================
// BC�ɂ�铖���蔻�菈��
// �T�C�Y�͔��a
// �߂�l�FA��B�Ɠ������Ă���AA��B�̂ǂ�������ɂ��邱�ƁA
//         �������ĂȂ��Ȃ�-1
//=============================================================================
int CollisionBCDir4(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)//give up
{
	int direction=-1;//-1:no collision, 0:up, 1:right, 2:down, 3:left
	
	D3DXVECTOR2 min1, max1;
	D3DXVECTOR2 min2, max2;

	min1.x = pos1.x - size1.x / 2;
	min1.y = pos1.y - size1.y / 2;
	max1.x = pos1.x + size1.x / 2;
	max1.y = pos1.y + size1.y / 2;

	min2.x = pos2.x - size2.x / 2;
	min2.y = pos2.y - size2.y / 2;
	max2.x = pos2.x + size2.x / 2;
	max2.y = pos2.y + size2.y / 2;

	//X���̔���
	if (min1.x < max2.x && max1.x > min2.x)
	{
		//Y���̔���
		if (min1.y < max2.y && max1.y > min2.y)
		{
			//�S�Ă̏�����TRUE�Ȃ�q�b�g����
			float deltaX, deltaY;
			if (min1.x > min2.x)
			{
				deltaX = max2.x - min1.x;
			}
			else
			{
				deltaX = max1.x - min2.x;
			}
			if (min1.y > min2.y)
			{
				deltaY = max2.y - min1.y;
			}
			else
			{
				deltaY = max1.y - min2.y;
			}

			if (deltaX > deltaY)//up down col
			{
				if (pos1.y < pos2.y)
				{
					direction = 0;
				}
				else
				{
					direction = 2;
				}
			}
			else//left right col
			{
				if (pos1.x < pos2.x)
				{
					direction = 3;
				}
				else
				{
					direction = 1;
				}
			}
		}
	}

	//MyLog("col D$: %d \n",direction);
	return direction;
}
int CollisionBBDir4_2(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
	int direction = -1;//-1:no collision, 0:up, 1:right, 2:down, 3:left

	if (!CollisionBB(pos1, pos2, size1, size2))
	{
		return direction;
	}

	D3DXVECTOR2 pos2Up = { pos2.x,pos2.y - size2.y / 2 };
	D3DXVECTOR2 pos2Right = { pos2.x + size2.x / 2,pos2.y };
	D3DXVECTOR2 pos2Down = { pos2.x,pos2.y + size2.y / 2 };
	D3DXVECTOR2 pos2Left = { pos2.x - size2.x / 2,pos2.y };

	float ratio = size2.x / size2.y;

	float upDistance = powf((pos2Up.x - pos1.x)/ratio,2) + powf(pos2Up.y - pos1.y,2);
	float rightDistance = powf((pos2Right.x - pos1.x)/ratio,2) + powf(pos2Right.y - pos1.y,2);
	float downDistance = powf((pos2Down.x - pos1.x)/ratio,2) + powf(pos2Down.y - pos1.y,2);
	float leftDistance = powf((pos2Left.x - pos1.x)/ratio,2) + powf(pos2Left.y - pos1.y,2);

	float distance[4] = { upDistance,rightDistance,downDistance,leftDistance };
	
	int i = 0;
	direction = 0;
	while (true)
	{
		if (distance[i] < distance[direction])
		{
			direction = i;
		}

		i++;
		if (i == 4)
		{
			break;
		}
	}

	return direction;
}
//circle-capsule
bool CollisionCsC(D3DXVECTOR2 circlePos, D3DXVECTOR2 rectCirclePos, D3DXVECTOR2 rectCircleVec, float circleR, float rectCircleR)
{
	int nResult = false;
	float dx, dy; // �ʒu�̍��� 
	float t;
	float mx, my; // �ŏ��̋�����^������W 
	float ar; // 2 ���a�𑫂������� 
	float fDistSqr;
	dx = circlePos.x - rectCirclePos.x; // ���� 
	dy = circlePos.y - rectCirclePos.y; // ���� 
	t = (rectCircleVec.x * dx + rectCircleVec.y * dy) /
		(rectCircleVec.x * rectCircleVec.x + rectCircleVec.y * rectCircleVec.y);
	if (t < -0.5f)
	{
		t = -0.5f; // t �̉��� 
	}
	if (t > 0.5f)
	{
		t = 0.5f; // t �̏�� 
	}
	mx = rectCircleVec.x * t + rectCirclePos.x; // �ŏ��ʒu��^������W 
	my = rectCircleVec.y * t + rectCirclePos.y;
	// �����̂Q�� 
	fDistSqr = (mx - circlePos.x) * (mx - circlePos.x) + (my - circlePos.y)
		* (my - circlePos.y);
	ar = circleR + rectCircleR;
	if (fDistSqr < ar * ar) { // �Q��̂܂ܔ�r 
		nResult = true;
	}
	return nResult;
}