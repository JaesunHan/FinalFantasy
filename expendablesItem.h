#pragma once
#include "itemMother.h"

class expendablesItem : public itemMother
{
private:


public:
	expendablesItem();
	~expendablesItem();

	HRESULT init(itemKind itemKind, char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price, int ability);
	void release();
	void update();
};

