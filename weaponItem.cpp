#include "stdafx.h"
#include "weaponItem.h"


weaponItem::weaponItem()
{
}


weaponItem::~weaponItem()
{
}

HRESULT weaponItem::init(itemKind itemKind, char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price)
{
	itemMother::init(ITEM_EXPENDABLE, itemName, description, price);
	


	return S_OK;
}

void weaponItem::release()
{

}

void weaponItem::update()
{

}
