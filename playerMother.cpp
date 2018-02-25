#include "stdafx.h"
#include "playerMother.h"
#include "weaponItem.h"
#include "armorItem.h"

playerMother::playerMother()
{
	//�⺻ ���� ����
	_defaultWeapon = new weaponItem;
	_defaultWeapon->init(0, ITEM_WEAPON, "DefaultWeapon", "���ָ԰��ݹ����̴�", 0, 10, 200);
	_myWeapon = new weaponItem;
	_myWeapon = _defaultWeapon;
	//�⺻ ���� ����
	_myArmor = new armorItem;
	_myArmor->init(-1, ITEM_ARMOR, "", "", 0, 0, 0);
	//�⺻ ��� ����
	_myHelmet = new armorItem;
	_myHelmet->init(-2, ITEM_HELMET, "", "", 0, 0, 0);
	//�⺻ ���� ���� ����
	_mySubWeapon = new armorItem;
	_mySubWeapon->init(-3, ITEM_SUB_WEAPON, "", "", 0, 0, 0);
}	


playerMother::~playerMother()
{
	
}
