#include "stdafx.h"
#include "DarkWind.h"


DarkWind::DarkWind()
{
	_Lv = 5;								//����
	_maxEXP = 28;	 						//���� ����ġ, �ִ� ����ġ
	_gold = 41;								//��

	_curHP = _maxHP = 34;					//���� ü��, �ִ� ü��
	_curMP = _maxMP = 0;					//���� ����, �ִ� ����

	_attack = 13;							//���� ���ݷ�
	_magic = 10;							//���� ���ݷ�

	_m_Def = 140;							//���� ����
	_a_Def = 55;							//���� ����

	_speed = 30;							//���� Ÿ�̸�

	_evasion = 0;							//ȸ����
	_hitRate = 100;							//���߷�
	_block = 0;								//�����
}


DarkWind::~DarkWind()
{
}
