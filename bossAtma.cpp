#include "stdafx.h"
#include "bossAtma.h"
#include "battlePlayerMother.h"

bossAtma::bossAtma()
{
	//���ʹ� �̹���
	IMAGEMANAGER->addFrameImage("bossAtma", ".\\image\\enemyImg\\bossAtma.bmp", 1000, 500, 2, 1, true, RGB(255, 0, 255));

	_Lv = 67;										//����
	_maxEXP = 0;	 								//���� ����ġ, �ִ� ����ġ
	_gold = 0;										//��

	_curHP = _maxHP = 55000;						//���� ü��, �ִ� ü��
	_curMP = _maxMP = 19000;						//���� ����, �ִ� ����

	_attack = 20;									//���� ���ݷ�
	_magic = 10;									//���� ���ݷ�

	_m_Def = 70;									//���� ����
	_a_Def = 75;									//���� ����

	_speed = 63;									//���� Ÿ�̸�

	_evasion = 0;									//ȸ����
	_hitRate = 100;									//���߷�
	_block = 0;										//�����
}


bossAtma::~bossAtma()
{

}

void bossAtma::update()
{

}

void bossAtma::render()
{
	IMAGEMANAGER->findImage("bossAtma")->frameRender(getMemDC(), _x, _y);
}


void bossAtma::bearSkill()
{

}
