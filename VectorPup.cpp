#include "stdafx.h"
#include "VectorPup.h"
#include "battlePlayerMother.h"

VectorPup::VectorPup()
{
	//에너미 이미지
	IMAGEMANAGER->addFrameImage("vectorPup", ".\\image\\enemyImg\\VectorPup.bmp", 184, 46, 2, 1, true, RGB(255, 0, 255));
	
	_Lv = 11;										//레벨
	_maxEXP = RND->getFromIntTo(125, 135);	 		//현재 경험치, 최대 경험치
	_gold = RND->getFromIntTo(75, 90);				//돈

	_curHP = _maxHP = 166;							//현재 체력, 최대 체력
	_curMP = _maxMP = 10;							//현재 마력, 최대 마력

	_attack = 14;									//기본 데미지
	_magic = 10;									//마법 데미지

	_m_Def = 150;									//마법 방어력
	_a_Def = 80;									//물리 방어력

	_speed = 25;									//공격 타이머

	_evasion = 0;									//회피율
	_hitRate = 100;									//명중률
	_block = 0;										//방어율
}

VectorPup::~VectorPup()
{

}

//HRESULT VectorPup::init()
//{
//	
//
//	return S_OK;
//}

void VectorPup::update()
{
	//enemyAttack();
}

void VectorPup::render() 
{
	IMAGEMANAGER->findImage("vectorPup")->frameRender(getMemDC(), _x, _y);
}

void VectorPup::vectorPupAttack()
{
	

}

void VectorPup::vectorPupSkill()
{

}