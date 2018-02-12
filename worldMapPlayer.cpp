#include "stdafx.h"
#include "worldMapPlayer.h"


worldMapPlayer::worldMapPlayer()
{
}


worldMapPlayer::~worldMapPlayer()
{
}

HRESULT worldMapPlayer::init(int playerX, int playerY)
{
	_image = IMAGEMANAGER->addFrameImage("월드맵플레이어", ".//image//playerImg//player1Move.bmp", 84, 184, 3, 4, true, RGB(255, 0, 255));
	
	_player.x = playerX;
	_player.y = playerY;

	_rc = RectMake(_player.x, _player.y+30, TILE_SIZEX, TILE_SIZEY/2);

	_currentFrameX = 0;
	_currentFrameY = 0;

	_moveSpeed = 2.0f;

	_worldPlayerDirection = WPDOWN;

	_isCollision = false;
	_checkRc = false;


	_worldMap = new worldMap;
	_worldMap->init();


	return S_OK;
}

void worldMapPlayer::release()
{
}

void worldMapPlayer::update()
{
	worldPlayerImageFrameControl();
	worldPlayerKeyControl();

}

void worldMapPlayer::render()
{
	worldPlayerImageControl();
	//IMAGEMANAGER->findImage("월드맵플레이어")->frameRender(getMemDC(),_player.x, _player.y, _currentFrameX, _currentFrameY);
}

void worldMapPlayer::worldPlayerImageFrameControl()
{

	_count++;

	if (_count % 10 == 0)
	{
		_currentFrameX += 1;
		
		if (_currentFrameX == _image->getMaxFrameX())
		{
			_currentFrameX = 0;
		}
	}
}

void worldMapPlayer::worldPlayerImageControl()
{
	switch (_worldPlayerDirection)
	{
		case WPRIGHT: _currentFrameY = 3;
			IMAGEMANAGER->findImage("월드맵플레이어")->frameRender(getMemDC(), _player.x, _player.y, _currentFrameX, _currentFrameY);
		break;

		case WPLEFT: _currentFrameY = 2;
			IMAGEMANAGER->findImage("월드맵플레이어")->frameRender(getMemDC(), _player.x, _player.y, _currentFrameX, _currentFrameY);
		break;

		case WPUP: _currentFrameY = 1;
			IMAGEMANAGER->findImage("월드맵플레이어")->frameRender(getMemDC(), _player.x, _player.y, _currentFrameX, _currentFrameY);
		break;
				
		case WPDOWN: _currentFrameY = 0;
			IMAGEMANAGER->findImage("월드맵플레이어")->frameRender(getMemDC(), _player.x, _player.y, _currentFrameX, _currentFrameY);
		break;
	}

	if (_checkRc)
	{
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	}

}

void worldMapPlayer::worldPlayerKeyControl()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_worldPlayerDirection = WPLEFT;
		_player.x -= _moveSpeed;
		_rc = RectMake(_player.x, _player.y + 30, TILE_SIZEX, TILE_SIZEY / 2);

		//지역 속성값을 받는다.
		//worldMap클래스에서 타일포인터로 로드되어있는 세이브되어진 타일의 속성을 받아서
		//타일인덱스를 받는 함수를 통해 현재위치와 주변의 타일속성을 검출하여
		//만약 그 속성이 못움직이는 녀석이면 움직이는 속도와 반대로 준다.
		if (_worldMap->getWorldMapTiles()[tileNum(_rc.left, _rc.top + 3)].getTerrainAttr() == ATTR_UNMOVE ||
			_worldMap->getWorldMapTiles()[tileNum(_rc.left, _rc.bottom - 3)].getTerrainAttr() == ATTR_UNMOVE)
		{
			_player.x += _moveSpeed;
		}
		//오브젝트어트리뷰트도 추가해야한당
		//오브젝트 속성 OBJ_MOUNTAIN, OBJ_CAVE, OBJ_TOWN, OBJ_CASTLE, OBJ_NPC, OBJ_ENEMY,
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_worldPlayerDirection = WPRIGHT;
		_player.x += _moveSpeed;
		_rc = RectMake(_player.x, _player.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
		if (_worldMap->getWorldMapTiles()[tileNum(_rc.right, _rc.top + 3)].getTerrainAttr() == ATTR_UNMOVE ||
			_worldMap->getWorldMapTiles()[tileNum(_rc.right, _rc.bottom - 3)].getTerrainAttr() == ATTR_UNMOVE)
		{
			_player.x -= _moveSpeed;
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_worldPlayerDirection = WPUP;
		_player.y -= _moveSpeed;
		_rc = RectMake(_player.x, _player.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
		if (_worldMap->getWorldMapTiles()[tileNum(_rc.left + 3, _rc.top)].getTerrainAttr() == ATTR_UNMOVE ||
			_worldMap->getWorldMapTiles()[tileNum(_rc.right - 3, _rc.top)].getTerrainAttr() == ATTR_UNMOVE)
		{
			_player.y += _moveSpeed;
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_worldPlayerDirection = WPDOWN;
		_player.y += _moveSpeed;
		_rc = RectMake(_player.x, _player.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
		if (_worldMap->getWorldMapTiles()[tileNum(_rc.left+3, _rc.bottom)].getTerrainAttr() == ATTR_UNMOVE ||
			_worldMap->getWorldMapTiles()[tileNum(_rc.right-3, _rc.bottom)].getTerrainAttr() == ATTR_UNMOVE)
		{
			_player.y -= _moveSpeed;
		}
	}
	
	//렉트 체크용
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		_checkRc = true;
	}


	switch (_worldPlayerDirection)
	{
	case WPRIGHT: //_tile->getTerrainAttr()[tileNum(_rc.left)]
		break;

	case WPLEFT: //if (_worldMap->getWorldMapTiles()[tileNum(_rc.left, _rc.top + 3)].getTerrainAttr() == ATTR_UNMOVE ||
		//_worldMap->getWorldMapTiles()[tileNum(_rc.left, _rc.bottom - 3)].getTerrainAttr() == ATTR_UNMOVE)
	//{
	//	_player.x += _moveSpeed;
	//}
		break;

	case WPUP:
		break;

	case WPDOWN: 
		break;
	}
}


int worldMapPlayer::tileNum(float x, float y)
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