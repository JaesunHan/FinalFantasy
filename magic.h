#pragma once
#include "effect.h"

class magic
{
protected:
	char _magicName[256];		//���� �̸�
	int _abilityPower;			//���� ���� ȿ��
	int _manaCost;				//�Ҹ� ����
	int _hitRate;				//���� ���߷�

	bool _isHeal;				//�� �����̳�(true)? �ƴϳ�?(false)
	int _healHP;				//����� ��

	bool _isRevive;				//�츮�� �����̳�(true)? �ƴϳ�?(false)
	int  _reviveHP;				//�츮�� ��ŭ�� HP �� ��Ƴ��� ����

	image* _magicImg;			//���� �̹���
	effect* _magicEft;			//���� ����Ʈ
	string _maicEffectKeyString;	//����Ʈ �Ŵ����� ����� �� �� Ű��

public:
	//			�̹���,����Ʈ�Ŵ����� ����� Ű, �̹����������̸�,		�����̸�,			���� �Ŀ�,		�ʿ丶����,		���߷�,		����	,		�������ۿ���
	HRESULT init(string magicEffectKey, char* magicImgFileName, char magicName[256], int abilityPower, int manaConst, int hitRate, bool isHeal, bool isRevive);
	void update();
	void release();
	void render(HDC hdc);
	void draw(HDC hdc);

	//================ ���� ���� ������ ����� �� �ʿ��� �������� ���� ==================
	char* getMagicName() { return _magicName; }
	int getAbilityPower() { return _abilityPower; }
	int getManaCost() { return _manaCost; }
	int getHitRate() { return _hitRate; }
	bool getIsHeal() { return _isHeal; }
	int getHealHP() { return _healHP; }
	bool getIsRevive() { return _isRevive; }
	int getReviveHP() { return _reviveHP; }
	string getMaicEffectKey() { return _maicEffectKeyString; }

	
	magic();
	~magic();
};

