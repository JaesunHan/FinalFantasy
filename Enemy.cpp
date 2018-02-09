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
	IMAGEMANAGER->addFrameImage("bear", ".\\image\\enemyImg\\bear.bmp", 160, 103, 2, 1, true, RGB(255, 0, 255));

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
		int _2Lv;
		_2Lv = _Lv * _Lv;

		//몬스터가 플레이어를 공격할때 
		_damage = _2Lv * (_attack * 4 + (RND->getFromIntTo(56, 63))) / 256;
	}
}
