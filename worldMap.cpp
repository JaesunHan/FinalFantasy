#include "stdafx.h"
#include "worldMap.h"


worldMap::worldMap()
{
}


worldMap::~worldMap()
{
}

HRESULT worldMap::init()
{
	IMAGEMANAGER->addFrameImage("worldTerrain", ".//tileSet//worldMapTerrainTileSet.bmp", 384, 192, 12, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("worldObject", ".//tileSet//worldMapObjectTileSet.bmp", 256, 128, 8, 4, true, RGB(255, 0, 255));
	mapLoad();
	return S_OK;
}

void worldMap::release()
{
}

void worldMap::update()
{
}

void worldMap::render()
{
	for (int i = 0; i < _worldMap.x * _worldMap.y; ++i)
	{	//아일랜드.map 크기만큼 그려준다.
		_worldMapTiles[i].render(getMemDC(), 0, 0);
	}
}


void worldMap::mapLoad(void)
{
	HANDLE file;
	DWORD read;


	file = CreateFile(".//Island.map", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
					//포인트 변수로 xy선언되어있기에 포인트 변수로 받음
	ReadFile(file, &_worldMap, sizeof(POINT), &read, NULL);
	_worldMapTiles = new tile[_worldMap.x * _worldMap.y];
	ReadFile(file, _worldMapTiles, sizeof(tile) * _worldMap.x *  _worldMap.y, &read, NULL);

	CloseHandle(file);
}
