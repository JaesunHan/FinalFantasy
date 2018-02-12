#include "stdafx.h"
#include "celes.h"


celes::celes()
{
	_Lv = 1, _curEXP = 0; _maxEXP = 32;
	_curHP = 44, _maxHP = 44, _curMP = 15, _maxMP = 15;
	_strength = 34, _speed = 34, _stamina = 31;
	_magic = 36, _attack = 16, _a_Def = 44;
	_evasion = 7, _m_Def = 31, _m_evasion = 9;
	_partyIdx = 2;
}


celes::~celes()
{
}
