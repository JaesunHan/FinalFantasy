#include "stdafx.h"
#include "mapTool.h"

BOOL CALLBACK newTileProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK selectTerrainTileSetProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK selectObjectTileSetProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);

POINT operator+(POINT operand1, POINT operand2);
POINT operator-(POINT operand1, POINT operand2);


mapTool::mapTool()
	: _hSelectTerrain(NULL), _hSelectObject(NULL)
{
}


mapTool::~mapTool()
{
}

HRESULT mapTool::init(void)
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

	//버튼 초기화
	_newBtn = RectMake(850, 480, 100, 30);
	_saveBtn = RectMake(960, 480, 100, 30);
	_loadBtn = RectMake(1070, 480, 100, 30);
	//_terrainBtn = RectMake(850, 560, 100, 30);
	//_objectBtn = RectMake(960, 560, 100, 30);
	_eraserBtn = RectMake(850, 520, 100, 30);
	//_changeGameModeBtn = RectMake(850, 600, 100, 30);
	//_changeMapEditModeBtn = RectMake(960, 600, 100, 30);

	//타일셋 초기화
	terrainTileSetInit("worldTerrain");
	objectTileSetInit("worldObject");
	
	//맵 초기화
	_mapTiles = NULL;
	_mapSize = PointMake(0, 0);
	_mapMove = PointMake(-32, -32);

	_currentSelectMode = MODE_TERRAIN_SELECT;

	_selectedTerrainTile.init(PointMake(0, 0));
	_selectedObjectTile.init(PointMake(0, 0));

	_selectedTerrainTile.selectTerrain(_terrainTileSet[0]);

	_curMapFileName = "none";
	_autoSaveTimer = TIMEMANAGER->getWorldTime();

	if (_hSelectTerrain == NULL)
	{
		_hSelectTerrain = CreateDialogParam(_hInstance, MAKEINTRESOURCE(IDD_DIALOG2), _hWnd, selectTerrainTileSetProc, (LPARAM)this);
		ShowWindow(_hSelectTerrain, SW_SHOW);
	}

	if (_hSelectObject == NULL)
	{
		_hSelectObject = CreateDialogParam(_hInstance, MAKEINTRESOURCE(IDD_DIALOG3), _hWnd, selectObjectTileSetProc, (LPARAM)this);
		ShowWindow(_hSelectObject, SW_SHOW);
	}
	

	return S_OK;
}

void mapTool::release(void)
{

}

void mapTool::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		clickButton();
	}
	if (_mapSize.x != 0 && _mapSize.y != 0)
	{
		if (KEYMANAGER->isStayKeyDown(VK_UP) && _mapTiles[_mapSize.x * _mapSize.y - 1].getCenterPt().y + TILE_SIZEY / 2 > 640) _mapMove.y -= MAP_MOVE_SPEED;
		if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _mapTiles[_mapSize.x * _mapSize.y - 1].getCenterPt().y + TILE_SIZEY / 2 > 640) _mapMove.y += MAP_MOVE_SPEED;
		if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _mapTiles[_mapSize.x * _mapSize.y - 1].getCenterPt().x - TILE_SIZEX / 2 > 640) _mapMove.x -= MAP_MOVE_SPEED;
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _mapTiles[_mapSize.x * _mapSize.y - 1].getCenterPt().x - TILE_SIZEX / 2 > 640) _mapMove.x += MAP_MOVE_SPEED;

		if (_mapMove.x < -TILE_SIZEX) _mapMove.x = -TILE_SIZEX;
		if (_mapMove.y < -TILE_SIZEY) _mapMove.y = -TILE_SIZEY;
	
		if (_mapMove.x > (_mapTiles[_mapSize.x * _mapSize.y - 1].getCenterPt().x - TILE_SIZEX / 2 - MAP_AREA + TILE_SIZEX) && _mapSize.x > 20)
			_mapMove.x = (_mapTiles[_mapSize.x * _mapSize.y - 1].getCenterPt().x - TILE_SIZEX / 2 - MAP_AREA + TILE_SIZEX);
		if (_mapMove.y > (_mapTiles[_mapSize.x * _mapSize.y - 1].getCenterPt().y + TILE_SIZEY / 2 - MAP_AREA + TILE_SIZEY) && _mapSize.y > 20)
			_mapMove.y = (_mapTiles[_mapSize.x * _mapSize.y - 1].getCenterPt().y + TILE_SIZEY / 2 - MAP_AREA + TILE_SIZEY);
	}
	
	//autoSave 기능
	if (TIMEMANAGER->getWorldTime() - _autoSaveTimer >= 80)
	{
		_autoSaveTimer = TIMEMANAGER->getWorldTime();
		//MessageBox(_hWnd, "test", "test", MB_OK);
		if (_curMapFileName != "none") mapAutoSave();
	}
	
}

