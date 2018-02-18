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
					//!isOpen�̸� ������
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

	//�÷��̾�� ���ʹ��� ��ġ�� ���� ���ʹ� ���� ���� ����
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
		sprintf(str, "�浹�ߴ�");
		TextOut(getMemDC(), 400, 400, str, strlen(str));
	}
	if (!_isCollision)
	{
		sprintf(str1, "�浹���ߴ�");
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

	//Ÿ�� ���⿡ ����� Ÿ�� �ε���
	int tileX, tileY;	//�÷��̾� ������⿡ '����'�� Ÿ�� �ε��� ����� ���� 

	int tileNum;

	tileNum = 0;

	//���� Ÿ�� ��ġ�� �˱� ���� �����ǿ��� Ÿ�ϻ������ �����ش�.
	tileX = x / TILE_SIZEX;
	tileY = y / TILE_SIZEY;

	//����� Ÿ���� ->  ���� 5x5 ������ Ÿ���϶�
	//Ÿ��y ���ϱ� xŸ�ϰ����� �ϸ� 0���� ���° Y��° Ÿ�ϱ������� ����̵ǰ� 
	//�� ���� Ÿ��X�� ���ϸ� ���° XŸ�������� ���´�.
	//����ʿ� ����� �� ũ���� x���� �޾ƿ��� 
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

