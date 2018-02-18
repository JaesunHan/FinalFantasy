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
	for (int i = 0; i < WORLDMAPENEMY; ++i)
	{
		worldMapEnemy* _worldMapEnemy;

		switch (i % (RND->getInt(3) + 1))
		{
		case ENEMY_BEAR:
			_worldMapEnemy = new worldEnemyBear;
			_worldMapEnemy->init(700 - i * 50, 340 - i * 30);
			break;

		case ENEMY_SKELETON:
			_worldMapEnemy = new worldMapEnemySamurai;
			_worldMapEnemy->init(400 + i * 50, 200 + i * 20);
			break;
		
		case ENEMY_VECTORPUP:
			_worldMapEnemy = new worldMapEnemyVectorPup;
			_worldMapEnemy->init(800 - i * 50, 500 - i * 50);
		}

		_vWME.push_back(_worldMapEnemy);
	}

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

void worldMapEnemyManager::render()
{
	for (int i = 0; i < _vWME.size(); ++i)
	{
		_vWME[i]->render();
	}
}

void worldMapEnemyManager::beforeRender()
{
	for (int i = 0; i < _vWME.size(); ++i)
	{
		if (_vWME[i]->getWorldMapEnemyPoint().y <= _playerPos.y)
			_vWME[i]->render();
	}
}

void worldMapEnemyManager::afterRender()
{
	for (int i = 0; i < _vWME.size(); ++i)
	{
		if (_vWME[i]->getWorldMapEnemyPoint().y > _playerPos.y)
			_vWME[i]->render();
	}
}

void worldMapEnemyManager::worldEmenyDelete(int arrNum)
{
	SAFE_DELETE(_vWME[arrNum]);
	_vWME.erase(_vWME.begin() + arrNum);
}
