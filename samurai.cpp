#include "stdafx.h"
#include "samurai.h"


samurai::samurai()
{
	//���ʹ� �̹���
	//IMAGEMANAGER->addFrameImage("bear", ".\\image\\enemyImg\\bear.bmp", 160, 103, 2, 1, true, RGB(255, 0, 255));

	_Lv = 40;										//����
	_maxEXP = RND->getFromIntTo(1500, 1600);		//���� ����ġ, �ִ� ����ġ
	_gold = RND->getFromIntTo(750, 850);			//��

	_curHP = _maxHP = 3000;							//���� ü��, �ִ� ü��
	_curMP = _maxMP = 500;							//���� ����, �ִ� ����

	_attack = 13;									//���� ���ݷ�
	_magic = 10;									//���� ���ݷ�

	_m_Def = 20;									//���� ����
	_a_Def = 10;									//���� ����

	_speed = 20;									//���� Ÿ�̸�

	_evasion = 0;									//ȸ����
	_hitRate = 100;									//���߷�
	_block = 0;										//�����
}


samurai::~samurai()
{

}

void samurai::update()
{

}

void samurai::render()
{

}


void samurai::bearSkill()
{

}