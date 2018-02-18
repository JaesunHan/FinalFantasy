#pragma once
#include "itemMother.h"

class expendablesItem : public itemMother
{
protected:
	//================================ 장비 정보 ====================================

	unsigned int _currentHP;							//아이템 HP 효과
	unsigned int _currentMP;							//아이템 MP 효과
	
	bool _isDead;										//플레이어가 생사여부 == 피닉스깃털 사용
	bool _worldMap;										//월드맵에서만 쓸수있엉 == 침낭, 텐트
	bool _percentHP;									//체력 100% 회복 == 메가엘릭서 ,엘릭서, X-포션, X-에테르
	bool _percentMP;									//마력 100% 회복 == 메가엘릭서 ,엘릭서, X-포션, X-에테르

	//==============================================================================

public:
	expendablesItem();
	~expendablesItem();

	HRESULT init(itemKind itemKind, char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price,
		int currentHP, int currentMP, bool isDead, bool worldMap, bool percentHP, bool percentMP);
	void release();
	void update();
};

