#pragma once
#include "itemMother.h"

class expendablesItem : public itemMother
{
private:


public:
	expendablesItem();
	~expendablesItem();

	HRESULT init(char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price, int performance);
	void release();
	void update();
};

