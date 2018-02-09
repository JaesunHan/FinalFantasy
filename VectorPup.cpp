#include "stdafx.h"
#include "VectorPup.h"


VectorPup::VectorPup()
{
	_Lv = 11;							//레벨
	_maxEXP = 128;	 					//현재 경험치, 최대 경험치
	_gold = 83;							//돈

	_curHP = _maxHP = 166;				//현재 체력, 최대 체력
	_curMP = _maxMP = 10;				//현재 마력, 최대 마력

	_attack = 14;						//기본 공격력 + 무기의 공격력

	_magic = 10;						//마법 데미지

	_m_Def = 150;						//마법 방어력
	_a_Def = 80;						//물리 방어력

	_speed = 25;						//공격 타이머

	_evasion = 0;						//회피율
	_hitRate = 100;						//명중률
	_block = 0;							//방어율
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
