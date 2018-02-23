#include "stdafx.h"
#include "DarkWind.h"
#include "battlePlayerMother.h"

DarkWind::DarkWind()
{
	//=================================================== 에너미 이미지 ==========================================================
	
	_img = IMAGEMANAGER->addFrameImage("darkWind", ".\\image\\enemyImg\\DarkWind.bmp", 132, 85, 2, 1, true, RGB(255, 0, 255), true);

	//===========================================================================================================================

	//================================================= 에너미 이펙트 이미지 =====================================================
	
	IMAGEMANAGER->addImage("darkWind기본공격이미지", ".\\image\\enemyEffect\\effect12.bmp", 310, 62, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("darkWind스킬공격이미지", ".\\image\\enemyEffect\\effect10.bmp", 679, 109, true, RGB(255, 0, 255), true);

	_atkEffect = new effect;
	_atkEffect->init(IMAGEMANAGER->findImage("darkWind기본공격이미지"), 62, 62, 1.0f, 0.5f);

	_spellEffect = new effect;
	_spellEffect->init(IMAGEMANAGER->findImage("darkWind스킬공격이미지"), 97, 109, 1.0f, 0.5f);

	EFFECTMANAGER->addEffect("darkWind기본공격", ".\\image\\enemyEffect\\effect12.bmp", 310, 62, 62, 62, 1.0f, 1.0f, 2);
	EFFECTMANAGER->addEffect("darkWind스킬공격", ".\\image\\enemyEffect\\effect10.bmp", 679, 109, 97, 109, 1.0f, 1.0f, 2);
	
	//===========================================================================================================================
	
	//============================================== 기본공격 사운드 ==============================================

	SOUNDMANAGER->addSound("darkWind기본공격", ".\\sound\\sfx\\C0Bird.wav", true, false);

	//============================================================================================================

	//============================================== 스킬공격 사운드 ==============================================

	SOUNDMANAGER->addSound("darkWind스킬공격", ".\\sound\\sfx\\40CyanSwdtechActivation.wav", true, false);

	//============================================================================================================

	_Lv = 5;										//레벨
	_maxEXP = RND->getFromIntTo(25, 30);			//현재 경험치, 최대 경험치
	_gold = RND->getFromIntTo(38, 42);				//돈

	_curHP = _maxHP = 34;							//현재 체력, 최대 체력
	_curMP = _maxMP = 0;							//현재 마력, 최대 마력

	_attack = 13;									//물리 공격력
	_magic = 10;									//마법 공격력

	_m_Def = 140;									//마법 방어력
	_a_Def = 55;									//물리 방어력

	_speed = 30;									//공격 타이머

	_evasion = 0;									//회피율
	_hitRate = 100;									//명중률
	_block = 0;										//방어율

	_spellPower = _Lv / 2;							//마법력
}


DarkWind::~DarkWind()
{

}

//HRESULT DarkWind::init()
//{
//
//
//	return S_OK;
//}

void DarkWind::update()
{
	Enemy::update();
	wsprintf(_basicAttack, "darkWind기본공격");
	wsprintf(_skillAttack, "darkWind스킬공격");

	switch (_enemyItemNum)
	{
		case 1:
			if (_enemyItemNum == 1)
			{
				wsprintf(_itemString, "메가엘릭서");
			}
		break;

		case 2:
			if (_enemyItemNum >= 2 && _enemyItemNum <= 3)
			{
				wsprintf(_itemString, "엘릭서");
			}
		break;

		case 3:
			if (_enemyItemNum >= 4 && _enemyItemNum <= 33)
			{
				wsprintf(_itemString, "에테르");
			}
		break;

		case 4:
			if (_enemyItemNum >= 34 && _enemyItemNum <= 63)
			{
				wsprintf(_itemString, "육포");
			}
		break;

		case 5:
			if (_enemyItemNum >= 64 && _enemyItemNum <= 78)
			{
				wsprintf(_itemString, "토닉");
			}
		break;

		case 6:
			if (_enemyItemNum >= 79 && _enemyItemNum <= 90)
			{
				wsprintf(_itemString, "포션");
			}
		break;

		case 7:
			if (_enemyItemNum >= 91 && _enemyItemNum <= 96)
			{
				wsprintf(_itemString, "침낭");
			}
		break;

		case 8:
			if (_enemyItemNum >= 97 && _enemyItemNum <= 99)
			{
				wsprintf(_itemString, "Thief Knife");
			}
		break;

		case 9:
			if (_enemyItemNum == 100)
			{
				wsprintf(_itemString, "Striker");
			}
		break;

		//case 10:
		//	if (_enemyItemNum >= 91 && _enemyItemNum <= 100)
		//	{
		//		wsprintf(_itemString, "Wing Edge");
		//	}
		//break;
		//
		//case 11:
		//	if (_enemyItemNum >= 91 && _enemyItemNum <= 100)
		//	{
		//		wsprintf(_itemString, "Illumina");
		//	}
		//break;
	}
}

void DarkWind::render()
{
	Enemy::render();
	IMAGEMANAGER->findImage("darkWind")->alphaFrameRender(getMemDC(), _x - _img->getFrameWidth() / 2, _y - _img->getFrameHeight() / 2, _frameX, 0, _alpha);
}

void DarkWind::darkWindSkill()
{

}