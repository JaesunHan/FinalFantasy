#pragma once
#include "gameNode.h"
#include "worldMap.h"
#include "worldMapPlayer.h"

class worldMapScene : public gameNode
{
public:

	worldMap* _worldMap;
	worldMapPlayer* _worldMapPlayer;

	worldMapScene();
	~worldMapScene();


	HRESULT init();
	void release();
	void update();
	void render();
};

