#include "stdafx.h"
#include "Bear.h"
#include "battlePlayerMother.h"

Bear::Bear()
{
	//=================================================== 에너미 이미지 ==========================================================
	IMAGEMANAGER->addFrameImage("bear", ".\\image\\enemyImg\\bear.bmp", 180, 106, 2, 1, true, RGB(255, 0, 255), true);
	//===========================================================================================================================
	
	//================================================= 에너미 이펙트 이미지 =====================================================
	IMAGEMANAGER->addImage("bear기본공격이미지", ".\\image\\enemyEffect\\effect16.bmp", 411, 134, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("bear스킬공격이미지", ".\\image\\enemyEffect\\effect15.bmp", 660, 123, true, RGB(255, 0, 255), true);
	
	_atkEffect = new effect;
	_atkEffect->init(IMAGEMANAGER->findImage("bear기본공격이미지"), 137, 134, 1.0f, 0.5f);

	_spellEffect = new effect;
	_spellEffect->init(IMAGEMANAGER->findImage("bear스킬공격이미지"), 132, 123, 1.0f, 0.5f);
	
	EFFECTMANAGER->addEffect("bear기본공격이펙트", ".\\image\\enemyEffect\\effect16.bmp", 411, 134, 137, 134, 1.0f, 1.0f, 1000); 
	EFFECTMANAGER->addEffect("bear스킬공격이펙트", ".\\image\\enemyEffect\\effect15.bmp", 660, 123, 132, 123, 1.0f, 1.0f, 1000);
	//===========================================================================================================================

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
	if (_turnEnd == false)
	{
		//카운트 쁠쁠
		_count++;

		//_count가 15보다 작으면 반짝반짝
		if (_count < 15) glitter();

		//에너미의 상태가 공격 또는 스킬쓰는 상태를 랜덤으로 받음 
		if (_state == ENEMY_NULL)
		{
			_state = RND->getFromIntTo(ENEMY_HIT, ENEMY_SPELL);
		}
		
		//에너미 공격 상태면
		if (_state == ENEMY_HIT)
		{
			//_count가 200보다 커지면 공격 이펙트가 그려짐
			if (_count > 200 && _effectFire == true)
			{
				EFFECTMANAGER->play("bear기본공격이펙트", 800, 320);

				_effectFire = false;
			}
		}
		//if (_state == ENEMY_SPELL)
		//{
		//	//_count가 200보다 커지면 공격 이펙트가 그려짐
		//	if (_count > 200 && _effectFire == true)
		//	{
		//		EFFECTMANAGER->play("bear기본공격이펙트", 800, 320);
		//
		//		_effectFire = false;
		//	}
		//}

		//_count가 500보다 크면 턴을 플레이어에게 넘긴다
		if (_count > 500)
		{
			_turnEnd = true;
			_effectFire = true;
			_state = ENEMY_NULL;
			_glitterCount = 0;
			_count = 0;
		}
	}
}

void Bear::render()
{
	IMAGEMANAGER->findImage("bear")->alphaFrameRender(getMemDC(), _x, _y, _frameX, 0, _alpha);
	//IMAGEMANAGER->findImage("bear")->frameRender(getMemDC(), _x, _y);
}

void Bear::bearSkill()
{

}