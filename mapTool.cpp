#include "stdafx.h"
#include "mapTool.h"

POINT operator+(POINT operand1, POINT operand2);
POINT operator-(POINT operand1, POINT operand2);


mapTool::mapTool()
{
}


mapTool::~mapTool()
{
}

HRESULT mapTool::init(void)
{
	//버튼 초기화
	_newBtn = RectMake(850, 480, 100, 30);
	_saveBtn = RectMake(850, 520, 100, 30);
	_loadBtn = RectMake(960, 520, 100, 30);
	_terrainBtn = RectMake(850, 560, 100, 30);
	_objectBtn = RectMake(960, 560, 100, 30);
	_eraserBtn = RectMake(1070, 560, 100, 30);
	_changeGameModeBtn = RectMake(850, 600, 100, 30);
	_changeMapEditModeBtn = RectMake(960, 600, 100, 30);

	//타일셋 초기화
	worldMapTerrainTileSetInit();
	worldMapObjectTileSetInie();
	
	//맵 초기화
	_mapTiles = NULL;
	_mapSize = PointMake(0, 0);
	_mapMove = PointMake(-32, -32);

	_currentSelectMode = MODE_WORLDMAP_TERRAIN_SELECT;

	_selectedTerrainTile.init(PointMake(0, 0));
	_selectedObjectTile.init(PointMake(0, 0));

	_selectedTerrainTile.selectTerrain(_worldMapTerrainTileSet[0]);

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

	if (KEYMANAGER->isStayKeyDown(VK_UP) && _mapTiles[_mapSize.x * _mapSize.y - 1].getTileRect().bottom > 640) _mapMove.y -= MAP_MOVE_SPEED;
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _mapTiles[_mapSize.x * _mapSize.y - 1].getTileRect().bottom > 640) _mapMove.y += MAP_MOVE_SPEED;
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _mapTiles[_mapSize.x * _mapSize.y - 1].getTileRect().right > 640) _mapMove.x -= MAP_MOVE_SPEED;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _mapTiles[_mapSize.x * _mapSize.y - 1].getTileRect().right > 640) _mapMove.x += MAP_MOVE_SPEED;

	if (_mapMove.x < -TILE_SIZEX) _mapMove.x = -TILE_SIZEX;
	if (_mapMove.y < -TILE_SIZEY) _mapMove.y = -TILE_SIZEY;
	if (_mapSize.x != 0 && _mapSize.y != 0)
	{
		if (_mapMove.x > (_mapTiles[_mapSize.x * _mapSize.y - 1].getTileRect().right - MAP_AREA + TILE_SIZEX) && _mapSize.x > 20)
			_mapMove.x = (_mapTiles[_mapSize.x * _mapSize.y - 1].getTileRect().right - MAP_AREA + TILE_SIZEX);
		if (_mapMove.y > (_mapTiles[_mapSize.x * _mapSize.y - 1].getTileRect().bottom - MAP_AREA + TILE_SIZEY) && _mapSize.y > 20)
			_mapMove.y = (_mapTiles[_mapSize.x * _mapSize.y - 1].getTileRect().bottom - MAP_AREA + TILE_SIZEY);
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
		
		if (renderX > 23) renderX = 22;
		else ++renderX;

		if (renderY > 23) renderY = 22;
		else ++renderY;

		if (_mapMove.x / TILE_SIZEX < 0) indexX = 1;
		else indexX = 0;

		if (_mapMove.y / TILE_SIZEY < 0) indexY = 1;
		else indexY = 0;

		for (int i = indexY; i < renderY; ++i)
		{
			for (int j = indexX; j < renderX; ++j)
			{
				_mapTiles[_mapMove.x / TILE_SIZEX + j + (_mapMove.y / TILE_SIZEY + i) * _mapSize.x].render(tileMapDC->getMemDC(), _mapMove.x, _mapMove.y);
			}
		}
	}

	if (_currentSelectMode == MODE_WORLDMAP_TERRAIN_SELECT)
	{
		for (int i = 0; i < _worldMapTerrainTileSize.x * _worldMapTerrainTileSize.y; i++)
		{
			_worldMapTerrainTileSet[i].render(getMemDC(), 0, 0);
		}
	}
	if (_currentSelectMode == MODE_WORLDMAP_OBJECT_SELECT)
	{
		for (int i = 0; i < _worldMapObjectTileSize.x * _worldMapObjectTileSize.y; i++)
		{
			_worldMapObjectTileSet[i].render(getMemDC(), 0, 0);
		}
	}

	buttonDraw();

	tileMapDC->render(getMemDC(), -32, -32, 0, 0, 672, 672);
}

