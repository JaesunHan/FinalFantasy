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

	HRESULT init(int itemNumber,itemKind itemKind, char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price, int attack, int hitRate);
	void release();
	void update();

	inline int getAttack() { return _attack; }
	inline int getHitRate() { return _hitRate; }
};

