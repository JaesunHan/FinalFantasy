#pragma once
#include "itemMother.h"

class armorItem : public itemMother
{
protected:
	//================================ 장비 정보 ====================================
	
	unsigned int _a_Def;							//물리 방어력
	unsigned int _m_Def;							//마법 방어력
	
	//==============================================================================

public:
	armorItem();
	~armorItem();

	HRESULT init(itemKind itemKind, char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price);
	void release();
	void update();
};

