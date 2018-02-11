#include "stdafx.h"
#include "samurai.h"
#include "battlePlayerMother.h"

samurai::samurai()
{
	//에너미 이미지
	IMAGEMANAGER->addFrameImage("samurai", ".\\image\\enemyImg\\samurai.bmp", 108, 103, 2, 1, true, RGB(255, 0, 255), true);

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

}

void samurai::render()
{
	IMAGEMANAGER->findImage("samurai")->frameRender(getMemDC(), _x, _y);
}


void samurai::bearSkill()
{

}
