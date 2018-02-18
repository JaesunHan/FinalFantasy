#pragma once
#include "itemMother.h"

class weaponItem : public itemMother
{
protected:
	//================================ ��� ���� ====================================
	
	unsigned int _attack;							//���� ���ݷ�
	unsigned int _hitRate;							//���߷�
	
	//==============================================================================

public:
	weaponItem();
	~weaponItem();

	HRESULT init(itemKind itemKind, char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price, int attack, int hitRate);
	void release();
	void update();
};

