#pragma once
#include "gameNode.h"
#include "worldMapPlayer.h"
#include "npcManager.h"
#include "townMap.h"


class townScene : public gameNode
{
public:

	//월드맵 플레이어 등장용
	worldMapPlayer* _worldMapPlayer;

	//NPC등장용
	npcManager* _npcManager;

	//타운맵용
	townMap * _townMap;


	townScene();
	~townScene();

	HRESULT init();
	void release();
	void update();
	void render();

};

