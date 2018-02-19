#include "stdafx.h"
#include "shadow.h"
#include "weaponItem.h"

shadow::shadow()
{
	wsprintf(_name, "SHADOW");
	wsprintf(_job, "Assassin");
	_Lv = 3, _curEXP = 0; _maxEXP = 96;
	_curHP = 51 + 23, _maxHP = 51 + 23, _curMP = 6 + 11, _maxMP = 6 + 11;
	_strength = 39, _speed = 38, _stamina = 30;
	_magic = 33, _attack = 23, _a_Def = 47;
	_evasion = 28, _m_Def = 25, _m_evasion = 9;
	_partyIdx = 3;

	//기본 무기 세팅
	_defaultWeapon = new weaponItem;
	_defaultWeapon->init(ITEM_WEAPON, "DefaultWeapon", "맨주먹공격무기이다", 0, 10, 100);
	_myWeapon = new weaponItem;
	_myWeapon = _defaultWeapon;
}


shadow::~shadow()
{
}
