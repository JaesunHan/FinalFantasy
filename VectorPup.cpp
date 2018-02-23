#include "stdafx.h"
#include "VectorPup.h"
#include "battlePlayerMother.h"

VectorPup::VectorPup()
{
	//=================================================== 에너미 이미지 ==========================================================
	
	_img = IMAGEMANAGER->addFrameImage("vectorPup", ".\\image\\enemyImg\\VectorPup.bmp", 184, 46, 2, 1, true, RGB(255, 0, 255), true);
	
	//===========================================================================================================================

	//================================================= 에너미 이펙트 이미지 =====================================================
	
	IMAGEMANAGER->addImage("vectorPup기본공격이미지", ".\\image\\enemyEffect\\effect16.bmp", 411, 134, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("vectorPup스킬공격이미지", ".\\image\\enemyEffect\\effect15.bmp", 660, 123, true, RGB(255, 0, 255), true);

	_atkEffect = new effect;
	_atkEffect->init(IMAGEMANAGER->findImage("vectorPup기본공격이미지"), 137, 134, 1.0f, 0.5f);

	_spellEffect = new effect;
	_spellEffect->init(IMAGEMANAGER->findImage("vectorPup스킬공격이미지"), 132, 123, 1.0f, 0.5f);

	EFFECTMANAGER->addEffect("vectorPup기본공격", ".\\image\\enemyEffect\\effect16.bmp", 411, 134, 137, 134, 1.0f, 1.0f, 2);
	EFFECTMANAGER->addEffect("vectorPup스킬공격", ".\\image\\enemyEffect\\effect15.bmp", 660, 123, 132, 123, 1.0f, 1.0f, 2);

	//===========================================================================================================================
	
	//============================================== 기본공격 사운드 ==============================================

	SOUNDMANAGER->addSound("vectorPup기본공격", ".\\sound\\sfx\\8BClawSlash.wav", true, false);

	//============================================================================================================

	//============================================== 스킬공격 사운드 ==============================================

	SOUNDMANAGER->addSound("vectorPup스킬공격", ".\\sound\\sfx\\37Ice2Part2.wav", true, false);

	//============================================================================================================

	_Lv = 11;										//레벨
	_maxEXP = RND->getFromIntTo(125, 135);	 		//현재 경험치, 최대 경험치
	_gold = RND->getFromIntTo(75, 90);				//돈

	_curHP = _maxHP = 166;							//현재 체력, 최대 체력
	_curMP = _maxMP = 10;							//현재 마력, 최대 마력

	_attack = 14;									//기본 데미지
	_magic = 10;									//마법 데미지

	_m_Def = 150;									//마법 방어력
	_a_Def = 80;									//물리 방어력

	_speed = 25;									//공격 타이머

	_evasion = 0;									//회피율
	_hitRate = 100;									//명중률
	_block = 0;										//방어율

	_spellPower = _Lv - 4;							//마법력
}

VectorPup::~VectorPup()
{

}

//HRESULT VectorPup::init()
//{
//	
//
//	return S_OK;
//}

void VectorPup::update()
{
	Enemy::update();
	wsprintf(_basicAttack, "vectorPup기본공격");
	wsprintf(_skillAttack, "vectorPup스킬공격");

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

void VectorPup::render() 
{
	Enemy::render();
	IMAGEMANAGER->findImage("vectorPup")->alphaFrameRender(getMemDC(), _x - _img->getFrameWidth() / 2, _y - _img->getFrameHeight() / 2, _frameX, 0, _alpha);
}

void VectorPup::vectorPupAttack()
{
	

}

void VectorPup::vectorPupSkill()
{

}