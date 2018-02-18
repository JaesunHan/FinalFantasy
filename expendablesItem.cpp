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
	
	_currentHP = currentHP;									//������ HP ȿ��
	_currentMP = currentMP;									//������ MP ȿ��

	_isDead	= isDead;										//�÷��̾ ���翩�� == �Ǵн����� ���
	_worldMap = worldMap;									//����ʿ����� �����־�
	_percentHP = percentHP;									//ü�� 100% ȸ��
	_percentMP = percentMP;									//���� 100% ȸ��
	
	return S_OK;
}

void expendablesItem::release()
{

}

void expendablesItem::update()
{

}