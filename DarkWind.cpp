#include "stdafx.h"
#include "DarkWind.h"
#include "battlePlayerMother.h"

DarkWind::DarkWind()
{
	//=================================================== 에너미 이미지 ==========================================================
	_img = IMAGEMANAGER->addFrameImage("darkWind", ".\\image\\enemyImg\\DarkWind.bmp", 132, 81, 2, 1, true, RGB(255, 0, 255), true);
	//===========================================================================================================================

	//================================================= 에너미 이펙트 이미지 =====================================================
	IMAGEMANAGER->addImage("darkWind기본공격이미지", ".\\image\\enemyEffect\\effect12.bmp", 310, 62, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("darkWind스킬공격이미지", ".\\image\\enemyEffect\\effect10.bmp", 679, 109, true, RGB(255, 0, 255), true);

	_atkEffect = new effect;
	_atkEffect->init(IMAGEMANAGER->findImage("darkWind기본공격이미지"), 117, 85, 1.0f, 0.5f);

	_spellEffect = new effect;
	_spellEffect->init(IMAGEMANAGER->findImage("darkWind스킬공격이미지"), 117, 85, 1.0f, 0.5f);

	EFFECTMANAGER->addEffect("darkWind기본공격이펙트", ".\\image\\enemyEffect\\effect12.bmp", 310, 62, 62, 62, 1.0f, 1.0f, 1000);
	EFFECTMANAGER->addEffect("darkWind스킬공격이펙트", ".\\image\\enemyEffect\\effect10.bmp", 679, 109, 97, 109, 1.0f, 1.0f, 1000);
	//===========================================================================================================================

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
	if (_turnEnd == false)
	{
		_count++;
		if (_count < 50) glitter();

		if (_effectFire == true)
		{
			EFFECTMANAGER->play("darkWind기본공격이펙트", 800, 320);

			_effectFire = false;
		}
		//if (_effectFire == true)
		//{
		//	EFFECTMANAGER->play("darkWind스킬공격이펙트", 800, 320);
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

void DarkWind::render()
{
	IMAGEMANAGER->findImage("darkWind")->alphaFrameRender(getMemDC(), _x - _img->getWidth() / 2, _y - _img->getHeight() / 2, _frameX, 0, _alpha);
	//IMAGEMANAGER->findImage("darkWind")->frameRender(getMemDC(), _x, _y);
}

void DarkWind::darkWindSkill()
{

}