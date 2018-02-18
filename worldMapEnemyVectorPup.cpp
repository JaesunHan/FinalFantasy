#include "stdafx.h"
#include "worldMapEnemyVectorPup.h"


worldMapEnemyVectorPup::worldMapEnemyVectorPup()
{
}


worldMapEnemyVectorPup::~worldMapEnemyVectorPup()
{
}

HRESULT worldMapEnemyVectorPup::init(int enemyX, int enemyY)
{
	//마더 클래스 정보 가져오고 
	worldMapEnemy::init(enemyX, enemyY);
	IMAGEMANAGER->addFrameImage("벡터펍왼쪽", ".//image//enemyImg//worldEnemy_VectorPup_left.bmp", 350, 46, 4, 1, true, RGB(255, 0, 255));
	_image = IMAGEMANAGER->addFrameImage("벡터펍", ".//image//enemyImg//worldEnemy_VectorPup_right.bmp", 350, 46, 4, 1, true, RGB(255, 0, 255));

	_enemyType = ENEMY_VECTORPUP;

	_vectorPupCount = 0;
	return S_OK;




	return S_OK;
}

void worldMapEnemyVectorPup::release()
{
}

void worldMapEnemyVectorPup::update()
{
	worldMapEnemy::update();
	this->move();
}

void worldMapEnemyVectorPup::render()
{
	worldEnemyImageControl();

	if (_isDebug)
	{
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	}
}

void worldMapEnemyVectorPup::move()
{
	if (!_isDetect)
	{
		_vectorPupCount++;
		if (_vectorPupCount > 0 && _vectorPupCount < 30)
		{
			_enemy.x += 2;

			_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
			//월드맵 타일속성을 받아서 만약 그 속성이 움직이지 못하는 속성이면 반대움직임값줘서 움직임 차감하자.
			if (_worldMap->getWorldMapTiles()[tileNum(_rc.right, _rc.top + 3)].getTerrainAttr() == ATTR_UNMOVE ||
				_worldMap->getWorldMapTiles()[tileNum(_rc.right, _rc.bottom - 3)].getTerrainAttr() == ATTR_UNMOVE ||
				_worldMap->getWorldMapTiles()[tileNum(_rc.left, _rc.top + 3)].getTerrainAttr() == ATTR_UNMOVE ||
				_worldMap->getWorldMapTiles()[tileNum(_rc.left, _rc.bottom - 3)].getTerrainAttr() == ATTR_UNMOVE ||
				_worldMap->getWorldMapTiles()[tileNum(_rc.left + 3, _rc.top)].getTerrainAttr() == ATTR_UNMOVE ||
				_worldMap->getWorldMapTiles()[tileNum(_rc.right - 3, _rc.top)].getTerrainAttr() == ATTR_UNMOVE ||
				_worldMap->getWorldMapTiles()[tileNum(_rc.left + 3, _rc.bottom)].getTerrainAttr() == ATTR_UNMOVE ||
				_worldMap->getWorldMapTiles()[tileNum(_rc.right - 3, _rc.bottom)].getTerrainAttr() == ATTR_UNMOVE
				)
			{
				_enemy.x -= 2;
				_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
			}
		}
		if (_vectorPupCount > 30 && _vectorPupCount < 60)
		{
			_enemy.x -= 2;
			_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
			if (_worldMap->getWorldMapTiles()[tileNum(_rc.right, _rc.top + 3)].getTerrainAttr() == ATTR_UNMOVE ||
				_worldMap->getWorldMapTiles()[tileNum(_rc.right, _rc.bottom - 3)].getTerrainAttr() == ATTR_UNMOVE ||
				_worldMap->getWorldMapTiles()[tileNum(_rc.left, _rc.top + 3)].getTerrainAttr() == ATTR_UNMOVE ||
				_worldMap->getWorldMapTiles()[tileNum(_rc.left, _rc.bottom - 3)].getTerrainAttr() == ATTR_UNMOVE ||
				_worldMap->getWorldMapTiles()[tileNum(_rc.left + 3, _rc.top)].getTerrainAttr() == ATTR_UNMOVE ||
				_worldMap->getWorldMapTiles()[tileNum(_rc.right - 3, _rc.top)].getTerrainAttr() == ATTR_UNMOVE ||
				_worldMap->getWorldMapTiles()[tileNum(_rc.left + 3, _rc.bottom)].getTerrainAttr() == ATTR_UNMOVE ||
				_worldMap->getWorldMapTiles()[tileNum(_rc.right - 3, _rc.bottom)].getTerrainAttr() == ATTR_UNMOVE)
			{
				_enemy.x += 2;
				_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
			}
		}
		if (_vectorPupCount >= 65)
		{
			_vectorPupCount = 0;
		}
	}
	worldMapEnemy::move();
}

void worldMapEnemyVectorPup::worldEnemyImageFrameControl()
{
	worldMapEnemy::worldEnemyImageFrameControl();
}

void worldMapEnemyVectorPup::worldEnemyImageControl()
{
	//플레이어와 에너미의 위치에 따른 에너미 보는 방향 변경
	switch (_enemyDirection)
	{
	case ENEMYDIRECTION_RIGHT: _image = IMAGEMANAGER->findImage("벡터펍왼쪽");
		_image->frameRender(getMemDC(), _enemy.x, _enemy.y, _enemyCurrentFrameX, 0);

		break;
	case ENEMYDIRECTION_LEFT: _image = IMAGEMANAGER->findImage("벡터펍");
		_image->frameRender(getMemDC(), _enemy.x, _enemy.y, _enemyCurrentFrameX, 0);
		break;
	}
}
