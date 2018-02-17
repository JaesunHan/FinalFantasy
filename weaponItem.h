#pragma once
#include "itemMother.h"

class weaponItem : public itemMother
{
protected:
	//================================ 장비 정보 ====================================
	
	unsigned int _attack;							//물리 공격력
	unsigned int _hitRate;							//명중률
	
	//==============================================================================

public:
	weaponItem();
	~weaponItem();

	HRESULT init(itemKind itemKind, char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price);
	void release();
	void update();
};

