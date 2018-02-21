#pragma once
#include "effect.h"

class magic
{
protected:
	char _magicName[256];		//마법 이름
	int _abilityPower;			//마법 적용 효과
	int _needMana;				//소모 마나
	
	bool _isHeal;				//힐 마법이냐(true)? 아니냐?(false)
	int _healHP;				//적용될 힐

	image* _magicImg;			//마법 이미지
	effect* _magicEft;			//마법 이팩트

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