void mapTool::render(void)
{
	PatBlt(tileMapDC->getMemDC(), 0, 0, MAP_AREA, MAP_AREA, BLACKNESS);
	//================== 이 위는 손대지 마시오 =========================
	
	if (_mapTiles != NULL)
	{
		int renderX = _mapSize.x;
		int renderY = _mapSize.y;
		int indexX = 0;
		int indexY = 0;
		
		if (renderX > 23)
			renderX = 22;
		else if (renderX == 22);
		else ++renderX;

		if (renderY > 23)
			renderY = 22;
		else if (renderY == 22);
		else ++renderY;

		for (int i = indexY; i < renderY; ++i)
		{
			for (int j = indexX; j < renderX; ++j)
			{
				if (_mapMove.x / TILE_SIZEX + j + (_mapMove.y / TILE_SIZEY + i) * _mapSize.x < 0) continue;
				if (_mapMove.x / TILE_SIZEX + j + (_mapMove.y / TILE_SIZEY + i) * _mapSize.x >= _mapSize.x * _mapSize.y)
					continue;

				_mapTiles[_mapMove.x / TILE_SIZEX + j + (_mapMove.y / TILE_SIZEY + i) * _mapSize.x].render(tileMapDC->getMemDC(), _mapMove.x, _mapMove.y);
			}
		}
	}
	
	if (_currentSelectMode == MODE_TERRAIN_SELECT)
	{
		for (int i = 0; i < _terrainTileSize.x * _terrainTileSize.y; i++)
		{
			_terrainTileSet[i].render(getMemDC(), 0, 0);
		}
	}
	if (_currentSelectMode == MODE_OBJECT_SELECT)
	{
		for (int i = 0; i < _objectTileSize.x * _objectTileSize.y; i++)
		{
			_objectTileSet[i].render(getMemDC(), 0, 0);
		}
	}

	buttonDraw();

	tileMapDC->render(getMemDC(), -32, -32, 0, 0, 672, 672);
}

