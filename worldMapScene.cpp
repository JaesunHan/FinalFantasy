#include "stdafx.h"
#include "worldMapScene.h"


worldMapScene::worldMapScene()
{
}


worldMapScene::~worldMapScene()
{
}

HRESULT worldMapScene::init()
{
	_worldMap = new worldMap;
	_worldMap->init();

	_worldMapPlayer = new worldMapPlayer;
	_worldMapPlayer->init(200,150);

	_npc1 = new npc1;
	_npc1->init(30, 60);

	_npc2 = new npc2;
	_npc2->init(100, 80);

	_npc3 = new npc3;
	_npc3->init(300, 120);

	_npc4 = new npc4;
	_npc4->init(120, 500);

	_npc5 = new npc5;
	_npc5->init(500, 300);

	return S_OK;
}

void worldMapScene::release()
{
}

void worldMapScene::update()
{
	_worldMap->update();
	_worldMapPlayer->update();
	_npc1->update();
	_npc2->update();
	_npc3->update();
	_npc4->update();
	_npc5->update();
}

void worldMapScene::render()
{
	_worldMap->render();
	_npc1->render();
	_npc2->render();
	_npc3->render();
	_npc4->render();
	_npc5->render();
	_worldMapPlayer->render();
	
}
