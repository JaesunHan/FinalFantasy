#include "stdafx.h"
#include "guard.h"


guard::guard()
{
	//���ʹ� �̹���
	//IMAGEMANAGER->addFrameImage("bear", ".\\image\\enemyImg\\bear.bmp", 160, 103, 2, 1, true, RGB(255, 0, 255));

	_Lv = 5;										//����
	_maxEXP = RND->getFromIntTo(45, 50);	 		//���� ����ġ, �ִ� ����ġ
	_gold = RND->getFromIntTo(45, 50);				//��

	_curHP = _maxHP = 40;							//���� ü��, �ִ� ü��
	_curMP = _maxMP = 15;							//���� ����, �ִ� ����

	_attack = 16;									//���� ���ݷ�
	_magic = 6;										//���� ���ݷ�

	_m_Def = 140;									//���� ����
	_a_Def = 100;									//���� ����

	_speed = 30;									//���� Ÿ�̸�

	_evasion = 0;									//ȸ����
	_hitRate = 100;									//���߷�
	_block = 0;										//�����
}


guard::~guard()
{

}

void guard::update()
{

}

void guard::render()
{

}


void guard::bearSkill()
{

}
