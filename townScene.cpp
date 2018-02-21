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
		SCENEMANAGER->changeScene("����ʾ�",false);
		_worldMapPlayer->setWorldMapPlayerPoint(PointMake(_worldMapPlayer->getWorldMapPlayerPoint().x, _worldMapPlayer->getWorldMapPlayerPoint().y));
	}
	//�ε�ģ ������Ʈ�� Ÿ��� Ÿ�� �Ӽ��� ��������
	//"����ʾ�" ��ȯ
	_worldMapPlayer->setIsWorldMapeEnter(false);
}
