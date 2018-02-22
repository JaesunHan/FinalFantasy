#include "stdafx.h"
#include "magic.h"


magic::magic()
{
}


magic::~magic()
{

}

HRESULT magic::init(string magicEffectKey, char* magicImgFileName, char magicName[256], int abilityPower, int manaCost, int hitRate, bool isHeal, bool isRevive)
{
	_maicEffectKeyString = magicEffectKey;
	//�̹��� �Ŵ����� ��ϵ� �̹����� ã�Ƽ� ������ �����ϱ�
	_magicImg = IMAGEMANAGER->findImage(_maicEffectKeyString);
	wsprintf(_magicName, "%s", magicName);
	_abilityPower = abilityPower;
	_manaCost = manaCost;
	_hitRate = hitRate;
	_isHeal = isHeal;
	_isRevive = isRevive;

	//���� �� ������ �ƴϸ� ������ 0���� ����(Ȥ�ø� ���� �۾���)
	if (!_isHeal)
	{
		_healHP = 0;
	}
	//�� �����̸� �����Ƽ �Ŀ��� ����
	else
	{
		_healHP = _abilityPower;
	}
	//���� �ǻ츮�� ������ �ƴϸ� �ǻ츮�� HP �� 0���� ����
	if (!_isRevive)
	{
		_reviveHP = 0;
	}
	//�ǻ츮�� �����̸� �����Ƽ �Ŀ��� ����
	else
	{
		_reviveHP = _abilityPower;
	}

	//_magicEft->init(_magicImg, _magicImg->getFrameWidth(), _magicImg->getFrameHeight(), 1.0f, 1.0f);
	EFFECTMANAGER->addEffect(_maicEffectKeyString, magicImgFileName, _magicImg->getWidth(), _magicImg->getHeight(), _magicImg->getFrameWidth(), _magicImg->getFrameHeight(), 1.0f, 0.5f, 2);

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
