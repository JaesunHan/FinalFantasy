#include "stdafx.h"
#include "worldMapEnemy.h"

BOOL operator!=(POINT sour, POINT dest);
BOOL operator==(POINT sour, POINT dest);
BOOL operator!=(RECT sour, RECT dest);
BOOL operator==(RECT sour, RECT dest);

worldMapEnemy::worldMapEnemy()
{
}


worldMapEnemy::~worldMapEnemy()
{
}

HRESULT worldMapEnemy::init()
{
	return S_OK;
}

HRESULT worldMapEnemy::init(int enemyX, int enemyY)
{

	_enemy.x = enemyX;
	_enemy.y = enemyY;

	_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);

	_enemyCurrentFrameX = 0;
	_enemyCurrentFrameY = 0;

	_moveSpeed = 2.0f;

	_ast = new aStar;
	_wp = new worldMapPlayer;

	_isCollision = false;
	_isDetect = false;

	return S_OK;
}

void worldMapEnemy::release()
{
}

void worldMapEnemy::update()
{
	worldEnemyImageFrameControl();
	if(_isDetect)
	{ 
		if (_count % MAX_FIND_COUNTER == 0)//(KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			tile start;
			tile end;
			//_count = 0;

			for (int i = 0; i < _worldMap->getWorldMapPOINT().x * _worldMap->getWorldMapPOINT().y; ++i)
			{
				//RECT temp = RectMakeCenter(_worldMap->getWorldMapTiles()[i].getCenterPt().x, _worldMap->getWorldMapTiles()[i].getCenterPt().y, TILE_SIZEX, TILE_SIZEY);
				//if (PtInRect(&temp, PointMake(_enemy.x, _enemy.y)))
				if ((_worldMap->getWorldMapTiles()[i].getCenterPt().x - TILE_SIZEX / 2) / TILE_SIZEX == _enemy.x / TILE_SIZEX &&
					(_worldMap->getWorldMapTiles()[i].getCenterPt().y - TILE_SIZEY / 2) / TILE_SIZEY == (_enemy.y + 30) / TILE_SIZEY)
				{
					start = _worldMap->getWorldMapTiles()[i];
					break;
				}
			}

			for (int i = 0; i < _worldMap->getWorldMapPOINT().x * _worldMap->getWorldMapPOINT().y; ++i)
			{
				//RECT temp = RectMakeCenter(_worldMap->getWorldMapTiles()[i].getCenterPt().x, _worldMap->getWorldMapTiles()[i].getCenterPt().y, TILE_SIZEX, TILE_SIZEY);
				//if (PtInRect(&temp, _wp->getWorldMapPlayerPoint()))
				if ((_worldMap->getWorldMapTiles()[i].getCenterPt().x - TILE_SIZEX / 2) / TILE_SIZEX == _wp->getWorldMapPlayerPoint().x / TILE_SIZEX &&
					(_worldMap->getWorldMapTiles()[i].getCenterPt().y - TILE_SIZEY / 2) / TILE_SIZEY == (_wp->getWorldMapPlayerPoint().y + 30) / TILE_SIZEY)
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
	worldEnemyDetect();
	worldEnemyCollision();

}

void worldMapEnemy::render()
{
	if (_isCollision)
	{
		sprintf(str, "충돌했당");
		TextOut(getMemDC(), 400, 400, str, strlen(str));
	}
	if (!_isCollision)
	{
		sprintf(str1, "충돌안했당");
		TextOut(getMemDC(), 600, 600, str1, strlen(str1));
	}
}

void worldMapEnemy::move()
{
	POINT enemyPos = PointMake(_enemy.x / TILE_SIZEX, (_enemy.y + 30) / TILE_SIZEY);
	RECT collisionArea;

	if (_vCloseList.size() <= 0)
		return;
	else
	{
		/*RECT temp = RectMakeCenter(_vCloseList[_vCloseList.size() - 1].getCenterPt().x,
		_vCloseList[_vCloseList.size() - 1].getCenterPt().y, TILE_SIZEX, TILE_SIZEY);
		if (!PtInRect(&temp, PointMake(_enemy.x, _enemy.y)))
		{
		float angle = getAngle(_enemy.x, _enemy.y, temp.left + TILE_SIZEX / 2, temp.top + TILE_SIZEY / 2);
		_enemy.x += cos(angle) * ENEMY_MOVE_SPEED;
		_enemy.y += -sin(angle) * ENEMY_MOVE_SPEED;

		_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
		}*/
		POINT nextNodeIndex = PointMake(_vCloseList[_vCloseList.size() - 1].getCenterPt().x / TILE_SIZEX,
			_vCloseList[_vCloseList.size() - 1].getCenterPt().y / TILE_SIZEY);
		POINT nextNodePt = PointMake(_vCloseList[_vCloseList.size() - 1].getCenterPt().x - TILE_SIZEX / 2,
			_vCloseList[_vCloseList.size() - 1].getCenterPt().y - TILE_SIZEY / 2);
		RECT nextNodeRect = RectMake(nextNodePt.x, nextNodePt.y, TILE_SIZEX, TILE_SIZEY);

		IntersectRect(&collisionArea, &_rc, &nextNodeRect);

		if (collisionArea != _rc)
		{
			if (_enemy.x > nextNodePt.x)
			{
				if (abs(_enemy.x - nextNodePt.x) < ENEMY_MOVE_SPEED) _enemy.x = nextNodePt.x;
				else _enemy.x -= ENEMY_MOVE_SPEED;
			}
			else if (_enemy.x < nextNodePt.x)
			{
				if (abs(_enemy.x - nextNodePt.x) < ENEMY_MOVE_SPEED)  _enemy.x = nextNodePt.x;
				else _enemy.x += ENEMY_MOVE_SPEED;
			}
			else if (_enemy.y + 30 > nextNodePt.y)
			{
				if (abs(_enemy.y + 30 - nextNodePt.y) < ENEMY_MOVE_SPEED) _enemy.y = nextNodePt.y;
				else _enemy.y -= ENEMY_MOVE_SPEED;
			}
			else if (_enemy.y + 30 < nextNodePt.y)
			{
				if (abs(_enemy.y - nextNodePt.y) < ENEMY_MOVE_SPEED) _enemy.y = nextNodePt.y;
				else _enemy.y += ENEMY_MOVE_SPEED;
			}

			_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
		}
		//else if (enemyPos == nextNodeIndex && _enemy.x > nextNodeCenterPt.x)_enemy.x -= ENEMY_MOVE_SPEED;
		//else if (enemyPos == nextNodeIndex && _enemy.x < nextNodeCenterPt.x)_enemy.x += ENEMY_MOVE_SPEED;
		//else if (enemyPos == nextNodeIndex && _enemy.y > nextNodeCenterPt.y)_enemy.y -= ENEMY_MOVE_SPEED;
		//else if (enemyPos == nextNodeIndex && _enemy.y > nextNodeCenterPt.y)_enemy.y += ENEMY_MOVE_SPEED;
		else
		{
			_vCloseList.erase(_vCloseList.begin() + _vCloseList.size() - 1);
			//_ast->release();
		}
	}
}

void worldMapEnemy::worldEnemyImageFrameControl()
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

void worldMapEnemy::worldEnemyImageControl()
{
}



int worldMapEnemy::tileNum(float x, float y)
{

	//타일 검출에 사용할 타일 인덱스
	int tileX, tileY;	//플레이어 진행방향에 '검출'될 타일 인덱스 계산할 변수 

	int tileNum;

	tileNum = 0;

	//현재 타일 위치를 알기 위해 포지션에서 타일사이즈로 나눠준다.
	tileX = x / TILE_SIZEX;
	tileY = y / TILE_SIZEY;

	//검출될 타일은 ->  만약 5x5 사이즈 타일일때
	//타일y 곱하기 x타일갯수를 하면 0부터 몇번째 Y번째 타일까지인지 계산이되고 
	//그 다음 타일X를 더하면 몇번째 X타일인지가 나온다.
	//월드맵에 저장된 맵 크기의 x값을 받아오고 
	tileNum = tileY * _worldMap->getWorldMapPOINT().x + tileX;

	return tileNum;
}

BOOL operator!=(POINT sour, POINT dest)
{
	if (sour.x != dest.x || sour.y != dest.y)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL operator==(POINT sour, POINT dest)
{
	if (sour.x == dest.x && sour.y == dest.y)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL operator!=(RECT sour, RECT dest)
{
	if (sour.left != dest.left || sour.top != dest.top || sour.right != dest.right || sour.bottom != dest.bottom)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL operator==(RECT sour, RECT dest)
{
	if (sour.left == dest.left && sour.top == dest.top && sour.right == dest.right && sour.bottom == dest.bottom)
	{
		return TRUE;
	}

	return FALSE;
}


void worldMapEnemy::worldEnemyDetect()
{
	if (getDistance(_enemy.x, _enemy.y, _wp->getWorldMapPlayerPoint().x, _wp->getWorldMapPlayerPoint().y) <TILE_SIZEX+100)
	{
		_isDetect = true;
	}
	else if (getDistance(_enemy.x, _enemy.y, _wp->getWorldMapPlayerPoint().x, _wp->getWorldMapPlayerPoint().y) > TILE_SIZEX + 200)
	{
		_isDetect = false;
	}
}

void worldMapEnemy::worldEnemyCollision()
{
	if (getDistance(_enemy.x, _enemy.y, _wp->getWorldMapPlayerPoint().x, _wp->getWorldMapPlayerPoint().y) <= TILE_SIZEX)
	{
		_isCollision = true;
	}
}

