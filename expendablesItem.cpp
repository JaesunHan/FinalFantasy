#include "stdafx.h"
#include "expendablesItem.h"


expendablesItem::expendablesItem()
{
	
}


expendablesItem::~expendablesItem()
{
}

HRESULT expendablesItem::init(itemKind itemKind, char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price)
{
	itemMother::init(ITEM_EXPENDABLE, itemName, description, price);
	
	


	return S_OK;
}

void expendablesItem::release()
{

}

void expendablesItem::update()
{

}