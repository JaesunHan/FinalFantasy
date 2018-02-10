#include "stdafx.h"
#include "Locke.h"

Locke::Locke()
{
	_Lv = 1, _curEXP = 0; _maxEXP = 32;
	_curHP = 48, _maxHP = 48, _curMP = 7, _maxMP = 7;
	_strength = 37, _speed = 40, _stamina = 31;
	_magic = 28, _attack = 14, _a_Def = 46;
	_evasion = 15, _m_evasion = 2, _m_Def = 23;
	
}

Locke::~Locke()
{
}
