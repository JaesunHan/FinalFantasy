#include "stdafx.h"
#include "celes.h"
#include "weaponItem.h"

celes::celes()
{
	playerMother::playerMother();
	wsprintf(_name, "CELES");
	wsprintf(_job, "Rune Knight");
	_Lv = 3, _curEXP = 96; _maxEXP = 96;
	_curHP = 44 + 23, _maxHP = 44 + 23, _curMP = 15 + 11, _maxMP = 15 + 11;
	_strength = 34, _speed = 34, _stamina = 31;
	_magic = 36, _attack = 16, _a_Def = 44;
	_evasion = 7, _m_Def = 31, _m_evasion = 9;
	_partyIdx = 2;

}


celes::~celes()
{
}
