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
	_atkEffect->init(IMAGEMANAGER->findImage("covert기본공격이미지"), 117, 85, 1.0f, 0.5f);

	_spellEffect = new effect;
	_spellEffect->init(IMAGEMANAGER->findImage("covert스킬공격이미지"), 117, 85, 1.0f, 0.5f);

	EFFECTMANAGER->addEffect("covert기본공격이펙트", ".\\image\\enemyEffect\\effect2.bmp", 1536, 192, 192, 192, 1.0f, 1.0f, 1000);
	EFFECTMANAGER->addEffect("covert스킬공격이펙트", ".\\image\\enemyEffect\\effect8.bmp", 378, 107, 54, 107, 1.0f, 1.0f, 1000);
	//===========================================================================================================================

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
}


covert::~covert()
{

}

void covert::update()
{
	if (_turnEnd == false)
	{
		_count++;
		if (_count < 50) glitter();

		if (_effectFire == true)
		{
			EFFECTMANAGER->play("covert기본공격이펙트", 800, 320);

			_effectFire = false;
		}
		//if (_effectFire == true)
		//{
		//	EFFECTMANAGER->play("covert스킬공격이펙트", 800, 320);
		//
		//	_effectFire = false;
		//}

		if (_count > 150)
		{
			_turnEnd = true;
			_effectFire = true;

			_count = 0;
		}
	}
}

void covert::render()
{
	IMAGEMANAGER->findImage("covert")->alphaFrameRender(getMemDC(), _x - _img->getWidth() / 2, _y - _img->getHeight() / 2, _frameX, 0, _alpha);
	//IMAGEMANAGER->findImage("covert")->frameRender(getMemDC(), _x, _y);
}


void covert::bearSkill()
{

}
