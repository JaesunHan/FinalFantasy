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
	//_itemKind = ITEM_EXPENDABLE;						//������ �帣
	//
	//strcpy_s(_name, itemName);						//������ �̸�
	//strcpy_s(_description, description);				//������ ����
	//_price = price;									//������ ���� (����)
	//_performance = performance;						//������ ȿ��


	return S_OK;
}

void armorItem::release()
{

}

void armorItem::update()
{

}