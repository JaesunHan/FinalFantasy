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

	return S_OK;
}

void worldMapScene::release()
{
}

void worldMapScene::update()
{
	_worldMap->update();
}

void worldMapScene::render()
{
	_worldMap->render();
}
