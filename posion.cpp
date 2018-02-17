#include "stdafx.h"
#include "posion.h"

posion::posion()
{
}

posion::~posion()
{
}

HRESULT posion::init(itemKind itemKind, char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price, int ability)
{
	expendablesItem::init(ITEM_EXPENDABLE, itemName, description, price, ability);

	return E_NOTIMPL;
}

void posion::release()
{

}

void posion::update()
{

}