void mapTool::terrainTileSetInit(string imageKey)
{
	_terrainTileImage = IMAGEMANAGER->findImage(imageKey);
	_terrainTileSize = PointMake(_terrainTileImage->getMaxFrameX() + 1, _terrainTileImage->getMaxFrameY() + 1);
	_terrainTileSet = new tile[_terrainTileSize.x * _terrainTileSize.y];

	for (int i = 0; i < _terrainTileSize.x * _terrainTileSize.y; i++)
	{
		_terrainTileSet[i].init(PointMake(WINSIZEX - _terrainTileImage->getWidth()
			+ TILE_SIZEX / 2 + (i % _terrainTileSize.x) * TILE_SIZEX, TILE_SIZEY / 2 + (i / _terrainTileSize.x) * TILE_SIZEY));
		_terrainTileSet[i].setTerrainImageKey(imageKey);
		_terrainTileSet[i].setTerrainFramePos(PointMake(i % _terrainTileSize.x, i / _terrainTileSize.x));
		_terrainTileSet[i].setIndex(PointMake(i % _terrainTileSize.x, i / _terrainTileSize.x));
		
		if (imageKey == "worldTerrain")
		{
			// 지형 타입 부여
			_terrainTileSet[i].setTerrain(TR_GRASS);		// 대부분이 초원 타입이기 때문에 우선 초원 타입으로 초기화

			if ((i >= 0 && i <= 2) || i == 12 || i == 14 || (i >= 24 && i <= 26) || i == 40 || i == 41 || i == 52 || i == 53 || i == 63)
			{
				_terrainTileSet[i].setTerrain(TR_WATER);
			}
			if ((i >= 6 && i <= 8) || (i >= 18 && i <= 20) || (i >= 32 && i <= 34) || i == 36 || i == 37 || i == 48 || i == 49)
			{
				_terrainTileSet[i].setTerrain(TR_DESERT);
			}
		}
		else if (imageKey == "townTerrain1")
		{
			// 지형 타입 부여
			_terrainTileSet[i].setTerrain(TR_ROAD);		// 대부분이 길 타입이기 때문에 우선 길 타입으로 초기화

			if (i == 0 || i == 1 || (i >= 3 && i <= 6) || i == 20 || i == 22 || i == 23 || (i >= 28 && i <= 31))
			{
				_terrainTileSet[i].setTerrain(TR_GRASS);
			}
			if ((i >= 32 && i <= 34) || (i >= 40 && i <= 42) || (i >= 48 && i <= 50))
			{
				_terrainTileSet[i].setTerrain(TR_DIRT);
			}
			if (i == 35)
			{
				_terrainTileSet[i].setTerrain(TR_STUMP);
			}
		}
		else if (imageKey == "townTerrain2")
		{
			// 지형 타입 부여
			_terrainTileSet[i].setTerrain(TR_ROAD);		// 대부분이 길 타입이기 때문에 우선 길 타입으로 초기화

			if (i == 0 || i == 1 || (i >= 3 && i <= 6) || i == 20 || i == 22 || i == 23 || (i >= 28 && i <= 31))
			{
				_terrainTileSet[i].setTerrain(TR_GRASS);
			}
			if ((i >= 32 && i <= 34) || (i >= 40 && i <= 42) || (i >= 48 && i <= 50))
			{
				_terrainTileSet[i].setTerrain(TR_DIRT);
			}
			if (i == 35)
			{
				_terrainTileSet[i].setTerrain(TR_STUMP);
			}
		}
		else if (imageKey == "townTerrain3")
		{
			// 지형 타입 부여
			_terrainTileSet[i].setTerrain(TR_ROAD);		// 대부분이 길 타입이기 때문에 우선 길 타입으로 초기화

			if (i == 0 || i == 1 || (i >= 3 && i <= 6) || i == 20 || i == 22 || i == 23 || (i >= 28 && i <= 31))
			{
				_terrainTileSet[i].setTerrain(TR_GRASS);
			}
			if ((i >= 32 && i <= 34) || (i >= 40 && i <= 42) || (i >= 48 && i <= 50))
			{
				_terrainTileSet[i].setTerrain(TR_DIRT);
			}
			if (i == 35)
			{
				_terrainTileSet[i].setTerrain(TR_STUMP);
			}
		}
		
		// 지형 타입에 따른 속성 부여
		_terrainTileSet[i].updateTerrainAttr();
	}
}

void mapTool::objectTileSetInit(string imageKey)
{
	_objectTileImage = IMAGEMANAGER->findImage(imageKey);
	_objectTileSize = PointMake(_objectTileImage->getMaxFrameX() + 1, _objectTileImage->getMaxFrameY() + 1);
	_objectTileSet = new tile[_objectTileSize.x * _objectTileSize.y];

	for (int i = 0; i < _objectTileSize.x * _objectTileSize.y; i++)
	{
		_objectTileSet[i].init(PointMake(WINSIZEX - _objectTileImage->getWidth()
			+ TILE_SIZEX / 2 + (i % _objectTileSize.x) * TILE_SIZEX, TILE_SIZEY / 2 + (i / _objectTileSize.x) * TILE_SIZEY));
		_objectTileSet[i].setObjectImageKey(imageKey);
		_objectTileSet[i].setObjectFramePos(PointMake(i % _objectTileSize.x, i / _objectTileSize.x));
		_objectTileSet[i].setIndex(PointMake(i % _objectTileSize.x, i / _objectTileSize.x));
		
		//오브젝트 타입 부여
		_objectTileSet[i].setObject(OBJ_MOUNTAIN);		//대부분 산 타입이기 때문에 산 타입으로 초기화

		if (i == 16 || i == 17 || i == 24 || i == 25) _objectTileSet[i].setObject(OBJ_CASTLE);
		else if (i == 18 || i == 19 || i == 26 || i == 27) _objectTileSet[i].setObject(OBJ_TOWN);
		else if (i == 29) _objectTileSet[i].setObject(OBJ_CAVE);

		_objectTileSet[i].updateObjectAttr();
	}
}

