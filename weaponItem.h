#pragma once
#include "itemMother.h"

class weaponItem : public itemMother
{
public:
	weaponItem();
	~weaponItem();

	HRESULT init(char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price, int performance);
	void release();
	void update();
};

