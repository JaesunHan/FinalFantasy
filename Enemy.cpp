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

void Enemy::enemyAttack(int damage)
{
	if (_state == ENEMY_HIT)
	{
		int _2Lv;
		_2Lv = _Lv * _Lv;

		//���Ͱ� �÷��̾ �����Ҷ� 
		//���� = Damage = Level * Level * (Battle Power * 4 + Vigor) / 256
		//Vigor = 56 ~ 63 ������
		_damage = _2Lv * (damage * 4 + (RND->getFromIntTo(56, 63))) / 256;
	}
}
