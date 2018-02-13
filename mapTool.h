#pragma once
#include "gameNode.h"
#include "tile.h"
#include "resource1.h"
#include <commdlg.h>

/********************************************************/
/* 맵툴 클래스											*/
/* 작업자 : 이호형										*/
/********************************************************/

#define MAP_AREA 704
#define MAP_MOVE_SPEED 4

static image* tileMapDC = IMAGEMANAGER->addImage("tileMapArea", MAP_AREA, MAP_AREA);

enum SELECTMODE
{
	MODE_TERRAIN_SELECT,
	MODE_OBJECT_SELECT,
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
	tile* _mapTiles;
	tile* _terrainTileSet;
	tile* _objectTileSet;

	POINT _mapSize;
	POINT _mapMove;
	POINT _terrainTileSize;
	POINT _objectTileSize;

private:
	image* _terrainTileImage;
	image* _objectTileImage;

private:
	SELECTMODE _currentSelectMode;
	tile _selectedTerrainTile;
	tile _selectedObjectTile;

private:
	RECT _newBtn;
	RECT _saveBtn, _loadBtn;
	RECT _terrainBtn, _objectBtn, _eraserBtn;
	RECT _changeGameModeBtn, _changeMapEditModeBtn;

private:
	WPARAM _wParam;
	HWND _hDlgNewTile;
	HWND _hSelectTerrain;
	HWND _hSelectObject;

private:
	string _curMapFileName;
	float _autoSaveTimer;

public:
	mapTool();
	~mapTool();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void terrainTileSetInit(string imageKey);
	void objectTileSetInit(string imageKey);

	void clickButton(void);
	void buttonDraw(void);						//버튼 그리는 함수

//	void setTerrainTileSet(string tileSetKeyName, POINT tileSize);

	void createDefaultMap(POINT mapSize);		//맵 사이즈 받아서 기본맵 생성
	void newTileMap(void);

	void mapSave(void);
	void mapLoad(void);
	void mapAutoSave(void);

	//======================= 접근자 & 설정자 =======================
	inline void setSelTerrainTile(tile selTile) { _selectedTerrainTile = selTile; }
	inline tile getSelTerrainTile(void) { return _selectedTerrainTile; }

	inline void setSelObjectTile(tile selTile) { _selectedObjectTile = selTile; }
	inline tile getSelObjectTile(void) { return _selectedObjectTile; }

	inline void setSelectMode(SELECTMODE mode) { _currentSelectMode = mode; }
	inline SELECTMODE getSelectMode(void) { return _currentSelectMode; }

	inline tile getFirstTerrainTile(void) { return _terrainTileSet[0]; }
	inline tile getFirstObjectTile(void) { return _objectTileSet[0]; }

	inline void setHandleNewTile(HWND handle) { _hDlgNewTile = handle; }
	inline HWND getHandleNewTile(void) { return _hDlgNewTile; }

	inline void setHandleSelTerrain(HWND handle) { _hSelectTerrain = handle; }
	inline HWND getHandleSelTerrain(void) { return _hSelectTerrain; }

	inline void setHandleSelObject(HWND handle) { _hSelectObject = handle; }
	inline HWND getHandleSelObject(void) { return _hSelectObject; }
	
	inline void setWParam(WPARAM wParam) { _wParam = wParam; }

};
