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
	_itemKind = ITEM_EXPENDABLE;					//������ �帣

	strcpy_s(_name, itemName);						//������ �̸�
	strcpy_s(_description, description);			//������ ����
	_price = price;									//������ ���� (����)
	_performance = performance;

	return S_OK;
}

void itemMother::release()
{

}

void itemMother::update() 
{

}
