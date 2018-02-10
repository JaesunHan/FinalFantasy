#include "stdafx.h"
#include "guard.h"
#include "battlePlayerMother.h"

guard::guard()
{
	//에너미 이미지
	IMAGEMANAGER->addFrameImage("guard", ".\\image\\enemyImg\\guard.bmp", 132, 62, 2, 1, true, RGB(255, 0, 255));

	_Lv = 5;										//레벨
	_maxEXP = RND->getFromIntTo(45, 50);	 		//현재 경험치, 최대 경험치
	_gold = RND->getFromIntTo(45, 50);				//돈

	_curHP = _maxHP = 40;							//현재 체력, 최대 체력
	_curMP = _maxMP = 15;							//현재 마력, 최대 마력

	_attack = 16;									//물리 공격력
	_magic = 6;										//마법 공격력

	_m_Def = 140;									//마법 방어력
	_a_Def = 100;									//물리 방어력

	_speed = 30;									//공격 타이머

	_evasion = 0;									//회피율
	_hitRate = 100;									//명중률
	_block = 0;										//방어율
}


guard::~guard()
{

}

void guard::update()
{

}

void guard::render()
{
	IMAGEMANAGER->findImage("guard")->frameRender(getMemDC(), _x, _y);
}


void guard::bearSkill()
{

}
