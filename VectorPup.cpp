#include "stdafx.h"
#include "VectorPup.h"
#include "battlePlayerMother.h"

VectorPup::VectorPup()
{
	_Lv = 11;										//����
	_maxEXP = RND->getFromIntTo(125, 135);	 		//���� ����ġ, �ִ� ����ġ
	_gold = RND->getFromIntTo(75, 90);				//��

	_curHP = _maxHP = 166;							//���� ü��, �ִ� ü��
	_curMP = _maxMP = 10;							//���� ����, �ִ� ����

	_attack = 14;									//�⺻ ������
	_magic = 10;									//���� ������

	_m_Def = 150;									//���� ����
	_a_Def = 80;									//���� ����

	_speed = 25;									//���� Ÿ�̸�

	_evasion = 0;									//ȸ����
	_hitRate = 100;									//���߷�
	_block = 0;										//�����
}

VectorPup::~VectorPup()
{

}

//HRESULT VectorPup::init()
//{
//	
//
//	return S_OK;
//}

void VectorPup::update()
{
	enemyAttack();
}

void VectorPup::render() 
{
	
}

void VectorPup::vectorPupAttack()
{
	

}

void VectorPup::vectorPupSkill()
{

}