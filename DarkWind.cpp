#include "stdafx.h"
#include "DarkWind.h"
#include "battlePlayerMother.h"

DarkWind::DarkWind()
{
	//에너미 이미지
	IMAGEMANAGER->addFrameImage("darkWind", ".\\image\\enemyImg\\DarkWind.bmp", 132, 81, 2, 1, true, RGB(255, 0, 255), true);
	
	_Lv = 5;										//레벨
	_maxEXP = RND->getFromIntTo(25, 30);			//현재 경험치, 최대 경험치
	_gold = RND->getFromIntTo(38, 42);				//돈

	_curHP = _maxHP = 34;							//현재 체력, 최대 체력
	_curMP = _maxMP = 0;							//현재 마력, 최대 마력

	_attack = 13;									//물리 공격력
	_magic = 10;									//마법 공격력

	_m_Def = 140;									//마법 방어력
	_a_Def = 55;									//물리 방어력

	_speed = 30;									//공격 타이머

	_evasion = 0;									//회피율
	_hitRate = 100;									//명중률
	_block = 0;										//방어율
}


DarkWind::~DarkWind()
{

}

//HRESULT DarkWind::init()
//{
//
//
//	return S_OK;
//}

void DarkWind::update()
{

}

void DarkWind::render()
{
	IMAGEMANAGER->findImage("darkWind")->frameRender(getMemDC(), _x, _y);
}

void DarkWind::darkWindSkill()
{

}