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
	//지형 타일 이미지 추가
	IMAGEMANAGER->addFrameImage("worldTerrain", ".//tileSet//worldMapTerrainTileSet.bmp", 384, 192, 12, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("townTerrain1", ".//tileSet//tileMap01.bmp", 256, 256, 8, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("townTerrain2", ".//tileSet//tileMap02.bmp", 256, 256, 8, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("townTerrain3", ".//tileSet//tileMap03.bmp", 256, 256, 8, 8, true, RGB(255, 0, 255));
	//오브젝트 타일 이미지 추가
	IMAGEMANAGER->addFrameImage("worldObject", ".//tileSet//worldMapObjectTileSet.bmp", 256, 128, 8, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("townHouse1", ".//tileSet//House1.bmp", 160, 224, 5, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("townHouse2", ".//tileSet//House2.bmp", 256, 256, 8, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("townHouse3", ".//tileSet//House3.bmp", 256, 256, 8, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("townHouse4", ".//tileSet//House4.bmp", 320, 384, 10, 12, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("townHouse5", ".//tileSet//House5.bmp", 256, 384, 8, 12, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("townHouse6", ".//tileSet//House6.bmp", 224, 384, 7, 12, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("townObject1", ".//tileSet//tileMap04.bmp", 256, 384, 8, 12, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("townObject2", ".//tileSet//tileMap05.bmp", 256, 256, 8, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("townObject3", ".//tileSet//tileMap06.bmp", 256, 256, 8, 8, true, RGB(255, 0, 255));

	//IMAGEMANAGER->addFrameImage("worldTerrain", ".//tileSet//worldMapTerrainTileSet.bmp", 384, 192, 12, 6, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("worldObject", ".//tileSet//worldMapObjectTileSet.bmp", 256, 128, 8, 4, true, RGB(255, 0, 255));
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


	file = CreateFile(".//38X20.map", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	//포인트 변수로 xy선언되어있기에 포인트 변수로 받음
	ReadFile(file, &_worldMap, sizeof(POINT), &read, NULL);
	_worldMapTiles = new tile[_worldMap.x * _worldMap.y];
	ReadFile(file, _worldMapTiles, sizeof(tile) * _worldMap.x *  _worldMap.y, &read, NULL);


	for (int i = 0; i < _worldMap.x*_worldMap.y; ++i)
	{
		if (_worldMapTiles[i].getTerrainAttr() == (ATTRIBUTE)ATTR_UNMOVE)
		{
			_worldMapTiles[i].setIsOpen(false);
		}
		else
		{
			_worldMapTiles[i].setIsOpen(true);
		}

	}


	CloseHandle(file);
}