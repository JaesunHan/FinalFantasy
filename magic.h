#pragma once
#include "effect.h"

class magic
{
protected:
	char _magicName[256];		//���� �̸�
	int _abilityPower;			//���� ���� ȿ��
	int _needMana;				//�Ҹ� ����
	
	bool _isHeal;				//�� �����̳�(true)? �ƴϳ�?(false)
	int _healHP;				//����� ��

	image* _magicImg;			//���� �̹���
	effect* _magicEft;			//���� ����Ʈ

public:
	//HRESULT init(string magicImgKey, char magicName[256], int abilityPower, int needMana, int healHp, bool isHeal=false);
	void update();
	void release();
	void render(HDC hdc);
	void draw(HDC hdc);

	//void setEffect();

	magic();
	~magic();
};

