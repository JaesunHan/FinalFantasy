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
	_itemNumber = itemNumber;						//������ �ѹ�
	_itemKind = itemKind;							//������ ����

	strcpy_s(_name, itemName);						//������ �̸�
	strcpy_s(_description, description);			//������ ����

	_price = price;									//������ ����

	return S_OK;
}

void itemMother::release()
{

}

void itemMother::update() 
{

}