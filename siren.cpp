#include "stdafx.h"
#include "siren.h"


siren::siren()
{
	//���ʹ� �̹���
	//IMAGEMANAGER->addFrameImage("bear", ".\\image\\enemyImg\\bear.bmp", 160, 103, 2, 1, true, RGB(255, 0, 255));

	_Lv = 50;										//����
	_maxEXP = RND->getFromIntTo(2800, 3200);		//���� ����ġ, �ִ� ����ġ
	_gold = RND->getFromIntTo(1100, 1300);			//��

	_curHP = _maxHP = 10050;						//���� ü��, �ִ� ü��
	_curMP = _maxMP = 12850;						//���� ����, �ִ� ����

	_attack = 13;									//���� ���ݷ�
	_magic = 15;									//���� ���ݷ�

	_m_Def = 170;									//���� ����
	_a_Def = 70;									//���� ����

	_speed = 35;									//���� Ÿ�̸�

	_evasion = 0;									//ȸ����
	_hitRate = 100;									//���߷�
	_block = 0;										//�����
}


siren::~siren()
{

}

void siren::update()
{

}

void siren::render()
{

}


void siren::bearSkill()
{

}