void mapTool::clickButton(void)
{
	if (PtInRect(&_newBtn, _ptMouse))
	{
		newTileMap();
		return;
	}
	else if (PtInRect(&_saveBtn, _ptMouse))
	{
		mapSave();
		return;
	}
	else if (PtInRect(&_loadBtn, _ptMouse))
	{
		mapLoad();
		return;
	}
	else if (PtInRect(&_eraserBtn, _ptMouse)) _currentSelectMode = MODE_ERASER;
	//else if (PtInRect(&_terrainBtn, _ptMouse))
	//{
	//	_currentSelectMode = MODE_TERRAIN_SELECT;
	//	_selectedTerrainTile.selectTerrain(_terrainTileSet[0]);
	//}
	//else if (PtInRect(&_objectBtn, _ptMouse))
	//{
	//	
	//	_currentSelectMode = MODE_OBJECT_SELECT;
	//	_selectedObjectTile.selectObject(_objectTileSet[0]);
	//}
	//else if (PtInRect(&_changeGameModeBtn, _ptMouse)) _currentSelectMode = EDIT_BUTTON_CHANGE_GAME_MODE;
	//else if (PtInRect(&_changeMapEditModeBtn, _ptMouse)) _currentSelectMode = EDIT_BUTTON_CHANGE_MAP_EDIT_MODE;
	//else _currentSelectMode = EDIT_BUTTON_END;

	if (_currentSelectMode == MODE_TERRAIN_SELECT)
	{
		for (int i = 0; i < _terrainTileSize.x * _terrainTileSize.y; i++)
		{
			if (PtInRect(&RectMakeCenter(_terrainTileSet[i].getCenterPt().x, _terrainTileSet[i].getCenterPt().y, TILE_SIZEX, TILE_SIZEY), _ptMouse))
			{
				_selectedTerrainTile.selectTerrain(_terrainTileSet[i]);
				break;
			}
		}

		if (PtInRect(&RectMake(0, 0, MAP_AREA - TILE_SIZEX * 2, MAP_AREA - TILE_SIZEY * 2), _ptMouse))
		{
			for (int i = 0; i < _mapSize.x * _mapSize.y; i++)
			{
				if (PtInRect(&RectMakeCenter(_mapTiles[i].getCenterPt().x, _mapTiles[i].getCenterPt().y, TILE_SIZEX, TILE_SIZEY), _ptMouse + _mapMove + PointMake(TILE_SIZEX, TILE_SIZEY)))
				{
					_mapTiles[i].setTerrain(_selectedTerrainTile);
					break;
				}
			}
		}
	}
	else if (_currentSelectMode == MODE_OBJECT_SELECT)
	{
		for (int i = 0; i < _objectTileSize.x * _objectTileSize.y; i++)
		{
			if (PtInRect(&RectMakeCenter(_objectTileSet[i].getCenterPt().x, _objectTileSet[i].getCenterPt().y, TILE_SIZEX, TILE_SIZEY), _ptMouse))
			{
				_selectedObjectTile.selectObject(_objectTileSet[i]);
				break;
			}
		}

		if (PtInRect(&RectMake(0, 0, MAP_AREA - TILE_SIZEX * 2, MAP_AREA - TILE_SIZEY * 2), _ptMouse))
		{
			for (int i = 0; i < _mapSize.x * _mapSize.y; i++)
			{
				if (PtInRect(&RectMakeCenter(_mapTiles[i].getCenterPt().x, _mapTiles[i].getCenterPt().y, TILE_SIZEX, TILE_SIZEY), _ptMouse + _mapMove + PointMake(TILE_SIZEX, TILE_SIZEY)))
				{
					_mapTiles[i].setObject(_selectedObjectTile);
					break;
				}
			}
		}
	}
	else if (_currentSelectMode == MODE_ERASER)
	{
		for (int i = 0; i < _mapSize.x * _mapSize.y; i++)
		{
			if (PtInRect(&RectMakeCenter(_mapTiles[i].getCenterPt().x, _mapTiles[i].getCenterPt().y, TILE_SIZEX, TILE_SIZEY), _ptMouse))
			{
				_mapTiles[i].eraseObject();
				break;
			}
		}
	}
}

