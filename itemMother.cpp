#include "stdafx.h"
#include "itemMother.h"


itemMother::itemMother()
{
}


itemMother::~itemMother()
{

}

HRESULT itemMother::init(itemKind itemKind, char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price, int performance)
{
	_itemKind = ITEM_EXPENDABLE;					//아이템 장르

	strcpy_s(_name, itemName);						//아이템 이름
	strcpy_s(_description, description);			//아이템 종류
	_price = price;									//아이템 가격 (상점)
	_performance = performance;

	return S_OK;
}

void itemMother::release()
{

}

void itemMother::update() 
{

}
