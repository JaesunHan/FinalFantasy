#include "stdafx.h"
#include "playerMother.h"
#include "weaponItem.h"
#include "armorItem.h"

playerMother::playerMother()
{
	//기본 무기 세팅
	_defaultWeapon = new weaponItem;
	_defaultWeapon->init(0, ITEM_WEAPON, "DefaultWeapon", "맨주먹공격무기이다", 0, 10, 200);
	_myWeapon = new weaponItem;
	_myWeapon = _defaultWeapon;
	//기본 갑옷 세팅
	_myArmor = new armorItem;
	_myArmor->init(-1, ITEM_ARMOR, "", "", 0, 0, 0);
	//기본 헬멧 세팅
	_myHelmet = new armorItem;
	_myHelmet->init(-2, ITEM_HELMET, "", "", 0, 0, 0);
	//기본 서브 무기 세팅
	_mySubWeapon = new armorItem;
	_mySubWeapon->init(-3, ITEM_SUB_WEAPON, "", "", 0, 0, 0);
}	


playerMother::~playerMother()
{
	
}
