#include "stdafx.h"
#include "Locke.h"
#include "weaponItem.h"

Locke::Locke()
{
	wsprintf(_name, "LOCKE");
	wsprintf(_job, "Treasure Hunter");
	_Lv = 3, _curEXP = 0; _maxEXP = 96;
	_curHP = 48 + 23, _maxHP = 48 + 23, _curMP = 7 + 11, _maxMP = 7 + 11;
	_strength = 37, _speed = 40, _stamina = 31;
	_magic = 28, _attack = 14, _a_Def = 46;
	_evasion = 15, _m_evasion = 2, _m_Def = 23;
	_partyIdx = 1;
	
	//기본 무기 세팅
	_defaultWeapon = new weaponItem;
	_defaultWeapon->init(ITEM_WEAPON, "DefaultWeapon", "맨주먹공격무기이다", 0, 10, 100);
	_myWeapon = new weaponItem;
	_myWeapon = _defaultWeapon;
}

Locke::~Locke()
{
}
