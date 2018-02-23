#pragma once
#include "gameNode.h"
#include "tile.h"

enum MAPTYPE
{
	MAP_WORLD,
	MAP_TOWN,
	MAP_END
};

class generalMap : public gameNode
{
protected:
	POINT _mapTileNum;					//월드맵 x,y
	tile* _mapTile;				//월드맵 타일

public:

	//맵타입 구분을 위한 이넘문
	MAPTYPE _mapType;

	generalMap();
	~generalMap();

	HRESULT init(string mapFilePath);
	void release();
	void update();
	void render(HDC hdc);
	void afterRenderObject(HDC hdc);

	//맵 로드용 함수
	void mapLoad(string mapFilePath);
	void setCamera(void) { CAMERAMANAGER->setMapTotalSize(PointMake(_mapTileNum.x * TILE_SIZEX, _mapTileNum.y * TILE_SIZEY)); }

	//===============겟셋 모음==================

	//맵크기 x,y겟 함수
	POINT getMapTileNum() { return _mapTileNum; }

	//로드된 월드맵 타일 겟함수 
	tile* getMapTile() { return _mapTile; }
};

