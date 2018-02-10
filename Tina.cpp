#include "stdafx.h"
#include "Tina.h"


Tina::Tina()
{
	_Lv = 1, _curEXP = 0; _maxEXP = 32;
	_curHP = 40, _maxHP = 40, _curMP = 16, _maxMP = 16;
	_strength = 31, _speed = 33, _stamina = 28;
	_magic = 39, _attack = 12, _a_Def = 42;
	_m_Def = 33, _evasion = 5, _m_evasion = 7;
}


Tina::~Tina()
{
}
