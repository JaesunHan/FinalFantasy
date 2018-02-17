#pragma once
#include "itemMother.h"

class posion : public itemMother
{
public:
	posion();
	~posion();

	HRESULT init(char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price, int performance);
	void release();
	void update();
};

