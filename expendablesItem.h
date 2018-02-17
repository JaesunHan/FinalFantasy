#pragma once
#include "itemMother.h"

class expendablesItem : public itemMother
{
protected:
	//================================ 장비 정보 ====================================
	
	unsigned int _ability;							//아이템 효과

	//==============================================================================

public:
	expendablesItem();
	~expendablesItem();

	HRESULT init(itemKind itemKind, char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price);
	void release();
	void update();
};

