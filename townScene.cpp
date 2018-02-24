#include "stdafx.h"
#include "townScene.h"
#include "worldMapScene.h"

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

	//npc가 플레이어 함수들 가져다 쓰기위함
	for (int i = 0; i < _npcManager->getVNpc().size(); ++i)
	{
		_npcManager->getVNpc()[i]->setPlayerMemoryAddressLink(_worldMapPlayer);
	}

	return S_OK;
}

void townScene::release()
{
}

void townScene::update()
{
	if (!SOUNDMANAGER->isPlaySound(CH_BGM))
	{
		SOUNDMANAGER->addSound("townMapBGM", ".//sound//worldMapSound//07. Edgar \& Mash", true, true);
		SOUNDMANAGER->play("townMapBGM", CH_BGM, 1.0f);
	}
	
	_worldMapPlayer->setIsSavePoint(true);
	_townMap->update();
	_worldMapPlayer->update();
	_npcManager->update();


	//Z오더용
	//플레이어 현재 좌표를 받아서 계속 npc매니저쪽으로 넣어준다.
	_npcManager->setPlayerPos(_worldMapPlayer->getWorldMapPlayerPoint());

	enterWorldMap();
	entershop();
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

void townScene::enterWorldMap()
{
	if(_worldMapPlayer->getIsWorldMapEnter())
	{
		//부딪친 오브젝트가 타운에서 월드맵 속성을 가졌으면
		SOUNDMANAGER->releaseAllSound();
		SCENEMANAGER->changeSceneType1("월드맵씬", false);
		((worldMapScene*)SCENEMANAGER->findScene("월드맵씬"))->setPlayerPos();
		_worldMapPlayer->setWorldMapPlayerPoint(PointMake(_worldMapPlayer->getWorldMapPlayerPoint().x, _worldMapPlayer->getWorldMapPlayerPoint().y));
		INIDATA->addData("gameData", "stage", "OVER WORLD");
		INIDATA->iniSave("skgFile");
	}
	//부딪친 오브젝트가 타운에서 타운 속성을 가졌으면
	//"월드맵씬" 전환
	_worldMapPlayer->setIsWorldMapeEnter(false);
}

void townScene::entershop()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		for (int i = 0; i < _npcManager->getVNpc().size(); ++i)
		{
			//만약 플레이어와 npc의 겟디스턴스 거리가 TILE_SIZEX 미만일때 /iscollision = true일때
			if (_npcManager->getVNpc()[i]->getNpcCollison())
			{
				_npcManager->getVNpc()[i]->setNpcCollision(false);
				if (_npcManager->getVNpc()[i]->getNpcType() == NPC_WEAPON)
				{
					((storeScene*)SCENEMANAGER->findScene("storeScene"))->setStoreKey("weaponStore");
					SCENEMANAGER->changeSceneType1("storeScene");	
				}
				else if (_npcManager->getVNpc()[i]->getNpcType() == NPC_POTION)
				{
					((storeScene*)SCENEMANAGER->findScene("storeScene"))->setStoreKey("itemShop");
					SCENEMANAGER->changeSceneType1("storeScene");
					//_npcManager->getVNpc()[i]->setNpcCollision(false);
				}
				else if (_npcManager->getVNpc()[i]->getNpcType() == NPC_DEFENCE)
				{
					((storeScene*)SCENEMANAGER->findScene("storeScene"))->setStoreKey("armorStore");
					SCENEMANAGER->changeSceneType1("storeScene");
					//_npcManager->getVNpc()[i]->setNpcCollision(false);
				}
			}
		}
	}
}
