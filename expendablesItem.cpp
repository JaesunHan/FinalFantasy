#include "stdafx.h"
#include "expendablesItem.h"


expendablesItem::expendablesItem()
{
	
}


expendablesItem::~expendablesItem()
{
}

HRESULT expendablesItem::init(itemKind itemKind, char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price, int ability)
{
	itemMother::init(ITEM_EXPENDABLE, itemName, description, price, ability);
	//_itemKind = ITEM_EXPENDABLE;						//������ �帣
	//
	//strcpy_s(_name, itemName);						//������ �̸�
	//strcpy_s(_description, description);				//������ ����
	//_price = price;									//������ ���� (����)
	//_performance = performance;						//������ ȿ��


	return S_OK;
}

void expendablesItem::release()
{

}

void expendablesItem::update()
{

}