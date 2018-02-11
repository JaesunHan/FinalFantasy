#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy()
{
}


Enemy::~Enemy()
{

}

//	     몬스터를 뿌려줄 x,     y
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

//몬스터 턴이 되면
void Enemy::enemyTurn(int damage)
{
	if (_state == RND->getFromIntTo(ENEMY_HIT, ENEMY_SPELL));
	{
		//물리 데미지 공식
		//공식 = Damage = Level * Level * (Battle Power * 4 + Vigor) / 256
		//Vigor = 56 ~ 63 랜덤수
		int _2Lv;
		_2Lv = _Lv * _Lv;
		
		_damage = _2Lv * (damage * 4 + (RND->getFromIntTo(56, 63))) / 256; 
		
		//스킬 데미지 공식
		_spellDamage = _damage * RND->getFromFloatTo(1.2f, 2.5f);

		if (_state == ENEMY_HIT)
		{
			
		}
		
		if (_state == ENEMY_SPELL && _curMP > 0)
		{
		}
	}
}
