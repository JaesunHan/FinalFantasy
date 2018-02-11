#pragma once
#include "gameNode.h"
class townMap : public gameNode
{
public:
	townMap();
	~townMap();
	
	HRESULT init();
	void release();
	void update();
	void render();
};

