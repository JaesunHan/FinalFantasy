#pragma once
#include "gameNode.h"
#include "tile.h"
#include "resource1.h"
#include <commdlg.h>

/********************************************************/
/* ���� Ŭ����											*/
/* �۾��� : ��ȣ��										*/
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
	RECT _newBtn;
	RECT _saveBtn, _loadBtn;
	RECT _terrainBtn, _objectBtn, _eraserBtn;
	RECT _changeGameModeBtn, _changeMapEditModeBtn;

private:
	WPARAM _wParam;

	HWND _hDlgNewTile;

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
	void buttonDraw(void);						//��ư �׸��� �Լ�

//	void setTerrainTileSet(string tileSetKeyName, POINT tileSize);

	void createDefaultMap(POINT mapSize);		//�� ������ �޾Ƽ� �⺻�� ����
	void newTileMap(void);

	void mapSave(void);
	void mapLoad(void);

	inline void setWParam(WPARAM wParam) { _wParam = wParam; }

	friend BOOL CALLBACK newTileProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

