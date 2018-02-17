#pragma once
#include "expendablesItem.h"

class posion : public expendablesItem
{
public:
	posion();
	~posion();

	HRESULT init(itemKind itemKind, char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price, int ability);
	void release();
	void update();
};

