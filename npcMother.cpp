#include "stdafx.h"
#include "npcMother.h"
#include "worldMapPlayer.h"


npcMother::npcMother()
{
}


npcMother::~npcMother()
{
}

HRESULT npcMother::init(int npcX, int npcY)
{
	_npc.x = npcX;
	_npc.y = npcY;

	_npcCurrentFrameX = 0;
	_npcCurrentFrameY = 0;
	_count = 0;

	_rc = RectMake(_npc.x, _npc.y + 30, TILE_SIZEX, TILE_SIZEY / 2);

	_isCollision = false;


	return S_OK;
}

void npcMother::release()
{
}

void npcMother::update()
{
	worldNpcImageFrameControl();
	npcCollision();
}

void npcMother::render(HDC hdc, POINT movePt)
{
}

void npcMother::worldNpcImageFrameControl()
{
	_count++;

	if (_count % 10 == 0)
	{
		_npcCurrentFrameX++;

		if (_npcCurrentFrameX == _image->getMaxFrameX())
		{
			_npcCurrentFrameX = 0;
		}
	}
}

void npcMother::worldNpcImageControl()
{
}

void npcMother::worldNpcKeyControl()
{
}

void npcMother::npcCollision()
{
	if (getDistance(_npc.x, _npc.y, _wp->getWorldMapPlayerPoint().x, _wp->getWorldMapPlayerPoint().y)< TILE_SIZEX)
	{
		_isCollision = true;
	}
}

int npcMother::tileNum(float x, float y)
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
