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

#define MINIMAP_SIZEX 128
#define MINIMAP_SIZEY 128

static image* tileMapDC = IMAGEMANAGER->addImage("tileMapArea", MAP_AREA, MAP_AREA);
static image* miniMap = IMAGEMANAGER->addImage("miniMap", MINIMAP_SIZEX, MINIMAP_SIZEY);

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
	tile* _mapTiles;				// �׷��ִ� Ÿ���� ����
	tile* _terrainTileSet;			// ���� ���� Ÿ�ϼ��� ����
	tile* _objectTileSet;			// ���� ������Ʈ Ÿ�ϼ��� ����

	POINT _mapSize;					// �۾����� ���� ũ��
	POINT _mapMove;					// ���� ī�޶� �̵��� ���� ����
	POINT _terrainTileSize;			// ���� ���� Ÿ�ϼ��� ũ��
	POINT _objectTileSize;			// ���� ������Ʈ Ÿ�ϼ��� ũ��

private:
	image* _terrainTileImage;		// ������ ���� Ÿ�ϼ� �̹���
	image* _objectTileImage;		// ������ ������Ʈ Ÿ�ϼ� �̹���

	string _terrainTileImageKey;	// ������ ���� Ÿ�ϼ� �̹���
	string _objectTileImageKey;		// ������ ������Ʈ Ÿ�ϼ� �̹���

private:
	SELECTMODE _currentSelectMode;	// ���� �۾� ���
	tile _selectedTerrainTile;		// ������ ���� Ÿ��
	tile _selectedObjectTile;		// ������ ������Ʈ Ÿ��

	POINT _startPt;
	BOOL _isSetArea;

private:							// ��ư�� �簢�� ����
	RECT _newBtn;
	RECT _saveBtn, _loadBtn;
	RECT _terrainBtn, _objectBtn, _eraserBtn;
	RECT _changeGameModeBtn, _changeMapEditModeBtn;

private:
	WPARAM _wParam;					// �̻�� ����(������ winproc���� wParam�� �ޱ����� �������)
	HWND _hDlgNewTile;				// ���ο� �� ���� ���̾�α� �ڽ� �ڵ� 
	HWND _hSelectTerrain;			// ���� Ÿ�ϼ� ���� ���̾�α� �ڽ� �ڵ�
	HWND _hSelectObject;			// ������Ʈ Ÿ�ϼ� ���� ���̾�α� �ڽ� �ڵ�

private:
	string _curMapFileName;			// �ڵ� ������ ���� ���� �۾����� ���� �̸� 
	float _autoSaveTimer;			// �ڵ� ���� ������ ���� Ÿ�̸�

private:


public:
	mapTool();
	~mapTool();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void terrainTileSetInit();		// ���� Ÿ�ϼ� ���ý� Ÿ�ϼ� �̹����� �Ӽ��� �����̹����� �ο�
	void objectTileSetInit();		// ������Ʈ Ÿ�ϼ� ���ý� Ÿ�ϼ� �̹����� �Ӽ��� �����̹����� �ο�

	void clickButton(void);			// ������ ��ư Ŭ���� ó�� �ҷ��� �ߴµ� ��� Ŭ�� ó���� ���⼭ ��
	void setTerrainToMap(void);		// �ʿ� ���� �����ϴ� �Լ�
	void setTerraintAreaToMap(int startX, int startY, int endX, int endY);
	TERRAIN* getNearTerrain(int curTileIndex);	// �Ű������� ���� �ε��� Ÿ���� �����¿� Ÿ���� �Ӽ��� �޾ƿ�
	void buttonDraw(void);						// ��ư �׸��� �Լ�
	void minimapDraw(void);

//	void setTerrainTileSet(string tileSetKeyName, POINT tileSize);

	void createDefaultMap(POINT mapSize);		// �� ������ �޾Ƽ� �⺻�� ����
	void newTileMap(void);						// ���ο� �� ����

	void mapSave(void);							// �� ����
	void mapLoad(void);							// �� �ҷ�����
	void mapAutoSave(void);						// �� �ڵ� ����

	//======================= ������ & ������ =======================
	inline void setSelTerrainTile(tile selTile) { _selectedTerrainTile = selTile; }
	inline tile getSelTerrainTile(void) { return _selectedTerrainTile; }

	inline void setSelObjectTile(tile selTile) { _selectedObjectTile = selTile; }
	inline tile getSelObjectTile(void) { return _selectedObjectTile; }

	inline void setSelectMode(SELECTMODE mode) { _currentSelectMode = mode; }
	inline SELECTMODE getSelectMode(void) { return _currentSelectMode; }

	inline tile getFirstTerrainTile(void) { return _terrainTileSet[0]; }
	inline tile getFirstObjectTile(void) { return _objectTileSet[0]; }

	inline image* getTerrainTileImage(void) { return _terrainTileImage; }
	inline image* getObjectTileImage(void) { return _objectTileImage; }
	inline tile* getTerrainTileSet(void) { return _terrainTileSet; }
	inline tile* getObjectTileSet(void) { return _objectTileSet; }
	inline POINT getTerrainTileSetSize(void) { return _terrainTileSize; }
	inline POINT getObjectTileSetSize(void) { return _objectTileSize; }

	inline void setTerrainTileImageKey(string imageKey) { _terrainTileImageKey = imageKey; }
	inline string getTerrainTileImageKey(void) { return _terrainTileImageKey; }
	inline void setObjectTileImageKey(string imageKey) { _objectTileImageKey = imageKey; }
	inline string getObjectTileImageKey(void) { return _objectTileImageKey; }

	inline void setHandleNewTile(HWND handle) { _hDlgNewTile = handle; }
	inline HWND getHandleNewTile(void) { return _hDlgNewTile; }

	inline void setHandleSelTerrain(HWND handle) { _hSelectTerrain = handle; }
	inline HWND getHandleSelTerrain(void) { return _hSelectTerrain; }

	inline void setHandleSelObject(HWND handle) { _hSelectObject = handle; }
	inline HWND getHandleSelObject(void) { return _hSelectObject; }
	
	inline void setWParam(WPARAM wParam) { _wParam = wParam; }

};
