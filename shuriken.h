#pragma once
#include "expendablesItem.h"

class shuriken : public itemMother
{
public:
	shuriken();
	~shuriken();

	HRESULT init(itemKind itemKind, char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price, int ability);
	void release();
	void update();
};

