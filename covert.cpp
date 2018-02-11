#include "stdafx.h"
#include "covert.h"
#include "battlePlayerMother.h"

covert::covert()
{
	//에너미 이미지
	IMAGEMANAGER->addFrameImage("covert", ".\\image\\enemyImg\\covert.bmp", 260, 91, 2, 1, true, RGB(255, 0, 255), true);

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

}

void covert::render()
{
	IMAGEMANAGER->findImage("covert")->frameRender(getMemDC(), _x, _y);
}


void covert::bearSkill()
{

}
