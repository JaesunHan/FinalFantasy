#pragma once
#include "weaponItem.h"

class shuriken : public weaponItem
{
public:
	shuriken();
	~shuriken();

	HRESULT init(itemKind itemKind, char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price);
	void release();
	void update();
};

