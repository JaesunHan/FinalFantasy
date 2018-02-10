#include "stdafx.h"
#include "siren.h"


siren::siren()
{
	//에너미 이미지
	//IMAGEMANAGER->addFrameImage("bear", ".\\image\\enemyImg\\bear.bmp", 160, 103, 2, 1, true, RGB(255, 0, 255));

	_Lv = 50;										//레벨
	_maxEXP = RND->getFromIntTo(2800, 3200);		//현재 경험치, 최대 경험치
	_gold = RND->getFromIntTo(1100, 1300);			//돈

	_curHP = _maxHP = 10050;						//현재 체력, 최대 체력
	_curMP = _maxMP = 12850;						//현재 마력, 최대 마력

	_attack = 13;									//물리 공격력
	_magic = 15;									//마법 공격력

	_m_Def = 170;									//마법 방어력
	_a_Def = 70;									//물리 방어력

	_speed = 35;									//공격 타이머

	_evasion = 0;									//회피율
	_hitRate = 100;									//명중률
	_block = 0;										//방어율
}


siren::~siren()
{

}

void siren::update()
{

}

void siren::render()
{

}


void siren::bearSkill()
{

}
