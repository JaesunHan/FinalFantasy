#include "stdafx.h"
#include "worldMapEnemy.h"


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



	_isCollision = false;




	return S_OK;
}

void worldMapEnemy::release()
{
}

void worldMapEnemy::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		tile start;
		tile end;

		for (int i = 0; i < _worldMap->getWorldMapPOINT().x * _worldMap->getWorldMapPOINT().y; ++i)
		{
			RECT temp = RectMakeCenter(_worldMap->getWorldMapTiles()[i].getCenterPt().x, _worldMap->getWorldMapTiles()[i].getCenterPt().y, TILE_SIZEX, TILE_SIZEY);
			if (PtInRect(&temp, PointMake(_enemy.x, _enemy.y)))
			{
				start = _worldMap->getWorldMapTiles()[i];
				break;
			}
		}

		for (int i = 0; i <_worldMap->getWorldMapPOINT().x * _worldMap->getWorldMapPOINT().y; ++i)
		{
			RECT temp = RectMakeCenter(_worldMap->getWorldMapTiles()[i].getCenterPt().x, _worldMap->getWorldMapTiles()[i].getCenterPt().y, TILE_SIZEX, TILE_SIZEY);
			if (PtInRect(&temp, _ptMouse))
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

	this->move();



}

void worldMapEnemy::render()
{
	if (_isDebug)
	{
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	}
}

void worldMapEnemy::move()
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

void worldMapEnemy::worldEnemyImageFrameControl()
{
}

void worldMapEnemy::worldEnemyImageControl()
{
}

void worldMapEnemy::worldEnemyKeyControl()
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
