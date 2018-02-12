#pragma once
#include "gameNode.h"

class worldMapPlayer : public gameNode
{
public:
	worldMapPlayer();
	~worldMapPlayer();

	HRESULT init();
	void release();
	void update();
	void render();

};

