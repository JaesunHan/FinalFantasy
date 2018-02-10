#include "stdafx.h"
#include "celes.h"


celes::celes()
{
	_Lv = 1, _curEXP = 0; _maxEXP = 50;
	_curHP = 50, _maxHP = 50, _curMP = 60, _maxMP = 60;
	_strength = 34, _speed = 34, _stamina = 31;
	_magic = 36, _attack = 16, _a_Def = 44;
	_evasion = 7, _m_Def = 31, _m_evasion = 9;
}


celes::~celes()
{
}
