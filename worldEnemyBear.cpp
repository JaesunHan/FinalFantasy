#include "stdafx.h"
#include "worldEnemyBear.h"


worldEnemyBear::worldEnemyBear()
{
}


worldEnemyBear::~worldEnemyBear()
{
}

HRESULT worldEnemyBear::init(int enemyX, int enemyY)
{
	IMAGEMANAGER->addFrameImage("월드맵곰탱이왼쪽", ".//image//enemyImg//worldEnemy_bear_left.bmp", 174, 34, 6, 1, true, RGB(255, 0, 255));

	_image = IMAGEMANAGER->addFrameImage("월드맵곰탱이", ".//image//enemyImg//worldEnemy_bear.bmp", 170, 34, 6, 1, true, RGB(255, 0, 255));

	_enemy.x = enemyX;
	_enemy.y = enemyY;

	_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);

	_enemyCurrentFrameX = 0;
	_enemyCurrentFrameY = 0;

	_moveSpeed = 2.0f;

	_ast = new aStar;
	_wp = new worldMapPlayer;

	_isCollision = false;


	_enemyType = ENEMY_BEAR;

	return S_OK;
}

void worldEnemyBear::release()
{
}

void worldEnemyBear::update()
{
	worldEnemyImageFrameControl();
	if (_count % 20 == 0)//(KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		tile start;
		tile end;

		for (int i = 0; i < _worldMap->getWorldMapPOINT().x * _worldMap->getWorldMapPOINT().y; ++i)
		{
			//RECT temp = RectMakeCenter(_worldMap->getWorldMapTiles()[i].getCenterPt().x, _worldMap->getWorldMapTiles()[i].getCenterPt().y, TILE_SIZEX, TILE_SIZEY);
			//if (PtInRect(&temp, PointMake(_enemy.x, _enemy.y)))
			if (_worldMap->getWorldMapTiles()[i].getCenterPt().x / TILE_SIZEX == _enemy.x / TILE_SIZEX &&
				_worldMap->getWorldMapTiles()[i].getCenterPt().y / TILE_SIZEY == _enemy.y / TILE_SIZEY)
			{
				start = _worldMap->getWorldMapTiles()[i];
				break;
			}
		}

		for (int i = 0; i <_worldMap->getWorldMapPOINT().x * _worldMap->getWorldMapPOINT().y; ++i)
		{
			//RECT temp = RectMakeCenter(_worldMap->getWorldMapTiles()[i].getCenterPt().x, _worldMap->getWorldMapTiles()[i].getCenterPt().y, TILE_SIZEX, TILE_SIZEY);
			//if (PtInRect(&temp, _wp->getWorldMapPlayerPoint()))
			if (_worldMap->getWorldMapTiles()[i].getCenterPt().x / TILE_SIZEX == _wp->getWorldMapPlayerPoint().x / TILE_SIZEX &&
				_worldMap->getWorldMapTiles()[i].getCenterPt().y / TILE_SIZEY == _wp->getWorldMapPlayerPoint().y / TILE_SIZEY)
			{
				//!isOpen이면 못가게
				if (!_worldMap->getWorldMapTiles()[i].getIsOpen()) return;
				end = _worldMap->getWorldMapTiles()[i];
				break;
			}
		}

		_ast->init(_worldMap->getWorldMapTiles(), _worldMap->getWorldMapPOINT().x, _worldMap->getWorldMapPOINT().y, start, end);
		_vCloseList = _ast->pathFinder(start);
	}

	this->move();

	//플레이어와 에너미의 위치에 따른 에너미 보는 방향 변경
	if (_enemy.x <= _wp->getWorldMapPlayerPoint().x)
	{
		_enemyDirection = ENEMYDIRECTION_LEFT;
	}
	else if (_enemy.x > _wp->getWorldMapPlayerPoint().x)
	{
		_enemyDirection = ENEMYDIRECTION_RIGHT;
	}

}

void worldEnemyBear::render()
{
	worldEnemyImageControl();

	//_image->frameRender(getMemDC(), _enemy.x, _enemy.y, _enemyCurrentFrameX, 0);
	if (_isDebug)
	{
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	}
}

void worldEnemyBear::move()
{
	if (_vCloseList.size() <= 0)
		return;
	else
	{
		RECT temp = RectMakeCenter(_vCloseList[_vCloseList.size() - 1].getCenterPt().x,
			_vCloseList[_vCloseList.size() - 1].getCenterPt().y, TILE_SIZEX, TILE_SIZEY);
		if (!PtInRect(&temp, PointMake(_enemy.x, _enemy.y)))
		{
			float angle = getAngle(_enemy.x, _enemy.y, _vCloseList[_vCloseList.size() - 1].getCenterPt().x, _vCloseList[_vCloseList.size() - 1].getCenterPt().y);
			_enemy.x += cos(angle) * 5;
			_enemy.y += -sin(angle) * 5;


			_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
		}
		else
		{
			_ast->release();
		}
	}
}

void worldEnemyBear::worldEnemyImageFrameControl()
{
	_count++;

	if (_count % 10 == 0)
	{
		_enemyCurrentFrameX++;

		if (_enemyCurrentFrameX == _image->getMaxFrameX())
		{
			_enemyCurrentFrameX = 0;
		}
	}
}

void worldEnemyBear::worldEnemyImageControl()
{
	//플레이어와 에너미의 위치에 따른 에너미 보는 방향 변경
	switch (_enemyDirection)
	{
	case ENEMYDIRECTION_RIGHT: _image = IMAGEMANAGER->findImage("월드맵곰탱이");
		_image->frameRender(getMemDC(), _enemy.x, _enemy.y, _enemyCurrentFrameX, 0);

		break;
	case ENEMYDIRECTION_LEFT: _image = IMAGEMANAGER->findImage("월드맵곰탱이왼쪽");
		_image->frameRender(getMemDC(), _enemy.x, _enemy.y, _enemyCurrentFrameX, 0);
		break;
	}


}
