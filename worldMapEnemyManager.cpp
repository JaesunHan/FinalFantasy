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
	//�÷��̾�� �浹��, �Ұ��� üũ�ϰ�, ���� �浹�� Ȯ���� �Ǿ����� ���Ϳ��� ������ ���ش�.
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
