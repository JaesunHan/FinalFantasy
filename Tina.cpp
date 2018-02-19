#include "stdafx.h"
#include "Tina.h"
#include "weaponItem.h"

Tina::Tina()
{
	wsprintf(_name, "Tina");
	wsprintf(_job, "Magician");
	_Lv = 3, _curEXP = 0; _maxEXP = 96;
	_curHP = 40 + 23, _maxHP = 40 + 23, _curMP = 16 + 11, _maxMP = 16 + 11;
	_strength = 31, _speed = 33, _stamina = 28;
	_magic = 39, _attack = 12, _a_Def = 42;
	_m_Def = 33, _evasion = 5, _m_evasion = 7;
	_partyIdx = 0;
	//기본 무기 세팅
	_defaultWeapon = new weaponItem;
	_defaultWeapon->init(ITEM_WEAPON, "DefaultWeapon", "맨주먹공격무기이다", 0, 10, 100);
	_myWeapon = new weaponItem;
	_myWeapon = _defaultWeapon;
}


Tina::~Tina()
{
}
