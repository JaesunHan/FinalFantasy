#include "stdafx.h"
#include "shuriken.h"


shuriken::shuriken()
{
}


shuriken::~shuriken()
{
}

HRESULT shuriken::init(itemKind itemKind, char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price)
{
	expendablesItem::init(ITEM_EXPENDABLE, itemName, description, price);


	return E_NOTIMPL;
}

void shuriken::release()
{

}

void shuriken::update()
{

}
