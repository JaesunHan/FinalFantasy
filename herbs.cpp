#include "stdafx.h"
#include "herbs.h"

herbs::herbs()
{
}

herbs::~herbs()
{

}

HRESULT herbs::init(itemKind itemKind, char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price)
{
	expendablesItem::init(ITEM_EXPENDABLE, itemName, description, price);
	//_itemKind = ITEM_EXPENDABLE;						//아이템 장르
	//
	//strcpy_s(_name, itemName);						//아이템 이름
	//strcpy_s(_description, description);				//아이템 종류
	//_price = price;									//아이템 가격 (상점)
	//_performance = performance;						//아이템 효과


	return S_OK;
}

void herbs::release()																					  
{

}

void herbs::update()																					  
{

}
