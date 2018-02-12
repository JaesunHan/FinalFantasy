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
	_worldMapPlayer->init(5,5);

	return S_OK;
}

void worldMapScene::release()
{
}

void worldMapScene::update()
{
	_worldMap->update();
	_worldMapPlayer->update();
}

void worldMapScene::render()
{
	_worldMap->render();
	_worldMapPlayer->render();
}
