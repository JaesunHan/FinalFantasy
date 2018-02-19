#include "stdafx.h"
#include "celes.h"
#include "weaponItem.h"

celes::celes()
{
	wsprintf(_name, "Celes");
	_Lv = 3, _curEXP = 0; _maxEXP = 96;
	_curHP = 44 + 23, _maxHP = 44 + 23, _curMP = 15 + 11, _maxMP = 15 + 11;
	_strength = 34, _speed = 34, _stamina = 31;
	_magic = 36, _attack = 16, _a_Def = 44;
	_evasion = 7, _m_Def = 31, _m_evasion = 9;
	_partyIdx = 2;

	//기본 무기 세팅
	_defaultWeapon = new weaponItem;
	_defaultWeapon->init(ITEM_WEAPON, "DefaultWeapon", "맨주먹공격무기이다", 0, 10, 100);
	_myWeapon = new weaponItem;
	_myWeapon = _defaultWeapon;
}


celes::~celes()
{
}
