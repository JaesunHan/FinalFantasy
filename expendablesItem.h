#pragma once
#include "itemMother.h"

class expendablesItem : public itemMother
{
protected:
	//================================ 장비 정보 ====================================

	unsigned int _amountHP;								//아이템 HP 효과
	unsigned int _amountMP;								//아이템 MP 효과
	
	bool _reviveItem;									//소생 아이템인가?
	bool _partyItem;									//파티원 전체효과인가?
	bool _inBattle;										//배틀에서 사용 가능한가?
	bool _percentHP;									//체력 % 회복인지 == 메가엘릭서 ,엘릭서, X-포션, X-에테르
	bool _percentMP;									//마력 % 회복인지 == 메가엘릭서 ,엘릭서, X-포션, X-에테르

	//==============================================================================

public:
	expendablesItem();
	~expendablesItem();

	HRESULT init(int itemNumber,itemKind itemKind, char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price,
		int currentHP, int currentMP, bool reviveItem, bool partyItem, bool inBattle, bool percentHP, bool percentMP);
	void release();
	void update();

	inline unsigned int getAmountHpRestored() { return _amountHP; }
	inline unsigned int getAmountMpRestored() { return _amountMP; }
	inline bool getIsReviveItem() { return _reviveItem; }
	inline bool getIsPartyItem() { return _partyItem; }
	inline bool getIsInBattle() { return _inBattle; }
	inline bool getIsPercentHP() { return _percentHP; }
	inline bool getIsPercentMP() { return _percentMP; }
};

