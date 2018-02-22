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
	
	_amountHP = amountHP;									//������ HP ȿ��
	_amountMP = amountMP;									//������ MP ȿ��

	_reviveItem = reviveItem;								//�һ� �������ΰ�?
	_partyItem = partyItem;									//��Ƽ�� ��üȿ���ΰ�?
	_inBattle = inBattle;									//��Ʋ���� ��� �����Ѱ�?
	_percentHP = percentHP;									//ü�� % ȸ��
	_percentMP = percentMP;									//���� % ȸ��
	
	return S_OK;
}

void expendablesItem::release()
{

}

void expendablesItem::update()
{

}