#include "stdafx.h"
#include "worldMapScene.h"
#include "itemManager.h"
#include "optionMenu.h"

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

	_openBox = IMAGEMANAGER->addImage("���¹ڽ�", ".//image//enemyImg//treasureBoxOpen.bmp", 31, 29, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("messageBox", ".//image//userInterface//messageBox.bmp", 697, 206, true, RGB(255, 0, 255));

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
	_isOpenBox = false;
	_isNotEnemyVector = false;
	_isGetGongChi = false;
	_enemyNum = -1;

	_focus = FOCUS_PLAYER;


	//���ʹ� �����ŭ ��� �÷��� �ž��ش�.
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

	if (_focus == FOCUS_PLAYER)
	{
		_worldMap->update();
		_worldMapPlayer->update();
		//_npcManager->update();
		_wMEM->update();

		//Z������
		//�÷��̾� ���� ��ǥ�� �޾Ƽ� ��� npc�Ŵ��������� �־��ش�.
		//_npcManager->setPlayerPos(_worldMapPlayer->getWorldMapPlayerPoint());


		if (_isEscape)
		{
			if (_isNotEnemyVector)
			{
				_worldMapPlayer->successEscape();
				_enemyNum = -1;
				_isEscape = false;
			}
			else successEscape();
		}
		else
		{
			for (int i = 0; i < _wMEM->getVWME().size(); ++i)
			{
				//���࿡ ���ʹ̶� �ε��ƴµ� arry�ѹ� i�� �ӽ������ enemyNum�� ����, �������ڰ� �ƴѰ�쿡�� 
				if (i == _enemyNum && !_wMEM->getVWME()[i]->getIsBox())
				{
					//���Ϳ��� ���ʹ̸� ���������.
					_wMEM->worldEmenyDelete(i);
					_enemyNum = -1;
				}
			}
		}

		enterTownMap();
		getCollision();
		battleEncount();
		savePoint();
	}
	else if (_focus == FOCUS_MESSAGEBOX)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			_focus = FOCUS_PLAYER;
		}
	}


	

}

void worldMapScene::render()
{
	_worldMap->render(CAMERAMANAGER->getCameraDC());

	_wMEM->beforeRender(CAMERAMANAGER->getCameraDC(), CAMERAMANAGER->getMovePt());
	//������Ʈ���� ���� �÷��̾��� �ǽð� ��ǥ�� NPC�� ���Ͽ� 
	//�÷��̾�� ���� �׷��ִ� �̹��� -> �÷��̾� �̹��� -> �÷��̾�� ������ �׷��ִ� �̹��� ������ ������ �Ѵ�.
	//_npcManager->beforeRender(CAMERAMANAGER->getCameraDC(), CAMERAMANAGER->getMovePt());
	
	//_npcManager->afterRender(CAMERAMANAGER->getCameraDC(), CAMERAMANAGER->getMovePt());
	/*if (_isOpenBox)
	{
		IMAGEMANAGER->findImage("���¹ڽ�")->render(CAMERAMANAGER->getCameraDC(), CAMERAMANAGER->getMovePt().x- tempPoint.x, CAMERAMANAGER->getMovePt().y-tempPoint.y);
	}*/
	_worldMapPlayer->render(CAMERAMANAGER->getCameraDC(), CAMERAMANAGER->getMovePt());
	_wMEM->afterRender(CAMERAMANAGER->getCameraDC(), CAMERAMANAGER->getMovePt());

	

	CAMERAMANAGER->render(getMemDC());

	if (_focus == FOCUS_MESSAGEBOX)
	{
		IMAGEMANAGER->render("messageBox", getMemDC(), 100, 100);
	}

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
			//50%Ȯ���� �����Ǿ��� �������ڸ�
			if (_wMEM->getVWME()[i]->getIsBox())
			{
				if (((worldMapTreasureBox*)_wMEM->getVWME()[i])->getIsOpen()) break;
				
				//�浹�� �༮�� �ε����� ������ �����Ѵ�.
				_enemyNum = i;
				tempPoint = _wMEM->getVWME()[i]->getWorldMapEnemyPoint();
				getGongChi();
				_focus = FOCUS_MESSAGEBOX;
				//_wMEM->getVWME()[i]->setIsCollision(false);
				//���� ���� �̹��� ���� 
				//���� ������ ȹ�� �̹��� ���� 
				//���ڸ� ���Ϳ��� �����ְ�. <- ���Ϳ��� �����ִ°� ������ �ƴϸ� �׳� ���� �̹��� �״�� �ִ°� �������� �����غ�����.
				//_isOpenBox = true;
				//_wMEM->worldEmenyDelete(i);
				break;
			}
			else
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
	if (_worldMapPlayer->getIsEnter())
	{
		_curCameraPos = CAMERAMANAGER->getMovePt();

		SOUNDMANAGER->releaseAllSound();
		SCENEMANAGER->changeSceneType1("Ÿ��ʾ�");
		INIDATA->addData("gameData", "stage", "TOWN");
		INIDATA->iniSave("skgFile");
		//SOUNDMANAGER->stop(CH_BGM);
		//_worldMapPlayer->setWorldMapPlayerTempPoint(_worldMapPlayer->getWorldMapPlayerPoint());
		_worldMapPlayer->setWorldMapPlayerPoint(PointMake(_worldMapPlayer->getWorldMapPlayerPoint().x - 100, _worldMapPlayer->getWorldMapPlayerPoint().y));

		_curPlayerPos = _worldMapPlayer->getWorldMapPlayerPoint();
	}
	_worldMapPlayer->setIsEnter(false);

}

void worldMapScene::setPlayerPos(void)
{
	_worldMapPlayer->setWorldMapPlayerPoint(_curPlayerPos);
	_worldMap->setCamera();
	CAMERAMANAGER->setMovePt(_curCameraPos);
}

void worldMapScene::getGongChi()
{
	//�� �Լ��� �������ڸ� �������� �κ��丮�� ��ġ �������� �߰����ִ� �Լ�.
	if (!_isGetGongChi)
	{
		_im->changeWeaponNumber("KKongChi", 1);
	}
	_isGetGongChi = true;
}

void worldMapScene::battleEncount()
{
	if (_worldMapPlayer->getIsEncount())
	{
		_isNotEnemyVector = true;
		if (!_isEncounter)
		{
			_isEncounter = true;
			SOUNDMANAGER->play("encounterSound", CH_ENCOUNTER, 1.0f);
		}
		SCENEMANAGER->changeSceneType1("��Ʋ��");
	}
	_worldMapPlayer->setIsEncount(false);
}

void worldMapScene::savePoint()
{
	if (_worldMapPlayer->getIsSavePoint())
	{
		_optionMenu->setIsSavePoint(true);
		_worldMapPlayer->setIsSavePoint(false);
	}
	
}
