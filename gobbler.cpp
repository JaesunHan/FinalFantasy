#include "stdafx.h"
#include "gobbler.h"
#include "battlePlayerMother.h"

gobbler::gobbler()
{
	//���ʹ� �̹���
	IMAGEMANAGER->addFrameImage("gobbler", ".\\image\\enemyImg\\gobbler.bmp", 334, 171, 2, 1, true, RGB(255, 0, 255), true);

	_Lv = 19;										//����
	_maxEXP = RND->getFromIntTo(400, 450);			//���� ����ġ, �ִ� ����ġ
	_gold = RND->getFromIntTo(230, 270);			//��

	_curHP = _maxHP = 470;							//���� ü��, �ִ� ü��
	_curMP = _maxMP = 63;							//���� ����, �ִ� ����

	_attack = 13;									//���� ���ݷ�
	_magic = 8;										//���� ���ݷ�

	_m_Def = 120;									//���� ����
	_a_Def = 170;									//���� ����

	_speed = 30;									//���� Ÿ�̸�

	_evasion = 0;									//ȸ����
	_hitRate = 100;									//���߷�
	_block = 0;										//�����
}


gobbler::~gobbler()
{

}

void gobbler::update()
{

}

void gobbler::render()
{
	IMAGEMANAGER->findImage("gobbler")->frameRender(getMemDC(), _x, _y);
}


void gobbler::bearSkill()
{

}