void mapTool::buttonDraw(void)
{
	//타일 세팅을 위한 버튼
	SetTextAlign(getMemDC(), TA_CENTER);
	Rectangle(getMemDC(), _newBtn.left, _newBtn.top, _newBtn.right, _newBtn.bottom);
	TextOut(getMemDC(), _newBtn.left + 50, _newBtn.top + 7, "new", strlen("new"));
	Rectangle(getMemDC(), _saveBtn.left, _saveBtn.top, _saveBtn.right, _saveBtn.bottom);
	TextOut(getMemDC(), _saveBtn.left + 50, _saveBtn.top + 7, "save", strlen("save"));
	Rectangle(getMemDC(), _loadBtn.left, _loadBtn.top, _loadBtn.right, _loadBtn.bottom);
	TextOut(getMemDC(), _loadBtn.left + 50, _loadBtn.top + 7, "load", strlen("load"));
	//Rectangle(getMemDC(), _terrainBtn.left, _terrainBtn.top, _terrainBtn.right, _terrainBtn.bottom);
	//TextOut(getMemDC(), _terrainBtn.left + 50, _terrainBtn.top + 7, "terrain", strlen("terrain"));
	//Rectangle(getMemDC(), _objectBtn.left, _objectBtn.top, _objectBtn.right, _objectBtn.bottom);
	//TextOut(getMemDC(), _objectBtn.left + 50, _objectBtn.top + 7, "object", strlen("object"));
	Rectangle(getMemDC(), _eraserBtn.left, _eraserBtn.top, _eraserBtn.right, _eraserBtn.bottom);
	TextOut(getMemDC(), _eraserBtn.left + 50, _eraserBtn.top + 7, "eraser", strlen("eraser"));
	//맵툴 모드, 게임 모드 변경버튼
	//Rectangle(getMemDC(), _changeGameModeBtn.left, _changeGameModeBtn.top, _changeGameModeBtn.right, _changeGameModeBtn.bottom);
	//TextOut(getMemDC(), _changeGameModeBtn.left + 50, _changeGameModeBtn.top + 7, "gameMode", strlen("gameMode"));
	//Rectangle(getMemDC(), _changeMapEditModeBtn.left, _changeMapEditModeBtn.top, _changeMapEditModeBtn.right, _changeMapEditModeBtn.bottom);
	//TextOut(getMemDC(), _changeMapEditModeBtn.left + 50, _changeMapEditModeBtn.top + 7, "mapEdit", strlen("mapEdit"));

	HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oBrush = (HBRUSH)SelectObject(getMemDC(), hBrush);
	HPEN hPen = (HPEN)CreatePen(PS_SOLID, 4, RGB(200, 100, 0));
	HPEN oPen = (HPEN)SelectObject(getMemDC(), hPen);

	if (_currentSelectMode == MODE_TERRAIN_SELECT)
	{
		int selectIndex = _selectedTerrainTile.getTerrainFramePos().x + _selectedTerrainTile.getTerrainFramePos().y * _terrainTileSize.x;
		RECT selectTileRc = RectMakeCenter(_terrainTileSet[selectIndex].getCenterPt().x, _terrainTileSet[selectIndex].getCenterPt().y, TILE_SIZEX, TILE_SIZEY);
		
		Rectangle(getMemDC(), selectTileRc.left + 2, selectTileRc.top + 2, selectTileRc.right - 2, selectTileRc.bottom - 2);
	}
	else if (_currentSelectMode == MODE_OBJECT_SELECT)
	{
		int selectIndex = _selectedObjectTile.getObjectFramePos().x + _selectedObjectTile.getObjectFramePos().y * _objectTileSize.x;
		RECT selectTileRc = RectMakeCenter(_objectTileSet[selectIndex].getCenterPt().x, _objectTileSet[selectIndex].getCenterPt().y, TILE_SIZEX, TILE_SIZEY);

		Rectangle(getMemDC(), selectTileRc.left + 2, selectTileRc.top + 2, selectTileRc.right - 2, selectTileRc.bottom - 2);
	}

	SelectObject(getMemDC(), oPen);
	DeleteObject(hPen);
	DeleteObject(oPen);
	SelectObject(getMemDC(), oBrush);
	DeleteObject(hBrush);
	DeleteObject(oBrush);
}

