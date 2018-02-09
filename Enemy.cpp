#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{

}

HRESULT Enemy::init()
{
	_Lv = 1;
	_curEXP = _maxEXP = 100;
	_curHP = _maxHP = 100;
	_curMP = _maxMP = 100;
	_strength = 10;
	_magic = 10;
	_speed = 10;
	_m_Def = 10;
	_a_Def = 10;
	_attack = 10;
	_evasion = 10;
	_hitRate = 10;
	_block = 10;


	_gold = 10;

	return S_OK;
}

void Enemy::release()
{

}

void Enemy::update() 
{

}

void Enemy::render() 
{

}
