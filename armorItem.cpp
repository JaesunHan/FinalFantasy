#include "stdafx.h"
#include "armorItem.h"


armorItem::armorItem()
{
}


armorItem::~armorItem()
{
}

HRESULT armorItem::init(int itemNumber, itemKind itemKind, char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price, int a_Def, int m_Def)
{
	itemMother::init(itemNumber, itemKind, itemName, description, price);
	
	_a_Def = a_Def;									//���� ����
	_m_Def = m_Def;									//���� ����

	return S_OK;
}

void armorItem::release()
{

}

void armorItem::update()
{

}