void mapTool::worldMapTerrainTileSetInit(void)
{
	_worldMapTerrainTileImage = IMAGEMANAGER->addFrameImage("worldTerrain", ".//tileSet//worldMapTerrainTileSet.bmp", 384, 192, 12, 6, true, RGB(255, 0, 255));
	_worldMapTerrainTileSize = PointMake(_worldMapTerrainTileImage->getMaxFrameX() + 1, _worldMapTerrainTileImage->getMaxFrameY() + 1);
	_worldMapTerrainTileSet = new tile[_worldMapTerrainTileSize.x * _worldMapTerrainTileSize.y];

	for (int i = 0; i < _worldMapTerrainTileSize.x * _worldMapTerrainTileSize.y; i++)
	{
		_worldMapTerrainTileSet[i].init(PointMake(WINSIZEX - _worldMapTerrainTileImage->getWidth()
			+ TILE_SIZEX / 2 + (i % _worldMapTerrainTileSize.x) * TILE_SIZEX, TILE_SIZEY / 2 + (i / _worldMapTerrainTileSize.x) * TILE_SIZEY));
		_worldMapTerrainTileSet[i].setTerrainImageKey("worldTerrain");
		_worldMapTerrainTileSet[i].setTerrainFramePos(PointMake(i % _worldMapTerrainTileSize.x, i / _worldMapTerrainTileSize.x));
		_worldMapTerrainTileSet[i].setIndex(PointMake(i % _worldMapTerrainTileSize.x, i / _worldMapTerrainTileSize.x));
		
		// 지형 타입 부여
		_worldMapTerrainTileSet[i].setTerrain(TR_GRASS);		// 대부분이 초원 타입이기 때문에 우선 초원 타입으로 초기화

		if ((i >= 0 && i <= 2) || i == 12 || i == 14 || (i >= 24 && i <= 26) || i == 40 || i == 41 || i == 52 || i == 53 || i == 63)
		{
			_worldMapTerrainTileSet[i].setTerrain(TR_WATER);
		}
		if ((i >= 6 && i <= 8) || (i >= 18 && i <= 20) || (i >= 32 && i <= 34) || i == 36 || i == 37 || i == 48 || i == 49)
		{
			_worldMapTerrainTileSet[i].setTerrain(TR_DESERT);
		}

		// 지형 타입에 따른 속성 부여
		_worldMapTerrainTileSet[i].updateTerrainAttr();
	}
}

