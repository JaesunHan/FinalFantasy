#include "stdafx.h"
#include "Bear.h"
#include "battleCeles.h"
#include "battleLocke.h"
#include "battleShadow.h"
#include "battleTina.h"

Bear::Bear()
{
	_Lv = 5;										//����
	_maxEXP = RND->getFromIntTo(150, 170);	 		//���� ����ġ, �ִ� ����ġ
	_gold = RND->getFromIntTo(172, 196);			//��

	_curHP = _maxHP = 275;							//���� ü��, �ִ� ü��
	_curMP = _maxMP = 0;							//���� ����, �ִ� ����

	_attack = 13;									//���� ���ݷ�
	_magic = 10;									//���� ���ݷ�

	_m_Def = 140;									//���� ����
	_a_Def = 40;									//���� ����

	_speed = 25;									//���� Ÿ�̸�

	_evasion = 0;									//ȸ����
	_hitRate = 100;									//���߷�
	_block = 0;										//�����
}

Bear::~Bear()
{

}

//HRESULT Bear::init()
//{
//
//
//	return S_OK;
//}

void Bear::update()
{

}

void Bear::render()
{

}

void Bear::bearSkill()
{

}