#include "stdafx.h"
#include "gobbler.h"
#include "battlePlayerMother.h"

gobbler::gobbler()
{
	//=================================================== 에너미 이미지 ==========================================================
	
	_img = IMAGEMANAGER->addFrameImage("gobbler", ".\\image\\enemyImg\\gobbler.bmp", 334, 171, 2, 1, true, RGB(255, 0, 255), true);
	
	//===========================================================================================================================

	//================================================= 에너미 이펙트 이미지 =====================================================
	
	IMAGEMANAGER->addImage("gobbler기본공격이미지", ".\\image\\enemyEffect\\effect5.bmp", 846, 117, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("gobbler스킬공격이미지", ".\\image\\enemyEffect\\effect7.bmp", 1320, 80, true, RGB(255, 0, 255), true);

	_atkEffect = new effect;
	_atkEffect->init(IMAGEMANAGER->findImage("gobbler기본공격이미지"), 94, 117, 1.0f, 0.5f);

	_spellEffect = new effect;
	_spellEffect->init(IMAGEMANAGER->findImage("gobbler스킬공격이미지"), 120, 80, 1.0f, 0.5f);

	EFFECTMANAGER->addEffect("gobbler기본공격", ".\\image\\enemyEffect\\effect5.bmp", 846, 117, 94, 117, 1.0f, 1.0f, 2);
	EFFECTMANAGER->addEffect("gobbler스킬공격", ".\\image\\enemyEffect\\effect7.bmp", 1320, 80, 120, 80, 1.0f, 1.0f, 2);
	
	//===========================================================================================================================
	
	//============================================== 기본공격 사운드 ==============================================

	SOUNDMANAGER->addSound("gobbler기본공격", ".\\sound\\sfx\\91Idk.wav", true, false);

	//============================================================================================================

	//============================================== 스킬공격 사운드 ==============================================

	SOUNDMANAGER->addSound("gobbler스킬공격", ".\\sound\\sfx\\73NarsheWind.wav", true, false);

	//============================================================================================================

	_Lv = 19;										//레벨
	_maxEXP = RND->getFromIntTo(400, 450);			//현재 경험치, 최대 경험치
	_gold = RND->getFromIntTo(230, 270);			//돈

	_curHP = _maxHP = 470;							//현재 체력, 최대 체력
	_curMP = _maxMP = 63;							//현재 마력, 최대 마력

	_attack = 13;									//물리 공격력
	_magic = 8;										//마법 공격력

	_m_Def = 120;									//마법 방어력
	_a_Def = 170;									//물리 방어력

	_speed = 30;									//공격 타이머

	_evasion = 0;									//회피율
	_hitRate = 100;									//명중률
	_block = 0;										//방어율

	_spellPower = _Lv;								//마법력
}


gobbler::~gobbler()
{

}

void gobbler::update()
{
	Enemy::update();
	wsprintf(_basicAttack, "gobbler기본공격");
	wsprintf(_skillAttack, "gobbler스킬공격");

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

void gobbler::render()
{
	Enemy::render();
	IMAGEMANAGER->findImage("gobbler")->alphaFrameRender(getMemDC(), _x - _img->getFrameWidth() / 2, _y - _img->getFrameHeight() / 2, _frameX, 0, _alpha);
}


void gobbler::bearSkill()
{

}
