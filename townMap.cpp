#include "stdafx.h"
#include "townMap.h"


townMap::townMap()
{
}


townMap::~townMap()
{
}

HRESULT townMap::init()
{
	//지형 타일 이미지 추가
	IMAGEMANAGER->addFrameImage("worldTerrain", ".//tileSet//worldMapTerrainTileSet.bmp", 384, 192, 12, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("townTerrain1", ".//tileSet//tileMap01.bmp", 256, 256, 8, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("townTerrain2", ".//tileSet//tileMap02.bmp", 256, 256, 8, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("townTerrain3", ".//tileSet//tileMap03.bmp", 256, 256, 8, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("tempTile", ".//tileSet//tempTile.bmp", 576, 576, 18, 18, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("testTileSet", ".//tileSet//testTileSet.bmp", 128, 64, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("testTileSet2", ".//tileSet//testTileSet2.bmp", 480, 128, 15, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("townTile", ".//tileSet//townTileSet.bmp", 480, 320, 15, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("townTileSample", ".//tileSet//townTileSample.bmp", 128, 64, 4, 2, true, RGB(255, 0, 255));
	//오브젝트 타일 이미지 추가
	//IMAGEMANAGER->addFrameImage("worldObject", ".//tileSet//worldMapObjectTileSet.bmp", 256, 128, 8, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("worldObject", ".//tileSet//worldMapObject2.bmp", 256, 192, 8, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("townHouse1", ".//tileSet//House1.bmp", 160, 224, 5, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("townHouse2", ".//tileSet//House2.bmp", 256, 256, 8, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("townHouse3", ".//tileSet//House3.bmp", 256, 256, 8, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("townHouse4", ".//tileSet//House4.bmp", 320, 384, 10, 12, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("townHouse5", ".//tileSet//House5.bmp", 256, 384, 8, 12, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("townHouse6", ".//tileSet//House6.bmp", 224, 384, 7, 12, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("townObject1", ".//tileSet//townObject.bmp", 256, 384, 8, 12, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("townObject1", ".//tileSet//townObject.bmp", 512, 256, 16, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("townObject2", ".//tileSet//tileMap05.bmp", 256, 256, 8, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("townObject3", ".//tileSet//tileMap06.bmp", 256, 256, 8, 8, true, RGB(255, 0, 255));
	
	mapLoad();


	return S_OK;
}

void townMap::release()
{
}

void townMap::update()
{
}

void townMap::render(HDC hdc)
{
	



}

void townMap::terrianRender()
{
	if (_townTiles != NULL)
	{
		int renderX = _townMap.x;
		int renderY = _townMap.y;
		int indexX = 0;
		int indexY = 0;

		if (renderX > CAMERAMANAGER->getDcTileNum().x + 3)
			renderX = CAMERAMANAGER->getDcTileNum().x + 2;
		else if (renderX == CAMERAMANAGER->getDcTileNum().x + 2);
		else ++renderX;

		if (renderY > CAMERAMANAGER->getDcTileNum().y + 3)
			renderY = CAMERAMANAGER->getDcTileNum().y + 2;
		else if (renderY == CAMERAMANAGER->getDcTileNum().y + 2);
		else ++renderY;

		for (int i = indexY; i < renderY; ++i)
		{
			for (int j = indexX; j < renderX; ++j)
			{
				if (CAMERAMANAGER->getMovePt().x / TILE_SIZEX + j + (CAMERAMANAGER->getMovePt().y / TILE_SIZEY + i) * _townMap.x < 0) continue;
				if (CAMERAMANAGER->getMovePt().x / TILE_SIZEX + j + (CAMERAMANAGER->getMovePt().y / TILE_SIZEY + i) * _townMap.x >= _townMap.x * _townMap.y)
					continue;

				_townTiles[CAMERAMANAGER->getMovePt().x / TILE_SIZEX + j + (CAMERAMANAGER->getMovePt().y / TILE_SIZEY + i) * _townMap.x].render(CAMERAMANAGER->getCameraDC(), CAMERAMANAGER->getMovePt().x, CAMERAMANAGER->getMovePt().y);
			}
		}
	}
}

void townMap::objectRender()
{

	int renderX = _townMap.x;
	int renderY = _townMap.y;
	int indexX = 0;
	int indexY = 0;

	//나중에 랜더해야할 오브젝트
	for (int i = indexY; i < renderY; ++i)
	{
		for (int j = indexX; j < renderX; ++j)
		{
		if (CAMERAMANAGER->getMovePt().x / TILE_SIZEX + j + (CAMERAMANAGER->getMovePt().y / TILE_SIZEY + i) * _townMap.x < 0) continue;
		if (CAMERAMANAGER->getMovePt().x / TILE_SIZEX + j + (CAMERAMANAGER->getMovePt().y / TILE_SIZEY + i) * _townMap.x >= _townMap.x * _townMap.y)
		continue;

		//_townTiles[_townMap.x / TILE_SIZEX + j + (CAMERAMANAGER->getMovePt().y / TILE_SIZEY + i) * _townMap.x].afterObjectRender(tileMapDC->getMemDC(), _townMap.x, _townMap.y);
		}
	}

}

void townMap::mapLoad(void)
{
	HANDLE file;
	DWORD read;


	file = CreateFile(".//town30X30.map", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	//포인트 변수로 xy선언되어있기에 포인트 변수로 받음
	ReadFile(file, &_townMap, sizeof(POINT), &read, NULL);
	_townTiles = new tile[_townMap.x * _townMap.y];
	ReadFile(file, _townTiles, sizeof(tile) * _townMap.x *  _townMap.y, &read, NULL);


	for (int i = 0; i < _townMap.x*_townMap.y; ++i)
	{
		if (_townTiles[i].getObjectAttr() == (ATTRIBUTE)ATTR_UNMOVE && _townTiles[i].getTerrainAttr() == (ATTRIBUTE)ATTR_UNMOVE)
		{
			_townTiles[i].setIsOpen(false);
		}
		else
		{
			_townTiles[i].setIsOpen(true);
		}

	}

	CAMERAMANAGER->setMapTotalSize(PointMake(_townMap.x * TILE_SIZEX, _townMap.y * TILE_SIZEY));

	CloseHandle(file);
}
