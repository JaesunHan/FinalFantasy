#include "stdafx.h"
#include "shadow.h"


shadow::shadow()
{
	_Lv = 1, _curEXP = 0; _maxEXP = 50;
	_curHP = 50, _maxHP = 50, _curMP = 60, _maxMP = 60;
	_strength = 39, _speed = 38, _stamina = 30;
	_magic = 33, _attack = 23, _a_Def = 47;
	_evasion = 28, _m_Def = 25, _m_evasion = 9;
}


shadow::~shadow()
{
}
