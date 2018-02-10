#include "stdafx.h"
#include "tornadoShark.h"


tornadoShark::tornadoShark()
{
	//에너미 이미지
	//IMAGEMANAGER->addFrameImage("bear", ".\\image\\enemyImg\\bear.bmp", 160, 103, 2, 1, true, RGB(255, 0, 255));

	_Lv = 29;										//레벨
	_maxEXP = RND->getFromIntTo(500, 550);	 		//현재 경험치, 최대 경험치
	_gold = RND->getFromIntTo(1100, 1300);			//돈

	_curHP = _maxHP = 1318;							//현재 체력, 최대 체력
	_curMP = _maxMP = 100;							//현재 마력, 최대 마력

	_attack = 15;									//물리 공격력
	_magic = 10;									//마법 공격력

	_m_Def = 153;									//마법 방어력
	_a_Def = 102;									//물리 방어력

	_speed = 30;									//공격 타이머

	_evasion = 0;									//회피율
	_hitRate = 100;									//명중률
	_block = 0;										//방어율
}


tornadoShark::~tornadoShark()
{

}

void tornadoShark::update()
{

}

void tornadoShark::render()
{

}


void tornadoShark::bearSkill()
{

}
