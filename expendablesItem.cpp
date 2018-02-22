#include "stdafx.h"
#include "expendablesItem.h"


expendablesItem::expendablesItem()
{
	
}


expendablesItem::~expendablesItem()
{
}

HRESULT expendablesItem::init(int itemNumber,itemKind itemKind, char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price,
								int amountHP, int amountMP, bool reviveItem, bool partyItem, bool inBattle, bool percentHP, bool percentMP)
{
	itemMother::init(itemNumber, itemKind, itemName, description, price);
	
	_amountHP = amountHP;									//아이템 HP 효과
	_amountMP = amountMP;									//아이템 MP 효과

	_reviveItem = reviveItem;								//소생 아이템인가?
	_partyItem = partyItem;									//파티원 전체효과인가?
	_inBattle = inBattle;									//배틀에서 사용 가능한가?
	_percentHP = percentHP;									//체력 % 회복
	_percentMP = percentMP;									//마력 % 회복
	
	return S_OK;
}

void expendablesItem::release()
{

}

void expendablesItem::update()
{

}