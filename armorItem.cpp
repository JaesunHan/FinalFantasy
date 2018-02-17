#include "stdafx.h"
#include "armorItem.h"


armorItem::armorItem()
{
}


armorItem::~armorItem()
{
}

HRESULT armorItem::init(itemKind itemKind, char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price)
{
	itemMother::init(ITEM_ARMOR, itemName, description, price);
	//_itemKind = ITEM_EXPENDABLE;						//아이템 장르
	//
	//strcpy_s(_name, itemName);						//아이템 이름
	//strcpy_s(_description, description);				//아이템 종류
	//_price = price;									//아이템 가격 (상점)
	//_performance = performance;						//아이템 효과


	return S_OK;
}

void armorItem::release()
{

}

void armorItem::update()
{

}