void mapTool::createDefaultMap(POINT mapSize)
{
	_mapSize = mapSize;

	_mapTiles = new tile[_mapSize.x * _mapSize.y];

	for (int i = 0; i < _mapSize.x * _mapSize.y; i++)
	{
		_mapTiles[i].init(PointMake(TILE_SIZEX / 2 + TILE_SIZEX * (i % _mapSize.x), TILE_SIZEY / 2 + TILE_SIZEY * (i / _mapSize.x)));
		_mapTiles[i].setTerrainImageKey("worldTerrain");
		_mapTiles[i].setTerrainFramePos(PointMake(1, 1));
		_mapTiles[i].setTerrain(TR_GRASS);
		//맵 타일 초기화 부분
	}
}

void mapTool::newTileMap(void)
{
	this->init();
	DialogBoxParam(_hInstance, MAKEINTRESOURCE(IDD_DIALOG1), _hWnd, newTileProc, (LPARAM)this);
}

void mapTool::mapSave(void)
{
	HANDLE file;
	DWORD write;

	OPENFILENAME ofn;
	char filePath[1024] = "";
	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = filePath;
	ofn.nMaxFile = sizeof(filePath);
	ofn.nFilterIndex = true;
	ofn.nMaxFileTitle = NULL;
	ofn.lpstrFileTitle = NULL;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrFilter = "Map File(*.map)\0*.map\0";
	ofn.Flags = OFN_OVERWRITEPROMPT;

	if (GetSaveFileName(&ofn) == false) return;

	_curMapFileName = ofn.lpstrFile;
	file = CreateFile(_curMapFileName.c_str(), GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, &_mapSize, sizeof(POINT), &write, NULL);
	WriteFile(file, _mapTiles, sizeof(tile) * _mapSize.x * _mapSize.y, &write, NULL);

	CloseHandle(file);
}

void mapTool::mapLoad(void)
{
	HANDLE file;
	DWORD read;

	OPENFILENAME ofn;
	char filePath[1024] = "";
	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = filePath;
	ofn.nMaxFile = sizeof(filePath);
	ofn.nFilterIndex = true;
	ofn.nMaxFileTitle = NULL;
	ofn.lpstrFileTitle = NULL;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrFilter = "Map File(*.map)\0*.map\0";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	//예외처리
	if (GetOpenFileName(&ofn) == FALSE) return;

	this->init();

	_curMapFileName = ofn.lpstrFile;
	file = CreateFile(_curMapFileName.c_str(), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, &_mapSize, sizeof(POINT), &read, NULL);
	_mapTiles = new tile[_mapSize.x * _mapSize.y];
	ReadFile(file, _mapTiles, sizeof(tile) * _mapSize.x * _mapSize.y, &read, NULL);

	CloseHandle(file);
}

void mapTool::mapAutoSave(void)
{
	HANDLE file;
	DWORD write;

	file = CreateFile(_curMapFileName.c_str(), GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, &_mapSize, sizeof(POINT), &write, NULL);
	WriteFile(file, _mapTiles, sizeof(tile) * _mapSize.x * _mapSize.y, &write, NULL);

	CloseHandle(file);
}

