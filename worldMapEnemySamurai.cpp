#include "stdafx.h"
#include "worldMapEnemySamurai.h"


worldMapEnemySamurai::worldMapEnemySamurai()
{
}


worldMapEnemySamurai::~worldMapEnemySamurai()
{
}

HRESULT worldMapEnemySamurai::init(int enemyX, int enemyY)
{
	//���� Ŭ���� ���� �������� 
	worldMapEnemy::init(enemyX, enemyY);
	IMAGEMANAGER->addFrameImage("����ʻ繫���̿���", ".//image//enemyImg//worldEnemy_samurai_left.bmp", 192, 54, 4, 1, true, RGB(255, 0, 255));
	_image = IMAGEMANAGER->addFrameImage("����ʻ繫����", ".//image//enemyImg//worldEnemy_samurai.bmp", 190, 54, 4, 1, true, RGB(255, 0, 255));

	_enemyType = ENEMY_SKELETON;

	_samuraiCount = 0;
	return S_OK;


}

void worldMapEnemySamurai::release()
{
}

void worldMapEnemySamurai::update()
{
	worldMapEnemy::update();
	this->move();
}

void worldMapEnemySamurai::render()
{
	worldEnemyImageControl();

	if (_isDebug)
	{
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	}
}

void worldMapEnemySamurai::move()
{
	if (!_isDetect)
	{
		_samuraiCount++;
		if (_samuraiCount > 0 && _samuraiCount < 30)
		{
			_enemy.x += 2;

			_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
			//����� Ÿ�ϼӼ��� �޾Ƽ� ���� �� �Ӽ��� �������� ���ϴ� �Ӽ��̸� �ݴ�����Ӱ��༭ ������ ��������.
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
		if (_samuraiCount > 30 && _samuraiCount < 60)
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
		if (_samuraiCount >= 65)
		{
			_samuraiCount = 0;
		}
	}
}


void worldMapEnemySamurai::worldEnemyImageFrameControl()
{
	worldMapEnemy::worldEnemyImageFrameControl();
}

	void worldMapEnemySamurai::worldEnemyImageControl()
{

	//�÷��̾�� ���ʹ��� ��ġ�� ���� ���ʹ� ���� ���� ����
	switch (_enemyDirection)
	{
	case ENEMYDIRECTION_RIGHT: _image = IMAGEMANAGER->findImage("����ʻ繫����");
		_image->frameRender(getMemDC(), _enemy.x, _enemy.y, _enemyCurrentFrameX, 0);

		break;
	case ENEMYDIRECTION_LEFT: _image = IMAGEMANAGER->findImage("����ʻ繫���̿���");
		_image->frameRender(getMemDC(), _enemy.x, _enemy.y, _enemyCurrentFrameX, 0);
		break;
	}
}

	void worldMapEnemySamurai::worldEnemyCollision()
	{
		worldMapEnemy::worldEnemyCollision();
	}
