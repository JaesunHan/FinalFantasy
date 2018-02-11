#include "stdafx.h"
#include "Bear.h"
#include "battlePlayerMother.h"

Bear::Bear()
{
	//에너미 이미지
	IMAGEMANAGER->addFrameImage("bear", ".\\image\\enemyImg\\bear.bmp", 180, 106, 2, 1, true, RGB(255, 0, 255), true);

	//에너미 이펙트 이미지
	IMAGEMANAGER->addImage("이펙트", ".\\image\\enemyEffect\\effect4.bmp", 585, 85, true, RGB(255, 0, 255), true);
	
	_test = new effect;
	_test->init(IMAGEMANAGER->findImage("이펙트"), 117, 85, 1.0f, 0.5f);
	
	EFFECTMANAGER->addEffect("폭발", ".\\image\\enemyEffect\\effect4.bmp", 585, 85, 117, 85, 1.0f, 1.0f, 1000); 

	_Lv = 5;										//레벨
	_maxEXP = RND->getFromIntTo(150, 170);	 		//현재 경험치, 최대 경험치
	_gold = RND->getFromIntTo(172, 196);			//돈

	_curHP = _maxHP = 275;							//현재 체력, 최대 체력
	_curMP = _maxMP = 0;							//현재 마력, 최대 마력

	_attack = 13;									//물리 공격력
	_magic = 10;									//마법 공격력

	_m_Def = 140;									//마법 방어력
	_a_Def = 40;									//물리 방어력

	_speed = 25;									//공격 타이머

	_evasion = 0;									//회피율
	_hitRate = 100;									//명중률
	_block = 0;										//방어율
}

Bear::~Bear()
{

}

//HRESULT Bear::init()
//{
//
//
//	return S_OK;
//}

void Bear::update()
{
	if (_effectFire == true)
	{
		EFFECTMANAGER->play("폭발", 800, 320);

		_effectFire = false;
	}

	if (_turnEnd == false)
	{
		_count++;
		
		if (_count > 100)
		{
			_turnEnd = true;
			_effectFire = true;

			_count = 0;
		}
	}
}

void Bear::render()
{
	IMAGEMANAGER->findImage("bear")->frameRender(getMemDC(), _x, _y);
}

void Bear::bearSkill()
{

}