#pragma once
#include "gameNode.h"
#include "worldMap.h"

class worldMapScene : public gameNode
{
public:

	worldMap* _worldMap;

	worldMapScene();
	~worldMapScene();


	HRESULT init();
	void release();
	void update();
	void render();
};