void mapTool::worldMapObjectTileSetInie(void)
{
	_worldMapObjectTileImage = IMAGEMANAGER->addFrameImage("worldMapObjectTileSet", ".//tileSet//worldMapObjectTileSet.bmp", 256, 128, 8, 4, true, RGB(255, 0, 255));
	_worldMapObjectTileSize = PointMake(_worldMapObjectTileImage->getMaxFrameX() + 1, _worldMapObjectTileImage->getMaxFrameY() + 1);
	_worldMapObjectTileSet = new tile[_worldMapObjectTileSize.x * _worldMapObjectTileSize.y];

	for (int i = 0; i < _worldMapObjectTileSize.x * _worldMapObjectTileSize.y; i++)
	{
		_worldMapObjectTileSet[i].init(PointMake(WINSIZEX - _worldMapObjectTileImage->getWidth()
			+ TILE_SIZEX / 2 + (i % _worldMapObjectTileSize.x) * TILE_SIZEX, TILE_SIZEY / 2 + (i / _worldMapObjectTileSize.x) * TILE_SIZEY));
		_worldMapObjectTileSet[i].setObjectImageKey("worldMapObjectTileSet");
		_worldMapObjectTileSet[i].setObjectFramePos(PointMake(i % _worldMapObjectTileSize.x, i / _worldMapObjectTileSize.x));
		_worldMapObjectTileSet[i].setIndex(PointMake(i % _worldMapObjectTileSize.x, i / _worldMapObjectTileSize.x));
		
		//오브젝트 타입 부여
		_worldMapObjectTileSet[i].setObject(OBJ_MOUNTAIN);		//대부분 산 타입이기 때문에 산 타입으로 초기화

		if (i == 16 || i == 17 || i == 24 || i == 25) _worldMapObjectTileSet[i].setObject(OBJ_CASTLE);
		else if (i == 18 || i == 19 || i == 26 || i == 27) _worldMapObjectTileSet[i].setObject(OBJ_TOWN);
		else if (i == 29) _worldMapObjectTileSet[i].setObject(OBJ_CAVE);

		_worldMapObjectTileSet[i].updateObjectAttr();
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
	else if (PtInRect(&_terrainBtn, _ptMouse)) _currentSelectMode = MODE_WORLDMAP_TERRAIN_SELECT;
	else if (PtInRect(&_objectBtn, _ptMouse)) _currentSelectMode = MODE_WORLDMAP_OBJECT_SELECT;
	else if (PtInRect(&_eraserBtn, _ptMouse)) _currentSelectMode = MODE_ERASER;
	//else if (PtInRect(&_changeGameModeBtn, _ptMouse)) _currentSelectMode = EDIT_BUTTON_CHANGE_GAME_MODE;
	//else if (PtInRect(&_changeMapEditModeBtn, _ptMouse)) _currentSelectMode = EDIT_BUTTON_CHANGE_MAP_EDIT_MODE;
	//else _currentSelectMode = EDIT_BUTTON_END;

	if (_currentSelectMode == MODE_WORLDMAP_TERRAIN_SELECT)
	{
		for (int i = 0; i < _worldMapTerrainTileSize.x * _worldMapTerrainTileSize.y; i++)
		{
			if (PtInRect(&_worldMapTerrainTileSet[i].getTileRect(), _ptMouse))
			{
				_selectedTerrainTile.selectTerrain(_worldMapTerrainTileSet[i]);
				break;
			}
		}

		for (int i = 0; i < _mapSize.x * _mapSize.y; i++)
		{
			if (PtInRect(&_mapTiles[i].getTileRect(), _ptMouse + _mapMove + PointMake(TILE_SIZEX, TILE_SIZEY)))
			{
				_mapTiles[i].setTerrain(_selectedTerrainTile);
				break;
			}
		}
	}
	else if (_currentSelectMode == MODE_WORLDMAP_OBJECT_SELECT)
	{
		for (int i = 0; i < _worldMapObjectTileSize.x * _worldMapObjectTileSize.y; i++)
		{
			if (PtInRect(&_worldMapObjectTileSet[i].getTileRect(), _ptMouse))
			{
				_selectedObjectTile.selectObject(_worldMapObjectTileSet[i]);
				break;
			}
		}

		for (int i = 0; i < _mapSize.x * _mapSize.y; i++)
		{
			if (PtInRect(&_mapTiles[i].getTileRect(), _ptMouse + _mapMove + PointMake(TILE_SIZEX, TILE_SIZEY)))
			{
				_mapTiles[i].setObject(_selectedObjectTile);
				break;
			}
		}
	}
	else if (_currentSelectMode == MODE_ERASER)
	{
		for (int i = 0; i < _mapSize.x * _mapSize.y; i++)
		{
			if (PtInRect(&_mapTiles[i].getTileRect(), _ptMouse))
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
	Rectangle(getMemDC(), _terrainBtn.left, _terrainBtn.top, _terrainBtn.right, _terrainBtn.bottom);
	TextOut(getMemDC(), _terrainBtn.left + 50, _terrainBtn.top + 7, "terrain", strlen("terrain"));
	Rectangle(getMemDC(), _objectBtn.left, _objectBtn.top, _objectBtn.right, _objectBtn.bottom);
	TextOut(getMemDC(), _objectBtn.left + 50, _objectBtn.top + 7, "object", strlen("object"));
	Rectangle(getMemDC(), _eraserBtn.left, _eraserBtn.top, _eraserBtn.right, _eraserBtn.bottom);
	TextOut(getMemDC(), _eraserBtn.left + 50, _eraserBtn.top + 7, "eraser", strlen("eraser"));
	//맵툴 모드, 게임 모드 변경버튼
	Rectangle(getMemDC(), _changeGameModeBtn.left, _changeGameModeBtn.top, _changeGameModeBtn.right, _changeGameModeBtn.bottom);
	TextOut(getMemDC(), _changeGameModeBtn.left + 50, _changeGameModeBtn.top + 7, "gameMode", strlen("gameMode"));
	Rectangle(getMemDC(), _changeMapEditModeBtn.left, _changeMapEditModeBtn.top, _changeMapEditModeBtn.right, _changeMapEditModeBtn.bottom);
	TextOut(getMemDC(), _changeMapEditModeBtn.left + 50, _changeMapEditModeBtn.top + 7, "mapEdit", strlen("mapEdit"));

	HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oBrush = (HBRUSH)SelectObject(getMemDC(), hBrush);
	HPEN hPen = (HPEN)CreatePen(PS_SOLID, 4, RGB(200, 100, 0));
	HPEN oPen = (HPEN)SelectObject(getMemDC(), hPen);

	if (_currentSelectMode == MODE_WORLDMAP_TERRAIN_SELECT)
	{
		int selectIndex = _selectedTerrainTile.getTerrainFramePos().x + _selectedTerrainTile.getTerrainFramePos().y * _worldMapTerrainTileSize.x;
		RECT selectTileRc = _worldMapTerrainTileSet[selectIndex].getTileRect();
		
		Rectangle(getMemDC(), selectTileRc.left + 2, selectTileRc.top + 2, selectTileRc.right - 2, selectTileRc.bottom - 2);
	}
	else if (_currentSelectMode == MODE_WORLDMAP_OBJECT_SELECT)
	{
		int selectIndex = _selectedObjectTile.getObjectFramePos().x + _selectedObjectTile.getObjectFramePos().y * _worldMapObjectTileSize.x;
		RECT selectTileRc = _worldMapObjectTileSet[selectIndex].getTileRect();

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

	file = CreateFile(ofn.lpstrFile, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

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

	file = CreateFile(ofn.lpstrFile, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, &_mapSize, sizeof(POINT), &read, NULL);
	_mapTiles = new tile[_mapSize.x * _mapSize.y];
	ReadFile(file, _mapTiles, sizeof(tile) * _mapSize.x * _mapSize.y, &read, NULL);

	CloseHandle(file);
}

BOOL CALLBACK newTileProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	int mapSizeX = 0;
	int mapSizeY = 0;

	auto pThis = (mapTool*)GetWindowLongPtr(hDlg, GWLP_USERDATA);

	switch (iMessage)
	{
	case WM_INITDIALOG:

		SetWindowPos(hDlg, HWND_TOP, 100, 100, 0,0,SWP_NOSIZE);
		SetWindowLongPtr(hDlg, GWLP_USERDATA, (LONG_PTR)lParam);
		pThis = (mapTool*)lParam;
		pThis->_hDlgNewTile = hDlg;
		break;

	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case IDOK:
			mapSizeX = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, FALSE);
			mapSizeY = GetDlgItemInt(hDlg, IDC_EDIT2, NULL, FALSE);
			pThis->createDefaultMap(PointMake(mapSizeX, mapSizeY));
		case IDCANCEL:

			EndDialog(pThis->_hDlgNewTile, 0);

			return TRUE;
		}

		return FALSE;
	case WM_CLOSE:
		PostQuitMessage(0);
		return TRUE;
	}
	return FALSE;

}


POINT operator+(POINT operand1, POINT operand2)
{
	return PointMake(operand1.x + operand2.x, operand1.y + operand2.y);
}

POINT operator-(POINT operand1, POINT operand2)
{
	return PointMake(operand1.x - operand2.x, operand1.y - operand2.y);
}