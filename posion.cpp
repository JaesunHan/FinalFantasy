#include "stdafx.h"
#include "posion.h"

posion::posion()
{
}

posion::~posion()
{
}

HRESULT posion::init(itemKind itemKind, char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price)
{
	expendablesItem::init(ITEM_EXPENDABLE, itemName, description, price);

	return E_NOTIMPL;
}

void posion::release()
{

}

void posion::update()
{

}
