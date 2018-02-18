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

		switch (i)
		{
		case ENEMY_BEAR:
			_worldMapEnemy = new worldEnemyBear;
			_worldMapEnemy->init(700, 340);
			break;

		case ENEMY_SKELETON:
			_worldMapEnemy = new worldMapEnemySamurai;
			_worldMapEnemy->init(400, 200);
			break;
		
		case ENEMY_VECTORPUP:
			_worldMapEnemy = new worldMapEnemyVectorPup;
			_worldMapEnemy->init(800, 500);
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
