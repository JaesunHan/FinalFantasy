#include "stdafx.h"
#include "worldEnemyBear.h"
//#include 

worldEnemyBear::worldEnemyBear()
{
}


worldEnemyBear::~worldEnemyBear()
{
}

HRESULT worldEnemyBear::init(int enemyX, int enemyY)
{

	//����Ŭ���� init �ѹ� ���Ƽ� �⺻ ���� �������� 
	worldMapEnemy::init(enemyX, enemyY);
	//�߰��� ������ �ϴ� ������.
	IMAGEMANAGER->addFrameImage("����ʰ����̿���", ".//image//enemyImg//worldEnemy_bear_left.bmp", 174, 34, 6, 1, true, RGB(255, 0, 255));
	_image = IMAGEMANAGER->addFrameImage("����ʰ�����", ".//image//enemyImg//worldEnemy_bear.bmp", 170, 34, 6, 1, true, RGB(255, 0, 255));

	_enemyType = ENEMY_BEAR;

	_bearCount = 0;
	return S_OK;
}

void worldEnemyBear::release()
{
}

void worldEnemyBear::update()
{
	worldMapEnemy::update();
	this->move();
}

void worldEnemyBear::render()
{
	worldEnemyImageControl();

	if (_isDebug)
	{
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	}
}

void worldEnemyBear::move()
{
	if (!_isDetect)
	{
		_bearCount++;
			if (_bearCount > 0 && _bearCount < 30)
			{
				_enemy.x +=	2;
				_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
				//����� Ÿ�ϼӼ��� �޾Ƽ� ���� �� �Ӽ��� �������� ���ϴ� �Ӽ��̸� �ݴ�����Ӱ��༭ ������ ��������.
				if (_worldMap->getWorldMapTiles()[tileNum(_rc.right, _rc.top + 3)].getTerrainAttr() == ATTR_UNMOVE ||
					_worldMap->getWorldMapTiles()[tileNum(_rc.right, _rc.bottom - 3)].getTerrainAttr() == ATTR_UNMOVE ||
					_worldMap->getWorldMapTiles()[tileNum(_rc.left, _rc.top + 3)].getTerrainAttr() == ATTR_UNMOVE ||
					_worldMap->getWorldMapTiles()[tileNum(_rc.left, _rc.bottom - 3)].getTerrainAttr() == ATTR_UNMOVE ||
					_worldMap->getWorldMapTiles()[tileNum(_rc.left + 3, _rc.top)].getTerrainAttr() == ATTR_UNMOVE ||
					_worldMap->getWorldMapTiles()[tileNum(_rc.right - 3, _rc.top)].getTerrainAttr() == ATTR_UNMOVE||
					_worldMap->getWorldMapTiles()[tileNum(_rc.left + 3, _rc.bottom)].getTerrainAttr() == ATTR_UNMOVE ||
					_worldMap->getWorldMapTiles()[tileNum(_rc.right - 3, _rc.bottom)].getTerrainAttr() == ATTR_UNMOVE
					)
				{
					_enemy.x -= 2;
					_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
				}
			}
			if (_bearCount > 30 && _bearCount < 60)
			{
				_enemy.x -= 1;
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
			if (_bearCount >= 65)
			{
				_bearCount = 0;
			}
	}
	worldMapEnemy::move();
}

void worldEnemyBear::worldEnemyImageFrameControl()
{
	worldMapEnemy::worldEnemyImageFrameControl();
}

void worldEnemyBear::worldEnemyImageControl()
{
	//�÷��̾�� ���ʹ��� ��ġ�� ���� ���ʹ� ���� ���� ����
	switch (_enemyDirection)
	{
	case ENEMYDIRECTION_RIGHT: _image = IMAGEMANAGER->findImage("����ʰ�����");
		_image->frameRender(getMemDC(), _enemy.x, _enemy.y, _enemyCurrentFrameX, 0);

		break;
	case ENEMYDIRECTION_LEFT: _image = IMAGEMANAGER->findImage("����ʰ����̿���");
		_image->frameRender(getMemDC(), _enemy.x, _enemy.y, _enemyCurrentFrameX, 0);
		break;
	}
}


