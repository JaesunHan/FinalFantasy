#include "stdafx.h"
#include "VectorPup.h"
#include "battlePlayerMother.h"

VectorPup::VectorPup()
{
	//=================================================== 에너미 이미지 ==========================================================
	IMAGEMANAGER->addFrameImage("vectorPup", ".\\image\\enemyImg\\VectorPup.bmp", 184, 46, 2, 1, true, RGB(255, 0, 255), true);
	//===========================================================================================================================

	//================================================= 에너미 이펙트 이미지 =====================================================
	IMAGEMANAGER->addImage("vectorPup기본공격이미지", ".\\image\\enemyEffect\\effect13.bmp", 376, 92, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("vectorPup스킬공격이미지", ".\\image\\enemyEffect\\effect16.bmp", 411, 134, true, RGB(255, 0, 255), true);

	_atkEffect = new effect;
	_atkEffect->init(IMAGEMANAGER->findImage("vectorPup기본공격이미지"), 117, 85, 1.0f, 0.5f);

	_spellEffect = new effect;
	_spellEffect->init(IMAGEMANAGER->findImage("vectorPup스킬공격이미지"), 117, 85, 1.0f, 0.5f);

	EFFECTMANAGER->addEffect("vectorPup기본공격이펙트", ".\\image\\enemyEffect\\effect13.bmp", 376, 92, 94, 92, 1.0f, 1.0f, 1000);
	EFFECTMANAGER->addEffect("vectorPup스킬공격이펙트", ".\\image\\enemyEffect\\effect16.bmp", 411, 134, 137, 134, 1.0f, 1.0f, 1000);
	//===========================================================================================================================

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
	if (_turnEnd == false)
	{
		_count++;
		if (_count < 50) glitter();

		if (_effectFire == true)
		{
			EFFECTMANAGER->play("vectorPup기본공격이펙트", 800, 320);

			_effectFire = false;
		}
		//if (_effectFire == true)
		//{
		//	EFFECTMANAGER->play("vectorPup스킬공격이펙트", 800, 320);
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

void VectorPup::render() 
{
	IMAGEMANAGER->findImage("vectorPup")->alphaFrameRender(getMemDC(), _x, _y, _frameX, 0, _alpha);
	//IMAGEMANAGER->findImage("vectorPup")->frameRender(getMemDC(), _x, _y);
}

void VectorPup::vectorPupAttack()
{
	

}

void VectorPup::vectorPupSkill()
{

}