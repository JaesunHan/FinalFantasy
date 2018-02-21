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
	//�̹��� �Ŵ����� ��ϵ� �̹����� ã�Ƽ� ������ �����ϱ�
	_magicImg = IMAGEMANAGER->findImage(_maicEffectKeyString);
	wsprintf(_magicName, "%s", magicName);
	_abilityPower = abilityPower;
	_manaConst = manaConst;
	_hitRate = hitRate;
	_isHeal = isHeal;
	_healHP = healHp;

	//���� �� ������ �ƴϸ� ������ 0���� ����(Ȥ�ø� ���� �۾���)
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
