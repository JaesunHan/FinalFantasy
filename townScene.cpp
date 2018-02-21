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

	//npc�� �÷��̾� �Լ��� ������ ��������
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
	if (!SOUNDMANAGER->isPlaySound("townMapBGM"))
	{
		SOUNDMANAGER->addSound("townMapBGM", ".//sound//worldMapSound//07. Edgar \& Mash", true, true);
		SOUNDMANAGER->play("townMapBGM", CH_BGM, 1.0f);
	}
	
	_townMap->update();
	_worldMapPlayer->update();
	_npcManager->update();


	//Z������
	//�÷��̾� ���� ��ǥ�� �޾Ƽ� ��� npc�Ŵ��������� �־��ش�.
	_npcManager->setPlayerPos(_worldMapPlayer->getWorldMapPlayerPoint());

	enterWorldMap();
	entershop();
}

void townScene::render()
{

	_townMap->render(CAMERAMANAGER->getCameraDC());
	
	//������Ʈ���� ���� �÷��̾��� �ǽð� ��ǥ�� NPC�� ���Ͽ� 
	//�÷��̾�� ���� �׷��ִ� �̹��� -> �÷��̾� �̹��� -> �÷��̾�� ������ �׷��ִ� �̹��� ������ ������ �Ѵ�.
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
		//�ε�ģ ������Ʈ�� Ÿ��� ����� �Ӽ��� ��������
		SCENEMANAGER->changeSceneType1("����ʾ�", false);
		((worldMapScene*)SCENEMANAGER->findScene("����ʾ�"))->setPlayerPos();
		_worldMapPlayer->setWorldMapPlayerPoint(PointMake(_worldMapPlayer->getWorldMapPlayerPoint().x, _worldMapPlayer->getWorldMapPlayerPoint().y));
	}
	//�ε�ģ ������Ʈ�� Ÿ��� Ÿ�� �Ӽ��� ��������
	//"����ʾ�" ��ȯ
	_worldMapPlayer->setIsWorldMapeEnter(false);
}

void townScene::entershop()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		for (int i = 0; i < _npcManager->getVNpc().size(); ++i)
		{
			//���� �÷��̾�� npc�� �ٵ��Ͻ� �Ÿ��� TILE_SIZEX �̸��϶� /iscollision = true�϶�
			if (_npcManager->getVNpc()[i]->getNpcCollison())
			{
				if (_npcManager->getVNpc()[i]->getNpcType() == NPC_WEAPON)
				{
					((storeScene*)SCENEMANAGER->findScene("storeScene"))->setStoreKey("weaponStore");
					SCENEMANAGER->changeSceneType0("storeScene");
				}
				else if (_npcManager->getVNpc()[i]->getNpcType() == NPC_POTION)
				{
					((storeScene*)SCENEMANAGER->findScene("storeScene"))->setStoreKey("itemShop");
					SCENEMANAGER->changeSceneType0("storeScene");
				}
				else if (_npcManager->getVNpc()[i]->getNpcType() == NPC_DEFENCE)
				{
					((storeScene*)SCENEMANAGER->findScene("storeScene"))->setStoreKey("armorStore");
					SCENEMANAGER->changeSceneType0("storeScene");
				}
			}
		}
	}
}
