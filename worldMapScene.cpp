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


	//Z������
	//�÷��̾� ���� ��ǥ�� �޾Ƽ� ��� npc�Ŵ��������� �־��ش�.
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
	//������Ʈ���� ���� �÷��̾��� �ǽð� ��ǥ�� NPC�� ���Ͽ� 
	//�÷��̾�� ���� �׷��ִ� �̹��� -> �÷��̾� �̹��� -> �÷��̾�� ������ �׷��ִ� �̹��� ������ ������ �Ѵ�.
	_npcManager->beforeRender(CAMERAMANAGER->getCameraDC(), CAMERAMANAGER->getMovePt());
	_worldMapPlayer->render(CAMERAMANAGER->getCameraDC(), CAMERAMANAGER->getMovePt());
	_npcManager->afterRender(CAMERAMANAGER->getCameraDC(), CAMERAMANAGER->getMovePt());

	CAMERAMANAGER->render(getMemDC());

	
	//_worldMap->render(getMemDC());
	//
	//_wMEM->render(getMemDC());
	////������Ʈ���� ���� �÷��̾��� �ǽð� ��ǥ�� NPC�� ���Ͽ� 
	////�÷��̾�� ���� �׷��ִ� �̹��� -> �÷��̾� �̹��� -> �÷��̾�� ������ �׷��ִ� �̹��� ������ ������ �Ѵ�.
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
			//�浹�� �༮�� �ε����� ������ �����Ѵ�.
			_enemyNum = i;
			SCENEMANAGER->changeScene("��Ʋ��");
			break;
		}
	}

}

void worldMapScene::successEscape()
{
	_worldMapPlayer->successEscape();
	_isEscape = false;
}
