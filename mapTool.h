#pragma once
#include "gameNode.h"
#include "tile.h"

/********************************************************/
/* 맵툴 클래스											*/
/* 작업자 : 이호형										*/
/* 최종 수정 : 2018. 02. 08								*/
/********************************************************/

enum SELECTMODE
{
	MODE_WORLDMAP_TERRAIN_SELECT,
	MODE_WORLDMAP_OBJECT_SELECT,
	MODE_ERASER,
	MODE_END
};

enum BUTTONTAG
{
	EDIT_BUTTON_SAVE,
	EDIT_BUTTON_LOAD,
	EDIT_BUTTON_TERRAIN,
	EDIT_BUTTON_OBJECT,
	EDIT_BUTTON_ERASER,
	EDIT_BUTTON_CHANGE_GAME_MODE,
	EDIT_BUTTON_CHANGE_MAP_EDIT_MODE,
	EDIT_BUTTON_END
};

class mapTool : public gameNode
{
private:
	tile* _worldMapTiles;
	tile* _worldMapTerrainTileSet;
	tile* _worldMapObjectTileSet;

	POINT _mapSize;
	POINT _worldMapTerrainTileSize;
	POINT _worldMapObjectTileSize;

private:
	image* _worldMapTerrainTileImage;
	image* _worldMapObjectTileImage;

private:
	SELECTMODE _currentSelectMode;
	tile _selectedTerrainTile;
	tile _selectedObjectTile;

private:
	RECT _saveBtn, _loadBtn;
	RECT _terrainBtn, _objectBtn, _eraserBtn;
	RECT _changeGameModeBtn, _changeMapEditModeBtn;

public:
	mapTool();
	~mapTool();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void worldMapTerrainTileSetInit(void);
	void worldMapObjectTileSetInie(void);

	void clickButton(void);
	void buttonDraw(void);						//버튼 그리는 함수

//	void setTerrainTileSet(string tileSetKeyName, POINT tileSize);

	void createDefaultMap(POINT mapSize);		//맵 사이즈 받아서 기본맵 생성
};

