#include "stdafx.h"
#include "expendablesItem.h"


expendablesItem::expendablesItem()
{
	
}


expendablesItem::~expendablesItem()
{
}

HRESULT expendablesItem::init(char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price, int performance)
{
	_itemKind = ITEM_EXPENDABLE;					//������ �帣
	
	strcpy_s(_name, itemName);						//������ �̸�
	strcpy_s(_description, description);			//������ ����
	_price = price;									//������ ���� (����)
	_performance = performance;						//������ ȿ��


	return S_OK;
}

void expendablesItem::release()
{

}

void expendablesItem::update()
{

}