#pragma once
#include "gameNode.h"
#include "tile.h"
#include <vector>


class townMap : public gameNode
{
public:
	POINT _townMap;					//Å¸¿î¸Ê x,y
	tile* _townTiles;				//Å¸¿î¸Ê Å¸ÀÏ

	townMap();
	~townMap();
	
	HRESULT init();
	void release();
	void update();
	void render();

	//¸Ê ·Îµå¿ë ÇÔ¼ö
	void mapLoad(void);


	//===============°Ù¼Â ¸ðÀ½==================

	//¸ÊÅ©±â x,y°Ù ÇÔ¼ö
	POINT getTownMapPOINT() { return _townMap; }

	//·ÎµåµÈ ¿ùµå¸Ê Å¸ÀÏ °ÙÇÔ¼ö 
	tile* getTownMapTiles() { return _townTiles; }

};

