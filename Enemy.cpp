#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy()
{
}


Enemy::~Enemy()
{

}

HRESULT Enemy::init(int x, int y)
{
	_x = x;
	_y = y;

	return S_OK;
}

void Enemy::update()
{

}

void Enemy::render() 
{

}

void Enemy::enemyAttack()
{
	if (_state == ENEMY_HIT)
	{

	}
}
