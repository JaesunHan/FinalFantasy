#include "stdafx.h"
#include "Locke.h"
#include "weaponItem.h"

Locke::Locke()
{
	playerMother::playerMother();
	wsprintf(_name, "LOCKE");
	wsprintf(_job, "Treasure Hunter");
	_Lv = 3, _curEXP =96; _maxEXP = 96;
	_curHP = 48 + 23, _maxHP = 48 + 23, _curMP = 7 + 11, _maxMP = 7 + 11;
	_strength = 37, _speed = 40, _stamina = 31;
	_magic = 28, _attack = 14, _a_Def = 46;
	_evasion = 15, _m_evasion = 2, _m_Def = 23;
	_partyIdx = 1;
	
}

Locke::~Locke()
{
}
