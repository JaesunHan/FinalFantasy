#include "stdafx.h"
#include "worldMapEnemySamurai.h"


worldMapEnemySamurai::worldMapEnemySamurai()
{
}


worldMapEnemySamurai::~worldMapEnemySamurai()
{
}

HRESULT worldMapEnemySamurai::init(int enemyX, int enemyY, ENEMYMOVEPATTERN enemyPattern)
{
	//���� Ŭ���� ���� �������� 
	worldMapEnemy::init(enemyX, enemyY, enemyPattern);
	IMAGEMANAGER->addFrameImage("����ʻ繫���̿���", ".//image//enemyImg//worldEnemy_samurai_left.bmp", 192, 54, 4, 1, true, RGB(255, 0, 255));
	_image = IMAGEMANAGER->addFrameImage("����ʻ繫����", ".//image//enemyImg//worldEnemy_samurai.bmp", 190, 54, 4, 1, true, RGB(255, 0, 255));

	_enemyType = ENEMY_SKELETON;

	_enemyMovePattern = enemyPattern;

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

void worldMapEnemySamurai::render(HDC hdc, POINT movePt)
{
	worldEnemyImageControl(hdc, movePt);

	if (_isDebug)
	{
		Rectangle(hdc, _rc.left - movePt.x, _rc.top - movePt.y, _rc.right - movePt.x, _rc.bottom - movePt.y);
	}
}

void worldMapEnemySamurai::move()
{
	if (!_isDetect)
	{
		_samuraiCount++;
		switch (_enemyMovePattern)
		{
		case ENEMYPATTERN_ONE:

			if (_samuraiCount > 0 && _samuraiCount < 30)
			{
				_enemy.x += 2;
				_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
				//����� Ÿ�ϼӼ��� �޾Ƽ� ���� �� �Ӽ��� �������� ���ϴ� �Ӽ��̸� �ݴ�����Ӱ��༭ ������ ��������.
				if (_worldMap->getMapTile()[tileNum(_rc.right, _rc.top + 3)].getTerrainAttr() == ATTR_UNMOVE ||
					_worldMap->getMapTile()[tileNum(_rc.right, _rc.bottom - 3)].getTerrainAttr() == ATTR_UNMOVE ||
					_worldMap->getMapTile()[tileNum(_rc.left, _rc.top + 3)].getTerrainAttr() == ATTR_UNMOVE ||
					_worldMap->getMapTile()[tileNum(_rc.left, _rc.bottom - 3)].getTerrainAttr() == ATTR_UNMOVE ||
					_worldMap->getMapTile()[tileNum(_rc.left + 3, _rc.top)].getTerrainAttr() == ATTR_UNMOVE ||
					_worldMap->getMapTile()[tileNum(_rc.right - 3, _rc.top)].getTerrainAttr() == ATTR_UNMOVE ||
					_worldMap->getMapTile()[tileNum(_rc.left + 3, _rc.bottom)].getTerrainAttr() == ATTR_UNMOVE ||
					_worldMap->getMapTile()[tileNum(_rc.right - 3, _rc.bottom)].getTerrainAttr() == ATTR_UNMOVE
					)
				{
					_enemy.x -= 2;
					_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
				}
				else if
					(_worldMap->getMapTile()[tileNum(_rc.right, _rc.top + 3)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.right, _rc.bottom - 3)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.left, _rc.top + 3)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.left, _rc.bottom - 3)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.left + 3, _rc.top)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.right - 3, _rc.top)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.left + 3, _rc.bottom)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.right - 3, _rc.bottom)].getTerrainAttr() == ATTR_SLOW
						)
				{
					_enemy.x -= 1;
					_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
				}
			}
			if (_samuraiCount > 35 && _samuraiCount < 65)
			{
				_enemy.x -= 2;
				_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
				if (_worldMap->getMapTile()[tileNum(_rc.right, _rc.top + 3)].getTerrainAttr() == ATTR_UNMOVE ||
					_worldMap->getMapTile()[tileNum(_rc.right, _rc.bottom - 3)].getTerrainAttr() == ATTR_UNMOVE ||
					_worldMap->getMapTile()[tileNum(_rc.left, _rc.top + 3)].getTerrainAttr() == ATTR_UNMOVE ||
					_worldMap->getMapTile()[tileNum(_rc.left, _rc.bottom - 3)].getTerrainAttr() == ATTR_UNMOVE ||
					_worldMap->getMapTile()[tileNum(_rc.left + 3, _rc.top)].getTerrainAttr() == ATTR_UNMOVE ||
					_worldMap->getMapTile()[tileNum(_rc.right - 3, _rc.top)].getTerrainAttr() == ATTR_UNMOVE ||
					_worldMap->getMapTile()[tileNum(_rc.left + 3, _rc.bottom)].getTerrainAttr() == ATTR_UNMOVE ||
					_worldMap->getMapTile()[tileNum(_rc.right - 3, _rc.bottom)].getTerrainAttr() == ATTR_UNMOVE)
				{
					_enemy.x += 2;
					_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
				}
				else if
					(_worldMap->getMapTile()[tileNum(_rc.right, _rc.top + 3)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.right, _rc.bottom - 3)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.left, _rc.top + 3)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.left, _rc.bottom - 3)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.left + 3, _rc.top)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.right - 3, _rc.top)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.left + 3, _rc.bottom)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.right - 3, _rc.bottom)].getTerrainAttr() == ATTR_SLOW)
				{
					_enemy.x += 1;
					_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
				}
			}
			if (_samuraiCount >= 70)
			{
				_samuraiCount = 0;
			}

			break;
		case ENEMYPATTERN_TWO:

			if (_samuraiCount > 0 && _samuraiCount < 30)
			{
				_enemy.y += 2;
				_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
				//����� Ÿ�ϼӼ��� �޾Ƽ� ���� �� �Ӽ��� �������� ���ϴ� �Ӽ��̸� �ݴ�����Ӱ��༭ ������ ��������.
				if (_worldMap->getMapTile()[tileNum(_rc.right, _rc.top + 3)].getTerrainAttr() == ATTR_UNMOVE ||
					_worldMap->getMapTile()[tileNum(_rc.right, _rc.bottom - 3)].getTerrainAttr() == ATTR_UNMOVE ||
					_worldMap->getMapTile()[tileNum(_rc.left, _rc.top + 3)].getTerrainAttr() == ATTR_UNMOVE ||
					_worldMap->getMapTile()[tileNum(_rc.left, _rc.bottom - 3)].getTerrainAttr() == ATTR_UNMOVE ||
					_worldMap->getMapTile()[tileNum(_rc.left + 3, _rc.top)].getTerrainAttr() == ATTR_UNMOVE ||
					_worldMap->getMapTile()[tileNum(_rc.right - 3, _rc.top)].getTerrainAttr() == ATTR_UNMOVE ||
					_worldMap->getMapTile()[tileNum(_rc.left + 3, _rc.bottom)].getTerrainAttr() == ATTR_UNMOVE ||
					_worldMap->getMapTile()[tileNum(_rc.right - 3, _rc.bottom)].getTerrainAttr() == ATTR_UNMOVE
					)
				{
					_enemy.y -= 2;
					_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
				}
				if (_worldMap->getMapTile()[tileNum(_rc.right, _rc.top + 3)].getTerrainAttr() == ATTR_SLOW ||
					_worldMap->getMapTile()[tileNum(_rc.right, _rc.bottom - 3)].getTerrainAttr() == ATTR_SLOW ||
					_worldMap->getMapTile()[tileNum(_rc.left, _rc.top + 3)].getTerrainAttr() == ATTR_SLOW ||
					_worldMap->getMapTile()[tileNum(_rc.left, _rc.bottom - 3)].getTerrainAttr() == ATTR_SLOW ||
					_worldMap->getMapTile()[tileNum(_rc.left + 3, _rc.top)].getTerrainAttr() == ATTR_SLOW ||
					_worldMap->getMapTile()[tileNum(_rc.right - 3, _rc.top)].getTerrainAttr() == ATTR_SLOW ||
					_worldMap->getMapTile()[tileNum(_rc.left + 3, _rc.bottom)].getTerrainAttr() == ATTR_SLOW ||
					_worldMap->getMapTile()[tileNum(_rc.right - 3, _rc.bottom)].getTerrainAttr() == ATTR_SLOW
					)
				{
					_enemy.y -= 1;
					_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
				}
			}
			if (_samuraiCount > 35 && _samuraiCount < 65)
			{
				_enemy.y -= 2;
				_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
				if (_worldMap->getMapTile()[tileNum(_rc.right, _rc.top + 3)].getTerrainAttr() == ATTR_UNMOVE ||
					_worldMap->getMapTile()[tileNum(_rc.right, _rc.bottom - 3)].getTerrainAttr() == ATTR_UNMOVE ||
					_worldMap->getMapTile()[tileNum(_rc.left, _rc.top + 3)].getTerrainAttr() == ATTR_UNMOVE ||
					_worldMap->getMapTile()[tileNum(_rc.left, _rc.bottom - 3)].getTerrainAttr() == ATTR_UNMOVE ||
					_worldMap->getMapTile()[tileNum(_rc.left + 3, _rc.top)].getTerrainAttr() == ATTR_UNMOVE ||
					_worldMap->getMapTile()[tileNum(_rc.right - 3, _rc.top)].getTerrainAttr() == ATTR_UNMOVE ||
					_worldMap->getMapTile()[tileNum(_rc.left + 3, _rc.bottom)].getTerrainAttr() == ATTR_UNMOVE ||
					_worldMap->getMapTile()[tileNum(_rc.right - 3, _rc.bottom)].getTerrainAttr() == ATTR_UNMOVE)
				{
					_enemy.y += 2;
					_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
				}
				if (_worldMap->getMapTile()[tileNum(_rc.right, _rc.top + 3)].getTerrainAttr() == ATTR_SLOW ||
					_worldMap->getMapTile()[tileNum(_rc.right, _rc.bottom - 3)].getTerrainAttr() == ATTR_SLOW ||
					_worldMap->getMapTile()[tileNum(_rc.left, _rc.top + 3)].getTerrainAttr() == ATTR_SLOW ||
					_worldMap->getMapTile()[tileNum(_rc.left, _rc.bottom - 3)].getTerrainAttr() == ATTR_SLOW ||
					_worldMap->getMapTile()[tileNum(_rc.left + 3, _rc.top)].getTerrainAttr() == ATTR_SLOW ||
					_worldMap->getMapTile()[tileNum(_rc.right - 3, _rc.top)].getTerrainAttr() == ATTR_SLOW ||
					_worldMap->getMapTile()[tileNum(_rc.left + 3, _rc.bottom)].getTerrainAttr() == ATTR_SLOW ||
					_worldMap->getMapTile()[tileNum(_rc.right - 3, _rc.bottom)].getTerrainAttr() == ATTR_SLOW)
				{
					_enemy.y += 1;
					_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
				}


			}
			if (_samuraiCount >= 70)
			{
				_samuraiCount = 0;
			}

			break;
		case ENEMYPATTERN_THREE:
		
		if (_samuraiCount > 0 && _samuraiCount < 30)
				{
					_enemy.y += 2;
					_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
					//����� Ÿ�ϼӼ��� �޾Ƽ� ���� �� �Ӽ��� �������� ���ϴ� �Ӽ��̸� �ݴ�����Ӱ��༭ ������ ��������.
					if (_worldMap->getMapTile()[tileNum(_rc.right, _rc.top + 3)].getTerrainAttr() == ATTR_UNMOVE ||
						_worldMap->getMapTile()[tileNum(_rc.right, _rc.bottom - 3)].getTerrainAttr() == ATTR_UNMOVE ||
						_worldMap->getMapTile()[tileNum(_rc.left, _rc.top + 3)].getTerrainAttr() == ATTR_UNMOVE ||
						_worldMap->getMapTile()[tileNum(_rc.left, _rc.bottom - 3)].getTerrainAttr() == ATTR_UNMOVE ||
						_worldMap->getMapTile()[tileNum(_rc.left + 3, _rc.top)].getTerrainAttr() == ATTR_UNMOVE ||
						_worldMap->getMapTile()[tileNum(_rc.right - 3, _rc.top)].getTerrainAttr() == ATTR_UNMOVE ||
						_worldMap->getMapTile()[tileNum(_rc.left + 3, _rc.bottom)].getTerrainAttr() == ATTR_UNMOVE ||
						_worldMap->getMapTile()[tileNum(_rc.right - 3, _rc.bottom)].getTerrainAttr() == ATTR_UNMOVE
						)
					{
						_enemy.y -= 2;
						_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
					}
					if (_worldMap->getMapTile()[tileNum(_rc.right, _rc.top + 3)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.right, _rc.bottom - 3)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.left, _rc.top + 3)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.left, _rc.bottom - 3)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.left + 3, _rc.top)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.right - 3, _rc.top)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.left + 3, _rc.bottom)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.right - 3, _rc.bottom)].getTerrainAttr() == ATTR_SLOW
						)
					{
						_enemy.y -= 1;
						_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
					}
				}
				if (_samuraiCount > 35 && _samuraiCount < 65)
				{
					_enemy.x -= 2;
					_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
					if (_worldMap->getMapTile()[tileNum(_rc.right, _rc.top + 3)].getTerrainAttr() == ATTR_UNMOVE ||
						_worldMap->getMapTile()[tileNum(_rc.right, _rc.bottom - 3)].getTerrainAttr() == ATTR_UNMOVE ||
						_worldMap->getMapTile()[tileNum(_rc.left, _rc.top + 3)].getTerrainAttr() == ATTR_UNMOVE ||
						_worldMap->getMapTile()[tileNum(_rc.left, _rc.bottom - 3)].getTerrainAttr() == ATTR_UNMOVE ||
						_worldMap->getMapTile()[tileNum(_rc.left + 3, _rc.top)].getTerrainAttr() == ATTR_UNMOVE ||
						_worldMap->getMapTile()[tileNum(_rc.right - 3, _rc.top)].getTerrainAttr() == ATTR_UNMOVE ||
						_worldMap->getMapTile()[tileNum(_rc.left + 3, _rc.bottom)].getTerrainAttr() == ATTR_UNMOVE ||
						_worldMap->getMapTile()[tileNum(_rc.right - 3, _rc.bottom)].getTerrainAttr() == ATTR_UNMOVE)
					{
						_enemy.x += 2;
						_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
					}
					if (_worldMap->getMapTile()[tileNum(_rc.right, _rc.top + 3)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.right, _rc.bottom - 3)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.left, _rc.top + 3)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.left, _rc.bottom - 3)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.left + 3, _rc.top)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.right - 3, _rc.top)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.left + 3, _rc.bottom)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.right - 3, _rc.bottom)].getTerrainAttr() == ATTR_SLOW)
					{
						_enemy.x += 1;
						_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
					}
				}
				if (_samuraiCount > 70 && _samuraiCount < 100)
				{
					_enemy.x += 2;
					_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
					if (_worldMap->getMapTile()[tileNum(_rc.right, _rc.top + 3)].getTerrainAttr() == ATTR_UNMOVE ||
						_worldMap->getMapTile()[tileNum(_rc.right, _rc.bottom - 3)].getTerrainAttr() == ATTR_UNMOVE ||
						_worldMap->getMapTile()[tileNum(_rc.left, _rc.top + 3)].getTerrainAttr() == ATTR_UNMOVE ||
						_worldMap->getMapTile()[tileNum(_rc.left, _rc.bottom - 3)].getTerrainAttr() == ATTR_UNMOVE ||
						_worldMap->getMapTile()[tileNum(_rc.left + 3, _rc.top)].getTerrainAttr() == ATTR_UNMOVE ||
						_worldMap->getMapTile()[tileNum(_rc.right - 3, _rc.top)].getTerrainAttr() == ATTR_UNMOVE ||
						_worldMap->getMapTile()[tileNum(_rc.left + 3, _rc.bottom)].getTerrainAttr() == ATTR_UNMOVE ||
						_worldMap->getMapTile()[tileNum(_rc.right - 3, _rc.bottom)].getTerrainAttr() == ATTR_UNMOVE)
					{
						_enemy.x -= 2;
						_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
					}
					if (_worldMap->getMapTile()[tileNum(_rc.right, _rc.top + 3)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.right, _rc.bottom - 3)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.left, _rc.top + 3)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.left, _rc.bottom - 3)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.left + 3, _rc.top)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.right - 3, _rc.top)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.left + 3, _rc.bottom)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.right - 3, _rc.bottom)].getTerrainAttr() == ATTR_SLOW)
					{
						_enemy.x -= 1;
						_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
					}
				}
				if (_samuraiCount > 105 && _samuraiCount < 135)
				{
					_enemy.y -= 2;
					_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
					if (_worldMap->getMapTile()[tileNum(_rc.right, _rc.top + 3)].getTerrainAttr() == ATTR_UNMOVE ||
						_worldMap->getMapTile()[tileNum(_rc.right, _rc.bottom - 3)].getTerrainAttr() == ATTR_UNMOVE ||
						_worldMap->getMapTile()[tileNum(_rc.left, _rc.top + 3)].getTerrainAttr() == ATTR_UNMOVE ||
						_worldMap->getMapTile()[tileNum(_rc.left, _rc.bottom - 3)].getTerrainAttr() == ATTR_UNMOVE ||
						_worldMap->getMapTile()[tileNum(_rc.left + 3, _rc.top)].getTerrainAttr() == ATTR_UNMOVE ||
						_worldMap->getMapTile()[tileNum(_rc.right - 3, _rc.top)].getTerrainAttr() == ATTR_UNMOVE ||
						_worldMap->getMapTile()[tileNum(_rc.left + 3, _rc.bottom)].getTerrainAttr() == ATTR_UNMOVE ||
						_worldMap->getMapTile()[tileNum(_rc.right - 3, _rc.bottom)].getTerrainAttr() == ATTR_UNMOVE)
					{
						_enemy.y += 2;
						_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
					}
					if (_worldMap->getMapTile()[tileNum(_rc.right, _rc.top + 3)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.right, _rc.bottom - 3)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.left, _rc.top + 3)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.left, _rc.bottom - 3)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.left + 3, _rc.top)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.right - 3, _rc.top)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.left + 3, _rc.bottom)].getTerrainAttr() == ATTR_SLOW ||
						_worldMap->getMapTile()[tileNum(_rc.right - 3, _rc.bottom)].getTerrainAttr() == ATTR_SLOW)
					{
						_enemy.y += 1;
						_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
					}
				}
				if (_samuraiCount >= 140)
				{
					_samuraiCount = 0;
				}
				break;
		}
		
		
	}
	
}


void worldMapEnemySamurai::worldEnemyImageFrameControl()
{
	worldMapEnemy::worldEnemyImageFrameControl();
}

	void worldMapEnemySamurai::worldEnemyImageControl(HDC hdc, POINT movePt)
{

	//�÷��̾�� ���ʹ��� ��ġ�� ���� ���ʹ� ���� ���� ����
	switch (_enemyDirection)
	{
	case ENEMYDIRECTION_RIGHT: _image = IMAGEMANAGER->findImage("����ʻ繫����");
		_image->frameRender(hdc, _enemy.x - movePt.x, _enemy.y - movePt.y, _enemyCurrentFrameX, 0);

		break;
	case ENEMYDIRECTION_LEFT: _image = IMAGEMANAGER->findImage("����ʻ繫���̿���");
		_image->frameRender(hdc, _enemy.x - movePt.x, _enemy.y - movePt.y, _enemyCurrentFrameX, 0);
		break;
	}
}

	void worldMapEnemySamurai::worldEnemyCollision()
	{
		worldMapEnemy::worldEnemyCollision();
	}
