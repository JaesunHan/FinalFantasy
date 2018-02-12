#pragma once
#include "gameNode.h"
#include "tile.h"
#include <vector>



class worldMap :public gameNode
{
public: 

	POINT _worldMap;					//¿ùµå¸Ê x,y
	tile* _worldMapTiles;				//¿ùµå¸Ê Å¸ÀÏ

	worldMap();
	~worldMap();

	HRESULT init();
	void release();
	void update();
	void render();

	//¸Ê ·Îµå¿ë ÇÔ¼ö
	void mapLoad(void);
};

