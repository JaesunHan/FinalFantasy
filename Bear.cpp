#include "stdafx.h"
#include "Bear.h"


Bear::Bear()
{
	_Lv = 5;							//����
	_maxEXP = 160;	 					//���� ����ġ, �ִ� ����ġ
	_gold = 185;							//��

	_curHP = _maxHP = 275;				//���� ü��, �ִ� ü��
	_curMP = _maxMP = 0;				//���� ����, �ִ� ����

	_attack = 13;						//���� ���ݷ�
	_magic = 10;						//���� ���ݷ�

	_m_Def = 140;						//���� ����
	_a_Def = 40;						//���� ����

	_speed = 25;						//���� Ÿ�̸�

	_evasion = 0;						//ȸ����
	_hitRate = 100;						//���߷�
	_block = 0;							//�����
}

Bear::~Bear()
{
}
