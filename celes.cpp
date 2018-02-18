#include "stdafx.h"
#include "celes.h"
#include "weaponItem.h"

celes::celes()
{
	_Lv = 3, _curEXP = 0; _maxEXP = 32;
	_curHP = 44 + 12, _maxHP = 44 + 12, _curMP = 15, _maxMP = 15;
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
