#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy()
{
}


Enemy::~Enemy()
{

}

//	     ���͸� �ѷ��� x,     y
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

//���� ���� �Ǹ�
void Enemy::enemyTurn(int damage)
{
	if (_state == RND->getFromIntTo(ENEMY_HIT, ENEMY_SPELL));
	{
		//���� ������ ����
		//���� = Damage = Level * Level * (Battle Power * 4 + Vigor) / 256
		//Vigor = 56 ~ 63 ������
		int _2Lv;
		_2Lv = _Lv * _Lv;
		
		_damage = _2Lv * (damage * 4 + (RND->getFromIntTo(56, 63))) / 256; 
		
		//��ų ������ ����
		_spellDamage = _damage * RND->getFromFloatTo(1.2f, 2.5f);

		if (_state == ENEMY_HIT)
		{
			
		}
		
		if (_state == ENEMY_SPELL && _curMP > 0)
		{
		}
	}
}
