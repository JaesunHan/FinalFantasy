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
	CAMERAMANAGER->init(getMemDC());
	CAMERAMANAGER->createDC(PointMake(TILE_SIZEX, TILE_SIZEY), PointMake(30, 20));

	_worldMap = new worldMap;
	_worldMap->init();

	_worldMapPlayer = new worldMapPlayer;
	_worldMapPlayer->init(200, 150);

	_npcManager = new npcManager;
	_npcManager->init();

	_wMEM = new worldMapEnemyManager;
	_wMEM->init();

	_isEscape = false;
	_isCollision = false;

	_enemyNum = -1;

	for (int i = 0; i < WORLDMAPENEMY; ++i)
	{
		_wMEM->getVWME()[i]->setEnemyAddressLinkWithWM(_worldMap);
		_wMEM->getVWME()[i]->setEnemyAddressLinkWihtPlayer(_worldMapPlayer);
	}

	return S_OK;
}

void worldMapScene::release()
{
}

void worldMapScene::update()
{
	_worldMap->update();
	_worldMapPlayer->update();
	_npcManager->update();
	_wMEM->update();


	//Z오더용
	//플레이어 현재 좌표를 받아서 계속 npc매니저쪽으로 넣어준다.
	_npcManager->setPlayerPos(_worldMapPlayer->getWorldMapPlayerPoint());

	getCollision();
	if (_isEscape) successEscape();
	else
	{
		for (int i = 0; i < _wMEM->getVWME().size(); ++i)
		{
			if (i == _enemyNum)
			{
				_wMEM->worldEmenyDelete(i);
				_enemyNum = -1;
			}
		}
	}
}

void worldMapScene::render()
{
	_worldMap->render(CAMERAMANAGER->getCameraDC());
	
	_wMEM->render(CAMERAMANAGER->getCameraDC(), CAMERAMANAGER->getMovePt());
	//업데이트에서 받은 플레이어의 실시간 좌표를 NPC와 비교하여 
	//플레이어보다 먼저 그려주는 이미지 -> 플레이어 이미지 -> 플레이어보다 다음에 그려주는 이미지 순으로 랜더를 한다.
	_npcManager->beforeRender(CAMERAMANAGER->getCameraDC(), CAMERAMANAGER->getMovePt());
	_worldMapPlayer->render(CAMERAMANAGER->getCameraDC(), CAMERAMANAGER->getMovePt());
	_npcManager->afterRender(CAMERAMANAGER->getCameraDC(), CAMERAMANAGER->getMovePt());

	CAMERAMANAGER->render(getMemDC());

	
	//_worldMap->render(getMemDC());
	//
	//_wMEM->render(getMemDC());
	////업데이트에서 받은 플레이어의 실시간 좌표를 NPC와 비교하여 
	////플레이어보다 먼저 그려주는 이미지 -> 플레이어 이미지 -> 플레이어보다 다음에 그려주는 이미지 순으로 랜더를 한다.
	//_npcManager->beforeRender(getMemDC());
	//_worldMapPlayer->render(getMemDC());
	//_npcManager->afterRender(getMemDC());
}

void worldMapScene::getCollision()
{
	for (int i = 0; i < _wMEM->getVWME().size(); ++i)
	{
		if (_wMEM->getVWME()[i]->getIsCollision())
		{
			//충돌한 녀석의 인덱스를 변수에 저장한다.
			_enemyNum = i;
			SCENEMANAGER->changeScene("배틀씬");
			break;
		}
	}

}

void worldMapScene::successEscape()
{
	_worldMapPlayer->successEscape();
	_isEscape = false;
}
