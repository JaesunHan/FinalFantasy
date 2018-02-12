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
	_atkEffect->init(IMAGEMANAGER->findImage("gobbler기본공격이미지"), 117, 85, 1.0f, 0.5f);

	_spellEffect = new effect;
	_spellEffect->init(IMAGEMANAGER->findImage("gobbler스킬공격이미지"), 117, 85, 1.0f, 0.5f);

	EFFECTMANAGER->addEffect("gobbler기본공격이펙트", ".\\image\\enemyEffect\\effect5.bmp", 846, 117, 94, 117, 1.0f, 1.0f, 1000);
	EFFECTMANAGER->addEffect("gobbler스킬공격이펙트", ".\\image\\enemyEffect\\effect7.bmp", 1320, 80, 120, 80, 1.0f, 1.0f, 1000);
	//===========================================================================================================================

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
}


gobbler::~gobbler()
{

}

void gobbler::update()
{
	if (_turnEnd == false)
	{
		_count++;
		if (_count < 50) glitter();

		if (_effectFire == true)
		{
			EFFECTMANAGER->play("gobbler기본공격이펙트", 800, 320);

			_effectFire = false;
		}
		//if (_effectFire == true)
		//{
		//	EFFECTMANAGER->play("gobbler스킬공격이펙트", 800, 320);
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

void gobbler::render()
{
	IMAGEMANAGER->findImage("gobbler")->alphaFrameRender(getMemDC(), _x - _img->getWidth() / 2, _y - _img->getHeight() / 2, _frameX, 0, _alpha);
	//IMAGEMANAGER->findImage("gobbler")->frameRender(getMemDC(), _x, _y);
}


void gobbler::bearSkill()
{

}
