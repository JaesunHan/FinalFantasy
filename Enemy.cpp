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
	//에너미 이펙트 이미지
	//IMAGEMANAGER->addImage("이펙트", ".\\image\\enemyEffect\\effect4.bmp", 585, 85, true, RGB(255, 0, 255));
	//
	//_test = new effect;
	//_test->init(IMAGEMANAGER->findImage("이펙트"), 117, 85, 1.0f, 0.5f);
	//
	//EFFECTMANAGER->addEffect("폭발", ".\\image\\enemyEffect\\effect4.bmp", 585, 85, 117, 85, 1.0f, 1.0f, 1000); 
	
	_x = x;
	_y = y;

	return S_OK;
}

void Enemy::update()
{
	//if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	//{
	//	EFFECTMANAGER->play("폭발", _ptMouse.x, _ptMouse.y);
	//}
	//
	//EFFECTMANAGER->play("폭발", _ptMouse.x, _ptMouse.y);
	//
	//_test->update();
	//EFFECTMANAGER->update();
}

void Enemy::render() 
{
	//_test->render();
	//EFFECTMANAGER->render();
}

void Enemy::enemyAttack(int damage)
{
	if (_state == ENEMY_HIT)
	{
		int _2Lv;
		_2Lv = _Lv * _Lv;

		//몬스터가 플레이어를 공격할때 
		//공식 = Damage = Level * Level * (Battle Power * 4 + Vigor) / 256
		//Vigor = 56 ~ 63 랜덤수
		_damage = _2Lv * (damage * 4 + (RND->getFromIntTo(56, 63))) / 256;


	}
}
