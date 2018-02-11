#pragma once
#include "gameNode.h"


class worldMapScene
{
public:
	worldMapScene();
	~worldMapScene();


	HRESULT init();
	void release();
	void update();
	void render();
};

