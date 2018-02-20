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
	CAMERAMANAGER->init(getMemDC());
	CAMERAMANAGER->createDC(PointMake(TILE_SIZEX, TILE_SIZEY), PointMake(30, 20));

	_townMap = new generalMap;
	_townMap->init(".//town30X30.map");

	_worldMapPlayer = new worldMapPlayer;
	_worldMapPlayer->init(200, 150);
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
	_townMap->update();
	_worldMapPlayer->update();
	_npcManager->update();


	//Z������
	//�÷��̾� ���� ��ǥ�� �޾Ƽ� ��� npc�Ŵ��������� �־��ش�.
	_npcManager->setPlayerPos(_worldMapPlayer->getWorldMapPlayerPoint());


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
