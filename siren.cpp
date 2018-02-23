#include "stdafx.h"
#include "siren.h"
#include "battlePlayerMother.h"

siren::siren()
{
	//=================================================== 에너미 이미지 ==========================================================
	
	_img = IMAGEMANAGER->addFrameImage("siren", ".\\image\\enemyImg\\siren.bmp", 368, 148, 2, 1, true, RGB(255, 0, 255), true);
	
	//===========================================================================================================================

	//================================================= 에너미 이펙트 이미지 =====================================================
	
	IMAGEMANAGER->addImage("siren기본공격이미지", ".\\image\\enemyEffect\\effect14.bmp", 608, 76, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("siren스킬공격이미지", ".\\image\\enemyEffect\\effect9.bmp", 480, 59, true, RGB(255, 0, 255), true);

	_atkEffect = new effect;
	_atkEffect->init(IMAGEMANAGER->findImage("siren기본공격이미지"), 76, 76, 1.0f, 0.5f);

	_spellEffect = new effect;
	_spellEffect->init(IMAGEMANAGER->findImage("siren스킬공격이미지"), 80, 59, 1.0f, 0.5f);

	EFFECTMANAGER->addEffect("siren기본공격", ".\\image\\enemyEffect\\effect14.bmp", 608, 76, 76, 76, 1.0f, 1.0f, 2);
	EFFECTMANAGER->addEffect("siren스킬공격", ".\\image\\enemyEffect\\effect9.bmp", 480, 59, 80, 59, 1.0f, 1.0f, 2);
	
	//===========================================================================================================================
	
	//============================================== 기본공격 사운드 ==============================================

	SOUNDMANAGER->addSound("siren기본공격", ".\\sound\\sfx\\BFBuyingSelling.wav", true, false);

	//============================================================================================================

	//============================================== 스킬공격 사운드 ==============================================

	SOUNDMANAGER->addSound("siren스킬공격", ".\\sound\\sfx\\BBBigClose.wav", true, false);

	//============================================================================================================

	_Lv = 50;										//레벨
	_maxEXP = RND->getFromIntTo(2800, 3200);		//현재 경험치, 최대 경험치
	_gold = RND->getFromIntTo(1100, 1300);			//돈

	_curHP = _maxHP = 10050;						//현재 체력, 최대 체력
	_curMP = _maxMP = 12850;						//현재 마력, 최대 마력

	_attack = 13;									//물리 공격력
	_magic = 15;									//마법 공격력

	_m_Def = 170;									//마법 방어력
	_a_Def = 70;									//물리 방어력

	_speed = 35;									//공격 타이머

	_evasion = 0;									//회피율
	_hitRate = 100;									//명중률
	_block = 0;										//방어율

	_spellPower = (_Lv / 3) * 2;					//마법력
}


siren::~siren()
{

}

void siren::update()
{
	Enemy::update();
	wsprintf(_basicAttack, "siren기본공격");
	wsprintf(_skillAttack, "siren스킬공격");

	switch (_enemyItemNum)
	{
		case 1:
			if (_enemyItemNum <= 3)
			{
				wsprintf(_itemString, "메가엘릭서");
			}
		break;

		case 2:
			if (_enemyItemNum >= 4 && _enemyItemNum <= 9)
			{
				wsprintf(_itemString, "엘릭서");
			}
		break;

		case 3:
			if (_enemyItemNum >= 10 && _enemyItemNum <= 31)
			{
				wsprintf(_itemString, "에테르");
			}
		break;

		case 4:
			if (_enemyItemNum >= 32 && _enemyItemNum <= 53)
			{
				wsprintf(_itemString, "육포");
			}
		break;

		case 5:
			if (_enemyItemNum >= 54 && _enemyItemNum <= 68)
			{
				wsprintf(_itemString, "토닉");
			}
		break;

		case 6:
			if (_enemyItemNum >= 69 && _enemyItemNum <= 78)
			{
				wsprintf(_itemString, "포션");
			}
		break;

		case 7:
			if (_enemyItemNum >= 79 && _enemyItemNum <= 83)
			{
				wsprintf(_itemString, "침낭");
			}
		break;

		case 8:
			if (_enemyItemNum >= 84 && _enemyItemNum <= 88)
			{
				wsprintf(_itemString, "Thief Knife");
			}
		break;

		case 9:
			if (_enemyItemNum >= 89 && _enemyItemNum <= 93)
			{
				wsprintf(_itemString, "Striker");
			}
		break;

		case 10:
			if (_enemyItemNum >= 94 && _enemyItemNum <= 98)
			{
				wsprintf(_itemString, "Wing Edge");
			}
		break;
		
		case 11:
			if (_enemyItemNum >= 99 && _enemyItemNum <= 100)
			{
				wsprintf(_itemString, "Illumina");
			}
		break;
	}
}

void siren::render()
{
	Enemy::render();
	IMAGEMANAGER->findImage("siren")->alphaFrameRender(getMemDC(), _x - _img->getFrameWidth() / 2, _y - _img->getFrameHeight() / 2, _frameX, 0, _alpha);
}


void siren::bearSkill()
{

}
