#include "stdafx.h"
#include "weaponItem.h"


weaponItem::weaponItem()
{
}


weaponItem::~weaponItem()
{
}

HRESULT weaponItem::init(char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price, int performance)
{
	
	_performance = performance;						//아이템 효과
	
	return S_OK;
}

void weaponItem::release()
{

}

void weaponItem::update()
{

}
