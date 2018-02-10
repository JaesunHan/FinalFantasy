#include "stdafx.h"
#include "tornadoShark.h"
#include "battlePlayerMother.h"

tornadoShark::tornadoShark()
{
	//���ʹ� �̹���
	IMAGEMANAGER->addFrameImage("tornadoShack", ".\\image\\enemyImg\\tornadoShack.bmp", 262, 118, 2, 1, true, RGB(255, 0, 255));

	_Lv = 29;										//����
	_maxEXP = RND->getFromIntTo(500, 550);	 		//���� ����ġ, �ִ� ����ġ
	_gold = RND->getFromIntTo(1100, 1300);			//��

	_curHP = _maxHP = 1318;							//���� ü��, �ִ� ü��
	_curMP = _maxMP = 100;							//���� ����, �ִ� ����

	_attack = 15;									//���� ���ݷ�
	_magic = 10;									//���� ���ݷ�

	_m_Def = 153;									//���� ����
	_a_Def = 102;									//���� ����

	_speed = 30;									//���� Ÿ�̸�

	_evasion = 0;									//ȸ����
	_hitRate = 100;									//���߷�
	_block = 0;										//�����
}


tornadoShark::~tornadoShark()
{

}

void tornadoShark::update()
{

}

void tornadoShark::render()
{
	IMAGEMANAGER->findImage("tornadoShack")->frameRender(getMemDC(), _x, _y);
}


void tornadoShark::bearSkill()
{

}
