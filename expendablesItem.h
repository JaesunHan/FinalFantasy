#pragma once
#include "itemMother.h"

class expendablesItem : public itemMother
{
protected:
	//================================ ��� ���� ====================================
	
	unsigned int _ability;							//������ ȿ��

	//==============================================================================

public:
	expendablesItem();
	~expendablesItem();

	HRESULT init(itemKind itemKind, char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price);
	void release();
	void update();
};

