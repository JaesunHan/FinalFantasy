#pragma once
#include "gameNode.h"
class worldMap :public gameNode
{
public: 
	worldMap();
	~worldMap();

	HRESULT init();
	void release();
	void update();
	void render();
};

