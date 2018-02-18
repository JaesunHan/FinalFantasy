#include "stdafx.h"
#include "expendablesItem.h"


expendablesItem::expendablesItem()
{
	
}


expendablesItem::~expendablesItem()
{
}

HRESULT expendablesItem::init(itemKind itemKind, char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price,
								int currentHP, int currentMP, bool isDead, bool worldMap, bool percentHP, bool percentMP)
{
	itemMother::init(itemKind, itemName, description, price);
	
	_currentHP = currentHP;									//아이템 HP 효과
	_currentMP = currentMP;									//아이템 MP 효과

	_isDead	= isDead;										//플레이어가 생사여부 == 피닉스깃털 사용
	_worldMap = worldMap;									//월드맵에서만 쓸수있엉
	_percentHP = percentHP;									//체력 100% 회복
	_percentMP = percentMP;									//마력 100% 회복
	
	return S_OK;
}

void expendablesItem::release()
{

}

void expendablesItem::update()
{

}