#pragma once
#include "gameNode.h"
#include "worldMapPlayer.h"
#include "npcManager.h"
#include "generalMap.h"
#include "townMap.h"


class townScene : public gameNode
{
public:

	//월드맵 플레이어 등장용
	worldMapPlayer* _worldMapPlayer;

	//NPC등장용
	npcManager* _npcManager;

	//타운맵용
	generalMap* _townMap;


	townScene();
	~townScene();

	HRESULT init();
	void release();
	void update();
	void render();

	//월드맵으로 넘어가는 함수
	void enterWorldMap();

};

