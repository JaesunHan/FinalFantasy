#include "stdafx.h"
#include "VectorPup.h"


VectorPup::VectorPup()
{
	_Lv = 11;							//����
	_maxEXP = 128;	 					//���� ����ġ, �ִ� ����ġ
	_gold = 83;							//��

	_curHP = _maxHP = 166;				//���� ü��, �ִ� ü��
	_curMP = _maxMP = 10;				//���� ����, �ִ� ����

	_attack = 14;						//�⺻ ���ݷ� + ������ ���ݷ�

	_magic = 10;						//���� ������

	_m_Def = 150;						//���� ����
	_a_Def = 80;						//���� ����

	_speed = 25;						//���� Ÿ�̸�

	_evasion = 0;						//ȸ����
	_hitRate = 100;						//���߷�
	_block = 0;							//�����
}

VectorPup::~VectorPup()
{

}

void VectorPup::update() 
{

}

void VectorPup::render() 
{

}
