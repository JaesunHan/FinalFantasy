#include "stdafx.h"
#include "worldMapEnemyManager.h"


worldMapEnemyManager::worldMapEnemyManager()
{
}


worldMapEnemyManager::~worldMapEnemyManager()
{
}

HRESULT worldMapEnemyManager::init()
{
	/*for (int i = 0; i < WORLDMAPENEMY; ++i)
	{
		worldMapEnemy* _worldMapEnemy;

		switch (i % (RND->getInt(3) + 1))
		{
		case ENEMY_BEAR:
			_worldMapEnemy = new worldEnemyBear;
			_worldMapEnemy->init(700 - i * 50, 340 - i * 30, ENEMYPATTERN_ONE);
			break;

		case ENEMY_SKELETON:
			_worldMapEnemy = new worldMapEnemySamurai;
			_worldMapEnemy->init(400 + i * 50, 200 + i * 20, ENEMYPATTERN_THREE);
			break;
		
		case ENEMY_VECTORPUP:
			_worldMapEnemy = new worldMapEnemyVectorPup;
			_worldMapEnemy->init(800 - i * 50, 500 - i * 50, ENEMYPATTERN_TWO);
		}

		_vWME.push_back(_worldMapEnemy);
	}*/

	//for (int i = 0; i < 10; ++i)
	//{
	//	//_worldMapEmeneySamurai[i] = new worldMapEnemySamurai;
	//	_worldMapEmeneySamurai[0].init(1300, 600, ENEMYPATTERN_ONE);
	//	_worldMapEmeneySamurai[1].init(1400, 200, ENEMYPATTERN_TWO);
	//	_worldMapEmeneySamurai[2].init(1100, 600, ENEMYPATTERN_THREE);
	//	_worldMapEmeneySamurai[3].init(1000, 900, ENEMYPATTERN_TWO);
	//	_worldMapEmeneySamurai[4].init(900, 400, ENEMYPATTERN_THREE);
	//	_worldMapEmeneySamurai[5].init(800, 400, ENEMYPATTERN_ONE);
	//	_worldMapEmeneySamurai[6].init(700, 400, ENEMYPATTERN_ONE);
	//	_worldMapEmeneySamurai[7].init(600, 400, ENEMYPATTERN_THREE);
	//	_worldMapEmeneySamurai[8].init(1500, 400, ENEMYPATTERN_TWO);
	//	_worldMapEmeneySamurai[9].init(300, 1500, ENEMYPATTERN_THREE);
	//	_vWME.push_back(&_worldMapEmeneySamurai[i]);
	//}
	//1536, 1500

	_worldMapTreasureBox.init(1536, 1500, ENEMYPATTERN_ONE);
	_vWME.push_back(&_worldMapTreasureBox);
	
	
	for (int i = 0; i < 3; ++i)
	{
		_worldEnemyBear[0].init(400, 1400, ENEMYPATTERN_ONE);
		_worldEnemyBear[1].init(300, 800, ENEMYPATTERN_TWO);
		_worldEnemyBear[2].init(1200, 600, ENEMYPATTERN_THREE);
		_worldMapEmeneySamurai[0].init(500, 1400, ENEMYPATTERN_ONE);
		_worldMapEmeneySamurai[1].init(1300, 400, ENEMYPATTERN_TWO);
		_worldMapEmeneySamurai[2].init(400, 600, ENEMYPATTERN_THREE);
		_worldMapEnemyVectorPup[0].init(200, 300, ENEMYPATTERN_ONE);
		_worldMapEnemyVectorPup[1].init(550, 1000, ENEMYPATTERN_TWO);
		_worldMapEnemyVectorPup[2].init(300, 1300, ENEMYPATTERN_THREE);
		_vWME.push_back(&_worldEnemyBear[i]);
		_vWME.push_back(&_worldMapEmeneySamurai[i]);
		_vWME.push_back(&_worldMapEnemyVectorPup[i]);
	}

	_worldEnemyBear[3].init(1532, 1400, ENEMYPATTERN_FOUR);
	_vWME.push_back(&_worldEnemyBear[3]);



	return S_OK;
}

void worldMapEnemyManager::release()
{
	//플레이어와 충돌시, 불값을 체크하고, 만약 충돌이 확인이 되어지면 벡터에서 릴리즈 해준다.
}

void worldMapEnemyManager::update()
{
	for (int i = 0; i < _vWME.size(); ++i)
	{
		_vWME[i]->update();
	}
}

void worldMapEnemyManager::render(HDC hdc, POINT movePt)
{
	for (int i = 0; i < _vWME.size(); ++i)
	{
		_vWME[i]->render(hdc, movePt);
	}
}

void worldMapEnemyManager::beforeRender(HDC hdc, POINT movePt)
{
	for (int i = 0; i < _vWME.size(); ++i)
	{
		if (_vWME[i]->getWorldMapEnemyPoint().y <= _playerPos.y)
			_vWME[i]->render(hdc, movePt);
	}
}

void worldMapEnemyManager::afterRender(HDC hdc, POINT movePt)
{
	for (int i = 0; i < _vWME.size(); ++i)
	{
		if (_vWME[i]->getWorldMapEnemyPoint().y > _playerPos.y)
			_vWME[i]->render(hdc, movePt);
	}
}

void worldMapEnemyManager::worldEmenyDelete(int arrNum)
{
	//SAFE_DELETE(_vWME[arrNum]);
	_vWME.erase(_vWME.begin() + arrNum);
}
