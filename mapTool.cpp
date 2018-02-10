#include "stdafx.h"
#include "mapTool.h"

//BOOL CALLBACK MainDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);

mapTool::mapTool()
{
}


mapTool::~mapTool()
{
}

HRESULT mapTool::init(void)
{
	//��ư �ʱ�ȭ
	_newBtn = RectMake(850, 480, 100, 30);
	_saveBtn = RectMake(850, 520, 100, 30);
	_loadBtn = RectMake(960, 520, 100, 30);
	_terrainBtn = RectMake(850, 560, 100, 30);
	_objectBtn = RectMake(960, 560, 100, 30);
	_eraserBtn = RectMake(1070, 560, 100, 30);
	_changeGameModeBtn = RectMake(850, 600, 100, 30);
	_changeMapEditModeBtn = RectMake(960, 600, 100, 30);

	//Ÿ�ϼ� �ʱ�ȭ
	worldMapTerrainTileSetInit();
	worldMapObjectTileSetInie();
	
	//�� �ʱ�ȭ
	_worldMapTiles = NULL;
	_mapSize = PointMake(0, 0);

	_currentSelectMode = MODE_WORLDMAP_TERRAIN_SELECT;

	_selectedTerrainTile.init(PointMake(0, 0));
	_selectedObjectTile.init(PointMake(0, 0));

	_selectedTerrainTile.selectTerrain(_worldMapTerrainTileSet[0]);

	//DialogBox(_hInstance, MAKEINTRESOURCE(IDD_DIALOG1), HWND_DESKTOP, MainDlgProc);
	

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
}

void mapTool::render(void)
{
	if (_worldMapTiles != NULL)
	{
		for (int i = 0; i < _mapSize.x * _mapSize.y; i++)
		{
			_worldMapTiles[i].render();
		}
	}

	if (_currentSelectMode == MODE_WORLDMAP_TERRAIN_SELECT)
	{
		for (int i = 0; i < _worldMapTerrainTileSize.x * _worldMapTerrainTileSize.y; i++)
		{
			_worldMapTerrainTileSet[i].render();
		}
	}
	if (_currentSelectMode == MODE_WORLDMAP_OBJECT_SELECT)
	{
		for (int i = 0; i < _worldMapObjectTileSize.x * _worldMapObjectTileSize.y; i++)
		{
			_worldMapObjectTileSet[i].render();
		}
	}

	buttonDraw();
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
		_worldMapTerrainTileSet[i].setTerrain(TR_GRASS);
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
		_worldMapObjectTileSet[i].setObject(OBJ_MOUNTAIN);
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
			if (PtInRect(&_worldMapTiles[i].getTileRect(), _ptMouse))
			{
				_worldMapTiles[i].setTerrain(_selectedTerrainTile);
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
			if (PtInRect(&_worldMapTiles[i].getTileRect(), _ptMouse))
			{
				_worldMapTiles[i].setObject(_selectedObjectTile);
				break;
			}
		}
	}
	else if (_currentSelectMode == MODE_ERASER)
	{
		for (int i = 0; i < _mapSize.x * _mapSize.y; i++)
		{
			if (PtInRect(&_worldMapTiles[i].getTileRect(), _ptMouse))
			{
				_worldMapTiles[i].eraseObject();
				break;
			}
		}
	}
}

void mapTool::buttonDraw(void)
{
	//Ÿ�� ������ ���� ��ư
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
	//���� ���, ���� ��� �����ư
	Rectangle(getMemDC(), _changeGameModeBtn.left, _changeGameModeBtn.top, _changeGameModeBtn.right, _changeGameModeBtn.bottom);
	TextOut(getMemDC(), _changeGameModeBtn.left + 50, _changeGameModeBtn.top + 7, "gameMode", strlen("gameMode"));
	Rectangle(getMemDC(), _changeMapEditModeBtn.left, _changeMapEditModeBtn.top, _changeMapEditModeBtn.right, _changeMapEditModeBtn.bottom);
	TextOut(getMemDC(), _changeMapEditModeBtn.left + 50, _changeMapEditModeBtn.top + 7, "mapEdit", strlen("mapEdit"));
}

void mapTool::createDefaultMap(POINT mapSize)
{
	_mapSize = mapSize;

	_worldMapTiles = new tile[_mapSize.x * _mapSize.y];

	for (int i = 0; i < _mapSize.x * _mapSize.y; i++)
	{
		_worldMapTiles[i].init(PointMake(TILE_SIZEX / 2 + TILE_SIZEX * (i % _mapSize.x), TILE_SIZEY / 2 + TILE_SIZEY * (i / _mapSize.x)));
		_worldMapTiles[i].setTerrainImageKey("worldTerrain");
		_worldMapTiles[i].setTerrainFramePos(PointMake(1, 1));
		_worldMapTiles[i].setTerrain(TR_GRASS);
		//�� Ÿ�� �ʱ�ȭ �κ�
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
	WriteFile(file, _worldMapTiles, sizeof(tile) * _mapSize.x * _mapSize.y, &write, NULL);

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

	//����ó��
	if (GetOpenFileName(&ofn) == FALSE) return;

	//this->init();

	file = CreateFile(ofn.lpstrFile, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, &_mapSize, sizeof(POINT), &read, NULL);
	ReadFile(file, _worldMapTiles, sizeof(tile) * _mapSize.x * _mapSize.y, &read, NULL);

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
