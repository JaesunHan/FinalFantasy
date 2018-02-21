#include "stdafx.h"
#include "magic.h"


magic::magic()
{
}


magic::~magic()
{

}

HRESULT magic::init(string magicEffectKey, char* magicImgFileName, char magicName[256], int abilityPower, int manaConst, int hitRate, int healHp, bool isHeal)
{
	_maicEffectKeyString = magicEffectKey;
	//이미지 매니저에 등록된 이미지를 찾아서 변수에 저장하기
	_magicImg = IMAGEMANAGER->findImage(_maicEffectKeyString);
	wsprintf(_magicName, "%s", magicName);
	_abilityPower = abilityPower;
	_manaConst = manaConst;
	_hitRate = hitRate;
	_isHeal = isHeal;
	_healHP = healHp;

	//만약 힐 마법이 아니면 힐량은 0으로 저장(혹시모를 보정 작업임)
	if (!_isHeal)
	{
		_healHP = 0;
	}
	//_magicEft->init(_magicImg, _magicImg->getFrameWidth(), _magicImg->getFrameHeight(), 1.0f, 1.0f);
	EFFECTMANAGER->addEffect(_maicEffectKeyString, magicImgFileName, _magicImg->getWidth(), _magicImg->getHeight(), _magicImg->getFrameWidth(), _magicImg->getFrameHeight(), 1.0f, 1.0f, 2);

	return S_OK;
}

void magic::update()
{

}
void magic::release()
{

}
void magic::render(HDC hdc)
{
	EFFECTMANAGER->render();

}
void magic::draw(HDC hdc)
{

}
