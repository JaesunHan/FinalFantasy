#pragma once
#include "itemMother.h"

struct tagHerbs
{

};

class herbs : public itemMother
{
public:
	herbs();
	~herbs();

	HRESULT init(itemKind itemKind, char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price, int ability);
	void release();
	void update();
};

