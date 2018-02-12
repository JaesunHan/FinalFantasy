#pragma once
#include "gameNode.h"
#include "tile.h"
#include "resource1.h"
#include <commdlg.h>

/********************************************************/
/* ���� Ŭ����											*/
/* �۾��� : ��ȣ��										*/
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
	void buttonDraw(void);						//��ư �׸��� �Լ�

//	void setTerrainTileSet(string tileSetKeyName, POINT tileSize);

	void createDefaultMap(POINT mapSize);		//�� ������ �޾Ƽ� �⺻�� ����
	void newTileMap(void);

	void mapSave(void);
	void mapLoad(void);
	void mapAutoSave(void);
	
	inline void setWParam(WPARAM wParam) { _wParam = wParam; }

	friend BOOL CALLBACK newTileProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
	friend BOOL CALLBACK selectTerrainTileSetProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
	friend BOOL CALLBACK selectObjectTileSetProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
};
