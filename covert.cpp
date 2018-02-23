#include "stdafx.h"
#include "covert.h"
#include "battlePlayerMother.h"

covert::covert()
{
	//=================================================== 에너미 이미지 ==========================================================
	
	_img = IMAGEMANAGER->addFrameImage("covert", ".\\image\\enemyImg\\covert.bmp", 260, 91, 2, 1, true, RGB(255, 0, 255), true);
	
	//===========================================================================================================================

	//================================================= 에너미 이펙트 이미지 =====================================================
	
	IMAGEMANAGER->addImage("covert기본공격이미지", ".\\image\\enemyEffect\\effect2.bmp", 1536, 192, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("covert스킬공격이미지", ".\\image\\enemyEffect\\effect8.bmp", 378, 107, true, RGB(255, 0, 255), true);

	_atkEffect = new effect;
	_atkEffect->init(IMAGEMANAGER->findImage("covert기본공격이미지"), 192, 192, 1.0f, 0.5f);

	_spellEffect = new effect;
	_spellEffect->init(IMAGEMANAGER->findImage("covert스킬공격이미지"), 54, 107, 1.0f, 0.5f);

	EFFECTMANAGER->addEffect("covert기본공격", ".\\image\\enemyEffect\\effect2.bmp", 1536, 192, 192, 192, 1.0f, 1.0f, 2);
	EFFECTMANAGER->addEffect("covert스킬공격", ".\\image\\enemyEffect\\effect8.bmp", 378, 107, 54, 107, 1.0f, 1.0f, 2);
	
	//===========================================================================================================================
	
	//============================================== 기본공격 사운드 ==============================================

	SOUNDMANAGER->addSound("covert기본공격", ".\\sound\\sfx\\2ESwordSlashLong.wav", true, false);

	//============================================================================================================

	//============================================== 스킬공격 사운드 ==============================================

	SOUNDMANAGER->addSound("covert스킬공격", ".\\sound\\sfx\\4BDrill.wav", true, false);

	//============================================================================================================

	_Lv = 44;										//레벨
	_maxEXP = RND->getFromIntTo(1600, 1900);		//현재 경험치, 최대 경험치
	_gold = RND->getFromIntTo(1600, 1900);			//돈

	_curHP = _maxHP = 4530;							//현재 체력, 최대 체력
	_curMP = _maxMP = 240;							//현재 마력, 최대 마력

	_attack = 25;									//물리 공격력
	_magic = 11;									//마법 공격력

	_m_Def = 150;									//마법 방어력
	_a_Def = 100;									//물리 방어력

	_speed = 35;									//공격 타이머

	_evasion = 50;									//회피율
	_hitRate = 100;									//명중률
	_block = 0;										//방어율

	_spellPower = _Lv;								//마법력
}


covert::~covert()
{

}

void covert::update()
{
	Enemy::update();
	wsprintf(_basicAttack, "covert기본공격");
	wsprintf(_skillAttack, "covert스킬공격");

	switch (_enemyItemNum)
	{
		case 1:
			if (_enemyItemNum <= 2)
			{
				wsprintf(_itemString, "메가엘릭서");
			}
		break;

		case 2:
			if (_enemyItemNum >= 3 && _enemyItemNum <= 6)
			{
				wsprintf(_itemString, "엘릭서");
			}
		break;

		case 3:
			if (_enemyItemNum >= 7 && _enemyItemNum <= 31)
			{
				wsprintf(_itemString, "에테르");
			}
		break;

		case 4:
			if (_enemyItemNum >= 32 && _enemyItemNum <= 56)
			{
				wsprintf(_itemString, "육포");
			}
		break;

		case 5:
			if (_enemyItemNum >= 57 && _enemyItemNum <= 71)
			{
				wsprintf(_itemString, "토닉");
			}
		break;

		case 6:
			if (_enemyItemNum >= 72 && _enemyItemNum <= 81)
			{
				wsprintf(_itemString, "포션");
			}
		break;

		case 7:
			if (_enemyItemNum >= 82 && _enemyItemNum <= 86)
			{
				wsprintf(_itemString, "침낭");
			}
		break;

		case 8:
			if (_enemyItemNum >= 87 && _enemyItemNum <= 92)
			{
				wsprintf(_itemString, "Thief Knife");
			}
		break;

		case 9:
			if (_enemyItemNum >= 93 && _enemyItemNum <= 97)
			{
				wsprintf(_itemString, "Striker");
			}
		break;

		case 10:
			if (_enemyItemNum >= 98 && _enemyItemNum <= 99)
			{
				wsprintf(_itemString, "Wing Edge");
			}
		break;
		
		case 11:
			if (_enemyItemNum == 100)
			{
				wsprintf(_itemString, "Illumina");
			}
		break;
	}
}

void covert::render()
{
	Enemy::render();
	IMAGEMANAGER->findImage("covert")->alphaFrameRender(getMemDC(), _x - _img->getFrameWidth() / 2, _y - _img->getFrameHeight() / 2, _frameX, 0, _alpha);
}


void covert::bearSkill()
{

}
