#include "stdafx.h"
#include "itemMother.h"


itemMother::itemMother()
{
}


itemMother::~itemMother()
{

}

HRESULT itemMother::init(int itemNumber, itemKind itemKind, char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price)
{
	_itemNumber = itemNumber;						//아이템 넘버
	_itemKind = itemKind;							//아이템 종류

	strcpy_s(_name, itemName);						//아이템 이름
	strcpy_s(_description, description);			//아이템 설명

	_price = price;									//아이템 가격

	return S_OK;
}

void itemMother::release()
{

}

void itemMother::update() 
{

}