#pragma once
#include "expendablesItem.h"

class shuriken : public expendablesItem
{
public:
	shuriken();
	~shuriken();

	HRESULT init(itemKind itemKind, char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price);
	void release();
	void update();
};

