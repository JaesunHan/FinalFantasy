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

	HRESULT init(itemKind itemKind, char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price, int a_Def, int m_Def);
	void release();
	void update();
};

