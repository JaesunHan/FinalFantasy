#include "stdafx.h"
#include "bossAtma.h"
#include "battlePlayerMother.h"

bossAtma::bossAtma()
{
	//에너미 이미지
	IMAGEMANAGER->addFrameImage("bossAtma", ".\\image\\enemyImg\\bossAtma.bmp", 1000, 500, 2, 1, true, RGB(255, 0, 255), true);

	//에너미 이펙트 이미지
	IMAGEMANAGER->addImage("bossAtma기본공격이미지", ".\\image\\enemyEffect\\effect4.bmp", 585, 85, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("bossAtma스킬공격이미지", ".\\image\\enemyEffect\\effect4.bmp", 585, 85, true, RGB(255, 0, 255), true);

	_atkEffect = new effect;
	_atkEffect->init(IMAGEMANAGER->findImage("bossAtma기본공격이미지"), 117, 85, 1.0f, 0.5f);

	_spellEffect = new effect;
	_spellEffect->init(IMAGEMANAGER->findImage("bossAtma스킬공격이미지"), 117, 85, 1.0f, 0.5f);

	EFFECTMANAGER->addEffect("bossAtma기본공격이펙트", ".\\image\\enemyEffect\\effect4.bmp", 585, 85, 117, 85, 1.0f, 1.0f, 1000);
	EFFECTMANAGER->addEffect("bossAtma스킬공격이펙트", ".\\image\\enemyEffect\\effect4.bmp", 585, 85, 117, 85, 1.0f, 1.0f, 1000);

	_Lv = 67;										//레벨
	_maxEXP = 0;	 								//현재 경험치, 최대 경험치
	_gold = 0;										//돈

	_curHP = _maxHP = 55000;						//현재 체력, 최대 체력
	_curMP = _maxMP = 19000;						//현재 마력, 최대 마력

	_attack = 20;									//물리 공격력
	_magic = 10;									//마법 공격력

	_m_Def = 70;									//마법 방어력
	_a_Def = 75;									//물리 방어력

	_speed = 63;									//공격 타이머

	_evasion = 0;									//회피율
	_hitRate = 100;									//명중률
	_block = 0;										//방어율
}


bossAtma::~bossAtma()
{

}

void bossAtma::update()
{
	if (_turnEnd == false)
	{
		_count++;
		if (_count < 50) glitter();

		if (_effectFire == true)
		{
			EFFECTMANAGER->play("bossAtma기본공격이펙트", 800, 320);

			_effectFire = false;
		}
		//if (_effectFire == true)
		//{
		//	EFFECTMANAGER->play("bossAtma스킬공격이펙트", 800, 320);
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

void bossAtma::render()
{
	IMAGEMANAGER->findImage("bossAtma")->frameRender(getMemDC(), _x, _y);
}


void bossAtma::bearSkill()
{

}
