#include "stdafx.h"
#include "Locke.h"

Locke::Locke()
{
	_Lv = 1, _curEXP = 0; _maxEXP = 50;
	_curHP = 50, _maxHP = 50, _curMP = 60, _maxMP = 60;
	_strength = 37, _speed = 40, _stamina = 31;
	_magic = 28, _attack = 14, _a_Def = 46;
	_evasion = 15, _m_evasion = 2, _m_Def = 23;
}

Locke::~Locke()
{
}
