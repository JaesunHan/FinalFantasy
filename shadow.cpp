#include "stdafx.h"
#include "shadow.h"
#include "weaponItem.h"

shadow::shadow()
{
	_Lv = 3, _curEXP = 0; _maxEXP = 32;
	_curHP = 51 + 12, _maxHP = 51 + 12, _curMP = 6, _maxMP = 6;
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
