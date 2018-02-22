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
	//==============�������� ������ Ÿ���� �Դ´�!============
	_gameStartTime = TIMEMANAGER->getWorldTime();
	//==============�������� ������ Ÿ���� �Դ´�!============

	SOUNDMANAGER->addSound("worldMapBGM", ".//sound//worldMapSound//01. Tina.mp3", true, true);
	SOUNDMANAGER->addSound("encounterSound", ".//sound//worldMapSound//encounter.wav", false, false);
	SOUNDMANAGER->play("worldMapBGM", CH_BGM, 1.0f);
	CAMERAMANAGER->init(getMemDC());
	CAMERAMANAGER->createDC(PointMake(TILE_SIZEX, TILE_SIZEY), PointMake(30, 20));

	_worldMap = new generalMap;
	_worldMap->init(".//50X50.map");

	_worldMapPlayer = new worldMapPlayer;
	_worldMapPlayer->init(200, 150);
	_worldMapPlayer->setCurMapAddressLink(_worldMap);

	//_npcManager = new npcManager;
	//_npcManager->init();

	_wMEM = new worldMapEnemyManager;
	_wMEM->init();

	_isEscape = false;
	_isCollision = false;
	_isEncounter = false;

	_enemyNum = -1;

	for (int i = 0; i < _wMEM->getVWME().size(); ++i)
	{
		_wMEM->getVWME()[i]->setEnemyAddressLinkWithWM(_worldMap);
		_wMEM->getVWME()[i]->setEnemyAddressLinkWihtPlayer(_worldMapPlayer);
	}

	return S_OK;
}

void worldMapScene::release()
{
	SAFE_DELETE(_worldMap);
	SAFE_DELETE(_worldMapPlayer);

	SOUNDMANAGER->releaseAllSound();
}

void worldMapScene::update()
{
	if (!SOUNDMANAGER->isPlaySound(CH_BGM))
	{
		SOUNDMANAGER->addSound("worldMapBGM", ".//sound//worldMapSound//01. Tina.mp3", true, true);
		SOUNDMANAGER->addSound("encounterSound", ".//sound//worldMapSound//encounter.wav", false, false);
		SOUNDMANAGER->play("worldMapBGM", CH_BGM, 1.0f);
	}

	_worldMap->update();
	_worldMapPlayer->update();
	//_npcManager->update();
	_wMEM->update();


	//Z������
	//�÷��̾� ���� ��ǥ�� �޾Ƽ� ��� npc�Ŵ��������� �־��ش�.
	//_npcManager->setPlayerPos(_worldMapPlayer->getWorldMapPlayerPoint());

	
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

	enterTownMap();
	getCollision();
	
}

void worldMapScene::render()
{
	_worldMap->render(CAMERAMANAGER->getCameraDC());
	
	_wMEM->render(CAMERAMANAGER->getCameraDC(), CAMERAMANAGER->getMovePt());
	//������Ʈ���� ���� �÷��̾��� �ǽð� ��ǥ�� NPC�� ���Ͽ� 
	//�÷��̾�� ���� �׷��ִ� �̹��� -> �÷��̾� �̹��� -> �÷��̾�� ������ �׷��ִ� �̹��� ������ ������ �Ѵ�.
	//_npcManager->beforeRender(CAMERAMANAGER->getCameraDC(), CAMERAMANAGER->getMovePt());
	_worldMapPlayer->render(CAMERAMANAGER->getCameraDC(), CAMERAMANAGER->getMovePt());
	//_npcManager->afterRender(CAMERAMANAGER->getCameraDC(), CAMERAMANAGER->getMovePt());

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
			//SOUNDMANAGER->stop(CH_BGM);
			if (!_isEncounter)
			{
				_isEncounter = true;
				SOUNDMANAGER->play("encounterSound", CH_ENCOUNTER, 1.0f);
			}
			SCENEMANAGER->changeSceneType1("��Ʋ��");
			break;
		}
	}

}

void worldMapScene::successEscape()
{
	_wMEM->getVWME()[_enemyNum]->setIsCollision(false);
	_worldMapPlayer->successEscape();
	_enemyNum = -1;
	_isEscape = false;
}

void worldMapScene::enterTownMap()
{
	if(_worldMapPlayer->getIsEnter())
	{
		SCENEMANAGER->changeSceneType1("Ÿ��ʾ�");
		//SOUNDMANAGER->stop(CH_BGM);
		//_worldMapPlayer->setWorldMapPlayerTempPoint(_worldMapPlayer->getWorldMapPlayerPoint());
		_worldMapPlayer->setWorldMapPlayerPoint(PointMake(_worldMapPlayer->getWorldMapPlayerPoint().x - 100, _worldMapPlayer->getWorldMapPlayerPoint().y));

		_curPlayerPos = _worldMapPlayer->getWorldMapPlayerPoint();
		_curCameraPos = CAMERAMANAGER->getMovePt();
	}
	_worldMapPlayer->setIsEnter(false);

}

void worldMapScene::setPlayerPos(void)
{
	_worldMapPlayer->setWorldMapPlayerPoint(_curPlayerPos);
	CAMERAMANAGER->setMovePt(_curCameraPos);
}
