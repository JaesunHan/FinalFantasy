#include "stdafx.h"
#include "bossAtma.h"
#include "battlePlayerMother.h"

bossAtma::bossAtma()
{
	//에너미 이미지
	IMAGEMANAGER->addFrameImage("bossAtma", ".\\image\\enemyImg\\bossAtma.bmp", 1000, 500, 2, 1, true, RGB(255, 0, 255));

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

}

void bossAtma::render()
{
	IMAGEMANAGER->findImage("bossAtma")->frameRender(getMemDC(), _x, _y);
}


void bossAtma::bearSkill()
{

}
