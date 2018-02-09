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

void tile::render(void)
{
	if (_terrain != TR_NONE) terrainRender();
	if (_object != OBJ_NONE) objectRender();
}

void tile::terrainRender(void)
{
	if (_terrainImageKey != "none")
	{
		IMAGEMANAGER->frameRender(_terrainImageKey, getMemDC(), _tileRc.left, _tileRc.top, _terrainFramePos.x, _terrainFramePos.y);
	}
}

void tile::objectRender(void)
{
	if (_objectImageKey != "none")
	{
		IMAGEMANAGER->frameRender(_objectImageKey, getMemDC(), _tileRc.left, _tileRc.top, _objectFramePos.x, _objectFramePos.y);
	}
}

void tile::selectTerrain(tile sour)
{
	_terrain = sour.getTerrain();
	_terrainImageKey = sour.getTerrainImageKey();
	_terrainFramePos = sour.getIndex();
}

void tile::selectObject(tile sour)
{
	_object = sour.getObject();
	_objectImageKey = sour.getObjectImageKey();
	_objectFramePos = sour.getIndex();
}

void tile::setTerrain(tile sour)
{
	_terrain = sour.getTerrain();
	_terrainImageKey = sour.getTerrainImageKey();
	_terrainFramePos = sour.getTerrainFramePos();
}

void tile::setObject(tile sour)
{
	_object = sour.getObject();
	_objectImageKey = sour.getObjectImageKey();
	_objectFramePos = sour.getObjectFramePos();
}

void tile::eraseObject(void)
{
	_object = OBJ_NONE;
	_objectImageKey = "";
	_objectFramePos = PointMake(0, 0);
}
