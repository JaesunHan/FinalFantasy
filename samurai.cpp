#include "stdafx.h"
#include "samurai.h"
#include "battlePlayerMother.h"

samurai::samurai()
{
	//=================================================== 에너미 이미지 ==========================================================
	_img = IMAGEMANAGER->addFrameImage("samurai", ".\\image\\enemyImg\\samurai.bmp", 108, 103, 2, 1, true, RGB(255, 0, 255), true);
	//===========================================================================================================================

	//================================================= 에너미 이펙트 이미지 =====================================================
	IMAGEMANAGER->addImage("samurai기본공격이미지", ".\\image\\enemyEffect\\effect1.bmp", 1800, 130, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("samurai스킬공격이미지", ".\\image\\enemyEffect\\effect3.bmp", 800, 50, true, RGB(255, 0, 255), true);

	_atkEffect = new effect;
	_atkEffect->init(IMAGEMANAGER->findImage("samurai기본공격이미지"), 117, 85, 1.0f, 0.5f);

	_spellEffect = new effect;
	_spellEffect->init(IMAGEMANAGER->findImage("samurai스킬공격이미지"), 117, 85, 1.0f, 0.5f);

	EFFECTMANAGER->addEffect("samurai기본공격이펙트", ".\\image\\enemyEffect\\effect1.bmp", 1800, 130, 150, 130, 1.0f, 1.0f, 1000);
	EFFECTMANAGER->addEffect("samurai스킬공격이펙트", ".\\image\\enemyEffect\\effect3.bmp", 800, 50, 100, 50, 1.0f, 1.0f, 1000);
	//===========================================================================================================================

	_Lv = 40;										//레벨
	_maxEXP = RND->getFromIntTo(1500, 1600);		//현재 경험치, 최대 경험치
	_gold = RND->getFromIntTo(750, 850);			//돈

	_curHP = _maxHP = 3000;							//현재 체력, 최대 체력
	_curMP = _maxMP = 500;							//현재 마력, 최대 마력

	_attack = 13;									//물리 공격력
	_magic = 10;									//마법 공격력

	_m_Def = 20;									//마법 방어력
	_a_Def = 10;									//물리 방어력

	_speed = 20;									//공격 타이머

	_evasion = 0;									//회피율
	_hitRate = 100;									//명중률
	_block = 0;										//방어율
}


samurai::~samurai()
{

}

void samurai::update()
{
	if (_turnEnd == false)
	{
		_count++;
		if (_count < 50) glitter();

		if (_effectFire == true)
		{
			EFFECTMANAGER->play("samurai기본공격이펙트", 800, 320);

			_effectFire = false;
		}
		//if (_effectFire == true)
		//{
		//	EFFECTMANAGER->play("samurai스킬공격이펙트", 800, 320);
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

void samurai::render()
{
	IMAGEMANAGER->findImage("samurai")->alphaFrameRender(getMemDC(), _x - _img->getWidth() / 2, _y - _img->getHeight() / 2, _frameX, 0, _alpha);
	//IMAGEMANAGER->findImage("samurai")->frameRender(getMemDC(), _x, _y);
}


void samurai::bearSkill()
{

}
