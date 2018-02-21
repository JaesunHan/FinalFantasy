#pragma once
#include "effect.h"

class magic
{
protected:
	char _magicName[256];		//마법 이름
	int _abilityPower;			//마법 적용 효과
	int _manaCost;				//소모 마나
	int _hitRate;				//마법 명중률

	bool _isHeal;				//힐 마법이냐(true)? 아니냐?(false)
	int _healHP;				//적용될 힐

	image* _magicImg;			//마법 이미지
	effect* _magicEft;			//마법 이팩트
	string _maicEffectKeyString;	//이팩트 매니저에 등록할 때 쓸 키값

public:
	//			이미지,이팩트매니저에 등록할 키, 이미지파일의이름,		마법이름,			마법 파워,		필요마나량,		명중률,		힐량	,		힐아이템여부
	HRESULT init(string magicEffectKey, char* magicImgFileName, char magicName[256], int abilityPower, int manaConst, int hitRate, int healHp, bool isHeal=false);
	void update();
	void release();
	void render(HDC hdc);
	void draw(HDC hdc);

	//================ 마법 공격 데미지 계산할 때 필요한 변수들의 게터 ==================
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

