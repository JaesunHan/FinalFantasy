#pragma once
#include "itemMother.h"

class armorItem : public itemMother
{
protected:
	//================================ ��� ���� ====================================
	
	unsigned int _a_Def;							//���� ����
	unsigned int _m_Def;							//���� ����
	
	//==============================================================================

public:
	armorItem();
	~armorItem();

	HRESULT init(int itemNumber, itemKind itemKind, char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price, int a_Def, int m_Def);
	void release();
	void update();

	inline unsigned int getAttackDefRestored() { return _a_Def; }
	inline unsigned int getMagicDefRestored() { return _m_Def; }
};

