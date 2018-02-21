#include "stdafx.h"
#include "townScene.h"


townScene::townScene()
{
}


townScene::~townScene()
{
}

HRESULT townScene::init()
{
	SOUNDMANAGER->addSound("townMapBGM", ".//sound//worldMapSound//07. Edgar \& Mash.mp3", true, true);
	SOUNDMANAGER->play("townMapBGM", CH_BGM, 1.0f);

	CAMERAMANAGER->init(getMemDC());
	CAMERAMANAGER->createDC(PointMake(TILE_SIZEX, TILE_SIZEY), PointMake(30, 20));

	_townMap = new generalMap;
	_townMap->init(".//town30X30.map");

	_worldMapPlayer = new worldMapPlayer;
	_worldMapPlayer->init(562, 50);
	_worldMapPlayer->setCurMapAddressLink(_townMap);

	_npcManager = new npcManager;
	_npcManager->init();

	return S_OK;
}

void townScene::release()
{
}

void townScene::update()
{
	if (SOUNDMANAGER->isPlaySound("townMapBGM"))
	{
		SOUNDMANAGER->addSound("townMapBGM", ".//sound//worldMapSound//07. Edgar \& Mash", true, true);
		SOUNDMANAGER->play("townMapBGM", CH_BGM, 1.0f);
	}
	
	_townMap->update();
	_worldMapPlayer->update();
	_npcManager->update();


	//Z오더용
	//플레이어 현재 좌표를 받아서 계속 npc매니저쪽으로 넣어준다.
	_npcManager->setPlayerPos(_worldMapPlayer->getWorldMapPlayerPoint());


}

void townScene::render()
{

	_townMap->render(CAMERAMANAGER->getCameraDC());
	
	//업데이트에서 받은 플레이어의 실시간 좌표를 NPC와 비교하여 
	//플레이어보다 먼저 그려주는 이미지 -> 플레이어 이미지 -> 플레이어보다 다음에 그려주는 이미지 순으로 랜더를 한다.
	_npcManager->beforeRender(CAMERAMANAGER->getCameraDC(), CAMERAMANAGER->getMovePt());
	_worldMapPlayer->render(CAMERAMANAGER->getCameraDC(), CAMERAMANAGER->getMovePt());
	_npcManager->afterRender(CAMERAMANAGER->getCameraDC(), CAMERAMANAGER->getMovePt());

	_townMap->afterRenderObject(CAMERAMANAGER->getCameraDC());

	CAMERAMANAGER->render(getMemDC());
}
