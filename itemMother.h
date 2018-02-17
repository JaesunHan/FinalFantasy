#pragma once
#include "gameNode.h"

#define MAXNAMESIZE 1024

enum itemKind
{
	ITEM_EXPENDABLE,
	ITEM_WEAPON,
	ITEM_SUB_WEAPON,
	ITEM_ARMOR,
	ITEM_HELMET,
	ITEM_ACCESSORY
};

class itemMother : public gameNode
{
protected:
	itemKind _itemKind;

	char _name[MAXNAMESIZE];
	char _description[MAXNAMESIZE];
	
	unsigned int _price;
	unsigned int _performance;
public:
	itemMother();
	~itemMother();

	virtual	HRESULT init(itemKind itemKind, char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price, int performance);
	virtual void release();
	virtual void update();
};

