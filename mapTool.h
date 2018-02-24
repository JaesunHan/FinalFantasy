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
	tile* _mapTiles;				// 그려주는 타일의 정보
	tile* _terrainTileSet;			// 현재 지형 타일셋의 정보
	tile* _objectTileSet;			// 현재 오브젝트 타일셋의 정보

	POINT _mapSize;					// 작업중인 맵의 크기
	POINT _mapMove;					// 맵의 카메라 이동을 위한 변수
	POINT _terrainTileSize;			// 현재 지형 타일셋의 크기
	POINT _objectTileSize;			// 현재 오브젝트 타일셋의 크기

private:
	image* _terrainTileImage;		// 선택한 지형 타일셋 이미지
	image* _objectTileImage;		// 선택한 오브젝트 타일셋 이미지

	string _terrainTileImageKey;	// 선택한 지형 타일셋 이미지
	string _objectTileImageKey;		// 선택한 오브젝트 타일셋 이미지

private:
	SELECTMODE _currentSelectMode;	// 현재 작업 모드
	tile _selectedTerrainTile;		// 선택한 지형 타일
	tile _selectedObjectTile;		// 선택한 오브젝트 타일

	POINT _startPt;
	BOOL _isSetArea;

private:							// 버튼의 사각형 영역
	RECT _newBtn;
	RECT _saveBtn, _loadBtn;
	RECT _terrainBtn, _objectBtn, _eraserBtn;
	RECT _changeGameModeBtn, _changeMapEditModeBtn;

private:
	WPARAM _wParam;					// 미사용 변수(원래는 winproc에서 wParam값 받기위해 만들었음)
	HWND _hDlgNewTile;				// 새로운 맵 생성 다이얼로그 박스 핸들 
	HWND _hSelectTerrain;			// 지형 타일셋 선택 다이얼로그 박스 핸들
	HWND _hSelectObject;			// 오브젝트 타일셋 선택 다이얼로그 박스 핸들

private:
	string _curMapFileName;			// 자동 저장을 위한 현재 작업중인 파일 이름 
	float _autoSaveTimer;			// 자동 저장 간격을 위한 타이머

private:


public:
	mapTool();
	~mapTool();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void terrainTileSetInit();		// 지형 타일셋 선택시 타일셋 이미지와 속성을 샘플이미지에 부여
	void objectTileSetInit();		// 오브젝트 타일셋 선택시 타일셋 이미지와 속성을 샘플이미지에 부여

	void clickButton(void);			// 원래는 버튼 클릭만 처리 할려고 했는데 모든 클릭 처리를 여기서 함
	void setTerrainToMap(void);		// 맵에 지형 설정하는 함수
	void setTerraintAreaToMap(int startX, int startY, int endX, int endY);
	TERRAIN* getNearTerrain(int curTileIndex);	// 매개변수로 받은 인덱스 타일의 상하좌우 타일의 속성을 받아옴
	void buttonDraw(void);						// 버튼 그리는 함수
	void minimapDraw(void);

//	void setTerrainTileSet(string tileSetKeyName, POINT tileSize);

	void createDefaultMap(POINT mapSize);		// 맵 사이즈 받아서 기본맵 생성
	void newTileMap(void);						// 새로운 맵 생성

	void mapSave(void);							// 맵 저장
	void mapLoad(void);							// 맵 불러오기
	void mapAutoSave(void);						// 맵 자동 저장

	//======================= 접근자 & 설정자 =======================
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
