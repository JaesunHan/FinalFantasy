#include "stdafx.h"
#include "shadow.h"


shadow::shadow()
{
	_Lv = 3, _curEXP = 0; _maxEXP = 32;
	_curHP = 51 + 12, _maxHP = 51 + 12, _curMP = 6, _maxMP = 6;
	_strength = 39, _speed = 38, _stamina = 30;
	_magic = 33, _attack = 23, _a_Def = 47;
	_evasion = 28, _m_Def = 25, _m_evasion = 9;
	_partyIdx = 3;
}


shadow::~shadow()
{
}