BOOL CALLBACK newTileProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	int mapSizeX = 0;
	int mapSizeY = 0;
	mapTool* pThis = (mapTool*)GetWindowLongPtr(hDlg, GWLP_USERDATA);

	switch (iMessage)
	{
	case WM_INITDIALOG:

		SetWindowPos(hDlg, HWND_TOP, 100, 100, 0,0,SWP_NOSIZE);
		SetWindowLongPtr(hDlg, GWLP_USERDATA, (LONG_PTR)lParam);
		pThis = (mapTool*)lParam;
		pThis->setHandleNewTile(hDlg);
		break;

	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case IDOK:
			mapSizeX = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, FALSE);
			mapSizeY = GetDlgItemInt(hDlg, IDC_EDIT2, NULL, FALSE);
			pThis->createDefaultMap(PointMake(mapSizeX, mapSizeY));
		case IDCANCEL:
			EndDialog(pThis->getHandleNewTile(), 0);
			return TRUE;
		}

		return FALSE;
	case WM_CLOSE:
		PostQuitMessage(0);
		return TRUE;
	}
	return FALSE;

}

BOOL CALLBACK selectTerrainTileSetProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	int selectPos = 0;
	char selectImageKey[1024] = "";
	mapTool* pThis = (mapTool*)GetWindowLongPtr(hDlg, GWLP_USERDATA);

	switch (iMessage)
	{
	case WM_INITDIALOG:

		SetWindowPos(hDlg, HWND_TOP, WINSIZEX + 3, 0, 0, 0, SWP_NOSIZE);
		SetWindowLongPtr(hDlg, GWLP_USERDATA, (LONG_PTR)lParam);
		pThis = (mapTool*)lParam;
		pThis->setHandleSelTerrain(hDlg);
		SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)"worldTerrain");
		SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)"townTerrain1");
		SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)"townTerrain2");
		SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)"townTerrain3");
		break;

	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case IDOK:
			selectPos = SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_GETCURSEL, 0, 0);
			SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_GETTEXT, (WPARAM)selectPos, (LPARAM)selectImageKey);
			pThis->terrainTileSetInit(selectImageKey);
			pThis->setSelectMode(MODE_TERRAIN_SELECT);
			pThis->getSelTerrainTile().selectTerrain(pThis->getFirstTerrainTile());
			break;
		}

		return FALSE;
	case WM_CLOSE:
		PostQuitMessage(0);
		return TRUE;
	}
	return FALSE;
}

BOOL CALLBACK selectObjectTileSetProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	int selectPos = 0;
	char selectImageKey[1024] = "";
	mapTool* pThis = (mapTool*)GetWindowLongPtr(hDlg, GWLP_USERDATA);

	switch (iMessage)
	{
	case WM_INITDIALOG:

		SetWindowPos(hDlg, HWND_TOP, WINSIZEX + 3, 160, 0, 0, SWP_NOSIZE);
		SetWindowLongPtr(hDlg, GWLP_USERDATA, (LONG_PTR)lParam);
		pThis = (mapTool*)lParam;
		pThis->setHandleSelObject(hDlg);
		SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)"townHouse1");
		SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)"townHouse2");
		SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)"townHouse3");
		SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)"townHouse4");
		SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)"townHouse5");
		SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)"townHouse6");
		SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)"townObject1");
		SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)"townObject2");
		SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)"townObject3");
		SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)"worldObject");
		//IMAGEMANAGER->render("townHouse1", getMemDC());
		break;

	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case IDOK:
			selectPos = SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_GETCURSEL, 0, 0);
			SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_GETTEXT, (WPARAM)selectPos, (LPARAM)selectImageKey);
			pThis->objectTileSetInit(selectImageKey);
			pThis->setSelectMode(MODE_OBJECT_SELECT);
			pThis->getSelObjectTile().selectObject(pThis->getFirstObjectTile());
			break;
		}
		return FALSE;
	case WM_CLOSE:
		PostQuitMessage(0);
		return TRUE;
	}
	return FALSE;
}

//POINT 변수를 위한 +, - 연산자 오버로딩(각각의 x, y값을 연산)
POINT operator+(POINT operand1, POINT operand2)
{
	return PointMake(operand1.x + operand2.x, operand1.y + operand2.y);
}

POINT operator-(POINT operand1, POINT operand2)
{
	return PointMake(operand1.x - operand2.x, operand1.y - operand2.y);
}