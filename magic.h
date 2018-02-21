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

	image* _magicImg;			//���� �̹���
	effect* _magicEft;			//���� ����Ʈ
	string _maicEffectKeyString;	//����Ʈ �Ŵ����� ����� �� �� Ű��

public:
	//			�̹���,����Ʈ�Ŵ����� ����� Ű, �̹����������̸�,		�����̸�,			���� �Ŀ�,		�ʿ丶����,		���߷�,		����	,		�������ۿ���
	HRESULT init(string magicEffectKey, char* magicImgFileName, char magicName[256], int abilityPower, int manaConst, int hitRate, int healHp, bool isHeal=false);
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
	string getMaicEffectKey() { return _maicEffectKeyString; }

	
	magic();
	~magic();
};

