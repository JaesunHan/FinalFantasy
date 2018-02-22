#pragma once
#include "itemMother.h"

class expendablesItem : public itemMother
{
protected:
	//================================ ��� ���� ====================================

	unsigned int _amountHP;								//������ HP ȿ��
	unsigned int _amountMP;								//������ MP ȿ��
	
	bool _reviveItem;									//�һ� �������ΰ�?
	bool _partyItem;									//��Ƽ�� ��üȿ���ΰ�?
	bool _inBattle;										//��Ʋ���� ��� �����Ѱ�?
	bool _percentHP;									//ü�� % ȸ������ == �ް������� ,������, X-����, X-���׸�
	bool _percentMP;									//���� % ȸ������ == �ް������� ,������, X-����, X-���׸�

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

