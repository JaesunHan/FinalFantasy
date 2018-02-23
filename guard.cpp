#include "stdafx.h"
#include "guard.h"
#include "battlePlayerMother.h"

guard::guard()
{
	//=================================================== 에너미 이미지 ==========================================================
	
	_img = IMAGEMANAGER->addFrameImage("guard", ".\\image\\enemyImg\\guard.bmp", 132, 62, 2, 1, true, RGB(255, 0, 255), true);
	
	//===========================================================================================================================

	//================================================= 에너미 이펙트 이미지 =====================================================
	
	IMAGEMANAGER->addImage("guard기본공격이미지", ".\\image\\enemyEffect\\effect1.bmp", 1800, 130, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("guard스킬공격이미지", ".\\image\\enemyEffect\\effect2.bmp", 1536, 192, true, RGB(255, 0, 255), true);

	_atkEffect = new effect;
	_atkEffect->init(IMAGEMANAGER->findImage("guard기본공격이미지"), 150, 130, 1.0f, 0.5f);

	_spellEffect = new effect;
	_spellEffect->init(IMAGEMANAGER->findImage("guard스킬공격이미지"), 192, 192, 1.0f, 0.5f);

	EFFECTMANAGER->addEffect("guard기본공격", ".\\image\\enemyEffect\\effect1.bmp", 1800, 130, 150, 130, 1.0f, 1.0f, 2);
	EFFECTMANAGER->addEffect("guard스킬공격", ".\\image\\enemyEffect\\effect2.bmp", 1536, 192, 192, 192, 1.0f, 1.0f, 2);
	
	//===========================================================================================================================
	
	//============================================== 기본공격 사운드 ==============================================

	SOUNDMANAGER->addSound("guard기본공격", ".\\sound\\sfx\\2ESwordSlashLong.wav", true, false);

	//============================================================================================================

	//============================================== 스킬공격 사운드 ==============================================

	SOUNDMANAGER->addSound("guard스킬공격", ".\\sound\\sfx\\BEDeathToll.wav", true, false);

	//============================================================================================================

	_Lv = 5;										//레벨
	_maxEXP = RND->getFromIntTo(45, 50);	 		//현재 경험치, 최대 경험치
	_gold = RND->getFromIntTo(45, 50);				//돈

	_curHP = _maxHP = 40;							//현재 체력, 최대 체력
	_curMP = _maxMP = 15;							//현재 마력, 최대 마력

	_attack = 16;									//물리 공격력
	_magic = 6;										//마법 공격력

	_m_Def = 140;									//마법 방어력
	_a_Def = 100;									//물리 방어력

	_speed = 30;									//공격 타이머

	_evasion = 0;									//회피율
	_hitRate = 100;									//명중률
	_block = 0;										//방어율
	
	_spellPower = _Lv - 2;							//마법력
}


guard::~guard()
{

}

void guard::update()
{
	Enemy::update();
	wsprintf(_basicAttack, "guard기본공격");
	wsprintf(_skillAttack, "guard스킬공격");

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

void guard::render()
{
	Enemy::render();
	IMAGEMANAGER->findImage("guard")->alphaFrameRender(getMemDC(), _x - _img->getFrameWidth() / 2, _y - _img->getFrameHeight() / 2, _frameX, 0, _alpha);
}


void guard::bearSkill()
{

}
