#include "stdafx.h"
#include "itemMother.h"


itemMother::itemMother()
{
}


itemMother::~itemMother()
{

}

HRESULT itemMother::init(itemKind itemKind, char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price, int ability)
{
	_itemKind = ITEM_EXPENDABLE;					//������ ����

	strcpy_s(_name, itemName);						//������ �̸�
	strcpy_s(_description, description);			//������ ����

	_price = price;									//������ ����
	_ability = ability;								//������ ȿ��

	return S_OK;
}

void itemMother::release()
{

}

void itemMother::update() 
{

}