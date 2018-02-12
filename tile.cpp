#include "stdafx.h"
#include "tile.h"


tile::tile()
{
}


tile::~tile()
{
}

HRESULT tile::init(POINT center)
{
	_centerPt = center;
	_index = PointMake(_centerPt.x / TILE_SIZEX, _centerPt.y / TILE_SIZEY);

	_tileRc = RectMakeCenter(_centerPt.x, _centerPt.y, TILE_SIZEX, TILE_SIZEY);
	_isChecked = FALSE;
	
	_terrainAttribute = ATTR_MOVE;
	_objectAttribute = ATTR_MOVE;
	_terrain = TR_NONE;
	_object = OBJ_NONE;

	_terrainImageKey = "none";
	_objectImageKey = "none";

	_terrainFramePos = PointMake(0, 0);
	_objectFramePos = PointMake(0, 0);


	return S_OK;
}

void tile::release(void)
{

}

void tile::update(void)
{

}

void tile::render(HDC hdc, int destX, int destY)
{
	if (_terrain != TR_NONE) terrainRender(hdc, destX, destY);
	if (_object != OBJ_NONE) objectRender(hdc, destX, destY);

	if (_isDebug) attributeRender(hdc, destX, destY);
}

void tile::terrainRender(HDC hdc, int destX, int destY)
{
	if (_terrainImageKey != "none")
	{
		IMAGEMANAGER->frameRender(_terrainImageKey, hdc, _tileRc.left - destX, _tileRc.top - destY, _terrainFramePos.x, _terrainFramePos.y);
	}
}

void tile::objectRender(HDC hdc, int destX, int destY)
{
	if (_objectImageKey != "none")
	{
		IMAGEMANAGER->frameRender(_objectImageKey, hdc, _tileRc.left - destX, _tileRc.top - destY, _objectFramePos.x, _objectFramePos.y);
	}
}

//디버그 모드시 타일의 대략적인 정보를 그려줌
void tile::attributeRender(HDC hdc, int destX, int destY)
{
	HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oBrush = (HBRUSH)SelectObject(hdc, hBrush);
	HPEN hPen;
	HPEN oPen;

	if (_terrainAttribute == ATTR_UNMOVE || _objectAttribute == ATTR_UNMOVE)
	{
		hPen = (HPEN)CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		oPen = (HPEN)SelectObject(hdc, hPen);
		MoveToEx(hdc, _tileRc.left - destX, _tileRc.top - destY, NULL);
		LineTo(hdc, _tileRc.right - destX, _tileRc.bottom - destY);
		MoveToEx(hdc, _tileRc.right - destX, _tileRc.top - destY, NULL);
		LineTo(hdc, _tileRc.left - destX, _tileRc.bottom - destY);
	}

	Rectangle(hdc, _tileRc.left - destX, _tileRc.top - destY, _tileRc.right - destX, _tileRc.bottom - destY);

	if (_terrainAttribute == ATTR_UNMOVE || _objectAttribute == ATTR_UNMOVE)
	{
		SelectObject(hdc, oPen);
		DeleteObject(hPen);
		DeleteObject(oPen);
	}
	SelectObject(hdc, oBrush);
	DeleteObject(hBrush);
	DeleteObject(oBrush);
}

//지형 타일셋에서 타일을 선택
void tile::selectTerrain(tile sour)
{
	string imageKey = sour.getTerrainImageKey();

	_terrainAttribute = sour.getTerrainAttr();
	_terrain = sour.getTerrain();
	_terrainImageKey = imageKey;
	_terrainFramePos = sour.getIndex();
}

//오브젝트 타일셋에서 타일을 선택
void tile::selectObject(tile sour)
{
	string imageKey = sour.getObjectImageKey();

	_objectAttribute = sour.getObjectAttr();
	_object = sour.getObject();
	_objectImageKey = imageKey;
	_objectFramePos = sour.getIndex();
}

//선택된 지형타일을 선택한 맵 타일에 적용
void tile::setTerrain(tile sour)
{
	string imageKey = sour.getTerrainImageKey();

	_terrainAttribute = sour.getTerrainAttr();
	_terrain = sour.getTerrain();
	_terrainImageKey = imageKey;
	_terrainFramePos = sour.getTerrainFramePos();
}

//선택된 오브젝트타일을 선택한 맵 타일에 적용
void tile::setObject(tile sour)
{
	string imageKey = sour.getObjectImageKey();

	_objectAttribute = sour.getObjectAttr();
	_object = sour.getObject();
	_objectImageKey = imageKey;
	_objectFramePos = sour.getObjectFramePos();
}

//선택한 맵 타일의 오브젝트 삭제
void tile::eraseObject(void)
{
	_object = OBJ_NONE;
	_objectImageKey = "";
	_objectFramePos = PointMake(0, 0);
	_objectAttribute = ATTR_MOVE;
}

//지형의 종류에 따라 타일 속성 적용
void tile::updateTerrainAttr(void)
{
	if (_terrain == TR_GRASS) _terrainAttribute = ATTR_MOVE;
	else if (_terrain == TR_WATER) _terrainAttribute = ATTR_UNMOVE;
	else if (_terrain == TR_DESERT) _terrainAttribute = ATTR_SLOW;
}

//오브젝트의 종류에 따라 타일 속성 적용
void tile::updateObjectAttr(void)
{
	if (_object == OBJ_CAVE || _object == OBJ_CASTLE || _object == OBJ_TOWN) _objectAttribute = ATTR_MOVE;
	else if (_object == OBJ_MOUNTAIN) _objectAttribute = ATTR_UNMOVE;
}
