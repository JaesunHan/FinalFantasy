#include "stdafx.h"
#include "covert.h"


covert::covert()
{
	//���ʹ� �̹���
	//IMAGEMANAGER->addFrameImage("bear", ".\\image\\enemyImg\\bear.bmp", 160, 103, 2, 1, true, RGB(255, 0, 255));

	_Lv = 44;										//����
	_maxEXP = RND->getFromIntTo(1600, 1900);		//���� ����ġ, �ִ� ����ġ
	_gold = RND->getFromIntTo(1600, 1900);			//��

	_curHP = _maxHP = 4530;							//���� ü��, �ִ� ü��
	_curMP = _maxMP = 240;							//���� ����, �ִ� ����

	_attack = 25;									//���� ���ݷ�
	_magic = 11;									//���� ���ݷ�

	_m_Def = 150;									//���� ����
	_a_Def = 100;									//���� ����

	_speed = 35;									//���� Ÿ�̸�

	_evasion = 50;									//ȸ����
	_hitRate = 100;									//���߷�
	_block = 0;										//�����
}


covert::~covert()
{

}

void covert::update()
{

}

void covert::render()
{

}


void covert::bearSkill()
{

}
