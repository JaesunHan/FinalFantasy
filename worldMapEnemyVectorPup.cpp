#include "stdafx.h"
#include "worldMapEnemyVectorPup.h"


worldMapEnemyVectorPup::worldMapEnemyVectorPup()
{
}


worldMapEnemyVectorPup::~worldMapEnemyVectorPup()
{
}

HRESULT worldMapEnemyVectorPup::init(int enemyX, int enemyY, ENEMYMOVEPATTERN enemyPattern)
{
	//마더 클래스 정보 가져오고 
	worldMapEnemy::init(enemyX, enemyY, enemyPattern);
	IMAGEMANAGER->addFrameImage("벡터펍왼쪽", ".//image//enemyImg//worldEnemy_VectorPup_left.bmp", 300, 39, 4, 1, true, RGB(255, 0, 255));
	_image = IMAGEMANAGER->addFrameImage("벡터펍", ".//image//enemyImg//worldEnemy_VectorPup_right.bmp", 300, 39, 4, 1, true, RGB(255, 0, 255));

	_enemyType = ENEMY_VECTORPUP;

	_enemyMovePattern = enemyPattern;

	_vectorPupCount = 0;
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

void worldMapEnemyVectorPup::render(HDC hdc, POINT movePt)
{
	worldEnemyImageControl(hdc, movePt);

	if (_isDebug)
	{
		Rectangle(hdc, _rc.left - movePt.x, _rc.top - movePt.y, _rc.right - movePt.x, _rc.bottom - movePt.y);
	}
}

void worldMapEnemyVectorPup::move()
{
	if (!_isDetect)
	{
		_vectorPupCount++;
		switch (_enemyMovePattern)
		{
		case ENEMYPATTERN_ONE:

			if (_vectorPupCount > 0 && _vectorPupCount < 30)
			{
				_enemy.x += 2;
				_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
				//월드맵 타일속성을 받아서 만약 그 속성이 움직이지 못하는 속성이면 반대움직임값줘서 움직임 차감하자.
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
			if (_vectorPupCount > 35 && _vectorPupCount < 65)
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
			if (_vectorPupCount >= 70)
			{
				_vectorPupCount = 0;
			}

			break;
		case ENEMYPATTERN_TWO:

			if (_vectorPupCount > 0 && _vectorPupCount < 30)
			{
				_enemy.y += 2;
				_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
				//월드맵 타일속성을 받아서 만약 그 속성이 움직이지 못하는 속성이면 반대움직임값줘서 움직임 차감하자.
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
			if (_vectorPupCount > 35 && _vectorPupCount < 65)
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
			if (_vectorPupCount >= 70)
			{
				_vectorPupCount = 0;
			}

			break;
		case ENEMYPATTERN_THREE:

			if (_vectorPupCount > 0 && _vectorPupCount < 30)
			{
				_enemy.x += 4;
				_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
				//월드맵 타일속성을 받아서 만약 그 속성이 움직이지 못하는 속성이면 반대움직임값줘서 움직임 차감하자.
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
					_enemy.x -= 4;
					_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
				}
				if (_worldMap->getMapTile()[tileNum(_rc.right, _rc.top + 3)].getTerrainAttr() == ATTR_SLOW||
					_worldMap->getMapTile()[tileNum(_rc.right, _rc.bottom - 3)].getTerrainAttr() == ATTR_SLOW ||
					_worldMap->getMapTile()[tileNum(_rc.left, _rc.top + 3)].getTerrainAttr() == ATTR_SLOW ||
					_worldMap->getMapTile()[tileNum(_rc.left, _rc.bottom - 3)].getTerrainAttr() == ATTR_SLOW ||
					_worldMap->getMapTile()[tileNum(_rc.left + 3, _rc.top)].getTerrainAttr() == ATTR_SLOW ||
					_worldMap->getMapTile()[tileNum(_rc.right - 3, _rc.top)].getTerrainAttr() == ATTR_SLOW ||
					_worldMap->getMapTile()[tileNum(_rc.left + 3, _rc.bottom)].getTerrainAttr() == ATTR_SLOW ||
					_worldMap->getMapTile()[tileNum(_rc.right - 3, _rc.bottom)].getTerrainAttr() == ATTR_SLOW
					)
				{
					_enemy.x -= 2;
					_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
				}
			}
			if (_vectorPupCount > 35 && _vectorPupCount < 65)
			{
				_enemy.x -= 4;
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
					_enemy.x += 4;
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
					_enemy.x += 2;
					_rc = RectMake(_enemy.x, _enemy.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
				}
			}
			if (_vectorPupCount >= 70)
			{
				_vectorPupCount = 0;
			}
			break;
		}
	}
}

void worldMapEnemyVectorPup::worldEnemyImageFrameControl()
{
	worldMapEnemy::worldEnemyImageFrameControl();
}

void worldMapEnemyVectorPup::worldEnemyImageControl(HDC hdc, POINT movePt)
{
	//플레이어와 에너미의 위치에 따른 에너미 보는 방향 변경
	switch (_enemyDirection)
	{
	case ENEMYDIRECTION_RIGHT: _image = IMAGEMANAGER->findImage("벡터펍왼쪽");
		_image->frameRender(hdc, _enemy.x - movePt.x, _enemy.y - movePt.y, _enemyCurrentFrameX, 0);

		break;
	case ENEMYDIRECTION_LEFT: _image = IMAGEMANAGER->findImage("벡터펍");
		_image->frameRender(hdc, _enemy.x - movePt.x, _enemy.y - movePt.y, _enemyCurrentFrameX, 0);
		break;
	}
}
