#include "stdafx.h"
#include "weaponItem.h"


weaponItem::weaponItem()
{
}


weaponItem::~weaponItem()
{
}

HRESULT weaponItem::init(int itemNumber, itemKind itemKind, char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price, int attack, int hitRate)
{
	itemMother::init(itemNumber, itemKind, itemName, description, price);

	_attack = attack;
	_hitRate = hitRate;

	return S_OK;
}

void weaponItem::release()
{

}

void weaponItem::update()
{

}
