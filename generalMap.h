#pragma once
#include "gameNode.h"
#include "tile.h"

class generalMap : public gameNode
{
protected:
	POINT _mapTileNum;					//¿ùµå¸Ê x,y
	tile* _mapTile;				//¿ùµå¸Ê Å¸ÀÏ

public:
	generalMap();
	~generalMap();

	HRESULT init(string mapFilePath);
	void release();
	void update();
	void render(HDC hdc);
	void afterRenderObject(HDC hdc);

	//¸Ê ·Îµå¿ë ÇÔ¼ö
	void mapLoad(string mapFilePath);

	//===============°Ù¼Â ¸ðÀ½==================

	//¸ÊÅ©±â x,y°Ù ÇÔ¼ö
	POINT getMapTileNum() { return _mapTileNum; }

	//·ÎµåµÈ ¿ùµå¸Ê Å¸ÀÏ °ÙÇÔ¼ö 
	tile* getMapTile() { return _mapTile; }
};

