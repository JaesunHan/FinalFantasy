#pragma once
#include "itemMother.h"

class expendablesItem : public itemMother
{
protected:
	//================================ ��� ���� ====================================

	unsigned int _currentHP;							//������ HP ȿ��
	unsigned int _currentMP;							//������ MP ȿ��
	
	bool _isDead;										//�÷��̾ ���翩�� == �Ǵн����� ���
	bool _worldMap;										//����ʿ����� �����־� == ħ��, ��Ʈ
	bool _percentHP;									//ü�� 100% ȸ�� == �ް������� ,������, X-����, X-���׸�
	bool _percentMP;									//���� 100% ȸ�� == �ް������� ,������, X-����, X-���׸�

	//==============================================================================

public:
	expendablesItem();
	~expendablesItem();

	HRESULT init(itemKind itemKind, char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price,
		int currentHP, int currentMP, bool isDead, bool worldMap, bool percentHP, bool percentMP);
	void release();
	void update();
};

