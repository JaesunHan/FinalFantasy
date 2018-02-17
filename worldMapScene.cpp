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
	_worldMapPlayer->init(200, 150);

	_npcManager = new npcManager;
	_npcManager->init();

	_wMEM = new worldMapEnemyManager;
	_wMEM->init();


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


}

void worldMapScene::render()
{
	_worldMap->render();

	_wMEM->render();
	//업데이트에서 받은 플레이어의 실시간 좌표를 NPC와 비교하여 
	//플레이어보다 먼저 그려주는 이미지 -> 플레이어 이미지 -> 플레이어보다 다음에 그려주는 이미지 순으로 랜더를 한다.
	_npcManager->beforeRender();
	_worldMapPlayer->render();
	_npcManager->afterRender();


}

//void worldMapScene::zOrderNpc1()
//{
//	Zorder
//	if (_npc1->getNpcPoint().y <= _worldMapPlayer->getWorldMapPlayerPoint().y)
//	{
//		_npc1->render();
//		_worldMapPlayer->render();
//	}
//	else if (_npc1->getNpcPoint().y > _worldMapPlayer->getWorldMapPlayerPoint().y)
//	{
//		_worldMapPlayer->render();
//		_npc1->render();
//	}
//	
//}
//
//void worldMapScene::zOrderNpc2()
//{
//	if (_npc2->getNpcPoint().y <= _worldMapPlayer->getWorldMapPlayerPoint().y)
//	{
//		_npc2->render();
//		_worldMapPlayer->render();
//	}
//	else if (_npc2->getNpcPoint().y > _worldMapPlayer->getWorldMapPlayerPoint().y)
//	{
//		_worldMapPlayer->render();
//		_npc2->render();
//	}
//	
//}
//
//void worldMapScene::zOrderNpc3()
//{
//	if (_npc3->getNpcPoint().y <= _worldMapPlayer->getWorldMapPlayerPoint().y)
//	{
//		_npc3->render();
//		_worldMapPlayer->render();
//	}
//	else if (_npc3->getNpcPoint().y > _worldMapPlayer->getWorldMapPlayerPoint().y)
//	{
//		_worldMapPlayer->render();
//		_npc3->render();
//	}
//	
//}
//
//void worldMapScene::zOrderNpc4()
//{
//	if (_npc4->getNpcPoint().y <= _worldMapPlayer->getWorldMapPlayerPoint().y)
//	{
//		_npc4->render();
//		_worldMapPlayer->render();
//	}
//	else if (_npc4->getNpcPoint().y > _worldMapPlayer->getWorldMapPlayerPoint().y)
//	{
//		_worldMapPlayer->render();
//		_npc4->render();
//	}
//
//}
//
//void worldMapScene::zOrderNpc5()
//{
//	if (_npc5->getNpcPoint().y <= _worldMapPlayer->getWorldMapPlayerPoint().y)
//	{
//		_npc5->render();
//		_worldMapPlayer->render();
//	}
//	else if (_npc5->getNpcPoint().y > _worldMapPlayer->getWorldMapPlayerPoint().y)
//	{
//		_worldMapPlayer->render();
//		_npc5->render();
//	}
//}
