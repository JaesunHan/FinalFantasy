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

	//_tileRc = RectMakeCenter(_centerPt.x, _centerPt.y, TILE_SIZEX, TILE_SIZEY);
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
		IMAGEMANAGER->frameRender(_terrainImageKey, hdc, _centerPt.x - TILE_SIZEX / 2 - destX, _centerPt.y - TILE_SIZEY / 2 - destY, _terrainFramePos.x, _terrainFramePos.y);
	}
}

void tile::objectRender(HDC hdc, int destX, int destY)
{
	if (_objectImageKey != "none")
	{
		if (_objectAttribute != ATTR_AFTER_RENDER)
		{
			IMAGEMANAGER->frameRender(_objectImageKey, hdc, _centerPt.x - TILE_SIZEX / 2 - destX, _centerPt.y - TILE_SIZEY / 2 - destY, _objectFramePos.x, _objectFramePos.y);
		}
	}
}

void tile::afterObjectRender(HDC hdc, int destX, int destY)
{
	if (_objectImageKey != "none")
	{
		if (_objectAttribute == ATTR_AFTER_RENDER)
		{
			IMAGEMANAGER->frameRender(_objectImageKey, hdc, _centerPt.x - TILE_SIZEX / 2 - destX, _centerPt.y - TILE_SIZEY / 2 - destY, _objectFramePos.x, _objectFramePos.y);
		}
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
		MoveToEx(hdc, _centerPt.x - TILE_SIZEX / 2 - destX, _centerPt.y - TILE_SIZEY / 2 - destY, NULL);
		LineTo(hdc, _centerPt.x + TILE_SIZEX / 2 - destX, _centerPt.y + TILE_SIZEY / 2 - destY);
		MoveToEx(hdc, _centerPt.x + TILE_SIZEX / 2 - destX, _centerPt.y - TILE_SIZEY / 2 - destY, NULL);
		LineTo(hdc, _centerPt.x - TILE_SIZEX / 2 - destX, _centerPt.y + TILE_SIZEY / 2 - destY);
	}
	else if (_objectAttribute == ATTR_AFTER_RENDER)
	{
		hPen = (HPEN)CreatePen(PS_SOLID, 2, RGB(50, 255, 50));
		oPen = (HPEN)SelectObject(hdc, hPen);

		Ellipse(hdc, _centerPt.x - TILE_SIZEX / 2 - destX, _centerPt.y - TILE_SIZEY / 2 - destY,
			_centerPt.x + TILE_SIZEX / 2 - destX, _centerPt.y + TILE_SIZEY / 2 - destY);
	}

	Rectangle(hdc, _centerPt.x - TILE_SIZEX / 2 - destX, _centerPt.y - TILE_SIZEY / 2 - destY, _centerPt.x + TILE_SIZEX / 2 - destX, _centerPt.y + TILE_SIZEY / 2 - destY);

	if (_terrainAttribute == ATTR_UNMOVE || _objectAttribute == ATTR_UNMOVE || _objectAttribute == ATTR_AFTER_RENDER)
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
	if (_terrain == TR_GRASS || _terrain == TR_DIRT) _terrainAttribute = ATTR_MOVE;
	else if (_terrain == TR_WATER || _terrain == TR_STUMP || _terrain == TR_WALL) _terrainAttribute = ATTR_UNMOVE;
	else if (_terrain == TR_DESERT) _terrainAttribute = ATTR_SLOW;
	else if (_terrain == TR_ROAD) _terrainAttribute = ATTR_FAST;
}

//오브젝트의 종류에 따라 타일 속성 적용
void tile::updateObjectAttr(void)
{
	if (_object == OBJ_NONE || _object == OBJ_CAVE || _object == OBJ_CASTLE || _object == OBJ_TOWN
		|| _object == OBJ_HOUSE_BOT_PASS || _object == OBJ_PLANT || _object == OBJ_BRIDGE_TOP) _objectAttribute = ATTR_MOVE;
	else if (_object == OBJ_MOUNTAIN || _object == OBJ_HOUSE_BOTTOM || _object == OBJ_SIGNBOARD || _object == OBJ_TOMBSTONE
		|| _object == OBJ_WELL_BOTTOM || _object == OBJ_BRIDGE_BOTTOM || _object == OBJ_TREE_BOTTOM) _objectAttribute = ATTR_UNMOVE;
	else if (_object == OBJ_HOUSE_TOP || _object == OBJ_WELL_TOP || _object == OBJ_TREE_TOP) _objectAttribute = ATTR_AFTER_RENDER;
}
